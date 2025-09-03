#ifndef WEAPON_THUNDER_H
#define WEAPON_THUNDER_H

#include "raw/weapon.h"
#include "screen/hud_skill.h"

class WeaponThunder : public Weapon {
public:
    static WeaponThunder* addWeaponThunderChild(Actor* parent, float coolDown, float manaCost);
public:
    virtual void init() override;
    virtual void update(float delta) override;
    virtual void handleEvents(SDL_Event& event) override;
protected:
    HUDSkill* hudSkill_ = nullptr;
};

#endif // WEAPON_THUNDER_H