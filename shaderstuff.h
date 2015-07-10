#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"

#include "bcm_host.h"

#ifndef STATE
#define STATE
#include "statetype.h"
#endif

#include "initogl.h"

void showlog(GLint shader);

void showprogramlog(GLint shader);

void load_vertex_shader(STATE_M *state, const char *filename);

void load_fragment_shader(STATE_M *state, const char *filename);

void link_shaders(STATE_M *state);
