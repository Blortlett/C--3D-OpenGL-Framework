#include "cTextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


void cTextureLoader::LoadTexture()//const char* fileName)
{
    // Load texture
    int ImageWidth;
    int ImageHeight;
    int ImageComponents;
    unsigned char* ImageData = stbi_load(   "Resources/Textures/Lancer-Walk02.png",
                                            &ImageWidth, &ImageHeight, &ImageComponents, 0);

    
}
