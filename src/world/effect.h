#ifndef EFFECT_H
#define EFFECT_H

#include "../core/object_world.h"
#include "../affiliate/sprite_animation.h"

class Effect : public ObjectWorld {
public:
    static Effect* addEffectChild(Object* parent, const std::string& file_path,
        const glm::vec2& position = glm::vec2(0, 0),
        float scale = 1.f,
        ObjectWorld* objectWorld = nullptr);
    virtual void update(float deltaTime) override;

    void setSpriteAnimation(SpriteAnimation* animation) { sprite_ = animation; }
    SpriteAnimation* getSpriteAnimation() const { return sprite_; }
    void setNextObject(ObjectWorld* nextObject) { nextObject_ = nextObject; }
    ObjectWorld* getNextObject() const { return nextObject_; }

private:
    void checkFinished();

private:
    SpriteAnimation* sprite_ = nullptr;
    ObjectWorld* nextObject_ = nullptr;
};

#endif // EFFECT_H