#include "cr_table.hpp"
#include <optional>

namespace KissShock{
  auto CRTable::GetNewId() -> BodyId{
    return m_currentId++;
  }

  auto CRTable::GetHandler(BodyId srcid, BodyId otherid) -> std::optional<CollisionResolutionF>{
    if(auto srctable = m_table.find(srcid); srctable != m_table.end()){
      auto handlerTable = srctable->second;
      if(auto handler = handlerTable.find(otherid); handler != handlerTable.end()){
        return handler->second;
      }
      else{
        return std::nullopt;
      }
    }
    else{
      return std::nullopt;
    }
  }
}
