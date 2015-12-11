#ifndef ARTEFACTDESCRIPTIONENTITY_H
#define ARTEFACTDESCRIPTIONENTITY_H

#include "sfml_game/SpriteEntity.h"
#include "ItemEntity.h"

class ArtefactDescriptionEntity : public SpriteEntity
{
  public:
    ArtefactDescriptionEntity(enumItemType);
    ~ArtefactDescriptionEntity();

    virtual void animate(float delay);
    virtual void render(cpp3ds::RenderTarget* app);
  private:
    cpp3ds::Sprite rectangle;

    std::string artefactName;
    std::string artefactDescription;
};
#endif // ARTEFACTDESCRIPTIONENTITY_H
