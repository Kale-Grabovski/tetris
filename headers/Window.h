#pragma once

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "EventManager.h"

class EventManager;
struct EventDetails;
class Window {
public:
    explicit Window(std::shared_ptr<EventManager>, const std::string& title, const sf::Vector2u& size);
    virtual ~Window();
    
    void beginDraw();
    void endDraw();
    void update();
    bool getIsDone();
    bool getIsFocused();
    std::shared_ptr<EventManager> getEventManager();
    sf::Vector2u getSize();
    void draw(sf::Drawable& drawable);
    std::shared_ptr<sf::RenderWindow> getWindow();
    void close(EventDetails* details = nullptr);

private:
    void setup(const std::string& title, const sf::Vector2u& size);
    void destroy();
    std::shared_ptr<EventManager> eventManager;
    std::shared_ptr<sf::RenderWindow> window;
    sf::Vector2u windowSize;
    std::string windowTitle;
    bool isDone;
    bool isFocused;
};
