#include "matrix.h"

static struct ll_node* head;

float *new_mat4()
{
  float *m = calloc(16, sizeof(*m));
  m[0x0] = 1.0f;
  m[0x5] = 1.0f;
  m[0xA] = 1.0f;
  m[0xF] = 1.0f;
  struct ll_node *node = malloc(sizeof(*node)); 
  node->matrix = m;
  node->next = head;
  head = node;
  return m;
}

void set_mat4(float *m)
{
  memset(m, 0, 16 * sizeof(*m));
  m[0x0] = 1.0f;
  m[0x5] = 1.0f;
  m[0xA] = 1.0f;
  m[0xF] = 1.0f;
}

float *new_projection_mat4(float angle, float aspect, float near, float far)
{
  float *m = calloc(16, sizeof(*m));
  float tan_half_angle = tan(angle * M_PI / 360.0f);
  m[0x0] = 1.0f/(aspect*tan_half_angle);
  m[0x5] = 1.0f/tan_half_angle;
  m[0xA] = -(far+near)/(far-near);
  m[0xB] = (-2.0f*far*near)/(far-near);
  m[0xE] = -1.0f;
  struct ll_node *node = malloc(sizeof(*node));
  node->matrix = m;
  node->next = head;
  head = node;
  return m;
}

void set_projection_mat4(float *m, float angle, float aspect, float near, float far)
{
  memset(m, 0, 16 * sizeof(*m));
  float tan_half_angle = tan(angle * M_PI / 360.0f);
  m[0x0] = 1.0f/(aspect*tan_half_angle);
  m[0x5] = 1.0f/tan_half_angle;
  m[0xA] = -(far+near)/(far-near);
  m[0xB] = (-2.0f*far*near)/(far-near);
  m[0xE] = -1.0f;
}

void look_at(float *m, float *eye, float *center, float *up)
{
  float f[3] = {center[0] - eye[0], center[1] - eye[1], center[2] - eye[2]};
  float mf = sqrt(f[0] * f[0] + f[1] * f[1] + f[2] * f[2]);
  f[0] /= mf; f[1] /= mf; f[2] /= mf;

  float u[3] = {up[0], up[1], up[2]};
  float mu = sqrt(u[0] * u[0] + u[1] * u[1] + u[2] * u[2]);
  u[0] /= mu; u[1] /= mu; u[2] /= mu;

  float s[3] = {f[1] * u[2] - f[2] * u[1],
                f[2] * u[0] - f[0] * u[2],
                f[0] * u[1] - f[1] * u[0]};
  float ms = sqrt(s[0] * s[0] + s[1] * s[1] + s[2] * s[2]);
  s[0] /= ms; s[1] /= ms; s[2] /= ms;

  u[0] = s[1] * f[2] - s[2] * f[1];
  u[1] = s[2] * f[0] - s[0] * f[2]; 
  u[2] = s[0] * f[1] - s[1] * f[0];
 
  m[0x0] =  s[0];
  m[0x1] =  s[1];
  m[0x2] =  s[2];
  m[0x4] =  u[0];
  m[0x5] =  u[1];
  m[0x6] =  u[2];
  m[0x8] = -f[0];
  m[0x9] = -f[1];
  m[0xA] = -f[2];
  m[0x3] = -(s[0] * eye[0] + s[1] * eye[1] + s[2] * eye[2]);
  m[0x7] = -(u[0] * eye[0] + u[1] * eye[1] + u[2] * eye[2]);
  m[0xB] =  (f[0] * eye[0] + f[1] * eye[1] + f[2] * eye[2]);
  m[0xF] =  1.0f;
  m[0xC] =  0.0f;
  m[0xD] =  0.0f;
  m[0xE] =  0.0f;
}

void normalize_vec3(float *v)
{
  float s = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  v[0] /= s;
  v[1] /= s;
  v[2] /= s;
}

