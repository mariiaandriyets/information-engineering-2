#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include<vector>

class CustomRectangleShape : public sf::RectangleShape {
private:
    float m_speed_x = 0;
    float m_speed_y = 0;
    float m_rotation_speed = 0;
    float m_left_bound = 0;
    float m_right_bound = 0;
    float m_top_bound = 0;
    float m_bottom_bound = 0;

public:
    CustomRectangleShape(const sf::Vector2f& size, const sf::Vector2f& position) : sf::RectangleShape(size) {
        setPosition(position);
    }

    void setSpeed(float speed_x, float speed_y, float rotation_speed) {
        m_speed_x = speed_x;
        m_speed_y = speed_y;
        m_rotation_speed = rotation_speed;
    }

    void setBounds(float left, float right, float top, float bottom) {
        m_left_bound = left;
        m_right_bound = right;
        m_top_bound = top;
        m_bottom_bound = bottom;
    }

    void animate(const sf::Time& elapsed) {
        float seconds = elapsed.asSeconds();

        move(m_speed_x * seconds, m_speed_y * seconds);

        rotate(m_rotation_speed * seconds);

        bounce();
    }

    void moveInDirection(const sf::Time& elapsed, const sf::Keyboard::Key& key) {
        float distance = m_speed_x * elapsed.asSeconds(); // Используйте скорость по x для примера, можно адаптировать

        switch (key) {
        case sf::Keyboard::Left:
            move(-distance, 0);
            break;
        case sf::Keyboard::Right:
            move(distance, 0);
            break;
        case sf::Keyboard::Up:
            move(0, -distance);
            break;
        case sf::Keyboard::Down:
            move(0, distance);
            break;
        default:
            break;
        }

        bounce();
    }

    bool isClicked(const sf::Vector2i& mouse_position) const {
        sf::FloatRect bounds = getGlobalBounds();
        return bounds.contains(static_cast<sf::Vector2f>(mouse_position));
    }
    void setSelected(bool isSelected) {
        m_isSelected = isSelected;
        setFillColor(isSelected ? sf::Color::Red : sf::Color::Green);
    }

    bool isSelected() const {
        return m_isSelected;
    }

private:
    void bounce() {
        sf::Vector2f position = getPosition();
        sf::Vector2f size = getSize();

        if (position.x < m_left_bound || (position.x + size.x) > m_right_bound) {
            m_speed_x = -std::abs(m_speed_x);
        }

        if (position.y < m_top_bound || (position.y + size.y) > m_bottom_bound) {
            m_speed_y = -std::abs(m_speed_y);
        }
    }

     bool m_isSelected = false;
};

    int main() {

        sf::RenderWindow window(sf::VideoMode(800, 600), "Custom Rectangle Shape Example");
        std::vector<CustomRectangleShape> rectangles;
        sf::Clock clock;

        for (int i = 0; i < 10; i++) {
            sf::Vector2f size(120.0f, 60.0f);
            sf::Vector2f position(static_cast<float>(std::rand() % (window.getSize().x - 120)), static_cast<float>(std::rand() % (window.getSize().y - 60)));
            rectangles.emplace_back(size, position);
            rectangles.back().setFillColor(sf::Color(0, 255, 0));
            rectangles.back().setBounds(0, window.getSize().x, 0, window.getSize().y);
            rectangles.back().setSpeed(100, 200, 10);
        }

        CustomRectangleShape* selectedRectangle = nullptr;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    for (auto& rectangle : rectangles) {
                        if (rectangle.isClicked(mousePosition)) {
                            if (selectedRectangle) {
                                selectedRectangle->setSelected(false);
                            }
                            selectedRectangle = &rectangle;
                            rectangle.setSelected(true);
                            break;
                        }
                    }
                }

                if (selectedRectangle && event.type == sf::Event::KeyPressed) {
                    sf::Time elapsed = clock.restart();
                    selectedRectangle->moveInDirection(elapsed, event.key.code);
                }
            }

            window.clear(sf::Color::Black);

            for (auto& rectangle : rectangles) {
                window.draw(rectangle);
            }

            window.display();
        }
        return 0;

    }
