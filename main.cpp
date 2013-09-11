#include "mesh/itf/mesh.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

const unsigned int WINDOW_WIDTH = 640;
const unsigned int WINDOW_HEIGHT = 480;

void printUsage()
{
    std::cout << "Usage: lightbox <filename.obj> [-h]" << std::endl;
}

int main(int argc, char **argv)
{
    // Determine the name of the OBJ mesh to render.
    if (argc != 2)
    {
        printUsage();
        return 1;
    }

    if (argv[1] == "-h")
    {
        printUsage();
        return 0;
    }

    std::string objMeshFileName = argv[1];
    std::ifstream objMeshFile(objMeshFileName);
    if (!objMeshFile)
    {
        std::cerr << "Could not open OBJ file '" << objMeshFileName << "'." << std::endl;
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        std::cerr << SDL_GetError() << std::endl;
        return 1;
    }

    // Load a font to be able to display FPS.
    if (TTF_Init() != 0)
    {
        std::cerr << TTF_GetError() << std::endl;
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("DroidSansMono.ttf", 14);
    if (font == nullptr)
    {
        std::cerr << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);

    SDL_Window *window = SDL_CreateWindow("LightBox", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cerr << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cerr << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a texture that will represent our drawing canvas. The streaming
    // flag indicates to SDL that this texture is going to change frequently.
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (texture == nullptr)
    {
        std::cerr << SDL_GetError() << std::endl;
        return 1;
    }

    // Create our buffer that represents the pixels on screen.
    uint32_t *pixels = new uint32_t[WINDOW_WIDTH * WINDOW_HEIGHT];

    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        int startTicks = SDL_GetTicks();

        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_KEYDOWN:
                    quit = e.key.keysym.sym == SDLK_q;
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
                default:
                    break;
            }
        }

        // Create static noise.
        uint32_t *pixel = &(pixels[0]);
        for (int j = 0; j < WINDOW_HEIGHT; ++j)
        {
            char gray = rand();
            for (int i = 0; i < WINDOW_WIDTH; ++i)
            {
                gray += 25;
                *pixel++ = (gray << 16) + (gray << 8) + gray;
            }
        }

        // Upload the pixel data to the texture.
        SDL_UpdateTexture(texture, nullptr, pixels, WINDOW_WIDTH * sizeof(uint32_t));

        // Draw the texture on the screen.
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);

        // Show FPS.
        int delta = SDL_GetTicks() - startTicks;
        if (delta != 0)
        {
            std::stringstream ss;
            ss << "FPS: " << std::setprecision(3) << std::fixed << 1000. / delta;
            SDL_Surface *text = TTF_RenderText_Solid(font, ss.str().c_str(), {255, 255, 255});
            SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, text);
            SDL_SetTextureBlendMode(textTexture, SDL_BLENDMODE_BLEND);

            SDL_Rect destRect;
            destRect.x = WINDOW_WIDTH - text->w - 1;
            destRect.y = 0;
            destRect.w = text->w;
            destRect.h = text->h;

            SDL_RenderCopy(renderer, textTexture, nullptr, &destRect);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
