#include "weapon_thunder.h"
#include "world/spell.h"
#include "core/scene.h"
#include "core/actor.h"

WeaponThunder* WeaponThunder::addWeaponThunderChild(Actor* parent, float coolDown, float manaCost) {
    auto weapon = new WeaponThunder();
    weapon->init();
    weapon->setParent(parent);
    weapon->setCoolDown(coolDown);
    weapon->setManaCost(manaCost);
    if (parent) {
        parent->addChild(weapon);
    }
    return weapon;
}

void WeaponThunder::init() {
    Weapon::init();
    auto scene = Game::GetInstance().getCurrentScene();
    auto position = glm::vec2(Game::GetInstance().getScreenSize().x - 300, 30);
    hudSkill_ = HUDSkill::addHUDSkillChild(scene, "assets/UI/Electric-Icon.png", position, 0.14f, Anchor::CENTER);
}

void WeaponThunder::update(float delta) {
    Weapon::update(delta);
    if (hudSkill_) {
        hudSkill_->setPercentage(coolDawnTimer_ / coolDown_);
    }
}

bool WeaponThunder::handleEvents(SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            if (canAttack()) {
                Game::GetInstance().playSound("assets/sound/big-thunder.mp3");
                auto position = Game::GetInstance().getMousePosition() + Game::GetInstance().getCurrentScene()->getCameraPosition();
                auto spell = Spell::addSpellChild(nullptr, "assets/effect/Thunderstrike w blur.png", position, 40.f, 3.f, Anchor::CENTER);
                attack(position, spell);
                return true;
            }
        }
    }
    return false;
}
