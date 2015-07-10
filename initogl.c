#include "initogl.h"

#ifndef STATE
#define STATE
#include "statetype.h"
#endif


#define check() assert(glGetError() == 0)

// opengl init and so on

//static void init_opengl(STATE_M *state){
void init_opengl(STATE_M *state){

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
					      0/*layer*/, &dst_rect,  0/*src*/,
					      &src_rect, DISPMANX_PROTECTION_NONE,
					      0 /*alpha*/,  0/*clamp*/,  (DISPMANX_TRANSFORM_T)0/*transform*/);

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

}
