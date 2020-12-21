//
//  TextBox.cpp
//  RPGProject
//
//  Created by Nathan FALLET on 21/12/2020.
//  Copyright © 2020 Nathan FALLET. All rights reserved.
//

#include "TextBox.hpp"

const float animation_duration = 0.05f;

TextBox::TextBox() {
    // Empty default text
    this->text = "";
    
    // Init font and text
    sfFont.loadFromFile(resourcePath() + "pokemon_pixel_font.ttf");
    sfText.setFont(sfFont);
    sfText.setCharacterSize(16);
    sfText.setFillColor(sf::Color::Black);
    background.setFillColor(sf::Color::White);
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Check if text should be shawn
    if (text.length() != 0) {
        // Draw the box
        target.draw(background);
        
        // Draw the text on it
        target.draw(sfText);
    }
}

void TextBox::update(float deltaTime) {
    // Check for animation
    if (animated) {
        // Increment animation time
        animation_time += deltaTime;
        while (animation_time >= animation_duration) {
            // Next frame
            animation_time -= animation_duration;
            progress++;
        }
        
        // Stop animation is limit is reached
        int lenght = text.length();
        if (progress >= lenght) {
            progress = lenght;
            animated = false;
        }
        
        // Update text
        sfText.setString(text.substr(0, progress));
    }
}

void TextBox::setRect(float x, float y, float width, float height) {
    // Set position and size
    sfText.setPosition(sf::Vector2f(x + 8, y + 4));
    background.setPosition(sf::Vector2f(x, y));
    background.setSize(sf::Vector2f(width, height));
}

void TextBox::setText(std::string newText) {
    // Save new text
    text = newText;
    
    // Start animating
    animated = true;
}

void TextBox::clearText() {
    // Clear text
    text = "";
    progress = 0;
    
    // Stop any animation
    animated = false;
}
