#include "Inventory.h"

namespace CQ::Data
{
  Inventory::Inventory() : m_workEvals(0)
  {
    for (EvidenceTier &evidencePiece : m_evidence)
    {
      evidencePiece = EvidenceTier::NONE;
    }
  }
  
  bool Inventory::isValidIndex(int index_) const
  {
    return index_ >= 0 && index_ <= 4;
  }
  
  bool Inventory::upgradeEvidence(int index_)
  {
    if (!isValidIndex(index_))
    {
      return false;
    }
    
    if (m_evidence[index_] != EvidenceTier::EVIDENCE)
    {
      int currentTier = static_cast<int>(m_evidence[index_]);
      int newTier = currentTier + 1;
      m_evidence[index_] = static_cast<EvidenceTier>(newTier);
      return true;
    }
    else
    {
      return false;
    }
  }
  
  EvidenceTier Inventory::getEvidenceTier(int index_) const
  {
    if (!isValidIndex(index_))
    {
      return EvidenceTier::NONE;
    }
    
    return m_evidence[index_];
  }
  
  int Inventory::getTotalEvidenceDamage() const
  {
    int totalEvidenceDamage {0};
    
    for (const EvidenceTier &evidencePiece : m_evidence)
    {
      switch (evidencePiece) {
        case EvidenceTier::NONE:
          break;
        case EvidenceTier::RUMOR:
          totalEvidenceDamage += 1;
          break;
        case EvidenceTier::LOCATION:
          totalEvidenceDamage += 2;
          break;
        case EvidenceTier::EVIDENCE:
          totalEvidenceDamage += 5;
          break;
        default:
          break;
      }
    }
    
    return totalEvidenceDamage;
  }
} // namespace
