//////////////////////////////////////////////////////////////////////////
//
// This header is a part of the Tutorial Tool Kit (TTK) library. 
// You may not use this header in your GDW games.
//
//
// Michael Gharbharan 2015
//
//////////////////////////////////////////////////////////////////////////

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "TTK/Matrix4x4.h"
#include "TTK/Vector3.h"
#include "TTK/Quaternion.h"
#include "TTK/AnimationClip.h"
#include "TTK/JointTypes.h"
#include "TTK/GraphicsUtils.h"

namespace TTK
{
	class TTK_API GameObject
	{
	private:
		Matrix4x4 localTransformationMatrix;
		Matrix4x4 localToWorldMatrix;

		GameObject* parent;
		std::vector<GameObject*> children;

		AnimationClip currentAnimation;
		AnimationClip nextAnimation;

		JointDescriptor* jointData;
		JointDescriptor* nextJointData;

		float transitionTime;
		float currentTransistionTime;

	public:
		GameObject();

		void setCurrentAnimation(AnimationClip anim);
		void setNextAnimation(AnimationClip anim, float _transistionTime);

		void Update(float dt);
		void Draw();

		Matrix4x4 getLocalToWorldMatrix();
		Vector3 getWorldPosition();
		Quaternion getWorldRotation();

		void addChild(GameObject* newChild);
		GameObject* findRootGameObject(); // change
		GameObject* findChildByName(std::string name);

		Vector3 localPosition;
		Quaternion localRotation;
		Vector4 colour;
		float scale;
		float rotX, rotY, rotZ;

		std::string name;
	};
}
#endif // !GAMEOBJECT_H

