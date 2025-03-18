#include "pch.h"
#include "AABBCollider.h"

AABBCollider::AABBCollider(Entity* entity, float xMin, float yMin, float width, float height) : Collider2D(entity)
{
    mColliderType = ColliderType::AABB;
    mWidth = width;
    mHeight = height;
    mXMin = xMin;
    mYMin = yMin;
}
