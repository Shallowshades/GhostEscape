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
    void renderTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size);
public:
    void renderFillCircle(const glm::vec2& position, const glm::vec2& size, float alpha);
    void drawGrid(const glm::vec2& top_left, const glm::vec2& bottom_right, float grid_width, SDL_FColor fcolor);
    void drawBoundary(const glm::vec2& top_left, const glm::vec2& bottom_right, float boundary_width, SDL_FColor fcolor);
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

    Uint64 FPS_ = 60;
    Uint64 frame_delay_ = 0;
    float dt_ = 0.0f;

    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;

    std::mt19937 gen_ = std::mt19937(std::random_device{}());

    AssetStore* asset_store_ = nullptr;
};

#endif // GAME_H