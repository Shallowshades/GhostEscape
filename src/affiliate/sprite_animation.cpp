#include "sprite_animation.h"

SpriteAnimation* SpriteAnimation::addSpriteAnimationChild(ObjectScreen* parent, const std::string& file_path, float scale, [[maybe_unused]] Anchor anchor) {
    auto sprite_animation = new SpriteAnimation();
    sprite_animation->init();
    sprite_animation->setAnchor(anchor);
    sprite_animation->setTexture(file_path);
    sprite_animation->setScale(scale);
    sprite_animation->setParent(parent);
    parent->addChild(sprite_animation);
    return sprite_animation;
}

void SpriteAnimation::update(float delta_time) {
    if (isFinished_) {
        return;
    }
    frameTimer += delta_time;
    if (frameTimer >= 1.0f / fps_) {
        ++currentFrame_;
        if (currentFrame_ >= totalFrames_) {
            currentFrame_ = 0; // Loop back to the first frame
            if (!isLoop_) {
                isFinished_ = true;
            }
        }
        frameTimer = 0.f;
    }
    texture_.src_rect.x = currentFrame_ * texture_.src_rect.w;
}

void SpriteAnimation::setTexture(const Texture& texture) {
    texture_ = texture;
    totalFrames_ = static_cast<int>(std::ceil(texture.src_rect.w / texture.src_rect.h));
    texture_.src_rect.w = texture_.src_rect.h;
    size_ = glm::vec2(texture_.src_rect.w, texture_.src_rect.h);
}
