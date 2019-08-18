#include <catch.hpp>
#include "neuralnet/activationfunctionhelper.h"

using namespace PlumLearn;

TEST_CASE("RELU function evaluates correctly")
{
	auto fn =  ActivationFunctionHelper::GetFunction( ActivationFunction::Relu);
	REQUIRE(fn(-1) == 0.0);
	REQUIRE(fn(1) == 1.0);
	REQUIRE(fn(2) == 2.0);
};

TEST_CASE("RELU derivative evaluates correctly")
{
	auto fn =  ActivationFunctionHelper::GetFunctionDerivative(ActivationFunction::Relu);
	REQUIRE(fn(-1) == 0.0);
	REQUIRE(fn(1) == 1.0);
	REQUIRE(fn(2) == 1.0);
};

TEST_CASE("Logistic function evaluates correctly")
{
	auto fn =  ActivationFunctionHelper::GetFunction(ActivationFunction::Logistic);
	REQUIRE(fn(0) == 0.5);
	REQUIRE(fn(1) == 1.0 / (1.0 + pow(M_E, -1)));
	REQUIRE(fn(-1) == 1.0 / (1.0 + M_E));
};

TEST_CASE("Logistic derivative evaluates correctly")
{
	auto i = GENERATE(take(10, random(-10.0,10.0)));
	auto fn =  ActivationFunctionHelper::GetFunction(ActivationFunction::Logistic);
	auto df =  ActivationFunctionHelper::GetFunctionDerivative(ActivationFunction::Logistic);
	REQUIRE(df(i) == fn(i) * (1.0 - fn(i)));
};

TEST_CASE("TanH function evaluates correctly")
{
	auto fn =  ActivationFunctionHelper::GetFunction(ActivationFunction::TanH);
	auto i = GENERATE(take(10, random(-10.0, 10.0)));
	REQUIRE(fn(i) == tanh(i));
};

TEST_CASE("TanH derivative evaluates correctly")
{
	auto i = GENERATE(take(10, random(-10.0, 10.0)));
	auto df =  ActivationFunctionHelper::GetFunctionDerivative(ActivationFunction::TanH);
	REQUIRE(df(i) == 1 - pow(tanh(i), 2));
};

TEST_CASE("Leaky function evaluates correctly < 0")
{
	auto fn =  ActivationFunctionHelper::GetFunction(ActivationFunction::LeakyRelu);
	auto i = GENERATE(take(10, random(-10.0, -0.0001)));
	REQUIRE(fn(i) == 0.1*i);
};

TEST_CASE("Leaky function evaluates correctly >= 0")
{
	auto fn =  ActivationFunctionHelper::GetFunction(ActivationFunction::LeakyRelu);
	auto j = GENERATE(take(10, random(0.0, 10.0)));
	REQUIRE(fn(j) == j);
};

TEST_CASE("Leaky derivative evaluates correctly < 0")
{
	auto i = GENERATE(take(10, random(-10.0, -0.0001)));
	auto df =  ActivationFunctionHelper::GetFunctionDerivative(ActivationFunction::LeakyRelu);
	REQUIRE(df(i) == 0.1);
};

TEST_CASE("Leaky derivative evaluates correctly >= 0")
{
	auto j = GENERATE(take(10, random(0.0, 10.0)));
	auto df =  ActivationFunctionHelper::GetFunctionDerivative(ActivationFunction::LeakyRelu);
	REQUIRE(df(j) == 1);
};
