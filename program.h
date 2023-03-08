#ifndef program_h
#define program_h

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

GLuint create_shader(const char *shaderSource, GLenum shaderType);

GLuint create_program(const char **shaders);

#endif
