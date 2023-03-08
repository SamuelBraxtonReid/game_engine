#include "main.h"

int main()
{
  GLFWwindow *window = initialize_window(360, 360, "game");

  if (!gladLoadGL()) { 
    printf("Failed to initialize GLAD");
    return 1;
  }

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  struct model cube = get_model("cube");
  
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, cube.size_of_vertices, cube.vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0x0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.size_of_elements, cube.elements, GL_STATIC_DRAW);

  const char **shaders = get_shaders();
  GLuint shaderProgram = create_program(shaders);
  glUseProgram(shaderProgram);

  initialize_camera(window, shaderProgram);

  GLuint TIME_uniform = glGetUniformLocation(shaderProgram, "time");
  double TIME = glfwGetTime();
  glUniform1f(TIME_uniform, TIME);
  double fps = 60.0f;
  struct timespec req = {0};

  clear_color(0x00, 0x00, 0x00, 0xFF);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  srandom((uint64_t)time(NULL));
  const int32_t cubecount = 4096;
  float p[cubecount * 6];
  float i_radius = 64.0f;
  for (int32_t i = 0; i < cubecount; i++) {
    float radius = i_radius;
    p[i * 6] = ((float)random())/((float)RAND_MAX/(radius*2.0f))-radius;
    radius = sqrt(radius * radius - p[i * 6] * p[i * 6]);
    p[i * 6 + 1] = ((float)random())/((float)RAND_MAX/(radius*2.0f))-radius;
    radius = sqrt(radius * radius - p[i * 6 + 1] * p[i * 6 + 1]);
    p[i * 6 + 2] = ((float)random())/((float)RAND_MAX/(radius*2.0f))-radius;
    /* 
    while (p[i*6]*p[i*6] + p[i*6+1]*p[i*6+1] + p[i*6+2]*p[i*6+2] < (i_radius / 2.0f) * (i_radius / 2.0f)) {
      p[i*6] *= 2;
      //p[i*6+1] *= 2;
      p[i*6+2] *= 2;
    }
    */
    p[i * 6] = round(p[i * 6]);
    p[i * 6 + 1] = round(p[i * 6 + 1]);
    p[i * 6 + 2] = round(p[i * 6 + 2]);
    p[i * 6 + 3] = ((float)random())/((float)RAND_MAX/(2.0f*M_PI));
    p[i * 6 + 4] = ((float)random())/((float)RAND_MAX/(2.0f*M_PI));
    p[i * 6 + 5] = ((float)random())/((float)RAND_MAX/(2.0f*M_PI));
  }

  float model_matrix[16];
  set_mat4(model_matrix);
  GLuint model_uniform = glGetUniformLocation(shaderProgram, "model");
  glUniformMatrix4fv(model_uniform, 1, GL_TRUE, model_matrix);
  glfwSwapBuffers(window);

  while (!glfwWindowShouldClose(window)) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int32_t i = 0; i < cubecount; i++) {
      translate_mat4(model_matrix, p[i*6], p[i*6+1], p[i*6+2]);
      glUniformMatrix4fv(model_uniform, 1, GL_TRUE, model_matrix);
      glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
      set_mat4(model_matrix);
    }
    glfwSwapBuffers(window);

    update_camera();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
    glfwPollEvents();

    req.tv_nsec = (int64_t)(((1.0f / fps) - (glfwGetTime() - TIME)) * 1000000000.0f);
    if (req.tv_nsec < 0) {
      printf("frame drop\n");
    }
    nanosleep(&req, NULL);
    TIME = glfwGetTime();
    glUniform1f(TIME_uniform, TIME);

  }

  glDeleteProgram(shaderProgram);
  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &vao);
  glfwTerminate();

  return 0;
}
