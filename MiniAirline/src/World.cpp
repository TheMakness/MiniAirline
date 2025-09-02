#include "World.h"
#include "SpriteNode.h"
#include "Arrow.h"
#include "RectangleShapeNode.h"
#include "Runway.h"


#define getRandom() static_cast <float> (rand()) / static_cast <float> (RAND_MAX)

World::World(sf::RenderWindow& window) :
	m_Window(window)
	, m_WorldView(window.getDefaultView())
	, m_Textures()
	, m_SceneGraph()
	, m_SceneLayers()
	, m_WorldBounds({ 0,0 } ,{ m_WorldView.getSize().x * 2,m_WorldView.getSize().y * 2 })
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

bool World::collisionCheck() const
{
	//Perfom collision Check only on Air layer

	for (auto& node : m_SceneLayers[static_cast<int>(Layer::Air)]->getChildren())
	{
		if (node->getCategory() == Category::Aircraft)
		{
			Aircraft* a = dynamic_cast<Aircraft*>(node.get());
			sf::Vector2f position = a->getPosition();

			for(auto& otherNode : m_SceneLayers[static_cast<int>(Layer::Air)]->getChildren())
			{
				if (node == otherNode)
					continue;
				if ((position - otherNode->getPosition()).length() < 50.f)
					return true;
			}
		}
	}

	return false;
}

void World::loadTextures()
{
	m_Textures.load(Textures::ID::Airplane, "media/textures/Plane.png");
	m_Textures.load(Textures::ID::Landscape, "media/textures/Map.png");
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

	//Init Background
	auto backgroundRect = std::make_unique<RectangleShapeNode>(RectangleShapeNode(
		{ m_WorldBounds.size.x, m_WorldBounds.size.y }
		, {m_WorldBounds.position.x, m_WorldBounds.position.y}));

	backgroundRect->setFillColor({ 25,25,25,255 });
	m_SceneLayers[static_cast<int>(Layer::Background)]
		->attachChild(std::move(backgroundRect));

	//Init Runway

    auto runway = std::make_unique<Runway>(
        sf::Vector2f{ 600,100 },
        sf::Vector2f{ m_WorldBounds.getCenter().x, m_WorldBounds.getCenter().y },
        sf::degrees(45)
    );

    m_SceneLayers[static_cast<int>(Layer::Ground)]
        ->attachChild(std::move(runway));

	//Init planes
	for (size_t i = 0; i < 4; i++)
	{
		auto aircraft = std::make_unique<Aircraft>(Aircraft::Type::Civilian, m_Textures);
		aircraft->setPosition({getRandom() * m_WorldBounds.size.x, getRandom() * m_WorldBounds.size.y});
		aircraft->SetVelocity((m_WorldBounds.getCenter() - aircraft->getPosition()).normalized() * 50.f);
		aircraft->setDesiredVelocity(aircraft->getVelocity());
		aircraft->AlignToVelocity();
		aircraft->setScale({ 0.3f, 0.3f });
	
		m_SceneLayers[static_cast<int>(Layer::Air)]->attachChild(std::move(aircraft));
	}


}

void World::update(sf::Time deltaTime)
{
	while (!m_CommandQueue.isEmpty())
		m_SceneGraph.onCommand(m_CommandQueue.pop(), deltaTime);
	m_SceneGraph.update(deltaTime);
	bool col = collisionCheck();
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
