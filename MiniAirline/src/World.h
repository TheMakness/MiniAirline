#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"
#include "SceneNode.h"

class World
{

public:
	explicit World(sf::RenderWindow& window);
	void update(sf::Time deltaTime);
	void draw();

private:
	enum class Layer
	{
		Background,
		Air,
		UI,
		LayerCount
	};

private:
	sf::RenderWindow& m_Window;
	sf::View m_WorldView;
	TextureHolder m_Textures;
	SceneNode m_SceneGraph;
	std::array<SceneNode*, static_cast<int>(Layer::LayerCount)> m_SceneLayers;
	sf::FloatRect m_WorldBounds;
	sf::Vector2f m_SpawnPosition;

private:
	void loadTextures();
	void buildScene();
};