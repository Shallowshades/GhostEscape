#ifndef OBJECT_AFFILIATE_H
#define OBJECT_AFFILIATE_H

#include "object_screen.h"

class ObjectAffiliate : public ObjectScreen {
public:
    ObjectAffiliate() = default;
    virtual ~ObjectAffiliate() = default;
public:
    ObjectScreen* getParent() const { return parrent_; }
    void setParent(ObjectScreen* parent) { parrent_ = parent; }
    glm::vec2 getOffset() const { return offset_; }
    void setOffset(const glm::vec2& offset) { offset_ = offset; }
    glm::vec2 getSize() const { return size_; }
    void setSize(const glm::vec2& size) { size_ = size; }
protected:
    ObjectScreen* parrent_ = nullptr;        // 父节点
    glm::vec2 offset_ = glm::vec2(0, 0);    // 相对父节点的偏移位置
    glm::vec2 size_ = glm::vec2(0, 0);      // 相对父节点的大小
};

#endif // OBJECT_AFFILIATE_H