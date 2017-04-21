#include "headers/Window.h"

Window::Window(std::shared_ptr<EventManager> iEventManager, const std::string& title, const sf::Vector2u& size)
    : eventManager(iEventManager) {
    setup(title, size);
}

Window::~Window() { 
    destroy(); 
}

void Window::setup(const std::string& title, const sf::Vector2u& size) {
    window      = std::make_shared<sf::RenderWindow>();
    windowTitle = title;
    windowSize  = size;
    isDone      = false;
    isFocused   = true;

    window->create({windowSize.x, windowSize.y, 32}, windowTitle, sf::Style::Close);
    eventManager->addCallback("Window_close", &Window::close, this);
}

void Window::update() {
    sf::Event event;

    while (window->pollEvent(event)) {
        if (event.type == sf::Event::LostFocus) {
            isFocused = false;
            eventManager->setFocus(false);
        } else if (event.type == sf::Event::GainedFocus) {
            isFocused = true;
            eventManager->setFocus(true);
        }

        eventManager->handleEvent(event);
    }
    
    eventManager->update();
}

void Window::destroy() {
    window->close();
}

void Window::beginDraw() { 
    window->clear(sf::Color::Black); 
}

void Window::endDraw() { 
    window->display(); 
}

void Window::draw(sf::Drawable& l_drawable) {
    window->draw(l_drawable);
}

bool Window::getIsDone() { return isDone; }
bool Window::getIsFocused() { return isFocused; }
void Window::close(EventDetails* l_details) { isDone = true; }

sf::Vector2u Window::getSize() { return windowSize; }
std::shared_ptr<sf::RenderWindow> Window::getWindow() { return window; }
std::shared_ptr<EventManager> Window::getEventManager() { return eventManager; }
