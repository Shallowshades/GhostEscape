#include "object.h"

void Object::handleEvents(SDL_Event& event) {
    for (auto& child : objectToAdd_) {
        addChild(child);
    }
    objectToAdd_.clear();

    for (auto& child : children_) {
        if (child->isActive()) {
            child->handleEvents(event);
        }
    }
}

void Object::update(float deltaTime) {
    for (auto iter = children_.begin(); iter != children_.end(); ) {
        if ((*iter)->isNeedRemove()) {
            iter = children_.erase(iter);
            (*iter)->clean();
            delete* iter;
        }
        else {
            if ((*iter)->isActive()) {
                (*iter)->update(deltaTime);
            }
            ++iter;
        }
    }
}

void Object::render() {
    for (auto& child : children_) {
        if (child->isActive()) {
            child->render();
        }
    }
}

void Object::clean() {
    for (auto& child : children_) {
        child->clean();
    }
    children_.clear();
}
