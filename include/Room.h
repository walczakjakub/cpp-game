#pragma once

namespace CQ::Map {
  enum class RoomType
  {
    PARKING_LOT,
    PLAYER_OFFICE,
    BOSS_OFFICE,
    BREAK_ROOM,
    MALE_RESTROOM,
    FEMALE_RESTROOM,
    CAFETERIA,
    ARCHIVES,
    COPY_ROOM,
    IT_ROOM,
    HR,
    EMPLOYEE_1_OFFICE,
    EMPLOYEE_2_OFFICE,
    EMPLOYEE_3_OFFICE,
    EMPLOYEE_4_OFFICE,
    EMPLOYEE_5_OFFICE
  };
  
  struct Room
  {
    RoomType type;
    bool discovered;
  };
  
  // Short display labels, kept narrow enough to fit a 100px map cell.
  // Note there is deliberately no `default:` case — leaving it out means the
  // compiler warns you if a new RoomType is added and not handled here.
  // The trailing return only fires if someone casts a bogus int to RoomType.
  inline const char* roomTypeToString(RoomType type_)
  {
    switch (type_)
    {
      case RoomType::PARKING_LOT:       return "Parking";
      case RoomType::PLAYER_OFFICE:     return "My Desk";
      case RoomType::BOSS_OFFICE:       return "Boss";
      case RoomType::BREAK_ROOM:        return "Break";
      case RoomType::MALE_RESTROOM:     return "WC (M)";
      case RoomType::FEMALE_RESTROOM:   return "WC (F)";
      case RoomType::CAFETERIA:         return "Cafeteria";
      case RoomType::ARCHIVES:          return "Archives";
      case RoomType::COPY_ROOM:         return "Copy";
      case RoomType::IT_ROOM:           return "IT";
      case RoomType::HR:                return "HR";
      case RoomType::EMPLOYEE_1_OFFICE: return "Emp 1";
      case RoomType::EMPLOYEE_2_OFFICE: return "Emp 2";
      case RoomType::EMPLOYEE_3_OFFICE: return "Emp 3";
      case RoomType::EMPLOYEE_4_OFFICE: return "Emp 4";
      case RoomType::EMPLOYEE_5_OFFICE: return "Emp 5";
    }
    return "?";
  }
} // namespace
