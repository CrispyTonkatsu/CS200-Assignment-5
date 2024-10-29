// SquareMesh.h
// -- standard square mesh
// cs200 1/19

#ifndef CS200_SQUAREMESH_H
#define CS200_SQUAREMESH_H

#include "Affine.h"
#include "Mesh.h"

namespace cs200 {

  class SquareMesh : public Mesh {
  public:
    int vertexCount() const override;
    const glm::vec4 *vertexArray() const override;
    glm::vec4 dimensions() const override;
    glm::vec4 center() const override;
    int faceCount() const override;
    const Face *faceArray() const override;
    int edgeCount() const override;
    const Edge *edgeArray() const override;

  private:
    static const glm::vec4 vertices[4]; // NOLINT *array*
    static const Face faces[2]; // NOLINT *array*
    static const Edge edges[4]; // NOLINT *array*
  };

} // namespace cs200

inline int cs200::SquareMesh::vertexCount() const { return 4; }

inline const glm::vec4 *cs200::SquareMesh::vertexArray() const {
  return vertices; // NOLINT *pointer*
}

inline glm::vec4 cs200::SquareMesh::dimensions() const {
  return cs200::vector(2, 2);
}

inline glm::vec4 cs200::SquareMesh::center() const {
  return cs200::point(0, 0);
}

inline int cs200::SquareMesh::faceCount() const { return 2; }

inline const cs200::Mesh::Face *cs200::SquareMesh::faceArray() const {
  return faces; // NOLINT *pointer*
}

inline int cs200::SquareMesh::edgeCount() const { return 4; }

inline const cs200::Mesh::Edge *cs200::SquareMesh::edgeArray() const {
  return edges; // NOLINT *pointer*
}

#endif
