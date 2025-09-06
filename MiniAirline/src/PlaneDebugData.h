#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "Aircraft.h"
#include "TextNode.h"


class PlaneDebugData : public TextNode
{
	public:
	PlaneDebugData(const Aircraft* aircraft, const sf::Font& font);
private:
	
	virtual void updateCurrent(sf::Time dt) override;
	const Aircraft* m_Plane;
};

