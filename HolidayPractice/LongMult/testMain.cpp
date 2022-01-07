/*
 *	main file for testing the LongMult program.
 */

//required for googletest, remember to also compile with pthreads
#include <thread>
#include "gtest/gtest.h"
#include "BigNumber.h"

/*
 * all tests need to be in a namespace or class, put them here
 * for now, move them into the class cpp file? eventually
 */

namespace {
	TEST(BasicTests, SetGet){
		std::string badVal("0a");
		BigNumber inval(badVal);
		EXPECT_TRUE(inval.getOverflow());
		EXPECT_EQ(inval.getLNum(),-1);
		BigNumber zero;
		EXPECT_EQ("0", zero.number());
		BigNumber one(1);
		EXPECT_EQ("1", one.number());
		one.set(5);
		EXPECT_EQ("5", one.number());
		//now we check the string set
		std::string numTwo("2");
		BigNumber two(numTwo);
		EXPECT_EQ("2", two.number());
		//check overflow
		std::string oneOver("9223372036854775808");
		std::string exactLimit("9223372036854775807");

		BigNumber plusOne(oneOver);
		EXPECT_TRUE(plusOne.getOverflow());
		BigNumber exactsies(exactLimit);
		EXPECT_FALSE(exactsies.getOverflow());
		EXPECT_EQ(exactsies.number(),exactLimit);
		//check negative numbers	
		std::string negativeOne("-1");	
		BigNumber negOne(negativeOne);
		EXPECT_FALSE(negOne.getOverflow());

	}

	TEST(BasicTests, AddMultiply){
		BigNumber two(2);
		BigNumber three(3);
		const char twelve[64] = {"12"};
		const char onethirtysix[64] = {"136"};
		std::string onefortyeight = two.symbAdd(twelve, onethirtysix);
		EXPECT_EQ(onefortyeight, "0148");
		const char ninetynine[64] = {"99"};
		std::string twothirtyfive = two.symbAdd(onethirtysix, ninetynine);
		EXPECT_EQ(twothirtyfive, "0235");
		const char nineninetynine[64] = {"999"};
		std::string oneonethreefive = two.symbAdd(onethirtysix, nineninetynine);
		EXPECT_EQ(oneonethreefive,"1135");
		BigNumber res;
		BigNumber six = two.multiply(three,res);
		//EXPECT_EQ(res.number(), "6");
		BigNumber zero(0);
		res = two.multiply(zero, res);
		//EXPECT_EQ(res.number(),"0");
	}
}


	

int main (int argc, char** argv){

	//new way of testing
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

