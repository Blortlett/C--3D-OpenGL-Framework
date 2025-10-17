/************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c)
 2024 Media Design School
 File Name : cTextureLoader
 Description : This class loads textures to be used by OpenGL functions
 Author : Matthew Bartlett
 Mail : Matthew.Bartlett@mds.ac.nz
 ************************************************/


#pragma once
#include <glew.h>
#include <string>
#include <iostream>

class cTextureLoader
{
private:
    int TimesRun = 0;
    const std::string mResourcePath = "Resources/Textures/";
    
    // Singleton mumbo jumbo
    cTextureLoader();
    
    // Delete copy/move constructors
    cTextureLoader(const cTextureLoader&) = delete;
    cTextureLoader& operator=(const cTextureLoader&) = delete;
    cTextureLoader(cTextureLoader&&) = delete;
    cTextureLoader& operator=(cTextureLoader&&) = delete;

public:
    GLuint Texture_01_A;
    GLuint Texture_01_B;
    GLuint Reflection_Map;
    GLuint Texture_Food_Cooked;
    GLuint Texture_Food_Uncooked;
    GLuint Cubemap_Texture;
    
    // Singleton access point
    static cTextureLoader& GetInstance()
    {
        static cTextureLoader instance; // Created once, reused
        return instance;
    }

    void LoadCubemap(const char* _folderName);
    void LoadTexture(const char* fileName);
};