#include "SceneNode.h"
#include <cassert>

SceneNode::SceneNode() :
	m_Children(),
	m_Parent(nullptr)
{
}

void SceneNode::attachChild(Ptr child)
{
	child->m_Parent = this;
	m_Children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(m_Children.begin(), m_Children.end(),
		[&](Ptr& p) -> bool {return p.get() == &node;});
		assert(found != m_Children.end());
		Ptr result = std::move(*found);
		result->m_Parent = nullptr;
		m_Children.erase(found);
		return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Apply transform of current node
	states.transform *= getTransform();

	//Draw node and children with changed transform
	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const Ptr& child : m_Children)
	{
		child->draw(target, states);
	}
}

void SceneNode::update(sf::Time deltaTime)
{
	updateCurrent(deltaTime);
	updateChildren(deltaTime);
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->m_Parent)
		transform = node->getTransform() * transform;

	return transform;
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	// Command current node, if category matches
	if (command.category & getCategory())
		command.action(*this, dt);

	// Command children
	for (const Ptr& child : m_Children)
		child->onCommand(command, dt);
}

unsigned int SceneNode::getCategory() const
{
	return Category::Scene;
}

void SceneNode::updateCurrent(sf::Time deltaTime)
{

}

void SceneNode::updateChildren(sf::Time deltaTime)
{
	for (const Ptr& child : m_Children)
	{
		child->update(deltaTime);
	}
}
