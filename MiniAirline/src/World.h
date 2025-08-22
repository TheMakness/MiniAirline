#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"
#include "SceneNode.h"
#include "CommandQueue.h"
#include "Player.h"

class World
{

public:
	explicit World(sf::RenderWindow& window);
	void update(sf::Time deltaTime);
	void zoomIn();
	void zoomOut();
	void draw();

	CommandQueue& getCommandQueue();

	const sf::View& getView() const;
	const sf::RenderWindow& getRenderWindow() const;

private:
	enum class Layer
	{
		Background,
		Ground,
		Air,
		LayerCount
	};

private:
	sf::RenderWindow& m_Window;
	sf::View m_WorldView;
	TextureHolder m_Textures;

	SceneNode m_SceneGraph;
	std::array<SceneNode*, static_cast<int>(Layer::LayerCount)> m_SceneLayers;
	CommandQueue m_CommandQueue;
	
	sf::FloatRect m_WorldBounds;
	sf::Vector2f m_SpawnPosition;

	float m_ZoomLevel = 1.f;
	float m_MinZoomLevel = 0.5f;
	float m_MaxZoomLevel = 5.f;
	
private:
	void loadTextures();
	void buildScene();
};