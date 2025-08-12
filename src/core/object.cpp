#include "object.h"

void Object::handleEvents(SDL_Event& event) {
    for (auto& child : children_) {
        child->handleEvents(event);
    }
}

void Object::update(float deltaTime) {
    for (auto& child : children_) {
        child->update(deltaTime);
    }
}

void Object::render() {
    for (auto& child : children_) {
        child->render();
    }
}

void Object::clean() {
    for (auto& child : children_) {
        child->clean();
    }
    children_.clear();
}
