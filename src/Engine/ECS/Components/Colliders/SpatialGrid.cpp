#include "pch.h"
#include "SpatialGrid.h"

#include "ECS/Components/Collider2D.h"

SpatialGrid::SpatialGrid(float cellSize, int minGridSizeX, int minGridSizeY, int maxGridSizeX, int maxGridSizeY)
    : mCellSize(cellSize), mMinX(minGridSizeX), mMinY(minGridSizeY),
      mMaxX(maxGridSizeX), mMaxY(maxGridSizeY), 
      mGridSizeX(maxGridSizeX - minGridSizeX), mGridSizeY(maxGridSizeY - minGridSizeY)
{
}

SpatialGrid::~SpatialGrid()
{
    for (auto& [coords, entities] : mCells)
    {
        for (Entity* entity : entities)
        {
            delete entity; 
        }
        entities.clear();
    }
    mCells.clear(); 
}


void SpatialGrid::UpdateEntity(Entity* entity)
{
    Collider2D* collider = entity->GetComponent<Collider2D>();
    if (!collider) return;

    auto newCoords = GetCellCoords(entity->GetTransform()->position.x,
                                   entity->GetTransform()->position.y);

    auto oldCoords = collider->GetLastGridPosition();

    if (oldCoords != newCoords)
    {
        auto& oldCell = mCells[oldCoords];
        oldCell.erase(std::remove(oldCell.begin(), oldCell.end(), entity), oldCell.end());

        if(oldCell.empty())
        {
            mCells.erase(oldCoords);
        }
        
        collider->SetLastGridPosition(newCoords);

        mCells[newCoords].push_back(entity);
    }
}

bool SpatialGrid::IsValidCell(const CellCoords& coords) const
{
    return coords.x >= mMinX && coords.x < mMaxX &&
           coords.y >= mMinY && coords.y < mMaxY;
}

CellCoords SpatialGrid::GetCellCoords(float x, float y) const
{
    return{
        static_cast<int>(x / mCellSize),
        static_cast<int>(y / mCellSize),
            };
}

void SpatialGrid::GetNeighboringEntities(int cellX, int cellY, std::vector<Entity*>& outEntities)
{
    outEntities.clear();
    
    for (int dx = -1; dx <= 1; dx++)
        {
        for (int dy = -1; dy <= 1; dy++)
            {
            for (int dz = -1; dz <= 1; dz++)
                {
                CellCoords coords = {cellX + dx, cellY + dy};
                if (IsValidCell(coords))
                    {
                    auto it = mCells.find(coords);
                    if (it != mCells.end())
                    {
                        outEntities.insert(outEntities.end(), it->second.begin(), it->second.end());
                    }
                }
            }
        }
    }
}

std::vector<Entity*> SpatialGrid::GetEntitiesInCell(int x, int y)
{
    CellCoords coords = {x, y};
    if (IsValidCell(coords))
    {
        return mCells[coords];
    }
    return {};
}