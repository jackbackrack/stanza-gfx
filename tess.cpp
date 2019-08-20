#ifdef MACOSX
// #include "/System/Library/Frameworks/OpenGL.framework/Headers/glu.h"
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#endif
#include <vector>
#include "tess.hpp"

int tess_mesh_delete(tess_mesh* m) {
  delete [] m->verts;
  delete [] m->tris;
  delete m;
  return 0;
}

typedef struct tess_mesh_data {
  std::vector<int> indices;
  std::vector<tess_vec3> vertices;
} tess_mesh_data;

static tess_mesh_data mesh;

int vertex_callback (int index, int mesh_index) {
  mesh.indices.push_back(index);
  return 0;
}

static int begin_callback (int index, int mesh_index) {
  return 0;
}

static int edge_flag_callback (int index, int mesh_index) {
  return 0;
}

static int end_callback (int mesh_index) {
  return 0;
}

static int error_callback (int errno, int mesh_index) {
  return 0;
}

static int combine_callback (double* coords, int* vertex_data, float* weight, int* out_data, int mesh_index) {
  tess_vec3 vec = { (float)coords[0], (float)coords[1], (float)coords[2] };
  mesh.vertices.push_back(vec);
  return mesh.vertices.size() - 1;
}

tess_mesh* tess_triangulate (float* poly) {
  auto tess = gluNewTess();
  gluTessCallback(tess, GLU_TESS_BEGIN,   (void (*)())(&begin_callback));
  gluTessCallback(tess, GLU_TESS_END,     (void (*)())(&end_callback));
  gluTessCallback(tess, GLU_TESS_VERTEX,  (void (*)())(&vertex_callback));
  gluTessCallback(tess, GLU_TESS_COMBINE, (void (*)())(&combine_callback));
  gluTessCallback(tess, GLU_TESS_ERROR,   (void (*)())(&error_callback));
  mesh.vertices.clear();
  mesh.indices.clear();
  gluTessBeginPolygon(tess, 0);
  int poly_count = (int)(*poly++);
  for (int i = 0; i < poly_count; i++) {
    int contour_count = (int)(*poly++);
    gluTessBeginContour(tess);
    for (int j = 0; j < contour_count; j++) {
      tess_vec3 pt = { (*poly++), (*poly++), 0.0 };
      mesh.vertices.push_back(pt);
      tess_vec3d pt3 = { (double)pt.x, (double)pt.y, (double)pt.z };
      gluTessVertex(tess, (double*)(&pt3.x), (void*)(mesh.vertices.size() - 1));
    }
    gluTessEndContour(tess);
  }
  gluTessEndPolygon(tess);
  gluDeleteTess(tess);
  auto out = new tess_mesh;
  out->verts = new tess_vec3[mesh.vertices.size()];
  out->vert_count = mesh.vertices.size();
  out->tris = new tess_tri[mesh.indices.size() / 3];
  out->tri_count = mesh.indices.size() / 3;
  int i;
  i=0;
  for (auto& v : mesh.vertices) {
    out->verts[i++] = {v.x, v.y, v.z};
  }
  i=0;
  for (int j = 0; j < mesh.indices.size(); j = j + 3) {
    out->tris[i++] = {(uint32_t)mesh.indices[j + 0], (uint32_t)mesh.indices[j + 1], (uint32_t)mesh.indices[j + 2]};
  }

  return out;
  
}

