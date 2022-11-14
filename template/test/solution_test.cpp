#include "catch2/catch_all.hpp"
#include "solution.h"

TEST_CASE("isDigit() correctly recognizes digits")
{
	for(char c = '0'; c <= '9'; ++c)
		CHECK(isDigit(c));
}

TEST_CASE("isDigit() returns false for non-digits")
{
	for(int c = 0; c < '0'; ++c)
		CHECK_FALSE(isDigit(c));

	for(int c = '9'+1; c <= 127; ++c)
		CHECK_FALSE(isDigit(c));
}

TEST_CASE("isOperation() returns true for all operations")
{
	CHECK(isOperation('+'));
	CHECK(isOperation('-'));
	CHECK(isOperation('*'));
	CHECK(isOperation('/'));
	CHECK(isOperation('^'));
}

TEST_CASE("toDouble() correctly converts digits to their numeric values")
{
	int expected = 0;
	
	for(char c = '0'; c <= '9'; ++c)
		REQUIRE(expected++ == toDouble(c));
}

TEST_CASE("toDouble() throws when passed a non-digit character")
{
	REQUIRE_THROWS_AS(toDouble('x'), std::invalid_argument);
}

TEST_CASE("priority() returns correct priority values for supported operations")
{
	CHECK(priority('+') == priority('-'));
	CHECK(priority('*') == priority('/'));
	CHECK(priority('+') < priority('*'));
	CHECK(priority('*') < priority('^'));
}

TEST_CASE("priority() throws when passed an incorrect operation")
{
	REQUIRE_THROWS_AS(priority('x'), std::invalid_argument);
}

/// Check if two double values are equal with precision up to a specified delta
inline bool areSame(double a, double b, double delta = 0.0001)
{
	return std::abs(a - b) < delta;
}

/// Uses the CHECK macro to test whether two double values are the same with a specified precision
inline void checkSame(double a, double b, double delta = 0.0001)
{
	CHECK(areSame(a, b, delta));
}

TEST_CASE("perform('+', 1.5, 2.5) returns 4.0")
{
	checkSame(4.0, perform('+', 1.5, 2.5));
}

TEST_CASE("perform('-', 1.5, 2.5) returns -1.0")
{
	checkSame(-1.0, perform('-', 1.5, 2.5));
}	

TEST_CASE("perform('*', 1.5, 2.5) returns 3.75") {
	checkSame(3.75, perform('*', 1.5, 2.5));
}

TEST_CASE("perform('/', 1.5, 2.5) returns 0.6")
{
	checkSame(0.6, perform('/', 1.5, 2.5));
}

TEST_CASE("perform('^', 1.5, 2.5) returns 2.755675961") {
	checkSame(2.7556765961, perform('^', 1.5, 2.5));
}

TEST_CASE("perform() throws when dividing by zero")
{
	REQUIRE_THROWS_AS(perform('/', 5.0, 0.0), std::invalid_argument);
}

TEST_CASE("perform() throws when passed an invalid operation")
{
	REQUIRE_THROWS_AS(perform('x', 5.0, 5.0), std::invalid_argument);
}

TEST_CASE("verify(nullptr) returns false")
{
	REQUIRE_FALSE(verify(nullptr));
}

TEST_CASE("verify(\"\") returns true")
{
	REQUIRE(verify(""));
}

TEST_CASE("verify() returns false for an all-whitespace expression")
{
	REQUIRE_FALSE(verify("   \r   \n    \t   "));
}

TEST_CASE("verify() returns true for single-number expressions")
{
	CHECK(verify("0"));
	CHECK(verify("5"));
}

TEST_CASE("verify() returns false for incorrect expressions")
{
	CHECK_FALSE(verify("55"));
	CHECK_FALSE(verify("5 5"));
	CHECK_FALSE(verify("55+"));
	CHECK_FALSE(verify("5+"));
	CHECK_FALSE(verify("+5"));
	CHECK_FALSE(verify("5+5+"));
	CHECK_FALSE(verify("+-5"));
}

TEST_CASE("verify() returns true for correct expressions")
{
	CHECK(verify("5+5"));
	CHECK(verify("1+2-3*4/5^6/7*8-9+0"));
}

TEST_CASE("evaluate(nullptr) throws")
{
	REQUIRE_THROWS_AS(evaluate(nullptr), std::invalid_argument);
}

TEST_CASE("evaluate(\"\") returns 0")
{
	checkSame(0, evaluate(""));
}

TEST_CASE("evaluate() throws for an all-whitespace string")
{
	REQUIRE_THROWS_AS(evaluate("   \r   \n    \t   "), std::invalid_argument);
}

TEST_CASE("evaluate() respects operation associativity")
{
	checkSame(1, evaluate("8/4/2"));
	checkSame(2, evaluate("8-4-2"));
	checkSame(4096, evaluate("4^3^2"));
}

TEST_CASE("evaluate() respects operation priority")
{
	checkSame(-25, evaluate("3-7*2^2"));
}

TEST_CASE("evaluate() works correctly even when stacks get depleted")
{
	checkSame(13, evaluate("2^3*2+2-5"));
}
