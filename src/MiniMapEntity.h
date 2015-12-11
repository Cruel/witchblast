#ifndef MINIMAPENTITY_H
#define MINIMAPENTITY_H

#include "sfml_game/TileMapEntity.h"

class MiniMapEntity : public TileMapEntity
{
  public:
    MiniMapEntity(cpp3ds::Texture* image, GameMap* gameMap, int tileWidth, int tileHeight, int tilesProLine);
    virtual ~MiniMapEntity();

    virtual void render(cpp3ds::RenderTarget* app);
    void display(cpp3ds::RenderTarget* app);
  protected:
  private:
};

#endif // MINIMAPENTITY_H
