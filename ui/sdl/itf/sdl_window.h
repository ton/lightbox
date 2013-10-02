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
namespace ui {

/// Base class for the main window of LightBox. This is just a wrapper around an
/// SDL window for now.
class SdlWindow: public Window
{
    public:
        SdlWindow(const std::string &title, unsigned int width, unsigned int height);
        ~SdlWindow();

        void show(const Renderer &renderer);

    private:
        /// Wrapped SDL window struct.
        SDL_Window *sdlWindow_;
        /// Font for drawing overlay text to the screen.
        TTF_Font *overlayFont_;
        /// Buffer representing the pixels on screen.
        std::unique_ptr<uint32_t> pixels_;
        /// Backend SDL renderer.
        SDL_Renderer *sdlRenderer_;
        /// Texture we render to and flip to the screen.
        SDL_Texture *texture_;
};

}}

#endif
