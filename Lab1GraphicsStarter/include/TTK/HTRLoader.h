#pragma once

#ifdef TTK_EXPORTS
#define TTK_API __declspec(dllexport)
#else
#define TTK_API __declspec(dllimport)
#endif

#include <string>
#include "TTK/JointTypes.h"

namespace TTK
{
	class TTK_API HTRLoader
	{
	public:

	//	friend class AnimationManager;

		HTRLoader();

		// Loads the specified HTR file. 
		// Returns true if successful
		bool loadHTR(std::string fileName);

		// Loop through each joint descriptor until the input jointName is found
		// If not found, will return a nullptr
		JointDescriptor* getJointDescriptorByName(std::string jointName);

		//	GameObject* getGameObjectByName(std::string jointName);

		//	void createGameObjects();

		//	GameObject* getRootGameObject();

		int getNumFrames(); // Returns the number of frames

	//private:

		void processHeader(std::string header, std::string value);

		// Increments the file pointer to the next line in the file
		// and copies it into buffer
		void goToNextValidLineInFile(FILE* fp, char* buffer);

		Quaternion createQuaternion(float rx, float ry, float rz);

		// Describes the data in the file

		std::string fileType;		// File extension
		std::string dataType;		// What kind of data is stored in file. 
		// Ie. HTRS means Hierarchical translations followed by rotations and scale

		int			fileVersion;	// Useful if you are generating binary object files, can check the version of the binary file, 
		//check version of text, if text > binary then reparse, otherwise just use binary

		int			numSegments;	// Number of bones in skeleton
		int			numFrames;		// number of frames in the animation
		int			fps;			// FPS of the animation

		RotationOrder	rotationOrder;	// Order to apply rotations
		std::string	calibrationUnits;// 
		char		upAxis;			// X, Y, Z (usually Y)
		std::string rotationUnits;	// "Degrees" or "Radians"
		char		boneLengthAxis;	// Axis that is aligned with bone

		// Actual animation data

		std::vector<JointDescriptor> jointDescriptors;	// Stores each joint and its parent (could be an array since we know number of segments)

		//std::vector<GameObject> jointGameObjects;

		//GameObject* rootGameObject;
	};
}