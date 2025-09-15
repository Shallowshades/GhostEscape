#include "collider.h"
#include "../core/defines.h"

void Collider::render() {
#ifdef DEBUG_MODE
    ObjectAffiliate::render();
    auto pos = getParent()->getRenderPosition() + offset_;
    Game::GetInstance().renderFillCircle(pos, size_, 0.3);
#endif
}

Collider* Collider::addColliderChild(ObjectScreen* parent, const glm::vec2& size, Type type, [[maybe_unused]] Anchor anchor) {
    Collider* collider = new Collider();
    collider->init();
    collider->setAnchor(anchor);
    collider->setParent(parent);
    collider->setSize(size);
    collider->setType(type);
    parent->addChild(collider);
    return collider;
}

bool Collider::isColliding(Collider* other) {
    if (other == nullptr || other == this) {
        return false;
    }
    if (type_ == Type::CIRCLE && other->getType() == Type::CIRCLE) {
        auto pos1 = getParent()->getRenderPosition() + offset_ + size_ / 2.f;
        auto pos2 = other->getParent()->getRenderPosition() + other->getOffset() + other->getSize() / 2.f;
        return glm::length(pos1 - pos2) < (size_.x + other->getSize().x) / 2.0f;
    }
    return false;
}
