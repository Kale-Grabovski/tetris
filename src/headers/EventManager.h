#pragma once

#include <vector>
#include <string>
#include <functional>
#include <utility>
#include <map>   
#include <SFML/Graphics.hpp>

enum class EventType {
    KeyDown = sf::Event::KeyPressed,
    KeyUp = sf::Event::KeyReleased,
    MButtonDown = sf::Event::MouseButtonPressed,
    MButtonUp = sf::Event::MouseButtonReleased,
    MouseWheel = sf::Event::MouseWheelMoved,
    WindowResized = sf::Event::Resized,
    GainedFocus = sf::Event::GainedFocus,
    LostFocus = sf::Event::LostFocus,
    MouseEntered = sf::Event::MouseEntered,
    MouseLeft = sf::Event::MouseLeft,
    Closed = sf::Event::Closed,
    TextEntered = sf::Event::TextEntered,
    Keyboard = sf::Event::Count + 1, 
    Mouse
};

struct EventInfo {
    EventInfo() { code = 0; }
    EventInfo(int event) { code = event; }
    union {
        int code;
    };
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails {
    EventDetails(const std::string& bindName) : name(bindName) {
        clear();
    }

    std::string name;
    sf::Vector2i size;
    sf::Uint32 textEntered;
    sf::Vector2i mouse;
    int mouseWheelDelta;
    int keyCode; // Single key code.

    void clear() {
        size = sf::Vector2i(0, 0);
        textEntered = 0;
        mouse = sf::Vector2i(0, 0);
        mouseWheelDelta = 0;
        keyCode = -1;
    }
};

struct Binding {
    Binding(const std::string& name) : name(name), details(name), c(0) {}

    void bindEvent(EventType type, EventInfo info = EventInfo()) {
        events.emplace_back(type, info);
    }

    Events events;
    std::string name;
    EventDetails details;
    uint c; // Count of events that are "happening".
};

using Bindings  = std::map<std::string, Binding*>;
using Callbacks = std::map<std::string, std::function<void(EventDetails*)>>;

class EventManager {
public:
    EventManager();
    virtual ~EventManager();

    bool addBinding(Binding* binding);
    bool removeBinding(std::string name);
    void setFocus(const bool& focus);

    template<class T>
    bool addCallback(const std::string& callbackName, void(T::*func)(EventDetails*), T* instance) {
        auto temp = std::bind(func, instance, std::placeholders::_1);
        return callbacks.emplace(callbackName, temp).second;
    }

    void removeCallback(const std::string& name);
    void handleEvent(sf::Event& event);
    void update();

private:
    void loadBindings();
    Bindings bindings;
    Callbacks callbacks;
    bool hasFocus;
};