void cross_vec3(float *out, float *in0, float *in1)
{
  float v[3];
  v[0] = in0[1] * in1[2] - in0[2] * in1[1];
  v[1] = in0[2] * in1[0] - in0[0] * in1[2]; 
  v[2] = in0[0] * in1[1] - in0[1] * in1[0];
  out[0] = v[0];
  out[1] = v[0];
  out[2] = v[2];
}

void scale_mat4(float *m, float x, float y, float z)
{
  m[0x0] *= x; m[0x1] *= y; m[0x2] *= z;
  m[0x4] *= x; m[0x5] *= y; m[0x6] *= z;
  m[0x8] *= x; m[0x9] *= y; m[0xA] *= z;
}

void translate_mat4(float *m, float x, float y, float z)
{
  m[0x3] += m[0x0] * x + m[0x1] * y + m[0x2] * z;
  m[0x7] += m[0x4] * x + m[0x5] * y + m[0x6] * z;
  m[0xB] += m[0x8] * x + m[0x9] * y + m[0xA] * z;
} 

void rotate_vec3(float *v, float x, float y, float z)
{
  if (x) rotate_x_vec3(v, x);
  if (y) rotate_y_vec3(v, y);
  if (z) rotate_z_vec3(v, z);
}

void rotate_x_vec3(float *v, float x)
{
  float c = cos(x);
  float s = sin(x);
  float r = c * v[0x2] - s * v[0x1];
  v[0x1] = c * v[0x1] + s * v[0x2];
  v[0x2] = r;
}

void rotate_y_vec3(float *v, float y)
{
  float c = cos(y);
  float s = sin(y);
  float r = c * v[0x2] + s * v[0x0];
  v[0x0] = c * v[0x0] - s * v[0x2];
  v[0x2] = r;
}

void rotate_z_vec3(float *v, float z)
{
  float c = cos(z);
  float s = sin(z);
  float r = c * v[0x1] - s * v[0x0];
  v[0x0] = c * v[0x0] + s * v[0x1];
  v[0x1] = r;
}

void rotate_mat4(float *m, float x, float y, float z)
{
  if (x) rotate_x_mat4(m, x);
  if (y) rotate_y_mat4(m, y);
  if (z) rotate_z_mat4(m, z);
}

void rotate_x_mat4(float *m, float x)
{
  float c = cos(x);
  float s = sin(x);
  float r = c * m[0x2] - s * m[0x1];
  m[0x1] = c * m[0x1] + s * m[0x2];
  m[0x2] = r;
  r = c * m[0x6] - s * m[0x5];
  m[0x5] = c * m[0x5] + s * m[0x6];
  m[0x6] = r;
  r = c * m[0xA] - s * m[0x9];
  m[0x9] = c * m[0x9] + s * m[0xA];
  m[0xA] = r;
}

void rotate_y_mat4(float *m, float y)
{
  float c = cos(y);
  float s = sin(y);
  float r = c * m[0x2] + s * m[0x0];
  m[0x0] = c * m[0x0] - s * m[0x2];
  m[0x2] = r;
  r = c * m[0x6] + s * m[0x4];
  m[0x4] = c * m[0x4] - s * m[0x6];
  m[0x6] = r;
  r = c * m[0xA] + s * m[0x8];
  m[0x8] = c * m[0x8] - s * m[0xA];
  m[0xA] = r;
}

void rotate_z_mat4(float *m, float z)
{
  float c = cos(z);
  float s = sin(z);
  float r = c * m[0x1] - s * m[0x0];
  m[0x0] = c * m[0x0] + s * m[0x1];
  m[0x1] = r;
  r = c * m[0x5] - s * m[0x4]; 
  m[0x4] = c * m[0x4] + s * m[0x5];
  m[0x5] = r;
  r = c * m[0x9] - s * m[0x8]; 
  m[0x8] = c * m[0x8] + s * m[0x9];
  m[0x9] = r;
}

