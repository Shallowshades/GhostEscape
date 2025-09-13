#include "scene.h"

bool Scene::handleEvents(SDL_Event& event) {
    // 屏幕对象多为hud, text, button, label等必须处理的事件
    // 世界对象是为暂停对象
    for (auto& child : children_screen_) {
        if (child->isActive()) {
            if (child->handleEvents(event)) {
                return true;
            }
        }
    }
    if (isPause_) {
        return false;
    }
    Object::handleEvents(event);
    for (auto& child : children_world_) {
        if (child->isActive()) {
            if (child->handleEvents(event)) {
                return true;
            }
        }
    }
    return false;
}

void Scene::update(float deltaTime) {
    if (!isPause_) {
        Object::update(deltaTime);
        for (auto iter = children_world_.begin(); iter != children_world_.end(); ) {
            if ((*iter)->isNeedRemove()) {
                (*iter)->clean();
                delete* iter;
                iter = children_world_.erase(iter);
            }
            else {
                if ((*iter)->isActive()) {
                    (*iter)->update(deltaTime);
                }
                ++iter;
            }
        }
    }
    for (auto iter = children_screen_.begin(); iter != children_screen_.end(); ) {
        if ((*iter)->isNeedRemove()) {
            (*iter)->clean();
            delete* iter;
            iter = children_screen_.erase(iter);
        }
        else {
            if ((*iter)->isActive()) {
                (*iter)->update(deltaTime);
            }
            ++iter;
        }
    }
}

void Scene::render() {
    Object::render();
    for (auto& child : children_world_) {
        if (child->isActive()) {
            child->render();
        }
    }
    for (auto& child : children_screen_) {
        if (child->isActive()) {
            child->render();
        }
    }
}

void Scene::clean() {
    Object::clean();
    for (auto& child : children_world_) {
        child->clean();
    }
    for (auto& child : children_screen_) {
        child->clean();
    }
    children_world_.clear();
    children_screen_.clear();
}

void Scene::addChild(Object* child) {
    switch (child->getType()) {
    case ObjectType::OBJECT_WORLD:
    case ObjectType::ENEMY:
        children_world_.push_back(static_cast<ObjectWorld*>(child));
        break;
    case ObjectType::OBJECT_SCREEN:
        children_screen_.push_back(static_cast<ObjectScreen*>(child));
        break;
    default:
        Object::addChild(child);
        break;
    }
}

void Scene::removeChild(Object* child) {
    switch (child->getType()) {
    case ObjectType::OBJECT_WORLD:
    case ObjectType::ENEMY:
        children_world_.erase(std::remove(children_world_.begin(), children_world_.end(), static_cast<ObjectWorld*>(child)), children_world_.end());
        break;
    case ObjectType::OBJECT_SCREEN:
        children_screen_.erase(std::remove(children_screen_.begin(), children_screen_.end(), static_cast<ObjectScreen*>(child)), children_screen_.end());
        break;
    default:
        Object::removeChild(child);
        break;
    }
}

void Scene::pause() {
    isPause_ = true;
    game_.pauseSound();
    game_.pauseMusic();
}

void Scene::resume() {
    isPause_ = false;
    game_.resumeSound();
    game_.resumeMusic();
}

void Scene::setCameraPosition(const glm::vec2& position) {
    camera_position_ = position;
    camera_position_ = glm::clamp(camera_position_, glm::vec2(-30), world_size_ - game_.getScreenSize() + glm::vec2(30));
}