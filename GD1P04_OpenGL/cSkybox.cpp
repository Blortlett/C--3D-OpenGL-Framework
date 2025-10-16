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

    // CRITICAL: Disable face culling for skybox
    glDisable(GL_CULL_FACE);

    // Disable depth writing so skybox doesn't block other objects
    glDepthMask(GL_FALSE);

    // Change depth function to render skybox at maximum depth
    glDepthFunc(GL_LEQUAL);

    glUseProgram(_Skybox_Program);

    // Bind the Skybox Texture as a cube map
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mCubemapTexture);
    GLint texLoc = glGetUniformLocation(_Skybox_Program, "Texture_Skybox");
    if (texLoc != -1)
    {
        glUniform1i(texLoc, 0);
    }
    else
    {
        std::cout << "Warning: Texture_Skybox uniform not found in shader!" << std::endl;
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
    else
    {
        std::cout << "Warning: VP uniform not found in shader!" << std::endl;
    }

    // Render the skybox using the cSkyCube's render method
    mSkyCube.bind();

    if (!mSkyCube.getIndices().empty())
    {
        glDrawElements(GL_TRIANGLES, (GLsizei)mSkyCube.getIndices().size(), GL_UNSIGNED_INT, 0);
    }
    else
    {
        std::cout << "Warning: No indices in skybox cube!" << std::endl;
    }

    mSkyCube.unbind();

    // CRITICAL: Restore OpenGL state for normal rendering
    glDepthFunc(GL_LESS);        // Restore default depth function
    glDepthMask(GL_TRUE);        // Re-enable depth writing (THIS WAS MISSING!)
    glEnable(GL_CULL_FACE);      // Re-enable face culling

    // Unbind texture and program
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    glUseProgram(0);
}