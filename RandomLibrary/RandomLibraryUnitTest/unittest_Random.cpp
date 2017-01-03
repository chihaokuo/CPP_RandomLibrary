#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RandomLibraryUnitTest
{
	TEST_CLASS(UnitTest_Random)
	{
	public:

		TEST_METHOD(TestSeed)
		{
			// TODO: Your test code here

			// set seed and get the Nth integer
			// if the seed is the same, the Nth integer should also be the same

			Random random;
			int num1, num2;
			int num_numbers1 = random.RangeInt() % 1000;
			int num_numbers2 = random.RangeInt() % 1000;
			int seed1 = random.RangeInt();
			int seed2 = random.RangeInt();

			char output[20];
			sprintf_s(output, "Get %dth number\n", num_numbers1);
			Logger::WriteMessage(output);

			random.SetSeed(seed1);
			for (int i = 0; i < num_numbers1; ++i)
				num1 = random.RangeInt();

			random.SetSeed(seed2);
			for (int i = 0; i < num_numbers2; ++i)
				num2 = random.RangeInt();

			random.SetSeed(seed1);
			for (int i = 0; i < num_numbers1; ++i)
				num2 = random.RangeInt();

			// random number with the same seed should be the same
			Assert::AreEqual(num1, num2);

		}

		TEST_METHOD(TestRangeInt)
		{
			// TODO: Your test code here

			// output should be in range

			Random random;
			int lowerbound = random.RangeInt() % 100;
			int upperbound = random.RangeInt() % 100 + 5000;
			int loopnum = random.RangeInt() % 500 + 500;
			bool testresult = true;

			for (int i = 0; i < loopnum; ++i)
			{
				int num = random.RangeInt(lowerbound, upperbound);

				if ((num < lowerbound) || (num > upperbound))
				{
					testresult = false;
					break;
				}

			}

			Assert::IsTrue(testresult);

		}

		TEST_METHOD(TestRangeFloat)
		{
			// TODO: Your test code here

			// output should be in range

			Random random;
			float lowerbound = static_cast<float>(random.RangeInt() % 100);
			float upperbound = static_cast<float>(random.RangeInt() % 100 + 5000);
			int loopnum = random.RangeInt() % 500 + 500;
			bool testresult = true;

			for (int i = 0; i < loopnum; ++i)
			{
				float num = random.RangeFloat(lowerbound, upperbound);

				if ((num < lowerbound) || (num > upperbound))
				{
					testresult = false;
					break;
				}

			}

			Assert::IsTrue(testresult);

		}

		// NormalRange
		TEST_METHOD(TestNormalRange)
		{
			// TODO: Your test code here

			Random random;
			int p[10] = {};
			int nrolls = 10000;  // number of experiments
			int num_one_dev = 0;
			int num_two_dev = 0;
			int num_three_dev = 0;

			for (int i = 0; i < nrolls; ++i) 
			{
				float number = random.NormalRange(5.0f, 2.0f);
				if ((number >= 0.0f) && (number < 10.0f))
					++p[static_cast<int>(number)];

				if ((number >= 3.0f) && (number < 7.0f))
					++num_one_dev;
				if ((number >= 1.0f) && (number < 9.0f))
					++num_two_dev;
				if ((number >= -1.0f) && (number < 11.0f))
					++num_three_dev;
			}

			float percent1 = static_cast<float>(num_one_dev) / static_cast<float>(nrolls);
			float percent2 = static_cast<float>(num_two_dev) / static_cast<float>(nrolls);
			float percent3 = static_cast<float>(num_three_dev) / static_cast<float>(nrolls);

			Assert::IsTrue(percent1 <= 0.7f && percent1 >= 0.66f);
			Assert::IsTrue(percent2 <= 0.99f && percent2 >= 0.93f);
			Assert::IsTrue(percent3 <= 1.0f && percent3 >= 0.98f);

			// log

			//int nstars = 100;    // maximum number of stars to distribut

			//Logger::WriteMessage("normal_distribution (5.0,2.0):\n");

			//for (int i = 0; i < 10; ++i) 
			//{
			//	char msg[10];
			//	sprintf(msg, "%d-%d: ", i, i + 1);
			//	Logger::WriteMessage(msg);
			//	Logger::WriteMessage(std::string(p[i] * nstars / nrolls, '*').c_str());
			//	Logger::WriteMessage("\n");
			//}

		}

		// NormalRange IsClamp
		TEST_METHOD(TestNormalRangeClamp)
		{
			// TODO: Your test code here

			Random random;
			int nrolls = 10000;  // number of experiments
			bool istrue = true;

			for (int i = 0; i < nrolls; ++i)
			{
				float number = random.NormalRange(5.0f, 2.0f, true);
				if ((number >= 11.0f) && (number < -1.0f))
				{
					istrue = false;
					break;
				}
			}

			Assert::IsTrue(istrue);
		}

		// NormalRangeMinMax
		TEST_METHOD(TestNormalRangeMinMax)
		{
			// TODO: Your test code here

			Random random;
			int p[10] = {};
			int nrolls = 10000;  // number of experiments
			int num_one_dev = 0;
			int num_two_dev = 0;
			int num_three_dev = 0;

			float min = 0.0f;
			float max = 10.0f;
			float mean = (max + min) / 2.0f;
			float dev = (mean - min) / 3.0f;

			for (int i = 0; i < nrolls; ++i)
			{
				float number = random.NormalRangeMinMax(min, max);
				if ((number >= 0.0f) && (number < 10.0f))
					++p[static_cast<int>(number)];

				if ((number >= mean - dev) && (number < mean + dev))
					++num_one_dev;
				if ((number >= mean - dev * 2.0f) && (number < mean + dev * 2.0f))
					++num_two_dev;
				if ((number >= mean - dev * 3.0f) && (number < mean + dev * 3.0f))
					++num_three_dev;
			}

			float percent1 = static_cast<float>(num_one_dev) / static_cast<float>(nrolls);
			float percent2 = static_cast<float>(num_two_dev) / static_cast<float>(nrolls);
			float percent3 = static_cast<float>(num_three_dev) / static_cast<float>(nrolls);

			Assert::IsTrue(percent1 <= 0.7f && percent1 >= 0.66f);
			Assert::IsTrue(percent2 <= 0.99f && percent2 >= 0.93f);
			Assert::IsTrue(percent3 <= 1.0f && percent3 >= 0.98f);

			// log

			//int nstars = 100;    // maximum number of stars to distribut

			//Logger::WriteMessage("normal_distribution (5.0,2.0):\n");

			//for (int i = 0; i < 10; ++i) 
			//{
			//	char msg[10];
			//	sprintf(msg, "%d-%d: ", i, i + 1);
			//	Logger::WriteMessage(msg);
			//	Logger::WriteMessage(std::string(p[i] * nstars / nrolls, '*').c_str());
			//	Logger::WriteMessage("\n");
			//}

		}

		TEST_METHOD(TestNormalBoundary)
		{
			// TODO: Your test code here

			// the boundary value from normal distribution
			// which is more than 3 times of standard deviation

			Random random;
			float deviation = random.RangeFloat();
			float boundary = random.NormalBoundary(deviation);

			Assert::IsTrue(std::abs(boundary - deviation * 3.0f) < 0.0001f);

		}

		// NormalMin
		TEST_METHOD(TestNormalMin)
		{
			// TODO: Your test code here

			Random random;
			float deviation = random.RangeFloat();
			float mean = random.RangeFloat();
			float boundary = random.NormalBoundary(deviation);
			float lowerboundary = random.NormalMin(mean, deviation);

			char output[50];
			sprintf_s(output, "mean: %.3f\nboundary: %.3f\nlower: %.3f\n", mean, boundary, lowerboundary);
			Logger::WriteMessage(output);

			Assert::IsTrue(std::abs((mean - boundary) - lowerboundary) < 0.0001f);
		}

		// NormalMax
		TEST_METHOD(TestNormalMax)
		{
			// TODO: Your test code here

			Random random;
			float deviation = random.RangeFloat();
			float mean = random.RangeFloat();
			float boundary = random.NormalBoundary(deviation);
			float upperboundary = random.NormalMax(mean, deviation);

			char output[50];
			sprintf_s(output, "mean: %.3f\nboundary: %.3f\nupper: %.3f\n", mean, boundary, upperboundary);
			Logger::WriteMessage(output);

			Assert::IsTrue(std::abs((mean + boundary) - upperboundary) < 0.0001f);
		}

		// CoinToss
		TEST_METHOD(TestCoinToss)
		{
			// TODO: Your test code here

			Random random;

			// check 10 times to ensure

			for (int j = 0; j < 10; ++j)
			{
				int num_face = 0;
				int num_toss = random.RangeInt(50000, 100000);

				for (int i = 0; i < num_toss; ++i)
				{
					if (random.CoinToss())
						++num_face;
				}

				float percentage = static_cast<float>(num_face) / static_cast<float>(num_toss);

				// check if the percentage of getting face is 49% ~ 51%
				Assert::IsTrue(std::abs(percentage - 0.5f) < 0.01f);
			}
		}
	};
}