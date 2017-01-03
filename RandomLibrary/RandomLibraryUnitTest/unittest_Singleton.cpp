#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AIModulesUnitTest
{
	TEST_CLASS(UnitTest_Singleton)
	{
	public:

		class SingletonTestClass
		{
		public:
			int m_stuff;

			SingletonTestClass()
			{
				m_stuff = 0;
			}
		};

		TEST_METHOD(TestSingleton)
		{
			// TODO: Your test code here

			// class1 and class2 should be the same instance

			SingletonTestClass &class1 = Singleton<SingletonTestClass>::GetInstance();
			class1.m_stuff = 999;

			SingletonTestClass &class2 = Singleton<SingletonTestClass>::GetInstance();
			Assert::AreEqual(class2.m_stuff, 999);
		}

	};
}