#include "spell.h"
#include "../core/scene.h"

Spell* Spell::addSpellChild(Object* parent, const std::string& filePath, glm::vec2 position, float damage, float scale, Anchor anchor) {
    auto spell = new Spell();
    spell->init();
    spell->damage_ = damage;
    spell->spriteAnimation_ = SpriteAnimation::addSpriteAnimationChild(spell, filePath, scale, anchor);
    auto size = spell->spriteAnimation_->getSize();
    spell->collider_ = Collider::addColliderChild(spell, size, Collider::Type::CIRCLE, anchor);
    spell->spriteAnimation_->setLoop(false);
    spell->setWorldPosition(position);
    if (parent) {
        parent->addChild(spell);
    }
    return spell;
}

void Spell::update(float deltaTime) {
    ObjectWorld::update(deltaTime);
    if (spriteAnimation_->isFinished()) {
        setIsNeedRemove(true);
    }
    attack();
}

void Spell::attack() const {
    auto objects = Game::GetInstance().getCurrentScene()->getWorldChildren();
    for (auto& object : objects) {
        if (object->getType() != ObjectType::ENEMY) {
            continue;
        }
        if (collider_ && object->getCollider() && collider_->isColliding(object->getCollider())) {
            object->takeDamage(damage_);
        }
    }
}