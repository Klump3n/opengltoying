
// State machine
typedef struct
{
  // display stuff
  uint32_t screen_width;
  uint32_t screen_height;

  // egl stuff
  EGLDisplay display;
  EGLSurface surface;
  EGLContext context;

  // shader stuff
  GLuint vbo;
  GLuint framebuffer;
  GLuint vshader;
  GLuint fshader;
  GLuint shaderProgram;

  // shader internal variables
  GLuint posAttrib;
  GLuint color;
  
} STATE_M;
