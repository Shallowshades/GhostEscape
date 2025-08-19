#include "effect.h"
#include "../core/scene.h"

Effect* Effect::addEffectChild(Object* parent, const std::string& filePath, const glm::vec2& position, float scale, ObjectWorld* nextObject) {
    Effect* effect = new Effect();
    effect->init();
    effect->sprite_ = SpriteAnimation::addSpriteAnimationChild(effect, filePath, scale);
    effect->sprite_->setLoop(false);
    effect->setWorldPosition(position);
    effect->setNextObject(nextObject);
    parent->addChild(effect);
    return effect;
}

void Effect::update(float deltaTime) {
    Object::update(deltaTime);
    checkFinished();
}

void Effect::checkFinished() {
    if (sprite_->isFinished()) {
        isNeedRemove_ = true;
        if (nextObject_) {
            game_.getCurrentScene()->safeAddChild(nextObject_);
        }
    }
}
