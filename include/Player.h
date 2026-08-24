#pragma once

#include "Inventory.h"
#include "Position.h"

namespace CQ::Data
{
  class Player
  {
  public:
    Player();
    
    int getEnergy() const;
    bool spendEnergy(int amount_ = 1);
    void resetEnergy();
    bool isOutOfEnergy();
    
    int getJobSecurity() const;
    void takeDamage(int damage_);
    void heal(int amount_);
    bool isFired();
    
    int getMaxJobSecurity() const;
    void increaseMaxJobSecurity(int amount_ = 1);
    
    void recordWork();
    bool workedCorrectlyToday();
    void resetDailyWork();
    int getHoursWorkedToday() const;
    
    void incrementDaysWorked();
    int getDaysWorked() const;
    bool hasRetired();
    int getAge();
    
    const Position& getPosition() const;
    void setPosition(const Position& newPosition_);
    
    Inventory& getInventory();
    
  private:
    const int m_maxEnergy {8};
    const int m_maxHoursWorkedToday {8};
    const int m_minViableWorkTime {4};
    const int m_daysRequiredForRetirement {11745};
    const int m_workingDaysPerYear {261};
    const int m_startingAge {20};
    
    int m_energy {m_maxEnergy};
    int m_jobSecurity {10};
    int m_maxJobSecurity {10};
    int m_hoursWorkedToday {0};
    int m_daysWorked {0};
    
    Position m_position;
    Inventory m_inventory;
    
  }; // class Player
} // namespace
