#pragma once

#include "simulator/body.hpp"

using namespace KissShock;

class TestBody: public KissShock::Body{

  public:
    TestBody(Vec2<int> topleft, Vec2<int> initialVel, Collision::Type coltype, std::size_t width, std::size_t height):
      Body{topleft, initialVel, coltype, width, height}
    {

    }

    virtual void Simulate(){/* empty simulation function*/ } 

    void SetPos(KissShock::Vec2<int> pos){
      m_pos = pos;
    }

    static void SetId(std::size_t val){ Id = val;}
    virtual std::size_t EntityId() const override{ return Id;}
    std::size_t GetId(){ return Id;}

    static std::size_t Id;
  private:
};

class TestBody1: public KissShock::Body{

  public:
    TestBody1(Vec2<int> topleft, Vec2<int> initialVel, Collision::Type coltype, std::size_t width, std::size_t height):
      Body{topleft, initialVel, coltype, width, height}
    {

    }

    virtual void Simulate(){/* empty simulation function*/ } 

    void SetPos(KissShock::Vec2<int> pos){
      m_pos = pos;
    }

    static void SetId(std::size_t val){ Id = val;}
    virtual std::size_t EntityId() const override{ return Id;}
    std::size_t GetId(){ return Id;}

    static std::size_t Id;
  private:
};

class TestBody2: public KissShock::Body{

  public:
    TestBody2(Vec2<int> topleft, Vec2<int> initialVel, Collision::Type coltype, std::size_t width, std::size_t height):
      Body{topleft, initialVel, coltype, width, height}
    {

    }

    virtual void Simulate(){/* empty simulation function*/ } 

    void SetPos(KissShock::Vec2<int> pos){
      m_pos = pos;
    }

    static void SetId(std::size_t val){ Id = val;}
    virtual std::size_t EntityId() const override{ return Id;}
    std::size_t GetId(){ return Id;}

    static std::size_t Id;
  private:
};
