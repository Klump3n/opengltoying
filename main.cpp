#include <iostream>

#include <assert.h>

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "bcm_host.h"

#ifndef STATE
#define STATE
#include "statetype.h"
#endif

#include "initogl.h"
#include "shaderstuff.h"

#define check() assert(glGetError() == 0)


static STATE_M _state;
static STATE_M *state=&_state;

// coloured triangle
GLfloat vertices[] = {
  -1.0f, -1.0f, 0.0f, 1.0f, .0f, .0f,
  1.0f, -1.0f, 0.0f, .0f, 1.0f, .0f,
  0.0f, 1.0f, 0.0f, .0f, .0f, 1.0f,
};

// white cube
GLfloat vertices2[] = {
.0f, .0f, .0f, 1.0f, 1.0f, 1.0f,
   .0f, .0f, 1.0f, 1.0f, 1.0f, 1.0f,
   .0f, 1.0f, .0f, 1.0f, 1.0f, 1.0f,
   .0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
   1.0f, .0f, .0f, 1.0f, 1.0f, 1.0f,
   1.0f, .0f, 1.0f, 1.0f, 1.0f, 1.0f,
   1.0f, 1.0f, .0f, 1.0f, 1.0f, 1.0f,
   1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
};


static void gen_buffers(STATE_M *state){
  // generate vertex buffer object
  glGenBuffers(1, &state->vbo);
  check();
  // upload to gfx card
  glBindBuffer(GL_ARRAY_BUFFER, state->vbo);
  check();
  // write vertices into vertex buffer object
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  check();
  
};

static void draw(STATE_M *state){

  // clear background
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  // set background colour
  glClearColor ( 0.2, 0.2, 0.2, 1.0 );

  // open buffer
  glBindBuffer(GL_ARRAY_BUFFER, state->vbo);

  // use this shader program
  glUseProgram(state->shaderProgram);

  // pointer to vertex shader object

  state->posAttrib = glGetAttribLocation(state->shaderProgram, "vPosition");
  glVertexAttribPointer(state->posAttrib, 3, GL_FLOAT, GL_FALSE,
  			6*sizeof(float), 0);
  glEnableVertexAttribArray(state->posAttrib);  // make active

  state->color = glGetAttribLocation(state->shaderProgram, "vColour");
  glVertexAttribPointer(state->color, 3, GL_FLOAT, GL_FALSE,
  			6*sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(state->color);
  
  // draw it
  glDrawArrays (GL_TRIANGLES, 0, 3);

  // update screen
  eglSwapBuffers(state->display, state->surface);
}

int main()
{
  bcm_host_init();
  init_opengl(state);
  load_fragment_shader(state, "shaders/nothing.fs.c");
  load_vertex_shader(state, "shaders/nothing.vs.c");
  link_shaders(state);
  gen_buffers(state);

  showprogramlog(state->shaderProgram);
  
  while(1){
    draw(state);
  };
  
  return 0;
}

// int main(){
//   std::cout << "Heaaaaallo World!" << std::endl;
//   return 0;
// };
