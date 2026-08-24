#include "SDLRenderer.h"

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

namespace CQ::Render
{
  // Constructor - This runs when you create an SDLRenderer object
  // It sets up everything SDL needs
  SDLRenderer::SDLRenderer(const std::string& title_, int width_, int height_)
    : m_window(nullptr)      // Initialize pointers to nullptr (null = nothing)
    , m_renderer(nullptr)
    , m_initialized(false)   // Start assuming we failed (prove success later)
  {
    // Step 1: Initialize SDL video subsystem
    // SDL_Init returns 0 on success, negative on failure
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
      return; // Exit constructor early if initialization fails
    }
    
    // Step 2: Create the window
    // Parameters: title, x position, y position, width, height, flags
    // SDL_WINDOWPOS_CENTERED centers the window on screen
    // SDL_WINDOW_SHOWN makes it visible immediately
    m_window = SDL_CreateWindow(
      title_.c_str(),           // Window title (convert std::string to C-string)
      SDL_WINDOWPOS_CENTERED,  // X position
      SDL_WINDOWPOS_CENTERED,  // Y position
      width_,                   // Width in pixels
      height_,                  // Height in pixels
      SDL_WINDOW_SHOWN         // Flags
    );
    
    // Check if window creation succeeded
    if (m_window == nullptr)
    {
      std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
      SDL_Quit(); // Clean up SDL before returning
      return;
    }
    
    // Step 3: Create a renderer for the window
    // The renderer is what actually draws things
    // Parameters: window, index (-1 = first supporting driver), flags
    // SDL_RENDERER_ACCELERATED uses hardware acceleration (GPU)
    m_renderer = SDL_CreateRenderer(
      m_window,
      -1,
      SDL_RENDERER_ACCELERATED
    );
    
    // Check if renderer creation succeeded
    if (m_renderer == nullptr)
    {
      std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
      SDL_DestroyWindow(m_window); // Clean up window
      SDL_Quit();                  // Clean up SDL
      return;
    }
    
    // If we got here, everything worked!
    m_initialized = true;
    std::cout << "SDL initialized successfully!" << std::endl;
  }
  
  // Destructor - This runs automatically when SDLRenderer is destroyed
  // It cleans up all SDL resources (this is RAII - Resource Acquisition Is Initialization)
  SDLRenderer::~SDLRenderer()
  {
    // Clean up in reverse order of creation
    if (m_renderer != nullptr)
    {
      SDL_DestroyRenderer(m_renderer);
      m_renderer = nullptr;
    }
    
    if (m_window != nullptr)
    {
      SDL_DestroyWindow(m_window);
      m_window = nullptr;
    }
    
    SDL_Quit(); // Shut down SDL
    
    std::cout << "SDL shut down successfully!" << std::endl;
  }
  
  // Clear the screen with a specific color
  void SDLRenderer::clear(const SDL_Color& color_)
  {
    if (!m_initialized) return; // Don't do anything if not initialized
    
    // Set the color that will be used for drawing
    SDL_SetRenderDrawColor(m_renderer, color_.r, color_.g, color_.b, color_.a);
    
    // Clear the entire screen with that color
    SDL_RenderClear(m_renderer);
  }
  
  // Present (show) what we've rendered to the screen
  void SDLRenderer::present()
  {
    if (!m_initialized) return; // Don't do anything if not initialized
    
    // This swaps the buffers and shows what we drew
    SDL_RenderPresent(m_renderer);
  }
  
  void SDLRenderer::renderText(const std::string& text_, TTF_Font* font_, const SDL_Color& color_, int x_, int y_)
  {
    if (!m_initialized || font_ == nullptr)
    {
      return;
    }
    
    //Surface
    SDL_Surface* surface = TTF_RenderText_Solid(font_, text_.c_str(), color_);
    
    if (surface == nullptr)
    {
      std::cerr << "Failed to render text! TTF_Error: " << TTF_GetError() << std::endl;
      return;
    }
    
    //Texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    
    if (texture == nullptr)
    {
      std::cerr << "Failed to create texture! SDL_Error: " << SDL_GetError() << std::endl;
      SDL_FreeSurface(surface);
      return;
    }
    
    int textWidth = surface->w;
    int textHeight = surface->h;
    
    SDL_FreeSurface(surface);
    
    // Render
    SDL_Rect destRect = {x_, y_, textWidth, textHeight};
    SDL_RenderCopy(m_renderer, texture, nullptr, &destRect);
    
    SDL_DestroyTexture(texture);
  }
  
} // namespace
