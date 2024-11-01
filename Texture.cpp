/**
 * File: Texture.cpp
 * Name: Edgar Jose Donoso Mansilla (e.donosomansilla)
 * Assignment: 5
 * Course: CS200
 * Term: FALL24
 */

#include "Texture.h"
#include <fstream>
#include <memory>
#include <stdexcept>
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

cs200::Bitmap::Bitmap(const char *bmp_file) {
  std::fstream in(bmp_file, std::ios_base::binary | std::ios_base::in);

  if (!in.is_open()) {
    throw std::runtime_error("[Bitmap] Attempted to construct Bitmap from a "
                             "file which doesn't exist");
  }

  char header[54]; // NOLINT *magic*
  in.read(header, 54);

  unsigned char ft_1 = *reinterpret_cast<unsigned char *>(header);
  unsigned char ft_2 = *reinterpret_cast<unsigned char *>(header + 1);
  if (ft_1 != 'B' || ft_2 != 'M') {
    throw std::runtime_error("[Bitmap] Attempted to construct Bitmap from a "
                             "file which is not a Bitmap file");
  }

  unsigned short bit_planes = *reinterpret_cast<unsigned short *>(header + 26);
  unsigned short bits_per_pixel =
      *reinterpret_cast<unsigned short *>(header + 28);
  unsigned int compression = *reinterpret_cast<unsigned int *>(header + 30);
  if (bit_planes != 1 || bits_per_pixel != 24 || compression != 0) {
    throw std::runtime_error("[Bitmap] Attempted to construct a Bitmap from a "
                             "bitmap not supported by the program");
  }

  unsigned data_size = *reinterpret_cast<unsigned *>(header + 34);
  unsigned data_offset = *reinterpret_cast<unsigned *>(header + 10);

  int width = *reinterpret_cast<int *>(header + 18);
  int height = *reinterpret_cast<int *>(header + 22);
  height = std::abs(height);

  bmp_width = width;
  bmp_height = height;
  bmp_stride = computeStride(width);

  if (data_size == 0) {
    data_size = height * bmp_stride;
  }

  std::unique_ptr<unsigned char[]> data{new unsigned char[data_size]};
  in.seekg(data_offset, std::ios_base::beg);
  in.read(reinterpret_cast<char *>(data.get()), data_size);

  for (size_t j = 0; j < bmp_height; j++) {
    for (size_t i = 0; i < bmp_width + 1; i++) {

      unsigned index = offset(i, j);

      bmp_data.push_back(data[index + 0]);
      bmp_data.push_back(data[index + 1]);
      bmp_data.push_back(data[index + 2]);
    }
  }
}

unsigned cs200::Bitmap::offset(int i, int j) const {
  if (i < 0 || j < 0 || i > static_cast<int>(bmp_width) ||
      j > static_cast<int>(bmp_height)) {
    throw std::out_of_range(
        "[Bitmap] Tried to access out of range in function offset.");
  }
  return ((bmp_stride * j) + (3 * i));
}

unsigned cs200::computeStride(unsigned W) {
  unsigned output = W * 3;
  unsigned remainder = output % 4;
  if (remainder != 0) {
    output += (4 - remainder);
  }
  return output;
}

void cs200::reverseRGB(Bitmap &b) {
  for (size_t j = 0; j < b.height(); j++) {
    for (size_t i = 0; i < b.width(); i++) {

      int index = (j * b.stride()) + (i * 3);

      std::swap(b.data()[index + 0], b.data()[index + 2]);
    }
  }
}

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

glm::vec3 cs200::getColor(const Bitmap &b, float u, float v) {
  float wrapped_u = textureWrap(u);
  float wrapped_v = textureWrap(v);

  glm::vec4 bitmap_coordinates = {
      wrapped_u * static_cast<float>(b.width()),
      wrapped_v * static_cast<float>(b.height()),
      0,
      1};
  bitmap_coordinates = glm::floor(bitmap_coordinates);

  unsigned offset = b.offset(
      static_cast<int>(bitmap_coordinates.x),
      static_cast<int>(bitmap_coordinates.y));

  return {b.data()[offset], b.data()[offset + 1], b.data()[offset + 2]};
}
