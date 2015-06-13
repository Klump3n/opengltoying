#include <SDL.h>
#include <SDL_opengl.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  // Initialise SDL
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);

  // Create vertex, i.e. a triangle
  float vertices[] = {
    0.0f, 0.5f,
    -.5f, -.5f,
    .5f, -.5f
  };
  
  //  GLuint vao;
  //  glGenVertexArrays(1, &vao);

  //  glBindVertexArray(vao);
  
  // Create vertex buffer object
  GLuint vbo;
  glGenBuffers(1, &vbo); // create 1 of them

  // Upload to gfx card
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  // Write triangle into vertex buffer object
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Shaders
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(GL_VERTEX_SHADER, 1, &"shaders/nothing.vs.c", NULL);
  glCompileShader(vertexShader);

  GLint vsStatus = GL_FALSE;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vsStatus);

  if (vsStatus = GL_FALSE){
    printf("Vertex shader build failed\n");
    char buffer[512];
    glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
    printf("Build log:\n%c", buffer);
  };

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(GL_FRAGMENT_SHADER, 1, &"shaders/nothing.fs.c", NULL);
  glCompileShader(fragmentShader);

  GLint fsStatus = GL_FALSE;
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fsStatus);

  if (fsStatus = GL_FALSE){
    printf("Fragment shader build failed\n");
    char buffer[512];
    glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
    printf("Build log:\n%c", buffer);
  };

  // Combining the shaders
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glEnableVertexAttribArray(posAttrib);


  glDrawArrays(GL_TRIANGLES, 0, 3);
  
  //    SDL_Surface *screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
  //    Uint32 screenColor = SDL_MapRGB(screen->format, 127, 168, 255);
  //    SDL_FillRect(screen, NULL, screenColor);
  //    SDL_Flip(screen);
    

  SDL_Delay(1000);

  //  SDL_GL_DeleteContext(context);
  
  SDL_Quit();
  return 0;
}


/* SDL_GLContext context = SDL_GL_CreateContext(window); */


/* SDL_Event windowEvent; */
/* while (true) */
/*   { */
/*     if (SDL_PollEvent(&windowEvent)) */
/*       { */
/* 	if (windowEvent.type == SDL_QUIT) break; */
/*       } */

/*     SDL_GL_SwapWindow(window); */
/*   } */
