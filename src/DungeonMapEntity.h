#ifndef DUNGEONMAPENTITY_H
#define DUNGEONMAPENTITY_H

#include "sfml_game/GameEntity.h"
#include "sfml_game/TileMapEntity.h"
#include "DungeonMap.h"

struct displayEntityStruct
{
  bool moving;
  int frame;
  float x;
  float y;
  Vector2D velocity;
  float scale;
  float initialScale;
  float age;
  float lifetime;
  cpp3ds::Color color;
};

class DungeonMapEntity : public GameEntity
{
public:
  DungeonMapEntity();
  virtual void animate(float delay);
  virtual void render(cpp3ds::RenderTarget* app);
  void renderDoors(cpp3ds::RenderTarget* app);
  void renderKeyStone(cpp3ds::RenderTarget* app);
  void renderPost(cpp3ds::RenderTarget* app);
  void renderOverlay(cpp3ds::RenderTarget* app);

  void refreshMap();

  /*!
   *  \brief Generates blood particle
   *
   *  \param x : x position of the blood
   *  \param y : y position of the blood
   *  \param bloodColor : color of the blood (red; green, ...)
   */
  displayEntityStruct& generateBlood(float x, float y, BaseCreatureEntity::enumBloodColor bloodColor);

  void addBlood(float x, float y, int frame, float scale);
  void addCorpse(float x, float y, int frame);

  displayEntityStruct& generateBoltParticle(float x, float y, Vector2D velocity, bool back, int frame, float scale, float lifetime);

  std::vector <displayEntityStruct> getBlood();
  std::vector <displayEntityStruct> getCorpses();
  void computeBoltParticulesVertices();

  void activateKeyRoomEffect();

private:
  cpp3ds::VertexArray vertices;
  cpp3ds::VertexArray overVertices;
  cpp3ds::VertexArray shadowVertices;
  bool hasChanged;
  enum EnumShadowType { ShadowTypeStandard, ShadowTypeCorner, ShadowTypeMedium, ShadowTypeSmall };
  EnumShadowType shadowType;

  cpp3ds::VertexArray bloodVertices;
  cpp3ds::VertexArray corpsesVertices;
  cpp3ds::VertexArray corpsesLargeVertices;
  cpp3ds::VertexArray boltParticlesVertices;
  cpp3ds::VertexArray backBoltParticlesVertices;

  bool getChanged();
  void computeVertices();
  void computeOverVertices();
  void computeShadowVertices();
  void computeBloodVertices();
  void computeCorpsesVertices();

  void computeDoors();

  bool shouldBeTransformed(int part);

  void animateParticle(displayEntityStruct &particle, float delay, float viscosity);
  bool collideWithWall(displayEntityStruct &particle, int boxWidth, int boxHeight, bool canGoThroughObstacle = false);
  void autoSpeed(displayEntityStruct &particle, float speed);
  bool checkFalling(displayEntityStruct &particle, int boxWidth, int boxHeight);

  void displayBlood(cpp3ds::RenderTarget* app);
  void displayCorpses(cpp3ds::RenderTarget* app);
  void displayBoltParticles(cpp3ds::RenderTarget* app);

  std::vector<displayEntityStruct> blood;
  std::vector<displayEntityStruct> boltParticles;
  std::vector<displayEntityStruct> backBoltParticles;
  std::vector<displayEntityStruct> corpses;
  std::vector<displayEntityStruct> corpsesLarge;

  bool collide[4];
  enum enumCollisionDirection
  {
    NordWest,
    NordEast,
    SudWest,
    SudEast
  };

  cpp3ds::Sprite overlaySprite;
  cpp3ds::Sprite randomSprite[NB_RANDOM_TILES_IN_ROOM];
  roomTypeEnum roomType;

  cpp3ds::Sprite doorShadow[4];
  bool isDoorShadow[4];
  cpp3ds::Sprite doorWall[4];
  bool isDoorWall[4];
  cpp3ds::Sprite doorFrame[4];
  bool isDoorFrame[4];
  cpp3ds::Sprite doorKeyStone[4];
  bool isDoorKeyStone[4];
  cpp3ds::Sprite doorSpecial;
  bool isDoorSpecial;

  struct structKeyRoomFX
  {
    float delay;
    int amplitude;
    bool isBlinking;
  } keyRoomEffect;
};

class DungeonMapEntityPost : public GameEntity
{
public:
  DungeonMapEntityPost(DungeonMapEntity* parent);
  virtual void animate(float delay);
  virtual void render(cpp3ds::RenderTarget* app);
private:
  DungeonMapEntity* parent;
};

class DungeonMapEntityOverlay: public GameEntity
{
public:
  DungeonMapEntityOverlay(DungeonMapEntity* parent);
  virtual void animate(float delay);
  virtual void render(cpp3ds::RenderTarget* app);
private:
  DungeonMapEntity* parent;
};
#endif // DUNGEONMAPENTITY_H
