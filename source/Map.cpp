#include "Map.h"
#include "colors.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <array>
#include <algorithm>
#include <random>
#include <utility>

namespace Render = CQ::Render;
namespace Data = CQ::Data;
namespace Colors = CQ::Colors;

namespace CQ::Map
{
  Map::Map()
  {
    generate();
  }
  
  void Map::generate()
  {
    std::array<RoomType, 16> rooms
    {
      RoomType::PARKING_LOT,
      RoomType::PLAYER_OFFICE,
      RoomType::BOSS_OFFICE,
      RoomType::BREAK_ROOM,
      RoomType::MALE_RESTROOM,
      RoomType::FEMALE_RESTROOM,
      RoomType::CAFETERIA,
      RoomType::ARCHIVES,
      RoomType::COPY_ROOM,
      RoomType::IT_ROOM,
      RoomType::HR,
      RoomType::EARL_OFFICE,
      RoomType::EUGENE_OFFICE,
      RoomType::MILDRED_OFFICE,
      RoomType::MURIEL_OFFICE,
      RoomType::DAKOTA_OFFICE
    };
    
    // randomize the order of rooms
    std::random_device random_device;
    std::mt19937 engine(random_device());
    
    std::shuffle(rooms.begin(), rooms.end(), engine);
    
    // move parking lot to a corner
    std::uniform_int_distribution<int> distribution(0, 3);
    int randomCornerIndex = distribution(engine);
    
    std::array<int, 4> corners
    {
      0,  // top left
      3,  // top right
      12, // bottom left
      15  // bottom right
    };
    
    int parkingLotIndex {0};
    
    for (int i {0}; i < 16; ++i)
    {
      if (rooms[i] == RoomType::PARKING_LOT)
      {
        parkingLotIndex = i;
        break;
      }
    }
    
    std::swap(rooms[corners[randomCornerIndex]], rooms[parkingLotIndex]);
    
    // map rooms to the grid
    int roomIndex {0};
    
    for (int row = 0; row < 4; ++row)
    {
      for (int col = 0; col < 4; ++col)
      {
        m_rooms[row][col].type = rooms[roomIndex];
        if (m_rooms[row][col].type == RoomType::PLAYER_OFFICE)
        {
          m_playerOfficePosition = {row, col};
          m_rooms[row][col].discovered = true;
        } else {
          m_rooms[row][col].discovered = false;
        }
        
        ++roomIndex;
      }
    }
  } // generate()
  
  int Map::mapAreaWidth(int windowWidth)
  {
    return windowWidth * 2 / 3;
  } // mapAreaWidth()
  
  int Map::cellSizeFor(int windowWidth, int windowHeight)
  {
    // The map occupies the left two thirds of the screen; the remaining third
    // is for the movement menu and the rest of the HUD. The grid stays square,
    // so it is limited by whichever runs out first - that width or the height.
    const int gridWidth = std::min(mapAreaWidth(windowWidth) * 85 / 100,
                                   windowHeight * 75 / 100);
    
    return gridWidth / 4;
  } // cellSizeFor()
  
  void Map::display(Render::SDLRenderer& renderer, TTF_Font* font, const Data::Position& playerPos)
  {
    // Grid settings, sized from the actual window rather than fixed pixels so
    // the map scales sensibly whatever resolution we are running at.
    const int windowWidth = renderer.getWidth();
    const int windowHeight = renderer.getHeight();
    
    const int cellSize = cellSizeFor(windowWidth, windowHeight);
    
    // Centred within the map area
    const int gridStartX = (mapAreaWidth(windowWidth) - cellSize * 4) / 2;
    const int gridStartY = (windowHeight - cellSize * 4) / 2;
    const int padding = 0;       // No space between cells
    
    // Get the raw SDL_Renderer for drawing rectangles
    SDL_Renderer* sdlRenderer = renderer.getRenderer();
    
    // Draw the 4x4 grid
    for (int row = 0; row < 4; ++row)
    {
      for (int col = 0; col < 4; ++col)
      {
        // Calculate position for this cell
        int x = gridStartX + col * (cellSize + padding);
        int y = gridStartY + row * (cellSize + padding);
        
        // Create rectangle for this cell
        SDL_Rect cellRect;
        cellRect.x = x;
        cellRect.y = y;
        cellRect.w = cellSize;
        cellRect.h = cellSize;
        
        // Check if this is the player's position
        bool isPlayerHere = (row == playerPos.row && col == playerPos.col);
        
        // Set color based on player position
        if (isPlayerHere)
        {
          // Player's cell - filled orange
          SDL_SetRenderDrawColor(sdlRenderer, Colors::ORANGE.r, Colors::ORANGE.g, Colors::ORANGE.b, 255);
          SDL_RenderFillRect(sdlRenderer, &cellRect);
        }
        else
        {
          // Empty cell - orange outline only
          SDL_SetRenderDrawColor(sdlRenderer, Colors::ORANGE.r, Colors::ORANGE.g, Colors::ORANGE.b, 255);
          SDL_RenderDrawRect(sdlRenderer, &cellRect);
        }
        
        // Label the cell: room name once discovered, "?" until then
        const Room& room = m_rooms[row][col];
        const char* label = room.discovered ? roomTypeToString(room.type) : "?";
        
        // The player's cell is filled orange, so its text has to be black
        const SDL_Color& textColor = isPlayerHere ? Colors::BLACK : Colors::ORANGE;
        
        // Measure the label so we can centre it in the cell
        int textWidth = 0;
        int textHeight = 0;
        
        if (font != nullptr && TTF_SizeText(font, label, &textWidth, &textHeight) == 0)
        {
          renderer.renderText(label,
                              font,
                              textColor,
                              x + (cellSize - textWidth) / 2,
                              y + (cellSize - textHeight) / 2);
        }
      }
    }
  } // display()
  
  void Map::discoverRoom(const Data::Position& roomPosition)
  {
    if (!roomPosition.isValid())
    {
      return;
    }
    
    Room& room = m_rooms[roomPosition.row][roomPosition.col];
    room.discovered = true;
  } // discoverRoom()
  
  const Data::Position& Map::getPlayerOfficePosition() const
  {
    return m_playerOfficePosition;
  } // getPlayerOfficePosition
  
  Room Map::getRoomAt(const Data::Position& roomPosition) const
  {
    return m_rooms[roomPosition.row][roomPosition.col];
  } // getRoomAt()

  
} // namespace

