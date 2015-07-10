#include <stdio.h>
#include <assert.h>

#include <EGL/egl.h>
#include "GLES2/gl2.h"
#include "EGL/eglext.h"

#include "bcm_host.h"

#define check() assert(glGetError() == 0)

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
  GLint posAttrib;

} STATE_M;

static STATE_M _state;
static STATE_M *state=&_state;

GLfloat vertices[] = {
  -1.0f, -1.0f, 0.5f,
  1.0f, -1.0f, 0.5f,
  0.0f, 1.0f, 0.5f,
};

/// pull logs from the gfx card
static void showlog(GLint shader)
{
   // Prints the compile log for a shader
   char log[1024];
   glGetShaderInfoLog(shader,sizeof(log),NULL,log);
   printf("%d:shader:\n%s\n", shader, log);
};

/// logs
static void showprogramlog(GLint shader)
{
   // Prints the information log for a program object
   char log[1024];
   glGetProgramInfoLog(shader,sizeof(log),NULL,log);
   printf("%d:program:\n%s\n", shader, log);
};

static void init_opengl(STATE_M *state){

  // dispmanx variables
  static EGL_DISPMANX_WINDOW_T nativewindow;  
  DISPMANX_ELEMENT_HANDLE_T dispman_element;
  DISPMANX_DISPLAY_HANDLE_T dispman_display;
  DISPMANX_UPDATE_HANDLE_T dispman_update;
  // window height and so on
  DISPMANX_MODEINFO_T info;
  // i dont know what these do
  VC_RECT_T dst_rect;
  VC_RECT_T src_rect;

  // other variables

  // integer return
  int ret;
  // success
  int32_t success = 0;
  // egl true or false
  EGLBoolean result;
  // egl number of configs
  EGLint num_config;
  // egl config
  EGLConfig config;

  // the kind of buffer we want
  static const EGLint attribute_list[] =
    {
      EGL_RED_SIZE, 8,
      EGL_GREEN_SIZE, 8,
      EGL_BLUE_SIZE, 8,
      EGL_ALPHA_SIZE, 8,
      EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
      EGL_NONE
    };

  // the kind of context we want
  static const EGLint context_attributes[] = 
    {
      EGL_CONTEXT_CLIENT_VERSION, 2,
      EGL_NONE
    };

  // get an egl display connection
  state->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  
  // initialize the EGL display connection
  result = eglInitialize(state->display, NULL, NULL);

  // get an appropriate EGL frame buffer configuration
  result = eglChooseConfig(state->display, attribute_list, &config, 1, &num_config);

  // bind opengl es api
  result = eglBindAPI(EGL_OPENGL_ES_API);

  // create an EGL rendering context
  state->context = eglCreateContext(state->display, config, EGL_NO_CONTEXT, context_attributes);

  // create an EGL window surface
  success = graphics_get_display_size(0 /* LCD */, &state->screen_width, &state->screen_height);
  //assert( success >= 0 );

  // no idea what this is for
  dst_rect.x = 0;
  dst_rect.y = 0;
  dst_rect.width = state->screen_width;
  dst_rect.height = state->screen_height;
      
  src_rect.x = 0;
  src_rect.y = 0;
  src_rect.width = state->screen_width << 16;
  src_rect.height = state->screen_height << 16;        

  dispman_display = vc_dispmanx_display_open(0 /* LCD */);
  dispman_update = vc_dispmanx_update_start(0);

  // and i dont understand this either. the documentations if f'ed up
  dispman_element = vc_dispmanx_element_add ( dispman_update, dispman_display,
					      0/*layer*/, &dst_rect, 0/*src*/,
					      &src_rect, DISPMANX_PROTECTION_NONE,
					      0 /*alpha*/, 0/*clamp*/, 0/*transform*/);

  // set dispmanx
  nativewindow.element = dispman_element;
  nativewindow.width = state->screen_width;
  nativewindow.height = state->screen_height;
  // End an update and wait for it to complete 
  vc_dispmanx_update_submit_sync( dispman_update );

  // create a surface to work with
  state->surface = eglCreateWindowSurface( state->display, config, &nativewindow, NULL );

  // connect the context to the surface
  result = eglMakeCurrent(state->display, state->surface, state->surface, state->context);
  glClear( GL_COLOR_BUFFER_BIT );
  glViewport(0,0,state->screen_width, state->screen_height);
  // Set background color and clear buffers
  //glClearColor(0.75f, 0.25f, 0.35f, 1.0f);
  
  
}

