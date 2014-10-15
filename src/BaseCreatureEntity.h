#ifndef BASECREATUREENTITY_H
#define BASECREATUREENTITY_H

#include "sfml_game/CollidingSpriteEntity.h"
#include "TextEntity.h"
#include "Constants.h"

class BaseCreatureEntity : public CollidingSpriteEntity
{
  public:
    BaseCreatureEntity(sf::Texture* image, float x, float y, int spriteWidth, int spriteHeight);
    int getHp();
    int getHpMax();
    void setHp(int hp);
    void setHpMax(int hpMax);
    int getHpDisplay();
    float getCreatureSpeed();

    IntCoord getCurrentTile();

    virtual void animate(float delay);
    virtual float animateStates(float delay);
    virtual void animateColors(float delay);
    virtual void animateRecoil(float delay);
    virtual void animatePhysics(float delay);
    virtual void render(sf::RenderTarget* app);
    virtual void calculateBB();
    virtual bool collideWithMap(int direction);
    virtual int hurt(int damages, enumShotType hurtingType, int level, bool critical, int sourceType);
    virtual void prepareDying();
    virtual void dying();
    enum enumMovingStyle { movWalking, movFlying};
    virtual enumMovingStyle getMovingStyle();
    enum enumBloodColor { BloodNone = -1, BloodRed, BloodGreen, BloodRock, BloodEgg, BloodBubble};
    enum enumSpecialState
    {
      SpecialStateIce, // = 0
      SpecialStateSlow,
      SpecialStatePoison,

      NB_SPECIAL_STATES
    };
    enum enumStateResistance { ResistanceImmune, ResistanceVeryHigh, ResistanceHigh, ResistanceStandard, ResistanceLow, ResistanceVeryLow};
    struct specialStateStuct
    {
      enumSpecialState type;
      bool active;
      float timer;
      float param1;
      float param2;
      float param3;
    };
    specialStateStuct specialState[NB_SPECIAL_STATES];
    void setSpecialState(enumSpecialState state, bool active, float timer, float param1, float param2);

    enum enumResistances
    {
      ResistanceIce, // = 0
      ResistanceFire,
      ResistanceStone,
      ResistanceLightning,
      ResistanceIllusion,
      ResistancePoison,

      ResistanceRecoil,
      ResistanceFrozen,

      NB_RESISTANCES
    };
    enumStateResistance resistance[NB_RESISTANCES];

    bool isSpecialStateActive(enumSpecialState state);

    virtual void giveRecoil(bool stun, Vector2D velocity, float timer);
    virtual void inflictsRecoilTo(BaseCreatureEntity* targetEntity);
    virtual void computeFacingDirection();
    virtual void dyingFromAge();
    virtual bool canCollide();

  protected:
    int hp;
    int hpMax;
    int hpDisplay;
    float creatureSpeed;
    int shadowFrame;
    int facingDirection;
    float armor;

    bool canExplode;  // true if the monster can explode with a fire attack
    bool exploding;   // true if exploding

    bool hurting;
    float hurtingDelay;
    enumShotType hurtingType;
    enumBloodColor bloodColor;
    enumMovingStyle movingStyle;

    struct  recoilStruct
    {
      bool active;
      Vector2D velocity;
      bool stun;
      float timer;
    } recoil;

    void generateStar(sf::Color starColor);

  private:
    bool determineSatusChance(enumStateResistance resistance, int level);
    int determineDamageBonus(enumStateResistance resistance, int level);
    bool textTooClose(TextEntity* textEntity, float xDistMin, float yDistMin);
};

#endif // BASECREATUREENTITY_H
