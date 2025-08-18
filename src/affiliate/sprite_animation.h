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
    float getFrameTimer() const { return frame_timer; }
    void setFrameTimer(float timer) { frame_timer = timer; }
    bool isLoop() const { return isLoop_; }
    void setLoop(bool loop) { isLoop_ = loop; }
private:
    int current_frame_;
    int total_frames_;
    int fps_ = 1;
    float frame_timer = 0.f;
    bool isLoop_ = true;
};

#endif // SPRITE_ANIMATION_H