static void init_shaders(STATE_M *state){
  GLint vsStatus = GL_FALSE;
  GLint fsStatus = GL_FALSE;

  // Shaders
  state->vshader = glCreateShader(GL_VERTEX_SHADER);

  const GLchar *vertexShaderSource =
    "attribute vec4 vPosition; \n"
    "void main(){ \n"
    "        gl_Position = vPosition; \n"
    "} \n";


  glShaderSource(state->vshader, 1, &vertexShaderSource, 0);
  glCompileShader(state->vshader);
  check();
  glGetShaderiv(state->vshader, GL_COMPILE_STATUS, &vsStatus);
  
  if (vsStatus = GL_TRUE){
    printf("Vertex shader compiled.\n");
    showlog(state->vshader);
  }
  else{
    printf("Vertex shader build failed\n");
    char buffer[512];
    glGetShaderInfoLog(state->vshader, 512, NULL, buffer);
    printf(buffer);
  };

  state->fshader = glCreateShader(GL_FRAGMENT_SHADER);

  const GLchar *fragmentShaderSource =
    "precision mediump float; \n"
    "void main(){ \n"
    "    gl_FragColor = vec4 ( 0.0, 0.0, 1.0, 1.0 ); \n"
    "} \n";

  glShaderSource(state->fshader, 1, &fragmentShaderSource, 0);
  glCompileShader(state->fshader);
  check();
  glGetShaderiv(state->fshader, GL_COMPILE_STATUS, &fsStatus);

  if (fsStatus = GL_TRUE){
    printf("Fragment shader compiled.\n");
    showlog(state->fshader);
  }
  else{
    printf("Fragment shader build failed\n");
    char buffer[512];
    glGetShaderInfoLog(state->fshader, 512, NULL, buffer);
    printf("Build log:\n%c", buffer);
  };

  // Combining the shaders
  state->shaderProgram = glCreateProgram();
  glAttachShader(state->shaderProgram, state->vshader);
  glAttachShader(state->shaderProgram, state->fshader);

  //  glBindAttribLocation(state->shaderProgram, 0, "vPosition");
  
  glLinkProgram(state->shaderProgram);
  showprogramlog(state->shaderProgram);
  check();
  /* glUseProgram(state->shaderProgram); */

  // set background colour to black



}

static void draw(STATE_M *state){


  /* glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); */
  glClear(GL_COLOR_BUFFER_BIT);
  
  glClearColor ( 0.1, 0.5, 0.1, 0.5 );
  glBindBuffer(GL_ARRAY_BUFFER, state->vbo);
  glUseProgram(state->shaderProgram);

  
  
  state->posAttrib = glGetAttribLocation(state->shaderProgram, "vPosition");
  /* glVertexAttribPointer(state->posAttrib, 2, GL_FLOAT, GL_FALSE, 0, vertices); */
  glVertexAttribPointer(state->posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
  /* glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices); */

  glEnableVertexAttribArray(state->posAttrib);
  /* glEnableVertexAttribArray(0); */
  
  


  glDrawArrays (GL_TRIANGLES, 0, 3);

  eglSwapBuffers(state->display, state->surface);
}


int main()
{


  bcm_host_init();
  init_opengl(state);
  init_shaders(state);

  // generate buffer
  glGenBuffers(1, &state->vbo);
  // upload to gfx card
  glBindBuffer(GL_ARRAY_BUFFER, state->vbo);
  // write triangle into vertex buffer object
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  check();

  
  while(1){
    draw(state);
  }
  
  return 0;
}
