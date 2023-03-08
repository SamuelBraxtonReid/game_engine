#ifndef models_h
#define models_h

#include <string.h>
#include <stdio.h>

#include <glad/glad.h>

struct model {
  GLfloat *vertices;
  GLuint size_of_vertices;
  GLuint *elements; 
  GLuint size_of_elements;
};

struct model get_model(char *name);

#endif
