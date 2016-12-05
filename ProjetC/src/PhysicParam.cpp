#include "PhysicParam.h"

PhysicParam::PhysicParam()
{

}

PhysicParam::PhysicParam(int physicId)
{
    this->m_physicId = physicId;
}

int PhysicParam::getPhysicId()
{
    return m_physicId;
}

void PhysicParam::setPhysicId(int physicId)
{
    this->m_physicId = physicId;
}
