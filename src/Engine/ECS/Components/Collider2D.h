#pragma once
#include "Component.h"
#include "Colliders/CollisionManifold.h"
#include "Colliders/SpatialGrid.h"

struct PhysicsMaterial;

class Collider2D : public Component
{
public:
    
    enum class ColliderType : uint8_t
    {
        AABB,
        CIRCLE,
        OBB,

        COLLIDER_COUNT
    };

    
    static constexpr int BITMASK = 1 << 8;
    Collider2D(Entity* entity);
    void SetOrigin(sf::Vector2f newPos) { mOrigin = newPos; }
    void SetType(ColliderType nType) { mColliderType = nType; }
    void SetLastGridPosition(const CellCoords& newPosition) { mLastGridPosition = newPosition; }
    void SetTrigger(bool trig) { mIsTrigger = trig;}
    void SetStatic(bool stat) { mIsStatic = stat; }
    
#pragma region Getters

    bool IsTrigger() const { return mIsTrigger; }
    bool IsStatic() const { return mIsStatic; }
    sf::Vector2f GetOrigin() const { return mOrigin; }
    int GetBitmask() override;
    ColliderType GetColliderType() const { return mColliderType; }
    CellCoords GetLastGridPosition() const {return mLastGridPosition; }
    sf::Shape* GetShape() const { return mpShape; }
#pragma endregion
    
#pragma region CollisionManifold Generation
    
    CollisionManifold Intersects(Collider2D* Collider);
    
    CollisionManifold CheckCollisionCircleCircle(Collider2D* Collider);
    CollisionManifold CheckCollisionBoxBox(Collider2D* BoxCollider);
    CollisionManifold CheckCollisionCircleBox(Collider2D* Collider2);
    
#pragma endregion

    
protected:
    bool mIsTrigger;
    bool mIsStatic;
    sf::Vector2f mOrigin;
    CellCoords mLastGridPosition;
    ColliderType mColliderType;
    sf::Shape* mpShape;
};
