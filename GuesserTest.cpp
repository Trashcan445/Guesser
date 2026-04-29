/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};


TEST(GuesserTest, distance_test)
{
	// normal secret
	Guesser object("Secret");
	ASSERT_EQ(object.distance("Secret") , 0);
	ASSERT_EQ(object.distance("Secre") , 1);
	ASSERT_EQ(object.distance("SecreT") , 1);
	ASSERT_EQ(object.distance("Secrete") , 1);
	ASSERT_EQ(object.distance("xxcret") , 2);
	ASSERT_EQ(object.distance("1e2r3t") , 3);
	ASSERT_EQ(object.distance("Sxxxxt") , 4);
	ASSERT_EQ(object.distance("SECRET") , 5);
	ASSERT_EQ(object.distance("_Secret_") , 6);
	ASSERT_EQ(object.distance("") , 6);
	ASSERT_EQ(object.distance("ABCDEFGHIJKLMNOP") , 6);

	// empty secret
	Guesser object2("");
	ASSERT_EQ(object2.distance("") , 0);
	ASSERT_EQ(object2.distance("Secret") , 0);
	ASSERT_EQ(object2.distance("Secre") , 0);
	ASSERT_EQ(object2.distance("__cret") , 0);
	ASSERT_EQ(object2.distance("SECRET") , 0);
	ASSERT_EQ(object2.distance("ABCDEFGHIJKLMNOP") , 0);
}

TEST(GuesserTest, match_test)
{
	// Guessed right after 2 wrong
	Guesser object("Secret");
	ASSERT_EQ(object.match("Secre") , false);
	ASSERT_EQ(object.match("Secrete") , false);
	ASSERT_EQ(object.match("Secret") , true);

	// Guessed wrong 3 times
	Guesser object2("Secret");
	ASSERT_EQ(object2.match("Secre") , false);
	ASSERT_EQ(object2.match("Secrete") , false);
	ASSERT_EQ(object2.match("SecreT") , false);
	ASSERT_EQ(object2.match("Secret") , false); // Always false after 3 wrong guesses

	// Guessed wrong by dist > 2
	Guesser object3("Secret");
	ASSERT_EQ(object3.match("___ret") , false);
	ASSERT_EQ(object3.match("Secret") , false); // Always false after dist > 2

	//short case, dist can never be > 2
	Guesser object4("ab");
	ASSERT_EQ(object4.match("123456") , false);
	ASSERT_EQ(object4.match("ab") , true);
}