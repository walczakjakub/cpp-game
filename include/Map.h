#pragma once

#include "SDLRenderer.h"
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
    
    void generate();
    
    // How big one grid cell will be for a given window. Static because it
    // needs no Map object - it is pure arithmetic on the window size. Exposed
    // so callers can size text to match without duplicating the layout maths.
    static int cellSizeFor(int windowWidth, int windowHeight);
    
    // Width of the screen region the map draws in. Everything to the right of
    // this is free for the menu and HUD.
    static int mapAreaWidth(int windowWidth);
    
    void display(Render::SDLRenderer& renderer, TTF_Font* font, const Data::Position& playerPos);
    
    void discoverRoom(const Data::Position& roomPosition);
    
    const Data::Position& getPlayerOfficePosition() const;
    
    Room getRoomAt(const Data::Position& roomPosition) const;
    
  private:
    std::array<std::array<Room  , 4>, 4> m_rooms;
    
    Data::Position m_playerOfficePosition;
  };
} // namespace
