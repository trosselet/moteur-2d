#include "pch.h"
#include "Collider2D.h"

#include "ObjectFactory.h"
#include "Colliders/AABBCollider.h"
#include "Colliders/CircleCollider.h"
#include "PhysicsMaterial.h"


Collider2D::Collider2D(Entity* entity) : Component(entity)
{
    mColliderType = ColliderType::COLLIDER_COUNT;

    mCenter = entity->GetTransform()->position;
    mIsTrigger = false;
    mIsStatic = false;

    ObjectFactory::CreateComponent<PhysicsMaterial>(entity);
}

int Collider2D::GetBitmask()
{
    return BITMASK;
}

CollisionManifold Collider2D::Intersects(Collider2D* Collider)
{
    CollisionManifold manifold;
    ColliderType entity1 = this->GetColliderType();
    ColliderType entity2 = Collider->GetColliderType();

    switch(entity1)
    {
    case ColliderType::CIRCLE:
        if (entity2 == ColliderType::CIRCLE) return CheckCollisionCircleCircle(Collider);
        if (entity2 == ColliderType::AABB) return CheckCollisionCircleBox(Collider);
        break;

    case ColliderType::AABB:
        if (entity2 == ColliderType::CIRCLE) return CheckCollisionCircleBox(Collider);
        if (entity2 == ColliderType::AABB) return CheckCollisionBoxBox(Collider);
        break;
    }

    return manifold;
}

CollisionManifold Collider2D::CheckCollisionCircleCircle(Collider2D* Collider)
{
    CollisionManifold manifold;
    CircleCollider* CCollider1 = static_cast<CircleCollider*>(this);
    CircleCollider* CCollider2 = static_cast<CircleCollider*>(Collider);
    
    float a = CCollider1->mCenter.x - CCollider2->mCenter.x;
    float b = CCollider1->mCenter.y- CCollider2->mCenter.y;
    float c = (a * a) + (b * b);
    float radius = CCollider1->GetRadius() + CCollider2->GetRadius();
    if (radius * radius >= c)
    {
        manifold.hasCollision = true;

        manifold.collisionNormal = CCollider1->mCenter - CCollider2->mCenter;

        manifold.penetrationDepth = radius - c;
    }

    return manifold;
}

CollisionManifold Collider2D::CheckCollisionBoxBox(Collider2D* BoxCollider)
{
    AABBCollider* AABBCollider1 = static_cast<AABBCollider*>(this);
    AABBCollider* AABBCollider2 = static_cast<AABBCollider*>(BoxCollider);

    float minX1 = AABBCollider1->GetMinX();
    float maxX1 = AABBCollider1->GetWidth();
    float minY1 = AABBCollider1->GetMinY();
    float maxY1 = AABBCollider1->GetHeight();
    
    float minX2 = AABBCollider2->GetMinX();
    float maxX2 = AABBCollider2->GetWidth();
    float minY2 = AABBCollider2->GetMinY();
    float maxY2 = AABBCollider2->GetHeight();
    
    CollisionManifold manifold;
    
    bool toTheRight = minX1 > maxX2;
    bool toTheLeft = maxX1 < minX2;
    bool isAbove = minY1 > maxY2;
    bool isBelow = maxY1 < minY2;
    
    if (toTheRight || toTheLeft || isAbove || isBelow)
    {
        manifold.hasCollision = false;
        return manifold;
    }
    
    float overlapX = std::min(maxX1, maxX2) - std::max(minX1, minX2);
    float overlapY = std::min(maxY1, maxY2) - std::max(minY1, minY2);
    
    if (overlapX < overlapY)
    {
        manifold.collisionNormal = sf::Vector2f((minX1 < minX2) ? -1.0f : 1.0f, 0.0f);
        manifold.penetrationDepth = overlapX;
    }
    else
    {
        manifold.collisionNormal = sf::Vector2f(0.0f, (minY1 < minY2) ? -1.0f : 1.0f);
        manifold.penetrationDepth = overlapY;
    }
    
    manifold.hasCollision = true;
    return manifold;
}

CollisionManifold Collider2D::CheckCollisionCircleBox(Collider2D* Collider2)
{

    CollisionManifold manifold;
    
    AABBCollider* AABBCollider1 = static_cast<AABBCollider*>(this);
    CircleCollider* CCollider1 = static_cast<CircleCollider*>(Collider2);

    float testX = CCollider1->mCenter.x;
    float testY = CCollider1->mCenter.y;

    if (testX < AABBCollider1->GetMinX())
    {
        testX = AABBCollider1->GetWidth();
    }
    else if (testX > AABBCollider1->GetMinX() + AABBCollider1->GetWidth())
    {
        testX = AABBCollider1->GetMinX() + AABBCollider1->GetWidth();
    }

    if (testY < AABBCollider1->GetMinY())
    {
        testY = AABBCollider1->GetMinY();
    }
    else if (testY > AABBCollider1->GetMinY() + AABBCollider1->GetHeight())
    {
        testY = AABBCollider1->GetMinY() + AABBCollider1->GetHeight();
    }
    
    float x = testX - CCollider1->mCenter.x;
    float y = testY - CCollider1->mCenter.y;

    float distance = sqrt(x*x + y*y);
    
    if (distance <= CCollider1->GetRadius())
    {
        manifold.hasCollision = true;

        manifold.collisionNormal = sf::Vector2f(x / distance, y / distance);

        manifold.penetrationDepth = CCollider1->GetRadius() - distance;

        return manifold;
    }

    return manifold;
}


