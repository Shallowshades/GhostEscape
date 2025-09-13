#ifndef GAME_H
#define GAME_H

#include <string>
#include <random>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>

#include "asset_store.h"

struct Texture;
class Scene;

class Game {
public:
    static Game& GetInstance() {
        static Game instance;
        return instance;
    }
public:
    glm::vec2 getScreenSize() const { return screen_size; }
    AssetStore* getAssetStore() const { return asset_store_; }
    Scene* getCurrentScene() const { return current_scene_; }
    glm::vec2 getMousePosition() const { return mousePosition_; }
    SDL_MouseButtonFlags getMouseButtons() const { return mouseButtons_; }
    void setScore(int score);
    int getScore() const { return score_; }
    void setHighScore(int highScore) { highScore_ = highScore; }
    int getHighScore() const { return highScore_; }
public:
    void addScore(int score);
    void quit() { is_running_ = false; }
public:
    void playMusic(const std::string& musicPath, bool loop = true) { Mix_PlayMusic(asset_store_->getMusic(musicPath), loop ? -1 : 0); }
    void playSound(const std::string& soundPath) { Mix_PlayChannel(-1, asset_store_->getSound(soundPath), 0); }
    void stopMusic() { Mix_HaltMusic(); }
    void stopSound() { Mix_HaltChannel(-1); }
    void pauseMusic() { Mix_PausedMusic(); }
    void pauseSound() { Mix_Pause(-1); }
    void resumeMusic() { Mix_ResumeMusic(); }
    void resumeSound() { Mix_Resume(-1); }
public:
    float randomFloat(float min, float max) {
        return std::uniform_real_distribution<float>(min, max)(gen_);
    }
    int randomInt(int min, int max) {
        return std::uniform_int_distribution<int>(min, max)(gen_);
    }
    glm::vec2 randomVec2(const glm::vec2& min, const glm::vec2& max) {
        return glm::vec2(randomFloat(min.x, max.x), randomFloat(min.y, max.y));
    }
    glm::ivec2 randomIVec2(const glm::ivec2& min, const glm::ivec2& max) {
        return glm::ivec2(randomInt(min.x, max.x), randomInt(min.y, max.y));
    }
    void renderTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size, const glm::vec2& mask = glm::vec2(1.f));
public:
    void renderHealthBar(const glm::vec2& position, const glm::vec2& size, float percent, SDL_FColor color);
    void renderFillCircle(const glm::vec2& position, const glm::vec2& size, float alpha);
    void drawGrid(const glm::vec2& top_left, const glm::vec2& bottom_right, float grid_width, SDL_FColor fcolor);
    void drawBoundary(const glm::vec2& top_left, const glm::vec2& bottom_right, float boundary_width, SDL_FColor fcolor);
    TTF_Text* createTTFText(const std::string& text, const std::string& fontPath, int fontSize = 16);
    bool isMouseInRect(const glm::vec2& topLeft, const glm::vec2& bottomRight);
public:
    void run();
    void init(std::string title, int width, int height);
    void handleEvents();
    void update(float dt);
    void render();
    void clean();

protected:

private:
    Game() = default;
    Game(const Game&) = delete;
    Game operator= (const Game&) = delete;
private:
    glm::vec2 screen_size = glm::vec2(0);
    bool is_running_ = true;
    Scene* current_scene_ = nullptr;

    glm::vec2 mousePosition_ = glm::vec2(0);
    SDL_MouseButtonFlags mouseButtons_ = 0;

    Uint64 FPS_ = 60;
    Uint64 frame_delay_ = 0;
    float dt_ = 0.0f;

    int score_ = 0;
    int highScore_ = 0;

    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;

    std::mt19937 gen_ = std::mt19937(std::random_device{}());

    AssetStore* asset_store_ = nullptr;
    TTF_TextEngine* ttfEngine_ = nullptr;
};

#endif // GAME_H