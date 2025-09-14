#include "effect.h"
#include "../core/scene.h"

Effect* Effect::addEffectChild(Object* parent, const std::string& filePath, const glm::vec2& position, float scale, ObjectWorld* nextObject) {
    Effect* effect = new Effect();
    effect->init();
    effect->sprite_ = SpriteAnimation::addSpriteAnimationChild(effect, filePath, scale);
    effect->sprite_->setLoop(false);
    effect->setWorldPosition(position);
    effect->setNextObject(nextObject);
    if (parent) {
        parent->addChild(effect);
    }
    return effect;
}

void Effect::update(float deltaTime) {
    ObjectWorld::update(deltaTime);     // 特效跟随角色移动, 错误; 实时更新世界对象在世界中的位置
    checkFinished();
}

void Effect::clean() {
    ObjectWorld::clean();
    if (nextObject_) {
        nextObject_->clean();
        delete nextObject_;
        nextObject_ = nullptr;
    }
}

void Effect::checkFinished() {
    if (sprite_->isFinished()) {
        isNeedRemove_ = true;
        if (nextObject_) {
            game_.getCurrentScene()->safeAddChild(nextObject_);
            nextObject_ = nullptr;                                  // 交给场景管理
        }
    }
}
