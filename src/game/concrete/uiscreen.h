#ifndef P_UISCREEN
#define P_UISCREEN

#include <game/core.h>
#include <game/common/scene.h>
#include <game/singleton.h>

namespace punkyoi::concrete {

    class UIScreen : public ::punkyoi::common::Scene {
    public:
        UIScreen();
        virtual ~UIScreen();
    };

    class UIElement : public ::punkyoi::common::Entity,
        public ::punkyoi_api::events::EventListener<::punkyoi::events::MouseMovedEvent>,
        public ::punkyoi_api::events::EventListener<::punkyoi::events::MouseButtonPressedEvent>,
        public ::punkyoi_api::events::EventListener<::punkyoi::events::MouseButtonReleasedEvent>,
        public ::punkyoi_api::events::EventListener<::punkyoi::events::RenderEvent> {
    public:
        UIElement(UIScreen& screen, const std::string& spriteName, vec2 pos, vec2 size, bool consistantRatio = true);
        virtual ~UIElement();

        virtual void hover();
        virtual bool isFocused();
        virtual void unhover();
        virtual void click();
        virtual void setPosition(vec2 pos);
        virtual void setSize(vec2 size);
        virtual vec2 getPosition();
        virtual vec2 getSize();

        virtual void onEvent(::punkyoi::events::MouseMovedEvent& event) override;
        virtual void onEvent(::punkyoi::events::MouseButtonPressedEvent& event) override;
        virtual void onEvent(::punkyoi::events::MouseButtonReleasedEvent& event) override;
        virtual void onEvent(::punkyoi::events::RenderEvent& event) override;

    protected:
        ::punkyoi_api::IImage& m_image;
        vec2 m_pos;
        vec2 m_size;
        bool m_consistantRatio;
        bool m_pressed;
        bool m_hovered;
    };

    class UIButton : public UIElement {
    public:
        template <typename Lambda>
        UIButton(UIScreen& screen, const std::string& spriteName, vec2 pos, vec2 size, Lambda& callback) 
            : UIElement(screen, spriteName, pos, size), m_hoveredImage(m_image), m_callback(callback) {
        }

        template<typename Lambda>
        UIButton(UIScreen& screen, const std::string& spriteName, const std::string& hoveredName, vec2 pos, vec2 size, Lambda& callback)
            : UIElement(screen, spriteName, pos, size), m_hoveredImage(dynamic_cast<::punkyoi_api::IImage&>(getAssetManager().getAsset(hoveredName))), m_callback(callback) {
        }

        template<typename Lambda>
        UIButton(UIScreen& screen, const std::string& spriteName, vec2 pos, vec2 size, bool consistantRatio, Lambda& callback)
            : UIElement(screen, spriteName, pos, size, consistantRatio), m_hoveredImage(m_image), m_callback(callback) {
        }

        template<typename Lambda>
        UIButton(UIScreen& screen, const std::string& spriteName, const std::string& hoveredName, vec2 pos, vec2 size, bool consistantRatio, Lambda& callback)
            : UIElement(screen, spriteName, pos, size, consistantRatio), m_hoveredImage(dynamic_cast<::punkyoi_api::IImage&>(getAssetManager().getAsset(hoveredName))), m_callback(callback) {
        }

        virtual void onEvent(::punkyoi::events::RenderEvent& event) override;
        virtual void click() override;
    protected:
        ::punkyoi_api::IImage& m_hoveredImage;

        std::function<void()> m_callback;
    };
}

#endif