#pragma once

#include "Event.h"
#include "Ferret/Core/KeyCodes.h"

//MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
namespace Ferret
{
    // Base Mouse Button Event
    class OnMouseButtonEvent : public Event {
    public:
        inline MouseButton GetMouseButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(CategoryMouseButtonEvent | CategoryInputEvent)
    protected:
        OnMouseButtonEvent(MouseButton button)
        : m_Button(button) {}
        MouseButton m_Button;
    };
    // Mouse Button Pressed Event, using OnMouseButtonEvent
    class MouseButtonPressedEvent : public OnMouseButtonEvent {
    public:
        MouseButtonPressedEvent(MouseButton button)
        : OnMouseButtonEvent(button) {}
        std::string ToString() const override {
            std::stringstream ss;
            ss << "Mouse Button Pressed Event " << m_Button;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseButtonPressed)
    };
    // Mouse Button Pressed Event, using OnMouseButtonEvent
    class MouseButtonReleasedEvent : public OnMouseButtonEvent {
    public:
        MouseButtonReleasedEvent(MouseButton button)
        : OnMouseButtonEvent(button) {}
        std::string ToString() const override {
            std::stringstream ss;
            ss << "Mouse Button Released Event " << m_Button;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

    // Mouse Moved Event
    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(const float mouseX, const float mouseY)
        : m_MouseX(mouseX), m_MouseY(mouseY) {}

        inline float GetMouseX() const { return m_MouseX; }
        inline float GetMouseY() const { return m_MouseY; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "Mouse Moved Event: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(CategoryMouseEvent | CategoryInputEvent)
    private:
        float m_MouseX, m_MouseY;
    };

    class MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(const float offsetX, const float offsetY)
        : m_OffsetX(offsetX), m_OffsetY(offsetY) {}

        inline float GetXOffset() const { return m_OffsetX; }
        inline float GetYOffset() const { return m_OffsetY; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "Mouse Scrolled Event: " << GetXOffset() << ", " << GetYOffset();
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(CategoryMouseEvent | CategoryInputEvent)
    private:
        float m_OffsetX, m_OffsetY;
    };
}
