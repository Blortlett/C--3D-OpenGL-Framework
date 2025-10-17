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


#include "cTextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <glew.h>
#include <stb_image.h>

cTextureLoader::cTextureLoader()
{
    LoadTexture("Texture_01_A.png");
    LoadTexture("Texture_01_B.png");
    LoadTexture("Cooked.png");
    LoadTexture("Uncooked.png");
    LoadTexture("Reflection_Map.png");

    LoadCubemap("Cubemap");
}

void cTextureLoader::LoadCubemap(const char* _folderName)
{
    // Array of cubemap face filenames in OpenGL order: +X, -X, +Y, -Y, +Z, -Z
    const char* faceNames[] = {
        "_px.png", "_nx.png",
        "_py.png", "_ny.png",
        "_pz.png", "_nz.png"
    };

    // Generate full folder path
    std::string folderPath = mResourcePath + _folderName + "/";

    // Generate and bind cubemap texture
    glGenTextures(1, &Cubemap_Texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, Cubemap_Texture);

    // Load each face
    int ImageWidth, ImageHeight, ImageComponents;
    for (int i = 0; i < 6; i++)
    {
        std::string fullPath = folderPath + faceNames[i];

        // Load texture data
        unsigned char* ImageData = stbi_load(
            fullPath.c_str(),
            &ImageWidth, &ImageHeight, &ImageComponents, 0
        );

        if (!ImageData)
        {
            std::cout << "Failed to load cubemap texture: " << fullPath << std::endl;
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
            return;
        }

        // Cubemap should be full color (RGB)
        GLint LoadedComponents = (ImageComponents == 4) ? GL_RGBA : GL_RGB;

        // Load texture data into cubemap face
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, // Face target
            0, LoadedComponents, ImageWidth, ImageHeight, 0,
            LoadedComponents, GL_UNSIGNED_BYTE, ImageData
        );

        // Free image data
        stbi_image_free(ImageData);
    }

    // Set texture parameters for cubemap
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Generate mipmaps and unbind
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void cTextureLoader::LoadTexture(const char* fileName)
{
    // Texture properties (Assigned by stbi_load())
    int ImageWidth;
    int ImageHeight;
    int ImageComponents;
    // Generate full filepath
    std::string fullPath = mResourcePath + fileName;

    // Set stb to flip textures so they align with the way OpenGL reads textures
    stbi_set_flip_vertically_on_load(true);

    // Load Texture
    unsigned char* ImageData = stbi_load(
        fullPath.c_str(),
        &ImageWidth, &ImageHeight, &ImageComponents, 0
    );
    if (!ImageData)
    {
        std::cout << "Failed to load texture: " << fullPath << std::endl;
        return;
    }

    // Create and bind a new texture variable
    if (TimesRun == 0)
    {
        glGenTextures(1, &Texture_01_A);
        glBindTexture(GL_TEXTURE_2D, Texture_01_A);
    }
    else if (TimesRun == 1)
    {
        glGenTextures(1, &Texture_01_B);
        glBindTexture(GL_TEXTURE_2D, Texture_01_B);
    }
    else if (TimesRun == 2)
    {
        glGenTextures(1, &Texture_Food_Cooked);
        glBindTexture(GL_TEXTURE_2D, Texture_Food_Cooked);
    }
    else if (TimesRun == 3)
    {
        glGenTextures(1, &Texture_Food_Uncooked);
        glBindTexture(GL_TEXTURE_2D, Texture_Food_Uncooked);
    }
    else if (TimesRun == 4)
    {
        glGenTextures(1, &Reflection_Map);
        glBindTexture(GL_TEXTURE_2D, Reflection_Map);
    }

    // Check how many components the loaded image has (RGBA or RGB?)
    GLint LoadedComponents = (ImageComponents == 4) ? GL_RGBA : GL_RGB;

    // Populate the texture with the image data
    glTexImage2D(   GL_TEXTURE_2D, 0, LoadedComponents, ImageWidth, ImageHeight, 0,
                    LoadedComponents, GL_UNSIGNED_BYTE, ImageData);

    // Pixel perfect filtering...
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Generate the mipmaps, free the memory and unbind the texture
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(ImageData);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Increment times run
    TimesRun++;
}
