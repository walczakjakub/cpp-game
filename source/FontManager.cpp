#include "FontManager.h"
#include <iostream>

namespace CQ::Render
{
  FontManager::FontManager()
    : m_initialized(false)
  {
    if (TTF_Init() == -1)
    {
      std::cerr << "SDL_ttf could not initialize! TTF_Error: "
      << TTF_GetError() << std::endl;
      return;
    }
    
    m_initialized = true;
    std::cout << "SDL_ttf initialized successfully!" << std::endl;
  }
  
  FontManager::~FontManager()
  {
    TTF_Quit();
    std::cout << "SDL_ttf shut down successfully!" << std::endl;
  }
  
  TTF_Font* FontManager::loadFont(const std::string& filepath_, int pointSize_)
  {
    if (!m_initialized)
    {
      std::cerr << "Cannot load font - SDL_ttf not initialized!" << std::endl;
      return nullptr;
    }
    
    TTF_Font* font = TTF_OpenFont(filepath_.c_str(), pointSize_);
    
    if (font == nullptr)
    {
      std::cerr << "Failed to load font: " << filepath_ << std::endl;
      std::cerr << "TTF_Error: " << TTF_GetError() << std::endl;
      return nullptr;
    }
    
    std::cout << "Font loaded successfully: " << filepath_
    << " (size: " << pointSize_ << ")" << std::endl;
    
    return font;
  }
} //namespace
