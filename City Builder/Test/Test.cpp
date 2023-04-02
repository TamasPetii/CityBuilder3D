#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{
	TEST_CLASS(TestClass)
	{
	public:	
		TEST_METHOD(TestMethode)
		{
			GameTable* game = new GameTable(50);
			Assert::AreEqual(50, game->Get_TableSize());
		}
	};
}
