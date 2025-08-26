#include <SFML/Graphics.hpp>
#include "Entity.h"

#pragma once
class Arrow : public sf::Shape
{
public:
    explicit Arrow(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint);
    void SetArrowPositionAndRotation(sf::Vector2f tailPos, sf::Vector2f headPos);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
    void setFillColor(sf::Color color);
private:
    sf::RectangleShape m_tail;
    sf::ConvexShape m_arrowHead;
    const sf::Vector2f c_arrowHeadSize{ 50.f, 50.f };
    const float c_arrowTailYSize = 10.f;

    sf::Vector2f m_tailSize;

    // Inherited via Shape
    std::size_t getPointCount() const override;
    sf::Vector2f getPoint(std::size_t index) const override;
};

