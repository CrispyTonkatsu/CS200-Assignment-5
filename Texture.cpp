/**
 * File: SolidRender.cpp
 * Name: Edgar Jose Donoso Mansilla (e.donosomansilla)
 * Assignment: 3
 * Course: CS200
 * Term: FALL24
 */

#include "Texture.h"
#include <cmath>
#include <iostream>
#include <ostream>
#include <tuple>
#include "Affine.h"

std::tuple<unsigned char, unsigned char, unsigned char>
calculateColor(glm::mat4 &transform, size_t x, size_t y) {
  glm::vec4 texture_coordinates =
      transform * cs200::vector(static_cast<float>(x), static_cast<float>(y));

  float sum = (texture_coordinates.x - 0.5f) * (texture_coordinates.x - 0.5f) +
              (texture_coordinates.y - 0.5f) * (texture_coordinates.y - 0.5f);

  unsigned char r = 100 + (150 * texture_coordinates.x);
  unsigned char b = 100 + (150 * texture_coordinates.y);

  if (sum > 0.16f) {
    return std::make_tuple(r, 0, b);
  }

  if (sum < 0.09f) {
    return std::make_tuple(r, 0, b);
  }

  return std::make_tuple(0, 255, 0);
}

cs200::Bitmap::Bitmap(unsigned W, unsigned H) :
    bmp_width(W), bmp_height(H), bmp_stride(computeStride(W)) {

  glm::mat4 bitmap_to_texture = cs200::bitmapToTextureTransform(*this);

  for (size_t i = 0; i < bmp_height; i++) {
    for (size_t j = 0; j < bmp_width; j++) {
      std::tuple<unsigned char, unsigned char, unsigned char> rgb =
          calculateColor(bitmap_to_texture, j, i);

      bmp_data.push_back(std::get<0>(rgb));
      bmp_data.push_back(std::get<1>(rgb));
      bmp_data.push_back(std::get<2>(rgb));
    }
  }
}

cs200::Bitmap::Bitmap(const char *) {}

unsigned cs200::Bitmap::offset(int i, int j) const {
  // TODO: Throw exception
  return (bmp_stride * j + 3 * i);
}

unsigned cs200::computeStride(unsigned W) {
  return (W * 3) + (4 - ((W * 3) % 4));
}

void cs200::reverseRGB(Bitmap &) {}

glm::mat4 cs200::bitmapToTextureTransform(const Bitmap &b) {
  return scale(1 / b.width(), 1 / b.height()) * // NOLINT *magic*
         translate(vector(0.5f, 0.5f)); // NOLINT *magic*
}

glm::mat4 cs200::textureToBitmapTransform(const Bitmap &b) {
  return translate(vector(-0.5f, -0.5f)) * // NOLINT *magic*
         scale(b.width(), b.height()); // NOLINT *magic*
}

float textureWrap(float x) {
  float fraction = std::modf(x, &x);
  fraction += 1;
  fraction = std::modf(fraction, &x);

  return fraction;
}

glm::vec3 cs200::getColor(const Bitmap &b, float u, float v) {
  // TODO: Add exception throw

  // BUG: There seems to be an issue here with the texture coordinates
  float wrapped_u = textureWrap(u);
  float wrapped_v = textureWrap(v);

  glm::vec4 bitmap_coordinates =
      textureToBitmapTransform(b) * vector(wrapped_u, wrapped_v);

  unsigned offset = b.offset(bitmap_coordinates.x, bitmap_coordinates.y);

  return {b.data()[offset], b.data()[offset + 1], b.data()[offset + 2]};
}
