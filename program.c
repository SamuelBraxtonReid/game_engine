#include "program.h"

GLuint create_shader(const char *shaderSource, GLenum shaderType)
{
  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &shaderSource, NULL);
  glCompileShader(shader);
  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    printf("shader failed to compile\n");
    char infoLog[256];
    glGetShaderInfoLog(shader, 256, NULL, infoLog);
    printf("%s\n",infoLog);
    exit(1);
  }
  return shader;
}

GLuint create_program(const char **shaders)
{
  // create shader program
  GLuint shaderProgram = glCreateProgram();

  // create shaders
  GLuint vertexShader = create_shader(shaders[0], GL_VERTEX_SHADER);
  GLuint geometryShader;
  if (shaders[1][0])
    geometryShader = create_shader(shaders[1], GL_GEOMETRY_SHADER);
  GLuint fragmentShader = create_shader(shaders[2], GL_FRAGMENT_SHADER);

  // attach shaders only after creating program and shaders
  glAttachShader(shaderProgram, vertexShader);
  if (shaders[1][0])
    glAttachShader(shaderProgram, geometryShader);
  glAttachShader(shaderProgram, fragmentShader);
  
  // link program only after attaching shaders
  glLinkProgram(shaderProgram);
  
  // detach shaders only after linking the program
  glDetachShader(shaderProgram, vertexShader);
  if (shaders[1][0])
    glDetachShader(shaderProgram, geometryShader);
  glDetachShader(shaderProgram, fragmentShader);
  
  // delete shaders only after detaching shaders
  glDeleteShader(vertexShader);
  if (shaders[1][0])
    glDeleteShader(geometryShader);
  glDeleteShader(fragmentShader);
  
  GLint success;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    printf("failed to link program\n");
    char infoLog[256];
    glGetShaderInfoLog(shaderProgram, 256, NULL, infoLog);
    printf("%s\n", infoLog);
    exit(1);
  }
  
  return shaderProgram;
}
