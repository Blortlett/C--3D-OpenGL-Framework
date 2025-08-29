#include "cTextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <glew.h>
#include <stb_image.h>

void cTextureLoader::LoadTexture() // const char* fileName)
{
    // Texture properties (Assigned by stbi_load())
    int ImageWidth;
    int ImageHeight;
    int ImageComponents;

    // Load Texture
    unsigned char* ImageData = stbi_load(
        "Resources/Textures/Lancer-Walk02.png",
        &ImageWidth, &ImageHeight, &ImageComponents, 0
    );

    // Create and bind a new texture variable
    glGenTextures(1, &Texture_Position);
    glBindTexture(GL_TEXTURE_2D, Texture_Position);

    // Check how many components the loaded image has (RGBA or RGB?)
    GLint LoadedComponents = (ImageComponents == 4) ? GL_RGBA : GL_RGB;

    // Populate the texture with the image data
    glTexImage2D(   GL_TEXTURE_2D, 0, LoadedComponents, ImageWidth, ImageHeight, 0,
                    LoadedComponents, GL_UNSIGNED_BYTE, ImageData);

    // Generate the mipmaps, free the memory and unbind the texture
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(ImageData);
    glBindTexture(GL_TEXTURE_2D, 0);
}
