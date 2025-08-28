#ifndef SPELL_H
#define SPELL_H

#include "../core/object_world.h"
#include "../affiliate/sprite_animation.h"

class Spell : public ObjectWorld {
public:
    static Spell* addSpellChild(Object* parent, const std::string& filePath, glm::vec2 position, float damage, float scale = 1.f, Anchor anchor = Anchor::CENTER);
public:
    virtual void update(float deltaTime) override;
public:
    float getDamage() const { return damage_; }
    void setDamage(float damage) { damage_ = damage; }
    SpriteAnimation* getSpriteAnimation() const { return spriteAnimation_; }
    void setSpriteAnimation(SpriteAnimation* animation) { spriteAnimation_ = animation; }
private:
    void attack() const;
protected:
    SpriteAnimation* spriteAnimation_ = nullptr;
    float damage_ = 60.f;
};

#endif //SPELL_H