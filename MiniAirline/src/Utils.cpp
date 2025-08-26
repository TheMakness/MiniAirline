#include "Utils.h"


sf::Vector2f Utils::lerp(sf::Vector2f source, sf::Vector2f target, float alpha)
{
    return sf::Vector2f(
        source.x + (target.x - source.x) * alpha,
        source.y + (target.y - source.y) * alpha
    );
}
