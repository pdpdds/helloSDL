#include <stdio.h>
#include <SDL.h>

int main(int argc, char** argv)
{
    int screen_w;
    int screen_h;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;

    if (SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN, &pWindow, &pRenderer) < 0)
    {
        printf("SDL_CreateWindowAndRenderer Error\n");
        return 0;
    }

    SDL_GetWindowSize(pWindow, &screen_w, &screen_h);

    SDL_Surface *pHellowBMP = SDL_LoadBMP("helloworld.bmp");
    if (pHellowBMP == 0)
    {
        SDL_DestroyRenderer(pRenderer);
        SDL_DestroyWindow(pWindow);
        printf("SDL_LoadBMP Error\n");
        return 0;
    }

    SDL_Texture *pTexture = SDL_CreateTextureFromSurface(pRenderer, pHellowBMP);
    if (pTexture == 0)
    {
        SDL_DestroyRenderer(pRenderer);
        SDL_DestroyWindow(pWindow);
        printf("SDL_LoadBMP Error\n");
        return 0;
    }

    bool running = true;

    int lastTickCount = SDL_GetTicks();
    int curTickCount = SDL_GetTicks();
    int k = 0;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                }
            }
            else if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }


        SDL_Rect srcrect, dstrect;

        srcrect.x = (int)0;
        srcrect.y = (int)0;
        srcrect.w = (int)507;
        srcrect.h = (int)133;

        dstrect.x = (int)0;
        dstrect.y = (int)0;
        dstrect.w = (int)screen_w;
        dstrect.h = (int)screen_h;

        SDL_RenderCopy(pRenderer, pTexture, &srcrect, &dstrect);
        SDL_RenderPresent(pRenderer);

    }

    SDL_DestroyTexture(pTexture);
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();

    return 0;
}