void multiply_mat4(float *a, float *b)
{
  float m[3];
  m[0x0] = a[0x0] * b[0x0] + a[0x1] * b[0x4] + a[0x2] * b[0x8] + a[0x3] * b[0xC]; 
  m[0x1] = a[0x0] * b[0x1] + a[0x1] * b[0x5] + a[0x2] * b[0x9] + a[0x3] * b[0xD]; 
  m[0x2] = a[0x0] * b[0x2] + a[0x1] * b[0x6] + a[0x2] * b[0xA] + a[0x3] * b[0xE]; 
  a[0x3] = a[0x0] * b[0x3] + a[0x1] * b[0x7] + a[0x2] * b[0xB] + a[0x3] * b[0xF]; 
  a[0x0] = m[0x0]; 
  a[0x1] = m[0x1]; 
  a[0x2] = m[0x2];
  m[0x0] = a[0x4] * b[0x0] + a[0x5] * b[0x4] + a[0x6] * b[0x8] + a[0x7] * b[0xC]; 
  m[0x1] = a[0x4] * b[0x1] + a[0x5] * b[0x5] + a[0x6] * b[0x9] + a[0x7] * b[0xD]; 
  m[0x2] = a[0x4] * b[0x2] + a[0x5] * b[0x6] + a[0x6] * b[0xA] + a[0x7] * b[0xE]; 
  a[0x7] = a[0x4] * b[0x3] + a[0x5] * b[0x7] + a[0x6] * b[0xB] + a[0x7] * b[0xF]; 
  a[0x4] = m[0x0]; 
  a[0x5] = m[0x1]; 
  a[0x6] = m[0x2];
  m[0x0] = a[0x8] * b[0x0] + a[0x9] * b[0x4] + a[0xA] * b[0x8] + a[0xB] * b[0xC]; 
  m[0x1] = a[0x8] * b[0x1] + a[0x9] * b[0x5] + a[0xA] * b[0x9] + a[0xB] * b[0xD]; 
  m[0x2] = a[0x8] * b[0x2] + a[0x9] * b[0x6] + a[0xA] * b[0xA] + a[0xB] * b[0xE]; 
  a[0xB] = a[0x8] * b[0x3] + a[0x9] * b[0x7] + a[0xA] * b[0xB] + a[0xB] * b[0xF]; 
  a[0x8] = m[0x0]; 
  a[0x9] = m[0x1];  
  a[0xA] = m[0x2];
  m[0x0] = a[0xC] * b[0x0] + a[0xD] * b[0x4] + a[0xE] * b[0x8] + a[0xF] * b[0xC]; 
  m[0x1] = a[0xC] * b[0x1] + a[0xD] * b[0x5] + a[0xE] * b[0x9] + a[0xF] * b[0xD]; 
  m[0x2] = a[0xC] * b[0x2] + a[0xD] * b[0x6] + a[0xE] * b[0xA] + a[0xF] * b[0xE]; 
  a[0xF] = a[0xC] * b[0x3] + a[0xD] * b[0x7] + a[0xE] * b[0xB] + a[0xF] * b[0xF]; 
  a[0xC] = m[0x0];  
  a[0xD] = m[0x1];  
  a[0xE] = m[0x2];
} 

void free_matrices()
{
  while (head) {
    printf("free\n");
    struct ll_node* node = head;
    head = head->next;
    free(node->matrix);
    free(node);
  }
}

void print_mat4(float *m)
{
  printf("[%.2f, %.2f, %.2f, %.2f]\n", m[0x0], m[0x1], m[0x2], m[0x3]);
  printf("[%.2f, %.2f, %.2f, %.2f]\n", m[0x4], m[0x5], m[0x6], m[0x7]);
  printf("[%.2f, %.2f, %.2f, %.2f]\n", m[0x8], m[0x9], m[0xA], m[0xB]);
  printf("[%.2f, %.2f, %.2f, %.2f]\n", m[0xC], m[0xD], m[0xE], m[0xF]);
}
