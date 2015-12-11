#include "MiniMapEntity.h"

MiniMapEntity::MiniMapEntity(cpp3ds::Texture* image, GameMap* gameMap, int tileWidth, int tileHeight, int tilesProLine)
    : TileMapEntity(image, gameMap, tileWidth, tileHeight, tilesProLine)
{
  //ctor
}

MiniMapEntity::~MiniMapEntity()
{
  //dtor
}

void MiniMapEntity::render(cpp3ds::RenderTarget* app)
{
  // nothing
}

void MiniMapEntity::display(cpp3ds::RenderTarget* app)
{
  TileMapEntity::render(app);
}
