#pragma once
#include "Component.h"

class Collider2D : public Component
{
public:
    
    enum class ColliderType : uint8_t
    {
        AABB,
        Sphere,
        OBB,

        COLLIDER_COUNT
    };

    
    static constexpr int BITMASK = 1 << 7;
    Collider2D(Entity* entity);
    void SetCenter(sf::Vector2f newPos) { mCenter = newPos; }
    void SetType(ColliderType nType) { mColliderType = nType; }


#pragma region Getters
    
    int GetBitmask() override;
    ColliderType GetColliderType() const { return mColliderType; }
    
#pragma endregion
    
#pragma region CollisionCheck
    
    bool Intersects(Collider2D* Collider);

    bool CheckCollisionSphereSphere(Collider2D* Collider);
    bool CheckCollisionBoxBox(Collider2D* Collider);
    bool CheckCollisionSphereBox(Collider2D* Collider);
    
#pragma endregion

    
protected:
    sf::Vector2f mCenter;
    ColliderType mColliderType;
};
