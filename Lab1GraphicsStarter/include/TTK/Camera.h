//////////////////////////////////////////////////////////////////////////
//
// This header is a part of the Tutorial Tool Kit (TTK) library. 
// You may not use this header in your GDW games.
//
//
// Michael Gharbharan 2015
//
//////////////////////////////////////////////////////////////////////////

#ifndef TTK_CAMERA_H
#define TTK_CAMERA_H

#include "TTK/TTK.h"

namespace TTK
{
	class TTK_API Camera
	{
	public:
		enum ProjectionMode
		{
			PERSPECTIVE = 0,
			ORTHO
		};

		Camera();
		Camera(ProjectionMode projMode, float winWidth, float winHeight, float moveSpeed = 0.5f, TTK::Vector3 pos = TTK::Vector3(10.0f), TTK::Vector3 focalPoint = TTK::Vector3(0.0f), float near = 0.01f, float far = 1000.0f, float fovDeg = 60.0f);
		~Camera();

		//View Related Functions /////////////////////////////////////////////////
		void moveForward();
		void moveBackward();
		void moveLeft();
		void moveRight();
		void moveUp(); // moves along global up
		void moveDown(); // moves along global down
		float getMoveSpeed();

		void setMousePosition(TTK::Vector3 pos);

		void rotateX(float deg);
		void rotateY(float deg);

		// Description:
		// Rotates camera on X and Y axis.
		// Uses the change in mouse position
		// Calls rotateX() and rotateY()
		void rotateXY(float mouseX, float mouseY);

		void lookAt(TTK::Vector3 lookTarget);

		// Sets m_view
		void updateView();

		// Projection Related Functions //////////////////////////////////////////

		void setFOV(float nFov);
		void setNear(float nNear);
		void setFar(float nFar);
		void setAspect(float nAspect);
		void setProjectionMatrix(TTK::Matrix4x4 newProj);
		void setProjectionMode(ProjectionMode newProjMode);
		void setViewPortSize(int winWidth, int winHeight);

		// Description:
		// Recomputes the aspect ratio.
		// Sets m_aspect to (width / height)
		// Returns:
		// The newly computed aspect ratio
		float updateAspectRatio(float width, float height);

		// Description:
		// Recomputes projection matrix.
		// If you call any of the functions above, you must call this function
		// to update the projection using the new values.
		// Sets m_proj to TTK::create*Projection(...) depending on projection type
		// Returns:
		// The newly computed projection matrix
		TTK::Matrix4x4 updateProjection();

		// Set Functions /////////////////////////////////////////////////////////
		void setMoveSpeed(float nSpeed);
		void setEye(TTK::Vector3 nEye);
		void setCenter(TTK::Vector3 nCtr);

		// Get Functions /////////////////////////////////////////////////////////
		TTK::Matrix4x4 getViewMat();
		TTK::Matrix4x4 getProjMat();
		TTK::Matrix4x4 getViewProjMat();
		TTK::Vector3 getEye();
		TTK::Vector3 getCenter();


	private:
		float m_moveSpeed;	// Used by move functions
		float m_aspect;		// Aspect ratio
		float m_fov;		// Field of view

		float m_near;		// Near clip plane
		float m_far;		// Far clip plane

		float m_pitch;		// Rotation on X axis
		float m_yaw;		// Rotation on Y axis

		TTK::Vector3 m_eye;	// Camera position
		TTK::Vector3 m_ctr;	// Camera's point of focus

		TTK::Vector3 m_up;		// Camera up (unit length)
		TTK::Vector3 m_fwd;	// Camera forward (unit length)
		TTK::Vector3 m_left;	// Camera left (unit length)

		TTK::Matrix4x4 m_view;	// View matrix
		TTK::Matrix4x4 m_proj;	// Projection matrix

		TTK::Vector3 m_mPos;	// Mouse Position

		ProjectionMode m_projMode;
		float m_width, m_height; // viewport sizes
	};
}
#endif