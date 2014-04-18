#include "EvilFlowerEntity.h"
#include "BoltEntity.h"
#include "EnnemyBoltEntity.h"
#include "PlayerEntity.h"
#include "sfml_game/SpriteEntity.h"
#include "sfml_game/ImageManager.h"
#include "sfml_game/SoundManager.h"
#include "Constants.h"
#include "WitchBlastGame.h"
#include <math.h>

EvilFlowerEntity::EvilFlowerEntity(float x, float y, GameMap* map, PlayerEntity* player)
    : EnnemyEntity (ImageManager::getImageManager()->getImage(IMAGE_FLOWER), x, y, map)
{
  hp = EVIL_FLOWER_HP;
  meleeDamages = EVIL_FLOWER_MELEE_DAMAGES;

  setSpin(50.0f);
  frame = 0;

  type = 23;
  bloodColor = bloodGreen;
  //shadowFrame = 2;

  fireDelay = EVIL_FLOWER_FIRE_DELAY;
  this->player = player;
  age = -1.0f + (rand() % 2500) * 0.001f;
}

void EvilFlowerEntity::animate(float delay)
{
  if (fireDelay < 0.7f) setSpin(500.0f);
  else if (fireDelay < 1.4f) setSpin(120.0f);
  else setSpin(50.0f);

  EnnemyEntity::animate(delay);
  angle += spin * delay;

  if (age > 0.0f)
  {
    fireDelay -= delay;
    if (fireDelay <= 0.0f)
    {
      fireDelay = EVIL_FLOWER_FIRE_DELAY;
      fire();
    }
  }
}

void EvilFlowerEntity::calculateBB()
{
    boundingBox.left = (int)x - width / 2 + EVIL_FLOWER_BB_LEFT;
    boundingBox.width = width - EVIL_FLOWER_BB_WIDTH_DIFF;
    boundingBox.top = (int)y - height / 2 + EVIL_FLOWER_BB_TOP;
    boundingBox.height =  height - EVIL_FLOWER_BB_HEIGHT_DIFF;
}

void EvilFlowerEntity::dying()
{
  isDying = true;
  SpriteEntity* deadFlower = new SpriteEntity(ImageManager::getImageManager()->getImage(IMAGE_CORPSES), x, y, 64, 64);
  deadFlower->setZ(OFFSET_Y);
  deadFlower->setFrame(FRAME_CORPSE_FLOWER);
  deadFlower->setType(TYPE_CORPSE);

  for (int i = 0; i < 4; i++) parentGame->generateBlood(x, y, bloodColor);
  drop();
  SoundManager::getSoundManager()->playSound(SOUND_ENNEMY_DYING);
}

void EvilFlowerEntity::fire()
{
    SoundManager::getSoundManager()->playSound(SOUND_BLAST_FLOWER);
    EnnemyBoltEntity* bolt = new EnnemyBoltEntity
          (ImageManager::getImageManager()->getImage(IMAGE_BOLT), x, y + 10);
    bolt->setFrame(1);
    bolt->setMap(map, TILE_WIDTH, TILE_HEIGHT, OFFSET_X, OFFSET_Y);

    bolt->setVelocity(Vector2D(200.0f, 0.0f));

    float tan = (player->getX() - x) / (player->getY() - y);
    float angle = atan(tan);

    if (player->getY() > y)
      bolt->setVelocity(Vector2D(sin(angle) * EVIL_FLOWER_FIRE_VELOCITY,
                                 cos(angle) * EVIL_FLOWER_FIRE_VELOCITY));
    else
      bolt->setVelocity(Vector2D(-sin(angle) * EVIL_FLOWER_FIRE_VELOCITY,
                                 -cos(angle) * EVIL_FLOWER_FIRE_VELOCITY));
}

void EvilFlowerEntity::render(sf::RenderWindow* app)
{
    sprite.setPosition(x, y);
    float savedAngle = sprite.getRotation();
    sprite.setRotation(0.0f);

    // shadow
    sprite.setTextureRect(sf::IntRect(width * 2, 0,  width, height));
    app->draw(sprite);
    sprite.setTextureRect(sf::IntRect(width, 0,  width, height));
    app->draw(sprite);

    sprite.setRotation(savedAngle);
    EnnemyEntity::render(app);
}
