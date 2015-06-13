#include <SDL.h>
#include <SDL_opengl.h>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);



    SDL_Surface *screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    Uint32 screenColor = SDL_MapRGB(screen->format, 127, 168, 255);
    SDL_FillRect(screen, NULL, screenColor);
    SDL_Flip(screen);


    SDL_Delay(1000);
    
    SDL_Quit();
    return 0;
}
