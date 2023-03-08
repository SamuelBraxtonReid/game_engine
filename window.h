#ifndef window_h
#define window_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <glad/glad.h>

#include "GLFW/glfw3.h"

void clear_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

void framebuffer_size_callback(GLFWwindow *window, int32_t width, int32_t height);

GLFWwindow* initialize_window(int32_t width, int32_t height, char *title);

float aspect_ratio(GLFWwindow *window);

#endif
