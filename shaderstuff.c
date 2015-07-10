#include "shaderstuff.h"
#ifndef STATE
#define STATE
#include "statetype.h"
#endif

#define check() assert(glGetError() == 0)

// pull logs from the gfx card
void showlog(GLint shader)
{
   // Prints the compile log for a shader
   char log[1024];
   glGetShaderInfoLog(shader,sizeof(log),NULL,log);
   printf("%d:shader:\n%s\n", shader, log);
};

/// logs
void showprogramlog(GLint shader)
{
   // Prints the information log for a program object
   char log[1024];
   glGetProgramInfoLog(shader,sizeof(log),NULL,log);
   printf("%d:program:\n%s\n", shader, log);
};

void load_vertex_shader(STATE_M *state, const char *filename){

  // status variables
  GLint vsStatus = GL_FALSE;

  FILE* f = fopen(filename, "rb");
  assert(f);
  fseek(f,0,SEEK_END);
  int sz = ftell(f);
  fseek(f,0,SEEK_SET);
  GLchar Src[sz+1];
  fread(Src,1,sz,f);
  Src[sz] = 0; //null terminate it!
  fclose(f);

  
  // shaders //
  // vertex shader
  // source for a simple vertex shader
  const GLchar *vertexShaderSource = Src;
  //printf(Src);
  // create vertex shader
  state->vshader = glCreateShader(GL_VERTEX_SHADER);
  check();
  // load shader source
  glShaderSource(state->vshader, 1, &vertexShaderSource, 0);
  check();
  // compile shader
  glCompileShader(state->vshader);
  check();
  // check whether or not it has compiled
  glGetShaderiv(state->vshader, GL_COMPILE_STATUS, &vsStatus);

  if (vsStatus = GL_TRUE){
    printf("Vertex shader compiled.\n");
    /* showlog(state->vshader); */
  }
  else{
    printf("Vertex shader build failed:\n");
    showlog(state->vshader);
    /* char buffer[512]; */
    /* glGetShaderInfoLog(state->vshader, 512, NULL, buffer); */
    /* printf(buffer); */
  };
};

void load_fragment_shader(STATE_M *state, const char *filename){

    // status variables
  GLint fsStatus = GL_FALSE;

  FILE* f = fopen(filename, "rb");
  assert(f);
  fseek(f,0,SEEK_END);
  int sz = ftell(f);
  fseek(f,0,SEEK_SET);
  GLchar Src[sz+1];
  fread(Src,1,sz,f);
  Src[sz] = 0; //null terminate it!
  fclose(f);
  
  // fragment shader
  const GLchar *fragmentShaderSource = Src;
  //  printf(Src);
  // create fragment shader
  state->fshader = glCreateShader(GL_FRAGMENT_SHADER);
  check();
  // load shader source
  glShaderSource(state->fshader, 1, &fragmentShaderSource, 0);
  check();
  // compile shader
  glCompileShader(state->fshader);
  check();
  // check whether it has compiled
  glGetShaderiv(state->fshader, GL_COMPILE_STATUS, &fsStatus);

  if (fsStatus = GL_TRUE){
    printf("Fragment shader compiled.\n");
    /* showlog(state->fshader); */
  }
  else{
    printf("Fragment shader build failed:\n");
    showlog(state->fshader);
    /* char buffer[512]; */
    /* glGetShaderInfoLog(state->fshader, 512, NULL, buffer); */
    /* printf("Build log:\n%c", buffer); */
  };
};

void link_shaders(STATE_M *state){
  // creating program, that holds the shaders
  state->shaderProgram = glCreateProgram();
  check();
  // load fragment shader into the program
  glAttachShader(state->shaderProgram, state->fshader);
  check();
  // load vertex shader into the program
  glAttachShader(state->shaderProgram, state->vshader);
  check();
  // link the programm
  glLinkProgram(state->shaderProgram);
  check();
  printf("Program linked\n");
};
