#include <catch.hpp>
#include "neuralnet/neuralnet.h"

using namespace PlumLearn;

TEST_CASE("Can create a neural network and perform SGD")
{
	auto nn = NeuralNet(5).AddLayer(10).AddLayer(2, ActivationFunctions::Softmax);
	std::vector<double> zeros({ 1, 1, 1, 1, 1 });
	std::vector<double> ones({ 0, 0, 0, 0, 0 });
	std::vector<double> label1({ 1, 0 });
	std::vector<double> label2({ 0, 1 });
	PlumLearn::FeatureLabelPair p1 = std::make_pair(zeros, label1);
	PlumLearn::FeatureLabelPair p2 = std::make_pair(ones, label2);
	std::vector<PlumLearn::FeatureLabelPair> data;
	for (int i = 0; i < 100; i++)
	{
		data.push_back(p1);
		data.push_back(p2);
	}
	REQUIRE_NOTHROW(nn.SGD(data, 10, 2, 0.1));
}

TEST_CASE("Can evaluate a single test feature")
{
	auto nn = NeuralNet(5).AddLayer(10).AddLayer(2, ActivationFunctions::Softmax);
	auto eval = nn.Evaluate({ 1, 2, 3, 4, 5 });
	REQUIRE(std::any_of(eval.begin(), eval.end(), [](double i) { return i != 0; }));
}
