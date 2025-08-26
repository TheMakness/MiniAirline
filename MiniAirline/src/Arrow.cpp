#include "Arrow.h"

Arrow::Arrow(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint)
{
	
	m_arrowHead = sf::ConvexShape{ 3 };
	m_arrowHead.setPoint(0, { 0.f, 0.f });
	m_arrowHead.setPoint(1, { c_arrowHeadSize.x, c_arrowHeadSize.y / 2.f });
	m_arrowHead.setPoint(2, { 0.f, c_arrowHeadSize.y });
	m_arrowHead.setOrigin({ c_arrowHeadSize.x, c_arrowHeadSize.y / 2.f });

	m_tail = sf::RectangleShape();
	
	SetArrowPositionAndRotation(startPoint, endPoint);
}

 void Arrow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_tail);
	target.draw(m_arrowHead);
}

 void Arrow::setFillColor(sf::Color color)
 {
	 m_tail.setFillColor(color);
	 m_arrowHead.setFillColor(color);

 }

 std::size_t Arrow::getPointCount() const
 {
	 return m_arrowHead.getPointCount() + m_tail.getPointCount();
 }

 sf::Vector2f Arrow::getPoint(std::size_t index) const
 {
	 if (index > m_arrowHead.getPointCount() - 1)
		 return m_tail.getPoint(index - (m_arrowHead.getPointCount() - 1));
	 else
		 return m_arrowHead.getPoint(index);
 }

 void Arrow::SetArrowPositionAndRotation(sf::Vector2f startPoint, sf::Vector2f endPoint)
 {
		const float xa = startPoint.x;
		const float ya = startPoint.y;
		const float xb = endPoint.x;
		const float yb = endPoint.y;

		const float arrowLength = std::sqrtf(std::powf(xb - xa, 2) + std::powf(yb - ya, 2));

		const float angleRad = std::atan2(yb - ya, xb - xa);
		sf::Angle angle = sf::radians(angleRad);

		m_tailSize = { arrowLength - c_arrowHeadSize.x, c_arrowTailYSize };
		m_tail.setSize(m_tailSize);
		m_tail.setOrigin({ 0.f, m_tailSize.y / 2.f });

		m_arrowHead.setPosition(endPoint);
		m_arrowHead.setRotation(angle);

		m_tail.setPosition(startPoint);
		m_tail.setRotation(angle);
 }
