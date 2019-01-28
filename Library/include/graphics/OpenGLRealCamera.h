//
//  OpenGLRealCamera.h
//  Stonefish
//
//  Created by Patryk Cieslak on 12/12/12.
//  Copyright (c) 2012-2019 Patryk Cieslak. All rights reserved.
//

#ifndef __Stonefish_OpenGLRealCamera__
#define __Stonefish_OpenGLRealCamera__

#include "graphics/OpenGLCamera.h"

namespace sf
{
    class ColorCamera;
 
    //! A class implementing a real camera in OpenGL.
    class OpenGLRealCamera : public OpenGLCamera
    {
    public:
        //! A constructor.
        /*!
         \param eyePosition the position of the camera eye in world space [m]
         \param direction a unit vector parallel to the camera optical axis
         \param cameraUp a unit vector pointing to the top edge of the image
         \param originX the x coordinate of the view origin in the program window
         \param originY the y coordinate of the view origin in the program window
         \param width the width of the view
         \param height the height of the view
         \param horizontalFovDeg the horizontal field of view of the camera [deg]
         \param horizonDistance the distance to the camera far plane [m]
         \param spp number of samples used (>1 means multisampling)
         \param ao a flag to decide if ambient occlusion should be rendered
         */
        OpenGLRealCamera(glm::vec3 eyePosition, glm::vec3 direction, glm::vec3 cameraUp,
                         GLint originX, GLint originY, GLint width, GLint height,
                         GLfloat horizontalFovDeg, GLfloat horizonDistance, GLuint spp = 1, bool ao = false);
        
        //! A destructor.
        ~OpenGLRealCamera();
        
        //! A method to render the low dynamic range (final) image to the screen.
        /*!
         \param destinationFBO the id of the framebuffer used as the destination for rendering
         */
        void DrawLDR(GLuint destinationFBO);
        
        //! A method that sets up the camera.
        void SetupCamera();
        
        //! A method used to set up the camera.
        /*!
         \param eye the position of the camera [m]
         \param dir a unit vector parallel to the camera optical axis
         \param up a unit vector pointing to the top edge of the image
         */
        void SetupCamera(glm::vec3 eye, glm::vec3 dir, glm::vec3 up);
        
        //! A method that updates camera world transform.
        void UpdateTransform();
        
        //! A method that flags the camera as needing update.
        void Update();
        
        //! A method returning the view matrix.
        glm::mat4 GetViewMatrix() const;
        
        //! A method returning the eye position.
        glm::vec3 GetEyePosition() const;
        
        //! A method returning a unit vector parallel to the optical axis of the camera.
        glm::vec3 GetLookingDirection() const;
        
        //! A method returning a unit vector pointing to the top edge of the image.
        glm::vec3 GetUpDirection() const;
        
        //! A method returning the type of the view.
        ViewType getType();
        
        //! A method to set a pointer to a camera sensor.
        /*!
         \param cam a pointer to a camera sensor
         */
        void setCamera(ColorCamera* cam);
         
        //! A method that informs if the camera needs update.
        bool needsUpdate();
        
    private:
        ColorCamera* camera;
        GLuint cameraFBO;
        GLuint cameraColorTex;
        
        glm::mat4 cameraTransform;
        glm::vec3 eye;
        glm::vec3 dir;
        glm::vec3 up;
        glm::vec3 tempEye;
        glm::vec3 tempDir;
        glm::vec3 tempUp;
        bool _needsUpdate;
        bool update;
    };
}

#endif