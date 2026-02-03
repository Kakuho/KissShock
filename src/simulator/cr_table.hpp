#pragma once
  
//  collision resolution table
//  users can add custom resolution functions to the table
//
//-----------------------------------------------------------------------------------------
//
//  Example:
//    Suppose you're creating pong,
//    You will define at least 5 Bodies:
//      * Ball
//      * Wall
//      * Paddle
//      * Paddle
//      * ScoringWall
//
//    Each of these bodies type will have a static member ID which will indicate its type. The
//    user of the engine must define this ID, either at runtime or compile time
//
//    To register a entity to the system:
//    
//      CRTbl.RegisterBodyType(Id)
//
//    By default a user body will be given the default collision resolution handler which assumes the body is a newtonian body.
//    If the user wants a body to be static then they can perform the following:
//
//      CRTbl.MakeStatic(Id)
//
//    Now its collision resolution function does nothing.
//
//    If the user wants customised behaviour for collision handling, they can use register a new collision handler like
//    so:
//      
//      CRTable.RegisterCollisionHandler(Id of the type of the object, Id of the type of the collided object,
//      CollisionHandler)
//
//-----------------------------------------------------------------------------------------
//
//  Implementation:
//    
//    For now the collision resolution table is an adjacency list like so:
//      
//      hashmap of hashmap of CRs
//      h_0[bid_0]  -> h_bid_0[0] -> crHandler
//      h_0[bid_1]  -> h_bid_1[0] -> crHandler
//      h_0[bid_2]  -> h_bid_2[0] -> crHandler
//      h_0[bid_3]  -> h_bid_3[0] -> crHandler
//  
//    The first index indicates the body, src, to be acted upon, it is this body whose state will change
//    The second index indicates  the body, other, which the original body has acted upon. Their state will not change
//    The CRHandler is the collision resolution handler for src when it collides with other

#include <map>

#include "body.hpp"

namespace KissShock{
  class CRTable{
    using CollisionResolutionF = void(Body& b1);
    using BodyId = int;
    public:
      void RegisterBody(BodyId bid);
      void MakeStatic(BodyId bid);
      void RegisterCollisionHandler(BodyId srcid, BodyId otherid, CollisionResolutionF f);

    private:
      std::map<BodyId, std::map<BodyId, CollisionResolutionF>> m_table;
  };
}
