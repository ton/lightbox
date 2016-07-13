#include "ui/sdl/itf/sdl_window.h"

#include "core/itf/camera.h"
#include "core/itf/scene.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace lb::ui;

SdlWindow::SdlWindow(
        const std::string &title, unsigned int width, unsigned int height,
        uint32_t* offscreenBuffer):
    Window(width, height),
    sdlWindow_(nullptr),
    sdlRenderer_(nullptr),
    overlayFont_(nullptr),
    offscreenBuffer_(offscreenBuffer),
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
void SdlWindow::show(Scene& scene)
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
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_q:
                            quit = true;
                            break;
                        case SDLK_UP:
                            scene.camera().setLocation(scene.camera().location() + Vector3d(0.0, 0.1, 0.0));
                            break;
                        case SDLK_DOWN:
                            scene.camera().setLocation(scene.camera().location() - Vector3d(0.0, 0.1, 0.0));
                            break;
                        case SDLK_LEFT:
                            scene.camera().setLocation(scene.camera().location() - Vector3d(0.1, 0.0, 0.0));
                            break;
                        case SDLK_RIGHT:
                            scene.camera().setLocation(scene.camera().location() + Vector3d(0.1, 0.0, 0.0));
                            break;
                    }
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
                default:
                    break;
            }
        }

        // Create static noise.
        auto start = std::chrono::high_resolution_clock::now();

        // Render using the supplied renderer.
        scene.render();

        // Upload the pixel data to the texture.
        SDL_UpdateTexture(texture_, nullptr, offscreenBuffer_, width() * sizeof(uint32_t));

        // Draw the texture on the screen.
        SDL_RenderCopy(sdlRenderer_, texture_, nullptr, nullptr);

        // Show FPS.
        int delta = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
        if (delta != 0)
        {
            std::stringstream ss;
            ss << "FPS: " << std::setprecision(3) << std::fixed << 1.0e6 / delta;
            SDL_Surface *text = TTF_RenderText_Solid(overlayFont_, ss.str().c_str(), {10, 255, 10});
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
