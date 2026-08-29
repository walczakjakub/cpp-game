#pragma once

#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>

namespace CQ::Render
{
  // SDLRenderer class - manages SDL window and rendering
  class SDLRenderer
  {
  public:
    // Constructor - creates window and renderer
    SDLRenderer(const std::string& title_, int width_, int height_);
    
    // Destructor - cleans up SDL resources
    ~SDLRenderer();
    
    // Delete copy constructor and assignment (we don't want to copy SDL resources)
    SDLRenderer(const SDLRenderer&) = delete;
    SDLRenderer& operator=(const SDLRenderer&) = delete;
    
    // Clear the screen with a color
    void clear(const SDL_Color& color_);
    
    // Present the rendered frame to the screen
    void present();
    
    void renderText(const std::string& text_, TTF_Font* font_, const SDL_Color& color_, int x_, int y_);
    
    // Check if initialization was successful
    bool isInitialized() const
    {
      return m_initialized;
    }
    
    // Get the SDL renderer (for advanced use later)
    SDL_Renderer* getRenderer()
    {
      return m_renderer;
    }
    
    // Actual drawable size in pixels. Not the width/height passed to the
    // constructor - in fullscreen SDL ignores those and uses the display.
    int getWidth() const
    {
      return m_width;
    }
    
    int getHeight() const
    {
      return m_height;
    }
    
  private:
    SDL_Window* m_window;       // Pointer to SDL window
    SDL_Renderer* m_renderer;   // Pointer to SDL renderer
    bool m_initialized;         // Track if initialization succeeded
    int m_width;                // Drawable width in pixels
    int m_height;               // Drawable height in pixels
  };
  
} //namespace
