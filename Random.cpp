// Author: Chi-Hao Kuo
// Created: 10/4/2015
// Updated: 10/5/2015

// A Random library

#include <ctime>		// time

#include "random.h"

/*--------------------------------------------------------------------------*
Name:           Random

Description:    Constructor with seed value comes from time(NULL).

Arguments:      None.

Returns:        None.
*---------------------------------------------------------------------------*/
Random::Random() : seed_(RandomSeed())
{
	UseDefaultSeed();
}

/*--------------------------------------------------------------------------*
Name:           Random

Description:    Constructor with preset seed value.

Arguments:      seed: default seed for random number engine.

Returns:        None.
*---------------------------------------------------------------------------*/
Random::Random(unsigned int seed) : seed_(seed)
{
	UseDefaultSeed();
}

/*--------------------------------------------------------------------------*
Name:           Random

Description:    Destructor.

Arguments:      None.

Returns:        None.
*---------------------------------------------------------------------------*/
Random::~Random()
{
}

/*--------------------------------------------------------------------------*
Name:           UseRandomSeed

Description:    Use random seed for generator.

Arguments:      None.

Returns:        None.
*---------------------------------------------------------------------------*/
void Random::UseRandomSeed(void)
{
	generator_.seed(RandomSeed());
}

/*--------------------------------------------------------------------------*
Name:           UseDefaultSeed

Description:    Use default seed for generator.

Arguments:      None.

Returns:        None.
*---------------------------------------------------------------------------*/
void Random::UseDefaultSeed(void)
{
	generator_.seed(seed_);
}


/*--------------------------------------------------------------------------*
Name:           GetSeed

Description:    Get seed for random number engine.

Arguments:      None.

Returns:        Seed for random number engine.
*---------------------------------------------------------------------------*/
unsigned int Random::GetSeed(void)
{
	return seed_;
}

/*--------------------------------------------------------------------------*
Name:           SetSeed

Description:    Set seed for random number engine.

Arguments:      seed: Seed for random number engine.

Returns:        None.
*---------------------------------------------------------------------------*/
void Random::SetSeed(unsigned int seed)
{
	seed_ = seed;
	UseDefaultSeed();
}

/*--------------------------------------------------------------------------*
Name:           RandomSeed

Description:    Obtain random seed value from time(NULL).

Arguments:      None.

Returns:        Seed value from time(NULL).
*---------------------------------------------------------------------------*/
unsigned int Random::RandomSeed(void)
{
	return (static_cast<unsigned int>(time(NULL)));
}

/*--------------------------------------------------------------------------*
Name:           RangeInt

Description:    Returns a random int number between and min[inclusive] and max[inclusive]

Arguments:      min: lower boundry of range.
				max: upper boundry of range.

Returns:        Random int number between min~max.
*---------------------------------------------------------------------------*/
int Random::RangeInt(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);

	return distribution(generator_);
}

/*--------------------------------------------------------------------------*
Name:           RangeFloat

Description:    Returns a random float number between and min[inclusive] and max[inclusive]

Arguments:      min: lower boundry of range.
				max: upper boundry of range.

Returns:        Random float number between min~max.
*---------------------------------------------------------------------------*/
float Random::RangeFloat(float min, float max)
{
	std::uniform_real_distribution<float> distribution(min, max);

	return distribution(generator_);
}

