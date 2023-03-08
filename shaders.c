static const char *v = 
  "#version 410 core\n"
  "layout (location = 0) in vec3 p;\n"
  "layout (location = 1) in vec3 n;\n"
  "uniform mat4 projection;\n"
  "uniform mat4 view;\n"
  "uniform mat4 model;\n"
  "out vec3 P;\n"
  "out vec3 N;\n"
  "void main()\n"
  "{\n"
  "  P = (model * vec4(p, 1.0f)).xyz;\n"
  "  N = n;\n"
  "  gl_Position = projection * view * model * vec4(p, 1.0f);\n"
  "}\n";

static const char *g =
  "";

static const char *f = 
  "#version 410 core\n"
  "in vec3 P;\n"
  "in vec3 N;\n"
  "uniform float time;\n"
  "out vec4 c;\n"
  "void main()\n"
  "{\n"
  "  vec3 t = vec3(P.x + cos(time) * 8.0f, P.y + sin(time) * 8.0f, P.z);\n"
  "  float value1 = max(0.1f, dot(normalize(t), N)) / pow(length(t) / 16.0f, 2.0f);\n"
  "  t = vec3(P.x + cos(time + 2.1) * 8.0f, P.y + sin(time + 2.1) * 8.0f, P.z);\n"
  "  float value2 = max(0.1f, dot(normalize(t), N)) / pow(length(t) / 16.0f, 2.0f);\n"
  "  t = vec3(P.x + cos(time + 4.2) * 8.0f, P.y + sin(time + 4.2) * 8.0f, P.z);\n"
  "  float value3 = max(0.1f, dot(normalize(t), N)) / pow(length(t) / 16.0f, 2.0f);\n"
  "  c = vec4(value1, value2, value3, 1.0f);\n"
  "}\n";

static const char *shaders[3];

const char **get_shaders()
{
  shaders[0] = v;
  shaders[1] = g;
  shaders[2] = f;
  return shaders;
}
