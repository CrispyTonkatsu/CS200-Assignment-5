/**
 * File: SolidRender.cpp
 * Name: Edgar Jose Donoso Mansilla (e.donosomansilla)
 * Assignment: 3
 * Course: CS200
 * Term: FALL24
 */

#include "Texture.h"
#include "Affine.h"

cs200::Bitmap::Bitmap(unsigned W, unsigned H) :
    bmp_width(W), bmp_height(H), bmp_stride(computeStride(W)) {}

cs200::Bitmap::Bitmap(const char *bmp_file) {}

unsigned cs200::Bitmap::offset(int i, int j) const {}

unsigned cs200::computeStride(unsigned W) {
  return (W * 3) + (4 - ((W * 3) % 4));
}

void cs200::reverseRGB(Bitmap &b) {}

glm::mat4 cs200::bitmapToTextureTransform(const Bitmap &b) {
  return scale(1 / b.width(), 1 / b.height()) * // NOLINT *magic*
         translate(vector(0.5f, 0.5f)); // NOLINT *magic*
}

glm::mat4 cs200::textureToBitmapTransform(const Bitmap &b) {
  return translate(vector(-0.5f, -0.5f)) * // NOLINT *magic*
         scale(b.width(), b.height()); // NOLINT *magic*
}

glm::vec3 cs200::getColor(const Bitmap &b, float u, float v) {}
