#pragma once

namespace CQ::Data {
  struct Position
  {
    int row;
    int col;
    
    // Constructor
    Position() : row(0), col(0)
    {
    }
    
    // Constructor w/ params
    Position(int row_, int col_) : row(row_), col(col_)
    {
    }
    
    bool operator==(const Position& comparedPosition_) const
    {
      return row == comparedPosition_.row && col == comparedPosition_.col;
    }
    
    bool operator!=(const Position& comparedPosition_) const
    {
      return !(*this == comparedPosition_);
    }
    
    bool isValid() const
    {
      return row >= 0 && row < 4 && col >= 0 && col < 4;
    }
    
  }; // struct Position
} // namespace
