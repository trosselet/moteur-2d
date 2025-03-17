#pragma once
#include <SFML/Graphics/Shader.hpp>

class Shader : public sf::Shader
{
public:
    Shader(const std::filesystem::path& path, sf::Shader::Type type);
    ~Shader() = default;
};
