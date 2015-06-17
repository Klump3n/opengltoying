# opengltoying
Toying with OpenGL on a RPi

For this to compile on the RPi you need libglm-dev (and of course build-essential, I hope nothing more):

    $ sudo apt-get install libglm-dev build-essential

Then simply write make to compile.

     $ make

It uses dispmanx to write directly to the HDMI output. I kinda stole the code from various sources and mixed everything together so that it now definitely and totally sucks balls. Trying to get back into C with this, possibly C++ later on.