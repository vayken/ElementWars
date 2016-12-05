#ifndef PHYSICPARAM_H
#define PHYSICPARAM_H
#define CLIPPED 0
#define NO_CLIPPED 1
#define ENHANCED_SPEED 2
#define NPC_PATHWAY 3


class PhysicParam
{
    public:
        PhysicParam();
        PhysicParam(int physicId);
        void    setPhysicId(int physicId);
        int     getPhysicId();
    protected:
    private:
        int m_physicId;
};

#endif // PHYSICPARAM_H
