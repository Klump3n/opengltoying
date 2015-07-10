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

void init_opengl(STATE_M *state);
