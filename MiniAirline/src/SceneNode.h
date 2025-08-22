#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Command.h"

class SceneNode : public sf::Transformable, public sf::Drawable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	SceneNode();

	void update(sf::Time deltaTime);
	sf::Vector2f getWorldPosition() const;
	sf::Transform getWorldTransform() const;

	void onCommand(const Command& command, sf::Time dt);
	virtual unsigned int getCategory() const;

	void attachChild(Ptr child);
	Ptr detachChild(const SceneNode& node);

private:
	// Inherited via Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void updateCurrent(sf::Time deltaTime);
	void updateChildren(sf::Time deltaTime);

private:
	std::vector<Ptr> m_Children;
	SceneNode* m_Parent;
};