#include "Player.h"

namespace CQ::Data {
  Player::Player()
  {
  }
  
  // Energy
  int Player::getEnergy() const
  {
    return m_energy;
  }
  
  bool Player::spendEnergy(int amount_)
  {
    if (m_energy >= amount_)
    {
      m_energy -= amount_;
      return true;
    }
    else
    {
      return false;
    }
    
    
  }

  void Player::resetEnergy()
  {
    m_energy = m_maxEnergy;
  }
  
  bool Player::isOutOfEnergy()
  {
    return m_energy <= 0;
  }
  
  //Job security
  int Player::getJobSecurity() const
  {
    return m_jobSecurity;
  }
  
  void Player::takeDamage(int damage_)
  {
    if (m_jobSecurity <= damage_)
    {
      m_jobSecurity = 0;
    }
    else
    {
      m_jobSecurity -= damage_;
    }
  }
  
  void Player::heal(int amount_)
  {
    if (m_jobSecurity + amount_ >= m_maxJobSecurity)
    {
      m_jobSecurity = m_maxJobSecurity;
    }
    else
    {
      m_jobSecurity += amount_;
    }
  }

  bool Player::isFired()
  {
    return m_jobSecurity <= 0;
  }
  
  int Player::getMaxJobSecurity() const
  {
    return m_maxJobSecurity;
  }
  
  void Player::increaseMaxJobSecurity(int amount_)
  {
    m_maxJobSecurity += amount_;
    m_jobSecurity += amount_;
  }
  
  // Work tracking
  void Player::recordWork()
  {
    if (m_hoursWorkedToday < m_maxHoursWorkedToday)
    {
      m_hoursWorkedToday += 1;
    }
  }
  
  bool Player::workedCorrectlyToday()
  {
    return m_hoursWorkedToday >= m_minViableWorkTime;
  }
  
  void Player::resetDailyWork()
  {
    m_hoursWorkedToday = 0;
  }
  
  int Player::getHoursWorkedToday() const
  {
    return m_hoursWorkedToday;
  }
  
  // Age tracking
  void Player::incrementDaysWorked()
  {
    m_daysWorked += 1;
  }
  
  int Player::getDaysWorked() const
  {
    return m_daysWorked;
  }
  
  bool Player::hasRetired()
  {
    return m_daysWorked >= m_daysRequiredForRetirement;
  }
  
  int Player::getAge()
  {
    return m_startingAge + (m_daysWorked / m_workingDaysPerYear);
  }
  
  // Position
  const Position& Player::getPosition() const
  {
    return m_position;
  }
  
  void Player::setPosition(const Position& newPosition_)
  {
    if (newPosition_.isValid())
    {
      m_position = newPosition_;
    }
  }
  
  // Inventory
  Inventory& Player::getInventory()
  {
    return m_inventory;
  }

}
