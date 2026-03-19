#include "Button.hpp"
#include <iostream>

const float Button::FLASH_DURATION = 0.15f;

Button::Button(float x, float y, float width, float height, const std::string& label, const sf::Font& font)
    : shape(), text(font), label(label), hovered(false), flashing(false), flashTimer(0.0f) {

    // Setup button shape
    shape.setSize({width, height});
    shape.setPosition({x, y});
    shape.setFillColor(sf::Color(50, 50, 50));
    shape.setOutlineThickness(2.0f);
    shape.setOutlineColor(sf::Color(100, 200, 255));

    // Setup text
    text.setString(label);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color(200, 200, 200));

    // Center text in button
    updateTextPosition(width, height);
}

void Button::updateTextPosition(float width, float height) {
    sf::FloatRect textBounds = text.getLocalBounds();
    float buttonX = shape.getPosition().x;
    float buttonY = shape.getPosition().y;
    
    // Calculate center position
    float centerX = buttonX + (width - textBounds.size.x) / 2.0f - textBounds.position.x;
    float centerY = buttonY + (height - textBounds.size.y) / 2.0f - textBounds.position.y;
    
    text.setPosition({centerX, centerY});
}

void Button::draw(sf::RenderWindow& window) {
    // Update color based on hover state
    if (hovered && !flashing) {
        shape.setFillColor(sf::Color(80, 80, 80));
    } else if (!flashing) {
        shape.setFillColor(sf::Color(50, 50, 50));
    }

    window.draw(shape);
    window.draw(text);
}

bool Button::handleMouseClick(sf::Vector2f mousePos) {
    if (shape.getGlobalBounds().contains(mousePos)) {
        flash();
        return true;
    }
    return false;
}

void Button::handleMouseMove(sf::Vector2f mousePos) {
    hovered = shape.getGlobalBounds().contains(mousePos);
}

void Button::flash() {
    flashing = true;
    flashTimer = FLASH_DURATION;
    shape.setFillColor(sf::Color(255, 200, 0));
}

void Button::updateFlash(float deltaTime) {
    if (flashing) {
        flashTimer -= deltaTime;
        if (flashTimer <= 0.0f) {
            flashing = false;
            shape.setFillColor(sf::Color(50, 50, 50));
        }
    }
}
