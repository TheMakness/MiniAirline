#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	SceneNode();

	void update(sf::Time deltaTime);
	sf::Vector2f getWorldPosition() const;
	sf::Transform getWorldTransform() const;
	void attachChild(Ptr child);
	Ptr detachChild(const SceneNode& node);

	// Inherited via Drawable
   
	



private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void updateCurrent(sf::Time deltaTime);
	void updateChildren(sf::Time deltaTime);

private:
	std::vector<Ptr> m_Children;
	SceneNode* m_Parent;
};