#include "cr_table.hpp"

namespace KissShock{
  auto CRTable::GetNewId() -> BodyId{
    return m_currentId++;
  }
}
