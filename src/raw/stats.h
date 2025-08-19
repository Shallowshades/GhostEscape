#ifndef STATS_H
#define STATS_H

#include "../core/actor.h"

class Stats : public Object {
public:
    static Stats* addStatsChild(Actor* parent, float maxHealth = 100.0f, float maxMana = 100.0f, float damage = 40.0f, float manaRegen = 10.0f);

    virtual void update(float deltaTime) override;

    bool canUseMana(float amount) const;
    void useMana(float amount);
    void regenMana(float deltaTime);
    void takeDamage(float amount);

    // getter and setter
    float getHealth() const { return health_; }
    void setHealth(float health) { health_ = health; }
    float getMaxHealth() const { return maxHealth_; }
    void setMaxHealth(float maxHealth) { maxHealth_ = maxHealth; }
    float getMana() const { return mana_; }
    void setMana(float mana) { mana_ = mana; }
    float getMaxMana() const { return maxMana_; }
    void setMaxMana(float maxMana) { maxMana_ = maxMana; }
    float getDamage() const { return damage_; }
    void setDamage(float damage) { damage_ = damage; }
    float getManaRegen() const { return manaRegen_; }
    void setManaRegen(float manaRegen) { manaRegen_ = manaRegen; }
    bool isAlive() const { return isAlive_; }
    void setAlive(bool isAlive) { isAlive_ = isAlive; }
    bool isInvincible() const { return isInvincible_; }
    void setInvincible(bool isInvincible) { isInvincible_ = isInvincible; }
    Actor* getParent() const { return parent_; }
    void setParent(Actor* parent) { parent_ = parent; }

protected:
    Actor* parent_ = nullptr;
    float health_ = 100.0f;
    float maxHealth_ = 100.0f;
    float mana_ = 100.0f;
    float maxMana_ = 100.0f;
    float damage_ = 10.0f;
    float manaRegen_ = 10.0f;

    float invincibilityTime_ = 1.5f;
    float invincibilityTimer_ = 0.0f;
    bool isAlive_ = true;
    bool isInvincible_ = false;
};

#endif // STATS_H