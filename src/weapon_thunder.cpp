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

void WeaponThunder::handleEvents(SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            if (canAttack()) {
                auto position = game_.getMousePosition() + game_.getCurrentScene()->getCameraPosition();
                auto spell = Spell::addSpellChild(nullptr, "assets/effect/Thunderstrike w blur.png", position, 40.f, 3.f, Anchor::CENTER);
                attack(position, spell);
            }
        }
    }
}
