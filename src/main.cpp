#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "MorseDecoder.hpp"
#include <iostream>
#include <memory>
#include <filesystem>


int main(int argc, char** argv) {
    // Create window
    sf::RenderWindow window(sf::VideoMode({1000u, 600u}), "Morse Code Decoder");
    window.setFramerateLimit(60);

    // Initialize decoder
    MorseDecoder decoder;

    // Load font for text displays
    sf::Font font;
    namespace fs = std::filesystem;

    fs::path exePath;
    if (argc > 0 && argv[0] != nullptr) {
        exePath = fs::absolute(argv[0]);
    } else {
        exePath = fs::current_path();
    }
    fs::path exeDir = exePath.parent_path();

    std::vector<fs::path> tried;
    std::vector<std::string> fontPaths = {
        (exeDir / "assets/SpecialElite-Regular.ttf").string(),
        (exeDir.parent_path() / "assets/SpecialElite-Regular.ttf").string(),
        (fs::current_path() / "assets/SpecialElite-Regular.ttf").string(),
        "assets/SpecialElite-Regular.ttf",
        "./assets/SpecialElite-Regular.ttf",
        "../assets/SpecialElite-Regular.ttf"
    };

    bool fontLoaded = false;
    for (const auto& path : fontPaths) {
        tried.push_back(path);
        if (font.openFromFile(path)) {
            fontLoaded = true;
            break;
        }
    }

    if (!fontLoaded) {
        std::cerr << "Warning: could not load font from assets. Tried paths:\n";
        for (const auto &p : tried) {
            fs::path absp = fs::absolute(p);
            std::cerr << "  Provided path: " << p << "\n    Absolute path: " << absp.string() << "\n";
        }
        std::cerr << "Place SpecialElite-Regular.ttf into the project's assets/ folder or into build/assets/.\n";
    }

    // Create buttons with font reference
    Button dotButton(150.0f, 480.0f, 120.0f, 60.0f, "DOT", font);
    Button dashButton(440.0f, 480.0f, 120.0f, 60.0f, "DASH", font);
    Button validateButton(730.0f, 480.0f, 120.0f, 60.0f, "VALIDATE", font);

    // Setup UI text
    sf::Text wordLabel(font);
    wordLabel.setCharacterSize(24);
    wordLabel.setFillColor(sf::Color(100, 200, 255));
    wordLabel.setPosition({50.0f, 50.0f});

    sf::Text wordDisplay(font);
    wordDisplay.setCharacterSize(32);
    wordDisplay.setFillColor(sf::Color(100, 255, 150));
    wordDisplay.setPosition({50.0f, 90.0f});

    sf::Text sequenceLabel(font);
    sequenceLabel.setCharacterSize(24);
    sequenceLabel.setFillColor(sf::Color(100, 200, 255));
    sequenceLabel.setPosition({50.0f, 200.0f});

    sf::Text sequenceDisplay(font);
    sequenceDisplay.setCharacterSize(36);
    sequenceDisplay.setFillColor(sf::Color(255, 200, 100));
    sequenceDisplay.setPosition({50.0f, 240.0f});

    sf::Text errorMessage(font);
    errorMessage.setCharacterSize(20);
    errorMessage.setFillColor(sf::Color(255, 100, 100));
    errorMessage.setPosition({50.0f, 340.0f});

    sf::Text instructionText(font);
    instructionText.setCharacterSize(14);
    instructionText.setFillColor(sf::Color(150, 150, 150));
    instructionText.setPosition({50.0f, 400.0f});
    instructionText.setString("Keyboard: . or D = DOT | - or K = DASH | Enter = VALIDATE | Backspace = CLEAR WORD");

    // Clock for frame timing
    sf::Clock clock;
    float errorMessageTimer = 0.0f;
    const float ERROR_MESSAGE_DURATION = 3.0f;

    // Main loop
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Event handling
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2f mousePos = window.mapPixelToCoords(mouseClick->position);

                if (dotButton.handleMouseClick(mousePos)) {
                    decoder.addDot();
                } else if (dashButton.handleMouseClick(mousePos)) {
                    decoder.addDash();
                } else if (validateButton.handleMouseClick(mousePos)) {
                    if (!decoder.validateLetter()) {
                        errorMessageTimer = ERROR_MESSAGE_DURATION;
                    }
                }
            }

            if (auto* mouseMove = event->getIf<sf::Event::MouseMoved>()) {
                sf::Vector2f mousePos = window.mapPixelToCoords(mouseMove->position);
                dotButton.handleMouseMove(mousePos);
                dashButton.handleMouseMove(mousePos);
                validateButton.handleMouseMove(mousePos);
            }

            if (auto* keyPress = event->getIf<sf::Event::KeyPressed>()) {
                switch (keyPress->code) {
                case sf::Keyboard::Key::Period:
                case sf::Keyboard::Key::D:
                    dotButton.flash();
                    decoder.addDot();
                    break;
                case sf::Keyboard::Key::Hyphen:
                case sf::Keyboard::Key::K:
                    dashButton.flash();
                    decoder.addDash();
                    break;
                case sf::Keyboard::Key::Enter:
                    validateButton.flash();
                    if (!decoder.validateLetter()) {
                        errorMessageTimer = ERROR_MESSAGE_DURATION;
                    }
                    break;
                case sf::Keyboard::Key::Backspace:
                    // Clear current word & sequence so user can start over
                    decoder.clearWord();
                    break;
                default:
                    break;
                }
            }
        }

        // Update flash timers
        dotButton.updateFlash(deltaTime);
        dashButton.updateFlash(deltaTime);
        validateButton.updateFlash(deltaTime);

        // Update error message timer
        if (errorMessageTimer > 0.0f) {
            errorMessageTimer -= deltaTime;
        }

        // Update text displays
        wordLabel.setString("WORD:");
        wordDisplay.setString(decoder.getCurrentWord().empty() ? "[empty]" : decoder.getCurrentWord());

        sequenceLabel.setString("SEQUENCE:");
        sequenceDisplay.setString(decoder.getCurrentSequence().empty() ? "-" : decoder.getCurrentSequence());

        if (errorMessageTimer > 0.0f) {
            errorMessage.setString(decoder.getLastError());
        } else {
            errorMessage.setString("");
        }

        // Clear and render
        window.clear(sf::Color(20, 20, 30));

        // Draw UI
        window.draw(wordLabel);
        window.draw(wordDisplay);
        window.draw(sequenceLabel);
        window.draw(sequenceDisplay);
        window.draw(errorMessage);
        window.draw(instructionText);

        // Draw buttons
        dotButton.draw(window);
        dashButton.draw(window);
        validateButton.draw(window);

        window.display();
    }

    return 0;
}
