#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class Button {
public:
    // Constructor
    Button(float x, float y, float width, float height, const std::string& label, const sf::Font& font);

    // Drawing
    void draw(sf::RenderWindow& window);

    // Event handling
    bool handleMouseClick(sf::Vector2f mousePos);
    void handleMouseMove(sf::Vector2f mousePos);

    // Flash effect
    void flash();
    void updateFlash(float deltaTime);

    // Getters
    bool isHovered() const { return hovered; }
    const std::string& getLabel() const { return label; }
    bool isFlashing() const { return flashing; }

private:
    sf::RectangleShape shape;
    sf::Text text;

    std::string label;
    bool hovered;
    bool flashing;
    float flashTimer;
    static const float FLASH_DURATION;

    void updateTextPosition(float width, float height);
};
