// Author: Chi-Hao Kuo
// Created: 10/4/2015
// Updated: 10/5/2015

// A Random library

#pragma once

#include <random>

// static variables

typedef std::initializer_list<double> DiscreteList;

static const float PI = 3.1415926f;
static const int DEFAULT_UNI_MIN_I = 0;
static const int DEFAULT_UNI_MAX_I = 10000;
static const float DEFAULT_UNI_MIN_F = 0.0f;
static const float DEFAULT_UNI_MAX_F = 1.0f;
static const float DEFAULT_NOR_MEAN = 0.0f;
static const float DEFAULT_NOR_STDDEV = 0.33333f;
static const float DEFAULT_NOR_MIN = DEFAULT_NOR_MEAN - DEFAULT_NOR_STDDEV * 3.0f;
static const float DEFAULT_NOR_MAX = DEFAULT_NOR_MEAN + DEFAULT_NOR_STDDEV * 3.0f;
static const float DEFAULT_BER_PERC = 0.5f;

class Random
{
private:
	// Pseudo-random number engine
	std::default_random_engine generator_;
	
	// default seed value
	unsigned int seed_;

public:
	// constructor
	Random();
	Random(unsigned int seed);

	// destructor
	~Random();

	// use random seed for generator
	void UseRandomSeed(void);

	// return to default seed for generator
	void UseDefaultSeed(void);

	// getter
	unsigned int GetSeed(void);

	// setter
	void SetSeed(unsigned int seed);

	// obtain random seed value
	unsigned int RandomSeed(void);

	// Returns a random int number between and min[inclusive] and max[inclusive]
	int RangeInt(int min = DEFAULT_UNI_MIN_I, int max = DEFAULT_UNI_MAX_I);

	// Returns a random float number between and min[inclusive] and max[inclusive]
	float RangeFloat(float min = DEFAULT_UNI_MIN_F, float max = DEFAULT_UNI_MAX_F);

	// Returns a normal distribution random float number with mean and standard deviation
	// 68% of values are within 1 standard deviation of the mean
	// 95% of values are within 2 standard deviations of the mean
	// 99.7% of values are within 3 standard deviations of the mean
	float NormalRange(float mean = DEFAULT_NOR_MEAN, float stddev = DEFAULT_NOR_STDDEV, bool is_clamp = true, bool calculate_minmax = true, float min = DEFAULT_NOR_MIN, float max = DEFAULT_NOR_MAX);

	// Returns a normal distribution random float number within the range of min and max
	// mean is the (min + max) / 2
	// and standard deviation is (mean - min) / 3
	// 68% of values are within 1 standard deviation of the mean
	// 95% of values are within 2 standard deviations of the mean
	// 99.7% of values are within 3 standard deviations of the mean
	float NormalRangeMinMax(float min = DEFAULT_NOR_MIN, float max = DEFAULT_NOR_MAX);

	// return the boundry value from normal distribution
	// which is more than 3 times of standard deviation
	float NormalBoundry(float stddev = DEFAULT_NOR_STDDEV);

	// return the lower boundry value from normal distribution
	float NormalMin(float mean = DEFAULT_NOR_MEAN, float stddev = DEFAULT_NOR_STDDEV);

	// return the upper boundry value from normal distribution
	float NormalMax(float mean = DEFAULT_NOR_MEAN, float stddev = DEFAULT_NOR_STDDEV);

	// returns true/false based on percentage (Bernoulli distribution)
	bool CoinToss(float percentage = DEFAULT_BER_PERC);

	// return the discrete distribution from the weighted list
	int DiscreteInt(DiscreteList &list);
};