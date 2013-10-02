#include "ui/sdl/itf/sdl_window.h"

#include "core/itf/renderer.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include <iomanip>
#include <iostream>
#include <sstream>

using namespace lb::ui;

SdlWindow::SdlWindow(const std::string &title, unsigned int width, unsigned int height):
    Window(width, height),
    sdlWindow_(nullptr),
    sdlRenderer_(nullptr),
    overlayFont_(nullptr),
    pixels_(new uint32_t[width * height]),
    texture_(nullptr)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        // FIXME: Throw an exception.
    }

    sdlWindow_ = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN);
    if (sdlWindow_ == nullptr)
    {
        // FIXME: Throw an exception.
    }

    sdlRenderer_ = SDL_CreateRenderer(sdlWindow_, -1, SDL_RENDERER_ACCELERATED);
    if (sdlRenderer_ == nullptr)
    {
        // FIXME: Throw an exception.
    }

    // Create a texture that will represent our drawing canvas. The streaming
    // flag indicates to SDL that this texture is going to change frequently.
    texture_ = SDL_CreateTexture(sdlRenderer_, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (texture_ == nullptr)
    {
        // FIXME: Throw an exception.
    }

    // Initialize the TTF subsystem to be able to display fonts in this window.
    if (TTF_Init() != 0)
    {
        // FIXME: Throw an exception.
    }

    overlayFont_ = TTF_OpenFont("DroidSansMono.ttf", 14);
    if (overlayFont_ == nullptr)
    {
        // FIXME: Throw an exception.
    }
    TTF_SetFontStyle(overlayFont_, TTF_STYLE_BOLD);
}

SdlWindow::~SdlWindow()
{
    SDL_DestroyTexture(texture_);
    SDL_DestroyRenderer(sdlRenderer_);
    SDL_DestroyWindow(sdlWindow_);
    SDL_Quit();
}

/// Shows the window, and loads the given \a scene data
///
/// \param scene the scene to render
void SdlWindow::show(const Renderer &renderer)
{
    // Starts the SDL event loop, and repeatedly calls renderer to render an
    // image to the screen.
    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
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
        int startTicks = SDL_GetTicks();

        // Render using the supplied renderer.
        renderer.render(width(), height(), pixels_.get());

        // Upload the pixel data to the texture.
        SDL_UpdateTexture(texture_, nullptr, pixels_.get(), width() * sizeof(uint32_t));

        // Draw the texture on the screen.
        SDL_RenderCopy(sdlRenderer_, texture_, nullptr, nullptr);

        // Show FPS.
        int delta = SDL_GetTicks() - startTicks;
        if (delta != 0)
        {
            std::stringstream ss;
            ss << "FPS: " << std::setprecision(3) << std::fixed << 1000. / delta;
            SDL_Surface *text = TTF_RenderText_Solid(overlayFont_, ss.str().c_str(), {255, 255, 255});
            SDL_Texture *textTexture = SDL_CreateTextureFromSurface(sdlRenderer_, text);
            SDL_SetTextureBlendMode(textTexture, SDL_BLENDMODE_BLEND);

            SDL_Rect destRect;
            destRect.x = width() - text->w - 1;
            destRect.y = 0;
            destRect.w = text->w;
            destRect.h = text->h;

            SDL_RenderCopy(sdlRenderer_, textTexture, nullptr, &destRect);

            SDL_DestroyTexture(textTexture);
            SDL_FreeSurface(text);
        }

        SDL_RenderPresent(sdlRenderer_);
    }
}
