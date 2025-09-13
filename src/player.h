#ifndef PLAYER_H
#define PLAYER_H

#include "core/actor.h"
#include "affiliate/sprite_animation.h"
#include "raw/timer.h"
#include "world/effect.h"
#include "weapon_thunder.h"

class Player : public Actor {
public:
    virtual void init() override;
    virtual bool handleEvents(SDL_Event& event) override;
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void clean() override;
    virtual void takeDamage(float damage) override;
public:
    void keyboardControl();
    void syncCamera();
    void checkState();
    void changeState(bool moving);
    void checkIsDead();
private:
    SpriteAnimation* sprite_idle_ = nullptr;
    SpriteAnimation* sprite_move_ = nullptr;
    Effect* effect_ = nullptr;
    WeaponThunder* weaponThunder_ = nullptr;
    Timer* flashTimer_ = nullptr;
    bool is_moving_ = false;
};

#endif // PLAYER_H