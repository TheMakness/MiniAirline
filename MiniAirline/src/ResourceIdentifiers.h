#pragma once

namespace sf
{
	class Texture;
}

namespace Textures
{
	enum class ID
	{
		Airplane,
		Runway,
		Landscape,
	};
}


// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;