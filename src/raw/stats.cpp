#include "stats.h"

Stats* Stats::addStatsChild(Actor* parent, float maxHealth, float maxMana, float damage, float manaRegen) {
    Stats* stats = new Stats();
    stats->setParent(parent);
    stats->setMaxHealth(maxHealth);
    stats->setHealth(maxHealth);
    stats->setMaxMana(maxMana);
    stats->setMana(maxMana);
    stats->setDamage(damage);
    stats->setManaRegen(manaRegen);
    parent->addChild(stats);
    return stats;
}

void Stats::update(float deltaTime) {
    Object::update(deltaTime);
    regenMana(deltaTime);
    if (isInvincible_) {
        invincibilityTimer_ += deltaTime;
        if (invincibilityTimer_ >= invincibilityTime_) {
            isInvincible_ = false;
            invincibilityTimer_ = 0.0f;
        }
    }
}

bool Stats::canUseMana(float amount) const {
    return mana_ >= amount;
}

void Stats::useMana(float amount) {
    mana_ -= amount;
    if (mana_ < 0) {
        mana_ = 0;
    }
}

void Stats::regenMana(float deltaTime) {
    if (isAlive_) {
        mana_ += manaRegen_ * deltaTime;
        if (mana_ > maxMana_) {
            mana_ = maxMana_;
        }
    }
}

void Stats::takeDamage(float amount) {
    if (isInvincible_) {
        return; // cannot damage
    }
    health_ -= amount;
    if (health_ <= 0) {
        health_ = 0;
        isAlive_ = false;
    }
    isInvincible_ = true;
    invincibilityTimer_ = 0.0f; // reset invincibility timer
}
