#include "Core/Enum.hpp"

ComponentType operator|(ComponentType A, ComponentType B)
{
    return static_cast<ComponentType>(static_cast<unsigned long long int>(A) | static_cast<unsigned long long int>(B));
}

ComponentType operator&(ComponentType A, ComponentType B)
{
    return static_cast<ComponentType>(static_cast<unsigned long long int>(A) & static_cast<unsigned long long int>(B));
}

ComponentType operator^(ComponentType A, ComponentType B)
{
    return static_cast<ComponentType>(static_cast<unsigned long long int>(A) ^ static_cast<unsigned long long int>(B));
}

ComponentType operator~(ComponentType X)
{
    return static_cast<ComponentType>(~static_cast<unsigned long long int>(X));
}


CollisionMask operator|(CollisionMask A, CollisionMask B)
{
    return static_cast<CollisionMask>(static_cast<unsigned long long int>(A) | static_cast<unsigned long long int>(B));
}

CollisionMask operator&(CollisionMask A, CollisionMask B)
{
    return static_cast<CollisionMask>(static_cast<unsigned long long int>(A) & static_cast<unsigned long long int>(B));
}

CollisionMask operator^(CollisionMask A, CollisionMask B)
{
    return static_cast<CollisionMask>(static_cast<unsigned long long int>(A) ^ static_cast<unsigned long long int>(B));
}

CollisionMask operator~(CollisionMask X)
{
    return static_cast<CollisionMask>(~static_cast<unsigned long long int>(X));
}