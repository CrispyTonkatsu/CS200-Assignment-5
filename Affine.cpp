/**
 * File: Affine.cpp
 * Name: Edgar Jose Donoso Mansilla (e.donosomansilla)
 * Assignment: 1
 * Course: CS200
 * Term: FALL24
 */

#include "Affine.h"

namespace cs200 {

  bool isPoint(const glm::vec4 &P) { return near(P.w, 1); }

  bool isVector(const glm::vec4 &v) { return near(v.w, 0); }

  bool isAffine(const glm::mat4 &A) {
    for (int i = 0; i < 4; i++) {
      if (i == 2) {
        if (!near(A[i][2], 1)) {
          return false;
        }
        if (!near(A[2][i], 1)) {
          return false;
        }
      } else {
        if (!near(A[i][2], 0)) {
          return false;
        }
        if (!near(A[2][i], 0)) {
          return false;
        }
      }

      if (i == 3) {
        if (!near(A[i][3], 1)) {
          return false;
        }
      } else {
        if (!near(A[i][3], 0)) {
          return false;
        }
      }
    }

    return !near(A[3][0], 0) && !near(A[3][1], 0);
  }

  glm::vec4 point(float x, float y) { return glm::vec4{x, y, 0, 1}; }

  glm::vec4 vector(float x, float y) { return glm::vec4{x, y, 0, 0}; }

  glm::mat4 affine(const glm::vec4 &u, const glm::vec4 &v, const glm::vec4 &C) {
    return {{u.x, u.y, 0, 0}, {v.x, v.y, 0, 0}, {0, 0, 1, 0}, {C.x, C.y, 0, 1}};
  }

  glm::mat4 rotate(float t) {

    float cosine = std::cos(glm::radians(t));
    float sine = std::sin(glm::radians(t));
    return {{cosine, sine, 0, 0}, {-sine, cosine, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
  }

  glm::mat4 translate(const glm::vec4 &v) { return {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {v.x, v.y, 0, 1}}; }

  glm::mat4 scale(float r) { return {{r, 0, 0, 0}, {0, r, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}; }

  glm::mat4 scale(float rx, float ry) { return {{rx, 0, 0, 0}, {0, ry, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}; }

} // namespace cs200
