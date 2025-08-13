#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include "sprite.h"

class SpriteAnimation : public Sprite {
public:
    static SpriteAnimation* addSpriteAnimationChild(ObjectScreen* parent, const std::string& file_path, float scale = 1.f);
    virtual void update(float delta_time) override;

    virtual void setTexture(const Texture& texture) override;

    int getCurrentFrame() const { return current_frame_; }
    void setCurrentFrame(int frame) { current_frame_ = frame; }
    int getTotalFrames() const { return total_frames_; }
    void setTotalFrames(int frames) { total_frames_ = frames; }
    int getFPS() const { return fps_; }
    void setFPS(int fps) { fps_ = fps; }
private:
    int current_frame_;
    int total_frames_;
    int fps_ = 10;
    float frame_timer = 0.f;
};

#endif // SPRITE_ANIMATION_H