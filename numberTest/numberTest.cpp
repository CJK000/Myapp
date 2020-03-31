#include "pch.h"
#include "CppUnitTest.h"
#include"../Myapp/number.h"
#include"../Myapp/make.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace numberTest
{
	TEST_CLASS(numberTest)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(true, Number(1, 2, 3) > Number(0, 0, 0));
		}
		TEST_METHOD(TestMethod2)
		{

			Assert::AreEqual(Number(5,5,6).ToString(), (Number(3, 2, 3) + Number(2, 1, 6)).ToString());
		}
	};
}
