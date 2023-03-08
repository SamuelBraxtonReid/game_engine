#ifndef matrix_h
#define matrix_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

struct ll_node {
  float *matrix;
  struct ll_node *next;
};

float *new_mat4(void);

void set_mat4(float *m);

float *new_projection_mat4(float angle, float aspect, float near, float far);

void set_projection_mat4(float *m, float angle, float aspect, float near, float far);

void look_at(float *m, float *p, float *t, float *u);

void normalize_vec3(float *v);

void cross_vec3(float *a, float *b, float *c);

void scale_mat4(float *m, float x, float y, float z);

void translate_mat4(float *m, float x, float y, float z);

void rotate_vec3(float *v, float x, float y, float z);

void rotate_x_vec3(float *v, float x);

void rotate_y_vec3(float *v, float y);

void rotate_z_vec3(float *v, float z);

void rotate_mat4(float *m, float x, float y, float z);

void rotate_x_mat4(float *m, float x);

void rotate_y_mat4(float *m, float y);

void rotate_z_mat4(float *m, float z);

void multiply_mat4(float *a, float *b); 

void free_matrices(void);

void print_mat4(float *m);

#endif
