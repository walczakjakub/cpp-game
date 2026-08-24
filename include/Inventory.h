#pragma once

#include <array>

namespace CQ::Data
{
  enum class EvidenceTier
  {
    NONE = 0,
    RUMOR = 1,
    LOCATION = 2,
    EVIDENCE = 3
  };
  
  class Inventory
  {
    public:
    Inventory(); // constructor
    
    bool upgradeEvidence(int index_);
    EvidenceTier getEvidenceTier(int index_) const;
    int getTotalEvidenceDamage() const;
    
    private:
    bool isValidIndex(int index_) const;
    std::array<EvidenceTier, 5> m_evidence;
    int m_workEvals;
  }; // class Inventory
} // namespace
