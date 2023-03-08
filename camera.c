#include "camera.h"

static GLFWwindow *window;
static float ar;
static float fovy = 45.0f;
static float near = 0.01f;
static float far = 2048.0f;
static float projection[16];
static GLuint projection_uniform;
static float p[3] = {0.0f, 0.0f, 0.0f};
static float r[3] = {1.0f, 0.0f, 0.0f};
static float u[3] = {0.0f, 1.0f, 0.0f};
static float f[3] = {0.0f, 0.0f, 1.0f};
static float view[16];
static GLuint view_uniform;
static float r_speed = 0.03f;
static float t_speed = 0.1f;

int32_t pressed(int32_t key)
{
  return (glfwGetKey(window, key) == GLFW_PRESS);
}

void initialize_camera(GLFWwindow *window_i, GLuint program)
{
  window = window_i;
  ar = aspect_ratio(window);
  set_projection_mat4(projection, fovy, ar, near, far);
  projection_uniform = glGetUniformLocation(program, "projection");
  glUniformMatrix4fv(projection_uniform, 1, GL_TRUE, projection);

  set_mat4(view);
  view_uniform = glGetUniformLocation(program, "view");
  float t[3] = {p[0] + f[0], p[1] + f[1], p[2] + f[2]};
  look_at(view, p, t, u);
  glUniformMatrix4fv(view_uniform, 1, GL_TRUE, view);
}

void update_camera()
{
  if (ar != aspect_ratio(window)) {
    ar = aspect_ratio(window);
    set_projection_mat4(projection, fovy, ar, near, far);
    glUniformMatrix4fv(projection_uniform, 1, GL_TRUE, projection);
  }
  int32_t xr = pressed(GLFW_KEY_UP) - pressed(GLFW_KEY_DOWN);
  int32_t yr = pressed(GLFW_KEY_RIGHT) - pressed(GLFW_KEY_LEFT);
  //float rv[] = {xr, yr, 0.0f};
  if (xr && yr) {
    r_speed *= M_SQRT1_2;
    //rv[0] = M_SQRT1_2 * xr;
    //rv[1] = M_SQRT1_2 * yr;
  }
  int32_t xt = pressed(GLFW_KEY_A) - pressed(GLFW_KEY_D);
  int32_t yt = pressed(GLFW_KEY_SPACE) - (pressed(GLFW_KEY_RIGHT_SHIFT) || pressed(GLFW_KEY_LEFT_SHIFT));
  int32_t zt = pressed(GLFW_KEY_W) - pressed(GLFW_KEY_S);
  if (xr) {
    float c = cos(r_speed * xr);
    float s = sin(r_speed * xr);
    float t[3] = {c * f[0] + s * u[0], c * f[1] + s * u[1], c * f[2] + s * u[2]};
    u[0] = c * u[0] - s * f[0];
    u[1] = c * u[1] - s * f[1];
    u[2] = c * u[2] - s * f[2];
    f[0] = t[0];
    f[1] = t[1];
    f[2] = t[2];
  }
  if (yr) {
    float c = cos(r_speed * yr);
    float s = sin(r_speed * yr);
    float t[3] = {c * f[0] - s * r[0], c * f[1] - s * r[1], c * f[2] - s * r[2]};
    r[0] = c * r[0] + s * f[0];
    r[1] = c * r[1] + s * f[1];
    r[2] = c * r[2] + s * f[2];
    f[0] = t[0];
    f[1] = t[1];
    f[2] = t[2];
  }
  if (xr || yr) {
    float mf = sqrt(f[0] * f[0] + f[1] * f[1] + f[2] * f[2]);
    f[0] /= mf; f[1] /= mf; f[2] /= mf;
    r[0] = u[1] * f[2] - u[2] * f[1];
    r[1] = u[2] * f[0] - u[0] * f[2];
    r[2] = u[0] * f[1] - u[1] * f[0];
    float mr = sqrt(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]);
    r[0] /= mr; r[1] /= mr; r[2] /= mr;
    u[0] = f[1] * r[2] - f[2] * r[1];
    u[1] = f[2] * r[0] - f[0] * r[2];
    u[2] = f[0] * r[1] - f[1] * r[0];
    float mu = sqrt(u[0] * u[0] + u[1] * u[1] + u[2] * u[2]);
    u[0] /= mu; u[1] /= mu; u[2] /= mu;
  }
  if (xt) {
    p[0] += r[0] * t_speed * xt;
    p[1] += r[1] * t_speed * xt;
    p[2] += r[2] * t_speed * xt;
  }
  if (yt) {
    p[0] += u[0] * t_speed * yt;
    p[1] += u[1] * t_speed * yt;
    p[2] += u[2] * t_speed * yt;
  }
  if (zt) {
    p[0] += f[0] * t_speed * zt;
    p[1] += f[1] * t_speed * zt;
    p[2] += f[2] * t_speed * zt;
  }
  if (xr || yr || xt || yt || zt) {
    /*
    printf("m(f): %.36f\n", sqrt(f[0] * f[0] + f[1] * f[1] + f[2] * f[2]));
    printf("m(r): %.36f\n", sqrt(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]));
    printf("m(u): %.36f\n", sqrt(u[0] * u[0] + u[1] * u[1] + u[2] * u[2]));
    float v[3];
    v[0] = f[1] * r[2] - f[2] * r[1];
    v[1] = f[2] * r[0] - f[0] * r[2];
    v[2] = f[0] * r[1] - f[1] * r[0];
    printf("m(f x r): %.32f\n", sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
    v[0] = f[1] * u[2] - f[2] * u[1];
    v[1] = f[2] * u[0] - f[0] * u[2];
    v[2] = f[0] * u[1] - f[1] * u[0];
    printf("m(f x u): %.32f\n", sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
    v[0] = r[1] * u[2] - r[2] * u[1];
    v[1] = r[2] * u[0] - r[0] * u[2];
    v[2] = r[0] * u[1] - r[1] * u[0];
    printf("m(r x u): %.32f\n", sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
    printf("%f\n", glfwGetTime());
    printf("\n");
    */
    float t[3] = {p[0] + f[0], p[1] + f[1], p[2] + f[2]};
    look_at(view, p, t, u);
    glUniformMatrix4fv(view_uniform, 1, GL_TRUE, view);
  }
  if (xr && yr) {
    r_speed *= M_SQRT2;
  }
}
