#include <iostream>
#include <sstream>

#define BEGIN_TEST(name) \
void TEST_##name()	\
{	\
	std::cerr << std::endl << "Start " << "TEST_" << #name << std::endl;

#define RUN_TEST(name) \
	setUp(); \
	TEST_##name(); \
	tearDown();

#define assertEquals(expected, expr) \
{ \
	std::ostringstream osExpected; \
	std::ostringstream osExpr; \
	osExpected << expected; \
	osExpr << expr; \
	if (osExpected.str() != osExpr.str()) \
	{ \
		std::cerr << "*** FAILED at line " << __LINE__ \
						<< ". Expecting: " << std::endl << osExpected.str() << std::endl \
						<< "Got: " << std::endl << osExpr.str() << std::endl; \
		return; \
	} \
}

#define assertNotEquals(notExpected, expr) \
{ \
	std::ostringstream osNotExpected; \
	std::ostringstream osExpr; \
	osNotExpected << notExpected; \
	osExpr << expr; \
	if (osNotExpected.str() == osExpr.str()) \
	{ \
		std::cerr << "*** FAILED at line " << __LINE__ << ". Not expecting: " << std::endl << osNotExpected.str() << std::endl; \
		return; \
	} \
}

