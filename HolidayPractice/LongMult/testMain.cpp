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

	TEST(BasicTests, Add){
		//test add
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
	}

	TEST(BasicTest, Multiply){	//test multiply
		BigNumber two(2);
		BigNumber three(3);
		BigNumber six = two.multiply(three);
		EXPECT_EQ(six.number(), "6");
		BigNumber zero(0);
		BigNumber res = two.multiply(zero);
		EXPECT_EQ(res.number(),"0");	
		std::string oneOver("9223372036854775808");
		std::string eightoheight("808");
		std::string exactLimit("9223372036854775807");	
		//test the products that use the extended version of multiply
		BigNumber big1(oneOver);
		BigNumber big2(exactLimit);
		BigNumber lil1(eightoheight);
		res = big2.multiply(lil1);
		EXPECT_EQ(res.number(), "7452484605778658852056");
		res = big1.multiply(big2);
		EXPECT_EQ(res.number(), "85070591730234615856620279821087277056");
		//make sure multiply works both ways
		res = zero.multiply(big1);	
		EXPECT_EQ(res.number(), "0");
		res = big1.multiply(zero);
		EXPECT_EQ(res.number(), "0");
		res = lil1.multiply(big2);
		EXPECT_EQ(res.number(), "7452484605778658852056");
		BigNumber hundred = BigNumber(100);
		res = hundred.multiply(lil1);
		EXPECT_EQ(res.number(),"80800");
		//negative numbers?
		std::string nOne("-1");
		BigNumber negOne(nOne);
		res = negOne.multiply(lil1);
		EXPECT_EQ(res.number(), "-808");
	}

	TEST(BasicTest, PrintSimulate){
		BigNumber two(2);
		std::vector<unsigned char>* num = two.vectorize();
		unsigned char c[64] = {0};
		int i = 0; 
		for (auto elem : *num){
			 c[i++] = elem;

		}
		delete num;
		EXPECT_EQ(std::string((char*)c),"2");
	}
}


	

int main (int argc, char** argv){

	//new way of testing
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

