#include "Utils.h"


sf::Vector2f Utils::lerp(sf::Vector2f source, sf::Vector2f target, float alpha)
{
    return sf::Vector2f(
        source.x + (target.x - source.x) * alpha,
        source.y + (target.y - source.y) * alpha
    );
}

sf::Vector2f Utils::slerp(sf::Vector2f source, sf::Vector2f target, float alpha)
{
    // Step 1: Normalize source and target
    float sourceLen = std::sqrt(source.x * source.x + source.y * source.y);
    float targetLen = std::sqrt(target.x * target.x + target.y * target.y);

    if (sourceLen == 0.f || targetLen == 0.f)
        return Utils::lerp(source, target, alpha);

    sf::Vector2f srcNorm = source / sourceLen;
    sf::Vector2f tgtNorm = target / targetLen;

    // Step 2: Compute dot product and clamp to [-1, 1]
    float dot = srcNorm.x * tgtNorm.x + srcNorm.y * tgtNorm.y;
    dot = std::clamp(dot, -1.f, 1.f);

    // Step 3: Compute angle between vectors
    float theta = std::acos(dot);

    // Step 4: If angle is very small, fallback to lerp
    if (theta < 1e-5f)
        return Utils::lerp(source, target, alpha);

    // Step 5: Compute slerp
    float sinTheta = std::sin(theta);
    float scaleSrc = std::sin((1 - alpha) * theta) / sinTheta;
    float scaleTgt = std::sin(alpha * theta) / sinTheta;

    sf::Vector2f result = srcNorm * scaleSrc * sourceLen + tgtNorm * scaleTgt * targetLen;
    return result;
}
