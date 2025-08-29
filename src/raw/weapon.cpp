#include "weapon.h"
#include "../core/actor.h"
#include "../world/spell.h"
#include "stats.h"
#include "../core/scene.h"

void Weapon::update(float delta) {
    Object::update(delta);
    coolDawnTimer_ += delta;
}

void Weapon::attack(glm::vec2 position, Spell* spell) {
    if (spell == nullptr) {
        return;
    }
    parent_->getStats()->useMana(manaCost_);
    coolDawnTimer_ = 0.f;
    spell->setWorldPosition(position);
    game_.getCurrentScene()->safeAddChild(spell);
}

bool Weapon::canAttack() {
    if (coolDawnTimer_ < coolDown_) {
        return false;
    }
    if (!parent_->getStats()->canUseMana(manaCost_)) {
        return false;
    }
    return true;
}
