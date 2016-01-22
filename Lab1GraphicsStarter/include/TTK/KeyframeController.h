#pragma  once

#include "TTK/AnimationMath.h"

template <typename T>
struct SpeedControlTableRow
{
	int segment;
	float tValue;
	float arcLength;
	float arcLengthNormalized;
	T sampleValue;
};

template <typename T>
class KeyframeController
{
public:
	KeyframeController()
	{
		doesLoop = true;
		paused = false;
		keyLocalTime = 0.0f;
		curvePlaySpeed = 5.0f;
	}

	T update(float dt)
	{
		if (keys.size() >= 1)
		{
			if (!doesSpeedControl)
			{
				keyLocalTime += dt;

				if (keyLocalTime >= 1.0f)
				{
					currentKeyframe = getNextFrame();
					keyLocalTime = 0.0f;
				}

				T p0 = keys[currentKeyframe];
				T p1 = keys[getNextFrame()];

				return lerp(p0, p1, keyLocalTime);
			}
			else
			{
				keyLocalTime += (dt / curvePlaySpeed);

				if (keyLocalTime >= 1.0f)
				{
					if (doesLoop)
						keyLocalTime = 0.0f;
					else
						keyLocalTime = 1.0f;
				}

				for (int i = 1; i < speedControlLookUpTable.size(); i++)
				{				
					if (speedControlLookUpTable[i].arcLengthNormalized >= keyLocalTime)
					{
						// Calculate t value
						float arc0 = speedControlLookUpTable[i - 1].arcLengthNormalized;
						float arc1 = speedControlLookUpTable[i].arcLengthNormalized;
						float tVal = invLerp(keyLocalTime, arc0, arc1);

						// Calculate intermediate sample
						T sample0 = speedControlLookUpTable[i - 1].sampleValue;
						T sample1 = speedControlLookUpTable[i].sampleValue;

						return lerp(sample0, sample1, tVal);
					}
				}
			}
		}
		else
			return T();
	}

	int getNextFrame()
	{
		int nextFrame = currentKeyframe + 1;

		int numKeys = keys.size();

		if (nextFrame >= numKeys)
		{
			if (doesLoop)
			{
				nextFrame = 0;
			}
			else
			{
				nextFrame = numKeys - 1;
			}
		}

		return nextFrame;
	}

	void calculateLookupTable(int numSamples)
	{
		if (keys.size() > 1)
		{
			// Clear existing table
			speedControlLookUpTable.clear();

			float timeStep = 1.0f / numSamples;

			for (int i = 0; i < keys.size() - 1; i++)
			{
 				for (float j = 0.0f; j <= 1.0f; j += timeStep)
				{
					SpeedControlTableRow<T> row;
					row.segment = i;
					row.tValue = j;
					row.sampleValue = lerp<T>(keys[i], keys[i + 1], j);

					speedControlLookUpTable.push_back(row);
				}
			}

			int numEntries = speedControlLookUpTable.size();

			// Calculate arc lengths
			if (numEntries > 0)
			{
				speedControlLookUpTable[0].arcLength = 0.0f;
				speedControlLookUpTable[0].arcLengthNormalized = 0.0f;
			}

			for (int i = 1; i < numEntries; i++)
			{
				float distance = magnitude<T>(speedControlLookUpTable[i].sampleValue, speedControlLookUpTable[i - 1].sampleValue);
				speedControlLookUpTable[i].arcLength = distance + speedControlLookUpTable[i - 1].arcLength;
			}

			// Store total length of curve
			float totalCurveLength = speedControlLookUpTable[numEntries - 1].arcLength;

			for (int i = 1; i < numEntries; i++)
				speedControlLookUpTable[i].arcLengthNormalized = speedControlLookUpTable[i].arcLength / totalCurveLength;
		}
	}

	int currentKeyframe;
	std::vector<T> keys;
	float keyLocalTime;
	bool doesLoop;
	bool paused;

	// Speed control
	bool doesSpeedControl;
	std::vector<SpeedControlTableRow<T>> speedControlLookUpTable;
	float curvePlaySpeed;
};