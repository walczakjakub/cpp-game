#include "GameState.h"
#include "Menu.h"
#include "strings.h"

#include <iostream>

namespace CQ::State {
  // TODO: Rewrite these functions for SDL rendering
  // Currently commented out to avoid terminal dependencies
  
  GameState openMainMenu()
  {
    
    
    // Temporary: just return to main menu
    std::cout << "[Main menu will be implemented with SDL]" << std::endl;
    return GameState::MAIN_MENU;
  }

  GameState startGame()
  {
    
    
    // Temporary: just return to main menu
    std::cout << "[Game start will be implemented with SDL]" << std::endl;
    return GameState::MAIN_MENU;
  }
}

