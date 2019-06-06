#include "plumlearn.h"
#include <iostream>
#include <utility>
#include <random>

#define PL_FN ::PlumLearn::ActivationFunction

int main()
{
	auto data = PlumLearn::CSVDataHelper::ReadTrainingData(".\\data\\training_data.dat", 38, 1);
	std::shuffle(data.begin(), data.end(), std::default_random_engine(2));
	std::vector<FeatureLabelPair> train(data.begin(), data.begin() + 4500);
	std::vector<FeatureLabelPair> test(data.begin() + 4500, data.end());

	auto nn = PlumLearn::NeuralNet(38).AddLayer(50, PL_FN::Logistic).AddLayer(50, PL_FN::Logistic).AddLayer(10, PL_FN::Logistic).AddLayer(1, PL_FN::Logistic).DiscreteOutput();
	nn.SGD(train, 100, 250, 2);
	
	int f_count = 0;
	for (auto& t : test)
	{
		auto eval = nn.Evaluate(t.first).front();
		if (eval != t.second.front())
		{
			f_count++;
		}
	}

	std::cout << f_count << "/" << test.size() << std::endl;

	return 0;
}