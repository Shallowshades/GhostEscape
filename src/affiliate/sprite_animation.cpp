#include "sprite_animation.h"

SpriteAnimation* SpriteAnimation::addSpriteAnimationChild(ObjectScreen* parent, const std::string& file_path, float scale) {
    auto sprite_animation = new SpriteAnimation();
    sprite_animation->init();
    sprite_animation->setTexture(file_path);
    sprite_animation->setScale(scale);
    sprite_animation->setParent(parent);
    parent->addChild(sprite_animation);
    return sprite_animation;
}

void SpriteAnimation::update(float delta_time) {
    frame_timer += delta_time;
    if (frame_timer >= 1.0f / fps_) {
        ++current_frame_;
        if (current_frame_ >= total_frames_) {
            current_frame_ = 0; // Loop back to the first frame
        }
        frame_timer = 0.f;
    }
    texture_.src_rect.x = current_frame_ * texture_.src_rect.w;
}

void SpriteAnimation::setTexture(const Texture& texture) {
    texture_ = texture;
    total_frames_ = static_cast<int>(std::ceil(texture.src_rect.w / texture.src_rect.h));
    texture_.src_rect.w = texture_.src_rect.h;
    size_ = glm::vec2(texture_.src_rect.w, texture_.src_rect.h);
}
