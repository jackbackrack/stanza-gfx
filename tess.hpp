typedef struct tess_vec2      { float x, y; } tess_vec2;
typedef struct tess_vec3      { float x, y, z; } tess_vec3;
typedef struct tess_vec3d     { double x, y, z; } tess_vec3d;
typedef struct tess_tri       { uint32_t a, b, c; } tess_tri;

typedef struct tess_mesh {
    tess_vec3* verts;
    tess_tri* tris;
    uint32_t tri_count;
    uint32_t vert_count;
} tess_mesh;

typedef struct tess_contour {
    tess_vec2* pts;
    uint32_t count;
} tess_contour;

typedef struct tess_contours {
    tess_contour* cs;
    uint32_t count;
} tess_contours;

extern "C" {
  tess_mesh* tess_triangulate (float* poly);
  int tess_mesh_delete (tess_mesh* m);
};