/*--------------------------------------------------------------------------*
Name:           NormalRange

Description:    Returns a normal distribution random float number with mean and standard deviation.
				68% of values are within 1 standard deviation of the mean.
				95% of values are within 2 standard deviations of the mean.
				99.7% of values are within 3 standard deviations of the mean.

Arguments:      mean: mean value of normal distribution.
				stddev: standard deviation.
				is_clamp: flag on if the random number is clamped between min~max.
				calculate_minmax: should the min/max value be auto-calculated (as 3 times stddev).
				min: lower boundry of range.
				max: upper boundry of range.

Returns:        Random normal (Gaussian) float number (between min~max if clamped).
*---------------------------------------------------------------------------*/
float Random::NormalRange(float mean, float stddev, bool is_clamp, bool calculate_minmax, float min, float max)
{
	std::normal_distribution<float> distribution(mean, stddev);

	float value = distribution(generator_);

	// 0.3% of values will be outside of 3 times standard deviation
	// use the flag to eliminate such value
	// if the random value is outside the boundry, reroll another one

	if (is_clamp)
	{
		// use counter to make sure it's not an infinite loop
		// if it runs for more than 10 times, stop it

		unsigned int counter = 0;

		if (calculate_minmax)
		{
			min = NormalMin(mean, stddev);
			max = NormalMax(mean, stddev);
		}

		while ((value < min) || (value > max))
		{
			value = distribution(generator_);
			++counter;

			assert(counter < 10 && "Can't produce normal distribution random number");
		}
	}

	return value;
}

/*--------------------------------------------------------------------------*
Name:           NormalRangeMinMax

Description:    Returns a normal distribution random float number within the range of min and max.
				68% of values are within 1 standard deviation of the mean.
				95% of values are within 2 standard deviations of the mean.
				99.7% of values are within 3 standard deviations of the mean.

Arguments:      min: lower boundry of range.
				max: upper boundry of range.

Returns:        Random normal (Gaussian) float number between min~max.
*---------------------------------------------------------------------------*/
float Random::NormalRangeMinMax(float min, float max)
{
	// calculate mean and standard deviation from min, max
	// then use such data to get Gaussian random number clamped between min~max

	float mean = (min + max) / 2.0f;
	float stddev = (mean - min) / 3.0f;

	return NormalRange(mean, stddev, true, false, min, max);
}

/*--------------------------------------------------------------------------*
Name:           NormalBoundry

Description:    Return the boundry value from normal distribution.
				Which is 3 times of standard deviation (99.7% of values are within mean).

Arguments:      stddev: standard deviation.

Returns:        Boundary from mean value.
*---------------------------------------------------------------------------*/
float Random::NormalBoundry(float stddev)
{
	return stddev * 3.0f;
}

/*--------------------------------------------------------------------------*
Name:           NormalMin

Description:    Return the lower boundry value from normal distribution (99.7% of values are within mean).
				Which is 3 times of standard deviation (99.7% of values are within mean).

Arguments:      mean: mean value of normal distribution.
				stddev: standard deviation.

Returns:        Lower boundary from mean value.
*---------------------------------------------------------------------------*/
float Random::NormalMin(float mean, float stddev)
{
	return (mean - NormalBoundry(stddev));
}

/*--------------------------------------------------------------------------*
Name:           NormalMax

Description:    Return the upper boundry value from normal distribution (99.7% of values are within mean).
				Which is 3 times of standard deviation (99.7% of values are within mean).

Arguments:      mean: mean value of normal distribution.
				stddev: standard deviation.

Returns:        Upper boundary from mean value.
*---------------------------------------------------------------------------*/
float Random::NormalMax(float mean, float stddev)
{
	return (mean + NormalBoundry(stddev));
}

/*--------------------------------------------------------------------------*
Name:           CoinToss

Description:    Returns true/false based on percentage (Bernoulli distribution)

Arguments:      percentage: Percentage value for True.

Returns:        True or false.
*---------------------------------------------------------------------------*/
bool Random::CoinToss(float percentage)
{
	assert((percentage <= 1.0f) && (percentage >= 0.0f) && "Percentage should be [0-1]");

	std::bernoulli_distribution distribution(percentage);

	return distribution(generator_);
}

/*--------------------------------------------------------------------------*
Name:           DiscreteInt

Description:    Return the discrete distribution from the weighted list.

Arguments:      list: initializer_list container for weight of each index.

Returns:        Random int number based on weight.
*---------------------------------------------------------------------------*/
int Random::DiscreteInt(DiscreteList &list)
{
	std::discrete_distribution<int> distribution(list);

	return distribution(generator_);
}
