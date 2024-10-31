/**
 * File: SolidRender.cpp
 * Name: Edgar Jose Donoso Mansilla (e.donosomansilla)
 * Assignment: 3
 * Course: CS200
 * Term: FALL24
 */

#include "Texture.h"
#include <cmath>
#include "Affine.h"

struct Color {
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

Color calculateColor(glm::mat4 &transform, size_t x, size_t y) {
  glm::vec4 texture_coordinates =
      transform * cs200::vector(static_cast<float>(x), static_cast<float>(y));

  float sum = (texture_coordinates.x - 0.5f) * (texture_coordinates.x - 0.5f) +
              (texture_coordinates.y - 0.5f) * (texture_coordinates.y - 0.5f);

  unsigned char r = 100 + (155 * texture_coordinates.x);
  unsigned char b = 100 + (155 * texture_coordinates.y);

  if (sum > 0.16f) {
    return {r, 0, b};
  }

  if (sum < 0.09f) {
    return {b, 0, r};
  }

  return {0, 255, 0};
}

cs200::Bitmap::Bitmap(unsigned W, unsigned H) :
    bmp_width(W), bmp_height(H), bmp_stride(computeStride(W)) {

  glm::mat4 bitmap_to_texture = cs200::bitmapToTextureTransform(*this);

  for (size_t j = 0; j < bmp_height; j++) {
    for (size_t i = 0; i < bmp_width; i++) {
      Color rgb = calculateColor(bitmap_to_texture, i, j);

      bmp_data.push_back(rgb.r);
      bmp_data.push_back(rgb.g);
      bmp_data.push_back(rgb.b);
    }
  }
}

cs200::Bitmap::Bitmap(const char *) {}

unsigned cs200::Bitmap::offset(int i, int j) const {
  // TODO: Throw exception
  return (bmp_stride * j + 3 * i);
}

unsigned cs200::computeStride(unsigned W) {
  return (W * 3) + (3 - ((W * 3) % 4));
}

void cs200::reverseRGB(Bitmap &) {}

glm::mat4 cs200::bitmapToTextureTransform(const Bitmap &b) {
  return scale(
             1.f / static_cast<float>(b.width()),
             1.f / static_cast<float>(b.height())) *
         translate(vector(0.5f, 0.5f)); // NOLINT *magic*
}

glm::mat4 cs200::textureToBitmapTransform(const Bitmap &b) {
  return translate(vector(-0.5f, -0.5f)) * // NOLINT *magic*
         scale(static_cast<float>(b.width()), static_cast<float>(b.height()));
}

float textureWrap(float x) {
  float fraction = std::fmod(x, 1.f);
  fraction = std::fmod(1.f + fraction, 1.f);

  return fraction;
}

// BUG: The continuity is fucked
glm::vec3 cs200::getColor(const Bitmap &b, float u, float v) {
  // TODO: Add exception throw

  float wrapped_u = textureWrap(u);
  float wrapped_v = textureWrap(v);

  glm::vec4 bitmap_coordinates =
      textureToBitmapTransform(b) * point(wrapped_u, wrapped_v);

  // TODO: add rounding
  unsigned offset = b.offset(
      std::round(bitmap_coordinates.x), std::round(bitmap_coordinates.y));

  return {b.data()[offset], b.data()[offset + 1], b.data()[offset + 2]};
}
