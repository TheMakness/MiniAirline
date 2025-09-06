#pragma once

#include "TextNode.h"

class GameDebugData : public TextNode
{
	public:
		GameDebugData(const sf::Font& font);
	private:
		virtual void updateCurrent(sf::Time dt) override;

};

