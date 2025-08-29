#pragma once
#include <glew.h>
#include <string>

class cTextureLoader
{
private:
    int TimesRun = 0;
    const std::string mResourcePath = "Resources/Textures/";
    
    // Singleton mumbo jumbo
    cTextureLoader() = default;
    
    // Delete copy/move constructors
    cTextureLoader(const cTextureLoader&) = delete;
    cTextureLoader& operator=(const cTextureLoader&) = delete;
    cTextureLoader(cTextureLoader&&) = delete;
    cTextureLoader& operator=(cTextureLoader&&) = delete;

public:
    GLuint Texture_Lancer;
    GLuint Texture_Orc;
    
    // Singleton access point
    static cTextureLoader& GetInstance()
    {
        static cTextureLoader instance; // Created once, reused
        return instance;
    }

    void LoadTexture(const char* fileName);
};