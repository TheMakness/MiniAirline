#include "World.h"
#include "SpriteNode.h"
#include "Arrow.h"


#define getRandom() static_cast <float> (rand()) / static_cast <float> (RAND_MAX)

World::World(sf::RenderWindow& window) :
	m_Window(window)
	, m_WorldView(window.getDefaultView())
	, m_Textures()
	, m_SceneGraph()
	, m_SceneLayers()
	, m_WorldBounds({ 0,0 } ,{ m_WorldView.getSize().x * 10,m_WorldView.getSize().y * 10 })
	, m_SpawnPosition(m_WorldView.getSize().x / 2, m_WorldView.getSize().y / 2)
{
	loadTextures();
	buildScene();

	m_WorldView.setCenter(m_WorldBounds.getCenter());
	//m_WorldView.zoom(2.f);
}

void World::draw()
{
	m_Window.setView(m_WorldView);
	m_Window.draw(m_SceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return m_CommandQueue;
}

const sf::View& World::getView() const
{
	return m_WorldView;
}

const sf::RenderWindow& World::getRenderWindow() const
{
	return m_Window;
}

void World::loadTextures()
{
	m_Textures.load(Textures::ID::Airplane, "media/textures/Plane.png");
	m_Textures.load(Textures::ID::Landscape, "media/textures/Desert.png");
}

void World::buildScene()
{
	// Layer initialize
	for (size_t i = 0; i < static_cast<int>(Layer::LayerCount); i++)
	{
		SceneNode::Ptr layer(new SceneNode());
		m_SceneLayers[i] = layer.get();
		m_SceneGraph.attachChild(std::move(layer));
	}

	//Tiled background texture
	sf::Texture& texture = m_Textures.get(Textures::ID::Landscape);
	sf::IntRect textureRect(m_WorldBounds);
	texture.setRepeated(true);

	//Init sprite node that contains background texture
	
	auto backgroundSprite = std::make_unique<SpriteNode>(texture, textureRect);
	backgroundSprite->setPosition({ m_WorldBounds.position.x, m_WorldBounds.position.y });
	m_SceneLayers[static_cast<int>(Layer::Background)]
		->attachChild(std::move(backgroundSprite));

	//Init planes
	for (size_t i = 0; i < 5; i++)
	{
		auto aircraft = std::make_unique<Aircraft>(Aircraft::Type::Civilian, m_Textures);
		aircraft->setPosition({getRandom() * m_WorldBounds.size.x, getRandom() * m_WorldBounds.size.y});
		aircraft->SetVelocity((m_WorldBounds.getCenter() - aircraft->getPosition()).normalized() * 200.f);
		aircraft->setDesiredVelocity(aircraft->getVelocity());
		aircraft->AlignToVelocity();
		//aircraft->setPosition({ 967, 526 });
	
		m_SceneLayers[static_cast<int>(Layer::Air)]->attachChild(std::move(aircraft));
	}


}

void World::update(sf::Time deltaTime)
{
	while (!m_CommandQueue.isEmpty())
		m_SceneGraph.onCommand(m_CommandQueue.pop(), deltaTime);
	m_SceneGraph.update(deltaTime);

}

void World::zoomIn()
{
	if (m_ZoomLevel > m_MinZoomLevel)
	{
		m_WorldView.zoom(.9f);
		m_ZoomLevel -= .1f;
	}
}

void World::zoomOut()
{
	if (m_ZoomLevel < m_MaxZoomLevel)
	{
		m_WorldView.zoom(1.1f);
		m_ZoomLevel += .1f;
	}
}
