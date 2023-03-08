#ifndef camera_h
#define camera_h

#include <stdlib.h>

#include <glad/glad.h>

#include "GLFW/glfw3.h"

#include "window.h"
#include "matrix.h"

void initialize_camera(GLFWwindow *window_i, GLuint program);

void key_callback(GLFWwindow *w, int32_t key, int32_t scancode, int32_t action, int32_t mods);

void update_camera(void);

#endif
