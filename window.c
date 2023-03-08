#include "window.h"

void clear_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  glClearColor(((float)r)/255.0f, ((float)g)/255.0f, ((float)b)/255.0f, ((float)a)/255.0f);
}

void framebuffer_size_callback(GLFWwindow *window, int32_t width, int32_t height)
{
  glViewport(0, 0, width, height);
}

GLFWwindow* initialize_window(int32_t width, int32_t height, char *title)
{
  glfwInit();
  
  // set OpenGL version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
 
  // use only core functionality
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
  // disallow depricated functionality
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
 
  GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window) {
    printf("failed to create window\n");
    glfwTerminate();
    exit(1);
  }
  glfwMakeContextCurrent(window);
  //glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);

  // disable vsync
  glfwSwapInterval(0);
 
  return window;
}

float aspect_ratio(GLFWwindow *window)
{
  int32_t width, height;
  glfwGetWindowSize(window, &width, &height);
  return (double) width / (double) height;
}
