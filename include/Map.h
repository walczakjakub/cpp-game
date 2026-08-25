#pragma once

#include "SDLRenderer.h"
#include "Player.h"
#include "FontManager.h"
#include "Position.h"
#include "Room.h"

#include <array>

namespace Data = CQ::Data;
namespace Render = CQ::Render;

namespace CQ::Map
{
  class Map
  {
  public:
    Map();
    
    void display(Render::SDLRenderer& renderer, TTF_Font* font, const Data::Position& playerPos);
    
  private:
    std::array<std::array<Room  , 4>, 4> m_rooms;
  };
} // namespace
