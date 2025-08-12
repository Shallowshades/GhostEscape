#include "scene.h"

void Scene::handleEvents(SDL_Event& event) {
    Object::handleEvents(event);
    for (auto& child : children_world_) {
        child->handleEvents(event);
    }
    for (auto& child : children_screen_) {
        child->handleEvents(event);
    }
}

void Scene::update(float deltaTime) {
    Object::update(deltaTime);
    for (auto& child : children_world_) {
        child->update(deltaTime);
    }
    for (auto& child : children_screen_) {
        child->update(deltaTime);
    }
}

void Scene::render() {
    Object::render();
    for (auto& child : children_world_) {
        child->render();
    }
    for (auto& child : children_screen_) {
        child->render();
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
    switch(child->getType()) {
        case ObjectType::OBJECT_WORLD:
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
    switch(child->getType()) {
        case ObjectType::OBJECT_WORLD:
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

void Scene::setCameraPosition(const glm::vec2& position) {
    camera_position_ = position;
    camera_position_ = glm::clamp(camera_position_, glm::vec2(-30), world_size_ - game_.getScreenSize() + glm::vec2(30));
}