#ifndef LB_UI_SDL_WINDOW_H
#define LB_UI_SDL_WINDOW_H

#include "ui/itf/window.h"

#include <memory>
#include <string>

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Window;
struct _TTF_Font;
typedef _TTF_Font TTF_Font;

namespace lb {

class Scene;

namespace ui {

/// Base class for the main window of LightBox. This is just a wrapper around an
/// SDL window for now.
class SdlWindow: public Window
{
    public:
        SdlWindow(const std::string &title, unsigned int width, unsigned int height,
                uint32_t* buffer);
        ~SdlWindow();

        void show(Scene &scene);

    private:
        /// Wrapped SDL window struct.
        SDL_Window *sdlWindow_;
        /// Font for drawing overlay text to the screen.
        TTF_Font *overlayFont_;
        /// Buffer representing the pixels on screen (naked pointer implies
        /// non-ownership).
        uint32_t* offscreenBuffer_;
        /// Backend SDL renderer.
        SDL_Renderer *sdlRenderer_;
        /// Texture we render to and flip to the screen.
        SDL_Texture *texture_;
};

}}

#endif
