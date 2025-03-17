#include "pch.h"
#include "Collider2D.h"

#include "Colliders/CircleCollider.h"

Collider2D::Collider2D(Entity* entity) : Component(entity)
{
}

int Collider2D::GetBitmask()
{
    return BITMASK;
}

bool Collider2D::Intersects(Collider2D* Collider)
{
    switch (Collider2D.) {  }
}

bool Collider2D::CheckCollisionSphereSphere(Collider2D* Collider)
{
    CircleCollider collider1 = 
}
