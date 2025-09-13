#ifndef HUD_TEXT_H
#define HUD_TEXT_H

#include "../core/object_screen.h"
#include "../affiliate/text_label.h"
#include "../affiliate/sprite.h"

class HUDText : public ObjectScreen {
public:
    static HUDText* addHUDTextChild(Object* parent, const std::string& text, glm::vec2 renderPosition, glm::vec2 size, const std::string& fontPath = "assets/font/VonwaonBitmap-16px.ttf", int fontSize = 32, const std::string& bgPath = "assets/UI/Textfield_01.png", Anchor anchor = Anchor::CENTER);
    void setBgSizeByText(float margin = 50.f);
public:
    void setTextLabel(TextLabel* textLabel) { textLabel_ = textLabel; }
    void setSpriteBg(Sprite* sprite) { spriteBg_ = sprite; }
    TextLabel* getTextLabel() const { return textLabel_; }
    Sprite* getSpriteBg() const { return spriteBg_; }
    void setText(const std::string& text) { textLabel_->setText(text); }
    std::string getText() const { return textLabel_->getText(); }
    void setSize(const glm::vec2& size);
    void setBackground(const std::string& filePath);
protected:
    TextLabel* textLabel_ = nullptr;
    Sprite* spriteBg_ = nullptr;
    glm::vec2 size_ = glm::vec2(0.f);
};

#endif // HUD_TEXT_H