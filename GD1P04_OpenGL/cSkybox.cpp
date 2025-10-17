/************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c)
 2024 Media Design School
 File Name : cSkybox
 Description : cSkybox contains data and functions to render and display a skybox in a 3D scene.
 Author : Matthew Bartlett
 Mail : Matthew.Bartlett@mds.ac.nz
 ************************************************/

#include "cSkybox.h"
#include "cTextureLoader.h"

cSkybox::cSkybox(cCamera* _Camera, GLuint _CubemapTexture)
{
    mCamera = _Camera;
    mCubemapTexture = _CubemapTexture;
    mIndiciesCount = mSkyCube.GetIndices().size();
    mVerticiesCount = mSkyCube.GetVertices().size();
    if (mIndiciesCount == 0)
    {
        std::cout << "Error: No indices in cSkyCube during cSkybox initialization!" << std::endl;
    }
}

void cSkybox::Render(GLuint _Skybox_Program)
{
    if (!mCamera || mCubemapTexture == 0)
    {
        std::cout << "Skybox render failed - Camera: " << (mCamera != nullptr)
            << " Texture: " << mCubemapTexture << std::endl;
        return;
    }

    // Save current OpenGL state
    GLboolean depthMaskEnabled;
    GLint depthFunc;
    GLboolean cullFaceEnabled;
    GLint cullFaceMode;

    glGetBooleanv(GL_DEPTH_WRITEMASK, &depthMaskEnabled);
    glGetIntegerv(GL_DEPTH_FUNC, &depthFunc);
    glGetBooleanv(GL_CULL_FACE, &cullFaceEnabled);
    glGetIntegerv(GL_CULL_FACE_MODE, &cullFaceMode);

    // Set skybox-specific state
    glDepthMask(GL_FALSE);      // Disable depth writing
    glDepthFunc(GL_LEQUAL);     // Render at maximum depth
    glDisable(GL_CULL_FACE);    // Disable face culling for skybox

    glUseProgram(_Skybox_Program);

    // Bind the Skybox Texture as a cube map
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mCubemapTexture);
    GLint texLoc = glGetUniformLocation(_Skybox_Program, "Texture_Skybox");
    if (texLoc != -1)
    {
        glUniform1i(texLoc, 0);
    }

    // Setup the camera matrices
    // Remove translation from view matrix so skybox moves with camera
    glm::mat4 CamMatView = glm::mat4(glm::mat3(mCamera->GetViewMat()));
    glm::mat4 CamMatProj = mCamera->GetProjectionMat();
    glm::mat4 VP = CamMatProj * CamMatView;

    GLint vpLoc = glGetUniformLocation(_Skybox_Program, "VP");
    if (vpLoc != -1)
    {
        glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(VP));
    }

    // Render the skybox
    mSkyCube.bind();

    if (!mSkyCube.getIndices().empty())
    {
        glDrawElements(GL_TRIANGLES, (GLsizei)mSkyCube.getIndices().size(), GL_UNSIGNED_INT, 0);
    }

    mSkyCube.unbind();

    // Restore previous OpenGL state
    glDepthFunc(depthFunc);
    glDepthMask(depthMaskEnabled);

    if (cullFaceEnabled)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(cullFaceMode);
    }

    // Unbind texture and program
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    glUseProgram(0);
}