//////////////////////////////////////////////////////////////////////////
//
// This header is a part of the Tutorial Tool Kit (TTK) library. 
// You may not use this header in your GDW games.
//
//
// Michael Gharbharan 2015
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <math.h>
#include <random>

// magnitude
template<typename T>
inline float magnitude(T d0, T d1)
{
	T difference = d1 - d0;
	float magSqrd = (difference * difference);
	return sqrt(magSqrd);
}

// inverse lerp
template <typename T>
inline float invLerp(T d, T d0, T d1)
{
	return (d - d0) / (d1 - d0);
}

// Linear interpolation 

inline float lerp(float a0, float a1, float t)
{
	return (1 - t) * a0 + t * a1;
}

inline TTK::Vector3 lerp(TTK::Vector3 p0, TTK::Vector3 p1, float t)
{
	return p0 * (1 - t) + p1 * t;
}

template <typename T>
T lerp(T d0, T d1, float t)
{
	return d0 * (1 - t) + d1 * t;
}

// Catmull-Rom interpolation

// Returns a point between p1 and p2
template <typename T>
T catmull(T p0, T p1, T p2, T p3, float t)
{
	return	((p1 * 2.0f) + (-p0 + p2) * t +
			((p0 * 2.0f) - (p1 * 5.0f) + (p2 * 4.0f) - p3) * (t * t) +
			(-p0 + (p1 * 3.0f) - (p2 * 3.0f) + p3) * (t * t * t)) * 0.5f;
}

// Bezier interpolation

template <typename T>
T bezier(T p0, float t)
{
	return p0;
}

template <typename T>
T bezier(T p0, T p1, float t)
{
	return lerp(bezier(p0, t), bezier(p1, t), t);
}

template <typename T>
T bezier(T p0, T p1, T p2, float t)
{
	return lerp(bezier(p0, p1, t), bezier(p1, p2, t), t);
}

template <typename T>
T bezier(T p0, T p1, T p2, T p3, float t)
{
	return lerp(bezier(p0, p1, p2, t), bezier(p1, p2, p3, t), t);
}

template <typename T>
T bezier(const T p[], const int degree, const float t)
{
	if (degree == 0)
		return *p;
	else
		return lerp(bezier(p, degree - 1, t), bezier(p + 1, degree - 1, t), t);
}

// NLERP
inline TTK::Vector3 nlerp(TTK::Vector3 p0, TTK::Vector3 p1, float t)
{
	return TTK::Vector3::normalize(lerp<TTK::Vector3>(p0, p1, t));
}

inline TTK::Vector3 slerp(TTK::Vector3 d0, TTK::Vector3 d1, float t)
{
	float d = TTK::Vector3::dot(d0, d1);

	if (d == 1.0f)
		return d0;
	else if (d == -1.0f)
		return lerp(d0, d1, t);

	float angle = acos(d);
	float s = sin(angle);

	return (d0 * sin((1.0f - t) * angle) + d1 * sin(t * angle)) / s;
}

// Returns a random float between 0 and 1
inline float randomFloat01()
{
	return (float)rand() / (float)RAND_MAX;
}

inline float randomFloatRange(float min = -1.0f, float max = 1.0f)
{
	return min + ((max - min) * rand()) / (RAND_MAX + 1.0f);
}

inline TTK::Vector3 randomDirection()
{
	return TTK::Vector3(randomFloatRange(), randomFloatRange(), randomFloatRange());
}

inline TTK::Vector3 randomColourRGB()
{
	return TTK::Vector3(randomFloatRange(0.0f), randomFloatRange(0.0f), randomFloatRange(0.0f)).normalized();
}