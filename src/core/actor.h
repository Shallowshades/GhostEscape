#ifndef ACTOR_H
#define ACTOR_H

#include "object_world.h"

class Stats;
class AffiliateBar;

class Actor : public ObjectWorld {
public:
    virtual void update(float delta) override;
    virtual void takeDamage(float amount);
public:
    // getters and setters
    glm::vec2 getVelocity() const { return velocity_; }
    void setVelocity(const glm::vec2& velocity) { velocity_ = velocity; }
    float getMaxSpeed() const { return max_speed_; }
    void setMaxSpeed(float max_speed) { max_speed_ = max_speed; }
    Stats* getStats() const { return stats_; }
    void setStats(Stats* stats) { stats_ = stats; }
    AffiliateBar* getHealthBar() { return healthBar_; }
    void setHealthBar(AffiliateBar* healthBar) { healthBar_ = healthBar; }
public:
    // logic
    bool isAlive() const;
    void move(float deltaTime);
private:
    void updateHealthBar();
protected:
    glm::vec2 velocity_ = glm::vec2(0, 0);
    float max_speed_ = 100.0f;
    Stats* stats_ = nullptr; // character stats
    AffiliateBar* healthBar_ = nullptr;
};

#endif // ACTOR_H