#include "pch.h"
#include "Collider2D.h"

#include "ObjectFactory.h"
#include "Colliders/AABBCollider.h"
#include "Colliders/CircleCollider.h"
#include "PhysicsMaterial.h"

Collider2D::Collider2D(Entity* entity) : Component(entity)
{
    mColliderType = ColliderType::COLLIDER_COUNT;

    mOrigin = entity->GetTransform()->position;
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

sf::Vector2f Clamp(sf::Vector2f& value, sf::Vector2f minValue, sf::Vector2f maxValue)     
{
    value.x = std::clamp(value.x, minValue.x, maxValue.x);
    value.y = std::clamp(value.y, minValue.y, maxValue.y);
    
    return value;
}

CollisionManifold Collider2D::CheckCollisionCircleCircle(Collider2D* Collider) {
    CollisionManifold manifold;
    CircleCollider* CCollider1 = static_cast<CircleCollider*>(this);
    CircleCollider* CCollider2 = static_cast<CircleCollider*>(Collider);
    
    float a = CCollider1->mOrigin.x - CCollider2->mOrigin.x;
    float b = CCollider1->mOrigin.y - CCollider2->mOrigin.y;
    float c = (a * a) + (b * b); 
    float radiusSum = CCollider1->GetRadius() + CCollider2->GetRadius();

    if (c <= radiusSum * radiusSum)
    {  
        manifold.hasCollision = true;

        manifold.collisionNormal = (CCollider1->mOrigin - CCollider2->mOrigin).normalized();
        manifold.penetrationDepth = radiusSum - std::sqrt(c);
    }

    return manifold;
}


CollisionManifold Collider2D::CheckCollisionBoxBox(Collider2D* BoxCollider)
{
    AABBCollider* AABBCollider1 = static_cast<AABBCollider*>(this);
    AABBCollider* AABBCollider2 = static_cast<AABBCollider*>(BoxCollider);

    float minX1 = AABBCollider1->GetMinX();
    float maxX1 = AABBCollider1->GetMaxX();
    float minY1 = AABBCollider1->GetMinY();
    float maxY1 = AABBCollider1->GetMaxY();
    
    float minX2 = AABBCollider2->GetMinX();
    float maxX2 = AABBCollider2->GetMaxX();
    float minY2 = AABBCollider2->GetMinY();
    float maxY2 = AABBCollider2->GetMaxY();
    
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
    CircleCollider* circle;
    AABBCollider* box;
    
    if (Collider2->GetColliderType() == ColliderType::CIRCLE)
        {
        circle = static_cast<CircleCollider*>(Collider2);
        box = static_cast<AABBCollider*>(this);
    }
    else
    {
        circle = static_cast<CircleCollider*>(this);
        box = static_cast<AABBCollider*>(Collider2);
    }

    sf::Vector2f center = circle->GetOrigin();
    sf::Vector2f bHalfExtents = {box->GetMaxX() * 0.5f, box->GetMaxY() * 0.5f};
    sf::Vector2f bCenter = box->GetOrigin();

    sf::Vector2f diff = center - bCenter;
    
    sf::Vector2f clamp = Clamp(diff, -bHalfExtents, bHalfExtents);

    sf::Vector2f closestP = bCenter + clamp;

    diff = closestP - center;
    
    if (diff.length() <= circle->GetRadius())
    {
        manifold.hasCollision = true;
        if(diff.length() <= 1e-6f)
        {
            diff = center - clamp;
            manifold.collisionNormal = diff.normalized();
        }
        else
        {
            manifold.collisionNormal = diff.normalized();
        }
        
        manifold.penetrationDepth = diff.length();
    }

    return manifold;
}


