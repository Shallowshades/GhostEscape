#ifndef GAME_H
#define GAME_H

#include <string>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>

#include "asset_store.h"


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
public:
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

    AssetStore* asset_store_ = nullptr;
};

#endif // GAME_H