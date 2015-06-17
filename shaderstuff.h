#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"

#include "bcm_host.h"

#include "initogl.h"

void showlog();

void showprogramlog();

void load_vertex_shader();

void load_fragment_shader();

void get_shader_variables();

void link_shaders();
