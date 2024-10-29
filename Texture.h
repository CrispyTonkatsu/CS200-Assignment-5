// Texture.h
// -- bitmaps and texture coordinates
// cs200 10/20

#ifndef CS200_TEXTURE_H
#define CS200_TEXTURE_H

#include <glm/glm.hpp>
#include <vector>

namespace cs200 {

  class Bitmap {
  public:
    explicit Bitmap(unsigned W = 64, unsigned H = 64); // NOLINT
    Bitmap(const char *bmp_file); // NOLINT
    unsigned char *data() { return &bmp_data[0]; }
    const unsigned char *data() const { return &bmp_data[0]; }
    unsigned width() const { return bmp_width; }
    unsigned height() const { return bmp_height; }
    unsigned stride() const { return bmp_stride; }
    unsigned offset(int i, int j) const;

  private:
    std::vector<unsigned char> bmp_data;
    unsigned bmp_width, bmp_height, bmp_stride;
  };

  unsigned computeStride(unsigned W);
  void reverseRGB(Bitmap &b);
  glm::mat4 bitmapToTextureTransform(const Bitmap &b);
  glm::mat4 textureToBitmapTransform(const Bitmap &b);
  glm::vec3 getColor(const Bitmap &b, float u, float v);
} // namespace cs200

#endif
