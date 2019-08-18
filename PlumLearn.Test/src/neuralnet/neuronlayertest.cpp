#include <catch.hpp>
#include "neuralnet/neuronlayer.h"

using namespace PlumLearn;

TEST_CASE("Can create a single layer and set values")
{
	auto layer = NeuronLayer(10);
	std::vector<double> vals = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	layer.SetValues(vals);
	REQUIRE(layer.GetValues() == vals);
}

TEST_CASE("Assigning too many does not throw")
{
	auto layer = NeuronLayer(10);
	std::vector<double> vals = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	REQUIRE_NOTHROW(layer.SetValues(vals));
}

TEST_CASE("Assigning too few does not throw")
{
	auto layer = NeuronLayer(10);
	std::vector<double> vals = { 1, 2, 3, 4, 5, 6, 7, 8 };
	REQUIRE_NOTHROW(layer.SetValues(vals));
}

TEST_CASE("Can connect two layers and perform learning operations")
{
	auto layer1 = std::make_shared<NeuronLayer>(10);
	auto layer2 = NeuronLayer(5, ActivationFunction::LeakyRelu);
	REQUIRE_NOTHROW(layer2.Connect(layer1));

	std::vector<double> vals1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	layer1->SetValues(vals1);
	REQUIRE_NOTHROW(layer2.Evaluate());

	// Evaluates to not all zeros
	auto eval = layer2.GetValues();
	REQUIRE(std::any_of(eval.begin(), eval.end(), [](double i) { return i != 0; }));

	std::vector<double> vals2 = { 10, 9, 8, 7, 6 };
	REQUIRE_NOTHROW(layer2.BackpropagateError(vals2));

	REQUIRE_NOTHROW(layer2.UpdateWeights(0.1, 1));
}