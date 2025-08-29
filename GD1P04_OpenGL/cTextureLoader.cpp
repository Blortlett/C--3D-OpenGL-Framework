#include "cTextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <glew.h>
#include <stb_image.h>

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

    // Create and bind a new texture variable
    glGenTextures(1, &Texture_Position);
    glBindTexture(GL_TEXTURE_2D, Texture_Position);

    // Check how many components the loaded image has (RGBA or RGB?)
    GLint LoadedComponents = (ImageComponents == 4) ? GL_RGBA : GL_RGB;

    // Populate the texture with the image data
    glTexImage2D(   GL_TEXTURE_2D, 0, LoadedComponents, ImageWidth, ImageHeight, 0,
                    LoadedComponents, GL_UNSIGNED_BYTE, ImageData);

    // QUICK HACK! Pixel perfect rendering... deleteable
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Generate the mipmaps, free the memory and unbind the texture
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(ImageData);
    glBindTexture(GL_TEXTURE_2D, 0);
}
