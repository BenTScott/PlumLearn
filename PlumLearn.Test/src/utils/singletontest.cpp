#include <catch.hpp>
#include "utils/singleton.h"

class MockSingleton : public Singleton<MockSingleton>
{
public:
	friend class Singleton<MockSingleton>;

private:
	MockSingleton() {};
};

TEST_CASE("Can get instance")
{
	REQUIRE_NOTHROW(MockSingleton::GetInstance());
}