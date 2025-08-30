#include "game.h"
#include "../scene_main.h"
#include "../affiliate/sprite.h"

constexpr float PER_SEC = 1000000000.f; // 1 second in nanoseconds
// constexpr Uint64 PER_MSEC = 1000000; // 1 millisecond in nanoseconds 

void Game::run() {
    while (is_running_) {
        auto start = SDL_GetTicksNS();
        handleEvents();
        update(dt_);
        render();
        auto elapsed = SDL_GetTicksNS() - start;
        // SDL_Log("Frame Time: %.10f ns\n", elapsed * 1.0);
        if (elapsed < frame_delay_) {
            SDL_DelayNS(frame_delay_ - elapsed);
            dt_ = static_cast<float>(frame_delay_ / PER_SEC);
        }
        else {
            dt_ = static_cast<float>(elapsed / PER_SEC);
        }

        // SDL_Log("FPS: %f, dt_ = %f", 1.f / dt_, dt_);
    }
}

void Game::init(std::string title, int width, int height) {
    screen_size = glm::vec2(width, height);
    // SDL3 init
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL Init Failed: %s\n", SDL_GetError());
        return;
    }
    // SDL_image not init

    // SDL_Mixer init
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_mixer Init Failed: %s\n", SDL_GetError());
        return;
    }
    if (!Mix_OpenAudio(0, nullptr)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_mixer Open Audio Failed: %s\n", SDL_GetError());
        return;
    }

    // SDL_mixer init
    Mix_AllocateChannels(16);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    Mix_Volume(-1, MIX_MAX_VOLUME / 4);

    // SDL_ttf init
    if (!TTF_Init()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_ttf Init Failed: %s\n", SDL_GetError());
        return;
    }


    // SDL create window and renderer
    SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &window_, &renderer_);
    if (!window_ || !renderer_) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL Create Window and Renderer Failed: %s\n", SDL_GetError());
        return;
    }
    // Set logical resolution
    SDL_SetRenderLogicalPresentation(renderer_, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // Calculate frame delay
    frame_delay_ = PER_SEC / FPS_;

    // Create asset manager
    asset_store_ = new AssetStore(renderer_);
    if (!asset_store_) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "AssetStore Creation Failed: %s\n", SDL_GetError());
        return;
    }

    // Create scene
    current_scene_ = new SceneMain();
    current_scene_->init();
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
            is_running_ = false;
            break;
        default:
            if (current_scene_) {
                current_scene_->handleEvents(event);
            }
            break;
        }
    }
}

void Game::update(float dt) {
    if (current_scene_) {
        mouseButtons_ = SDL_GetMouseState(&mousePosition_.x, &mousePosition_.y);
        current_scene_->update(dt);
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
    if (current_scene_) {
        current_scene_->render();
    }
    SDL_RenderPresent(renderer_);
}

void Game::clean() {
    if (current_scene_) {
        current_scene_->clean();
        delete current_scene_;
        current_scene_ = nullptr;
    }
    if (asset_store_) {
        asset_store_->clean();
        delete asset_store_;
        asset_store_ = nullptr;
    }
    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }
    if (window_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}

void Game::renderTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size) {
    SDL_FRect dst_rect = {
        position.x,
        position.y,
        size.x,
        size.y
    };
    SDL_RenderTextureRotated(renderer_, texture.texture, &texture.src_rect, &dst_rect, texture.angle, nullptr, texture.is_flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Game::renderHealthBar(const glm::vec2& position, const glm::vec2& size, float percent, SDL_FColor fcolor) {
    SDL_SetRenderDrawColorFloat(renderer_, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
    SDL_FRect boundaryRect = { position.x, position.y, size.x, size.y };
    SDL_FRect fillRect = { position.x, position.y, size.x * percent, size.y };
    SDL_RenderRect(renderer_, &boundaryRect);
    SDL_RenderFillRect(renderer_, &fillRect);
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1);
}

void Game::renderFillCircle(const glm::vec2& position, const glm::vec2& size, float alpha) {
    auto texture = asset_store_->getTexture("assets/UI/circle.png");
    SDL_FRect dst_rect = {
        position.x,
        position.y,
        size.x,
        size.y
    };
    SDL_SetTextureAlphaModFloat(texture, alpha);
    SDL_RenderTexture(renderer_, texture, nullptr, &dst_rect);
}

void Game::drawGrid(const glm::vec2& top_left, const glm::vec2& bottom_right, float grid_width, SDL_FColor fcolor) {
    SDL_SetRenderDrawColorFloat(renderer_, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
    for (float x = top_left.x; x <= bottom_right.x; x += grid_width) {
        SDL_RenderLine(renderer_, x, top_left.y, x, bottom_right.y);
    }
    for (float y = top_left.y; y <= bottom_right.y; y += grid_width) {
        SDL_RenderLine(renderer_, top_left.x, y, bottom_right.x, y);
    }
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1); // Reset color to black
}

void Game::drawBoundary(const glm::vec2& top_left, const glm::vec2& bottom_right, float boundary_width, SDL_FColor fcolor) {
    SDL_SetRenderDrawColorFloat(renderer_, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
    for (float i = 0; i < boundary_width; i++) {
        SDL_FRect rect = {
            top_left.x - i,
            top_left.y - i,
            bottom_right.x - top_left.x + 2 * i,
            bottom_right.y - top_left.y + 2 * i
        };
        SDL_RenderRect(renderer_, &rect);
    }
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1); // Reset color to black
}