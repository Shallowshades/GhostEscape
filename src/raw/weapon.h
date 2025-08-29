#ifndef WEAPON_H
#define WEAPON_H

#include "../core/object.h"

class Spell;
class Actor;

class Weapon : public Object {
public:
    virtual void update(float delta) override;
    void attack(glm::vec2 position, Spell* spell);
    bool canAttack();
public:
    float getCoolDown() const { return coolDown_; }
    void setCoolDown(float coolDown) { coolDown_ = coolDown; }
    float getManaCost() const { return manaCost_; }
    void setManaCost(float manaCost) { manaCost_ = manaCost; }
    Actor* getParent() const { return parent_; }
    void setParent(Actor* parent) { parent_ = parent; }
protected:
    Actor* parent_ = nullptr;
    float coolDown_ = 1.f;
    float manaCost_ = 0.f;
    float coolDawnTimer_ = 0.f;
};

#endif // WEAPON_H