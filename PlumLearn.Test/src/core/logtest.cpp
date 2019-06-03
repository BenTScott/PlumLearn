#include <catch.hpp>
#include "plumlearn.h"

TEST_CASE("Can initialise the cosole and log to it")
{
	CHECK_NOTHROW(PL_CORE_INFO("Info core log test"));
}