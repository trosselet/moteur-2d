#pragma once

class Sprite;

class Resources
{
public:
    Resources() = default;
    ~Resources();
    void CreateShaders();
    void CreateParticles();
    void CreateTextures();
    void CreateMaterials();
    
    static Resources& instance()
    {
        static Resources instance;
        return instance;
    }
    
    ////////////////////////////////
    /////// SPRITE

    Sprite* TEXTURE;
};
