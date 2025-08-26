#include "spawner.h"
#include "enemy.h"
#include "world/effect.h"
#include "core/scene.h"

void Spawner::update(float delta) {
    if (!target_ || !target_->isAlive()) {
        return;
    }
    timer_ += delta;
    if (timer_ > interval_) {
        SDL_Log("Spawner: spawn %d enemies\n", num_);
        timer_ = 0;
        for (int i = 0; i < num_; ++i) {
            // spawn enemy
            auto pos = game_.randomVec2(game_.getCurrentScene()->getCameraPosition(), game_.getCurrentScene()->getCameraPosition() + game_.getScreenSize());
            Enemy* enemy = Enemy::addEnemyChild(nullptr, pos, target_);
            Effect::addEffectChild(game_.getCurrentScene(), "assets/effect/184_3.png", pos, 1.f, enemy);
        }
    }
}