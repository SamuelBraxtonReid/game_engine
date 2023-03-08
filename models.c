#include "models.h"

static GLfloat cube_vertices[] = {
  // +x
   0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
   0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
   0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
   0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
  // -x
  -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
  -0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
  // +y
   0.5f,  0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
   0.5f,  0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
  -0.5f,  0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
  // -y
   0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
   0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
  // +z
   0.5f,  0.5f,  0.5f,  0.0f,  0.0f, -1.0f,
   0.5f, -0.5f,  0.5f,  0.0f,  0.0f, -1.0f,
  -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, -1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, -1.0f,
  // -z
   0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,
   0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,
  -0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,
};

static GLuint cube_elements[] = {
  // +x
  0x00,  0x03,  0x01,
  0x03,  0x00,  0x02, 
  // -x         
  0x05,  0x06,  0x04,
  0x06,  0x05,  0x07,
  // +y         
  0x08,  0x0b,  0x0a,
  0x0b,  0x08,  0x09,            
  // -y         
  0x0d,  0x0e,  0x0f,
  0x0e,  0x0d,  0x0c,
  // +z         
  0x11,  0x10,  0x13,
  0x12,  0x13,  0x10,
  // -z         
  0x17,  0x14,  0x15,
  0x14,  0x17,  0x16,
};

struct model get_model(char *name)
{
  struct model m = {0};
  if (strcmp(name, "cube") == 0) {
    m.vertices = cube_vertices;
    m.size_of_vertices = sizeof(cube_vertices);
    m.elements = cube_elements;
    m.size_of_elements = sizeof(cube_elements);
  }
  return m;
}
