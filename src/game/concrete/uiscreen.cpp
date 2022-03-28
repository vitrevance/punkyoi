#include "uiscreen.h"

namespace punkyoi::concrete {

    UIScreen::UIScreen() : ::punkyoi::common::Scene() {
    }

    UIScreen::~UIScreen() {
    }

    UIElement::UIElement(UIScreen& screen, const std::string& spriteName, vec2 pos, vec2 size, bool consistantRatio)
            : ::punkyoi::common::Entity(screen),
            m_image(dynamic_cast<::punkyoi_api::IImage&>(getAssetManager().getAsset(spriteName))) {
        
        m_pos = pos;
        m_consistantRatio = consistantRatio;
        m_pressed = false;
        m_hovered = false;
        setSize(size);
    }

    UIElement::~UIElement() {
    }

    void UIElement::hover() {}
    void UIElement::unhover() {}
    void UIElement::click() {}
    bool UIElement::isFocused() {
        return m_hovered;
    }

    void UIElement::onEvent(punkyoi::events::MouseMovedEvent& event) {
        if (AABB(m_pos, m_size).contains(vec2(event.getX(), event.getY()))) {
            if (!m_hovered) {
                m_hovered = true;
                hover();
            }
        }
        else {
            if (m_hovered) {
                m_hovered = false;
                unhover();
            }
        }
    }

    void UIElement::onEvent(punkyoi::events::MouseButtonPressedEvent& event) {
        if (m_hovered) {
            m_pressed = true;
        }
    }

    void UIElement::onEvent(punkyoi::events::MouseButtonReleasedEvent& event) {
        if (m_pressed) {
            if (m_hovered) {
                click();
            }
            m_pressed = false;
        }
    }

    void UIElement::onEvent(punkyoi::events::RenderEvent& event) {
        event.getContext().push();
        event.getContext().scale(m_size);
        event.getContext().translate(m_pos - m_size / 2);
        event.getContext().drawImage(m_image);
        event.getContext().pop();
    }

    void UIElement::setPosition(vec2 pos) {
        m_pos = pos;
    }

    void UIElement::setSize(vec2 size) {
        m_size = size;
        if (m_consistantRatio) {
            m_size.y = size.x * m_image.getHeight() / m_image.getWidth();
        }
    }

    vec2 UIElement::getPosition() {
        return m_pos;
    }

    vec2 UIElement::getSize() {
        return m_size;
    }

    void UIButton::onEvent(punkyoi::events::RenderEvent& event) {
        event.getContext().push();
        event.getContext().translate(m_pos);
        event.getContext().scale(m_size);
        if (m_hovered) {
            event.getContext().drawImage(m_hoveredImage);
        }
        else {
            event.getContext().drawImage(m_image);
        }
        event.getContext().pop();
    }

    void UIButton::click() {
        m_callback();
    }

}