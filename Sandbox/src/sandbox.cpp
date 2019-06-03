#include "plumlearn.h"
#include <iostream>
#include <utility>

#define PL_FN ::PlumLearn::ActivationFunctions

int main()
{
	auto net = PlumLearn::NeuralNet(2).AddLayer(5, PL_FN::Logistic).AddLayer(2, PL_FN::Softmax);
	std::vector<double> one_one({ 1, 1 });
	std::vector<double> one_zero({ 1, 0 });
	std::vector<double> zero_one({ 0, 1 });
	std::vector<double> zero_zero({ 0, 0 });
	PlumLearn::FeatureLabelPair p1 = std::make_pair(one_one, one_zero);
	PlumLearn::FeatureLabelPair p2 = std::make_pair(one_zero, zero_one);
	PlumLearn::FeatureLabelPair p3 = std::make_pair(zero_one, zero_one);
	PlumLearn::FeatureLabelPair p4 = std::make_pair(zero_zero, one_zero);
	std::vector<PlumLearn::FeatureLabelPair> data;
	for (int i = 0; i < 1000; i++)
	{

		data.push_back(p1);
		data.push_back(p2);
		data.push_back(p3);
		data.push_back(p4);
	}
	net.SGD(data, 100, 10, 25);
	auto test1 = net.Evaluate(one_one);
	auto test2 = net.Evaluate(one_zero);
	auto test3 = net.Evaluate(zero_one);
	auto test4 = net.Evaluate(zero_zero);
	std::cout << "(1 , 1): " << test1[0] << " " << test1[1] << std::endl;
	std::cout << "(1 , 0): " << test2[0] << " " << test2[1] << std::endl;
	std::cout << "(0 , 1): " << test3[0] << " " << test3[1] << std::endl;
	std::cout << "(0 , 0): " << test4[0] << " " << test4[1] << std::endl;
	return 0;
}