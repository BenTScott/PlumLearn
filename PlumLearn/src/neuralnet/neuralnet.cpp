#include "plpch.h"
#include "neuralnet.h"
#include "neuronlayer.h"
#include "activationfunctions.h"
#include <random>
#include <tuple>

namespace PlumLearn
{
	NeuralNet::NeuralNet(unsigned int n_inputs)
	{
		std::shared_ptr<NeuronLayer> input(new NeuronLayer(n_inputs));
		layers.push_back(input);
	}

	NeuralNet::~NeuralNet()
	{
	}

	void NeuralNet::SGD(std::vector<FeatureLabelPair>& training_data, unsigned mini_batch_size, unsigned epochs, double learning_rate)
	{
		auto rng = std::default_random_engine{};

		for (unsigned epoch = 0; epoch < epochs; epoch++)
		{
			std::shuffle(training_data.begin(), training_data.end(), rng);
			std::vector<FeatureLabelPair>::const_iterator first;
			std::vector<FeatureLabelPair>::const_iterator last;
			for (int i = 0; i < training_data.size() - mini_batch_size; i += mini_batch_size)
			{
				first = training_data.begin() + i;
				last = first + mini_batch_size;
				std::vector<FeatureLabelPair> batch(first, last);
				this->UpdateOnBatch(batch, learning_rate);
			}
			PL_CORE_INFO("Epoch {0} completed.", epoch);
		}
	}

	NeuralNet& NeuralNet::AddLayer(int n_neurons, ActivationFunctions::Enum fn)
	{
		std::shared_ptr<NeuronLayer> layer_ptr(new NeuronLayer(n_neurons, fn));
		layers.push_back(layer_ptr);
		layers.back()->Connect(*(layers.rbegin() + 1));
		return *this;
	}

	std::vector<double> NeuralNet::Evaluate(std::vector<double> features)
	{
		this->Feedforward(features);
		return layers.back()->GetValues();
	}

	void NeuralNet::ApplyDropout(double dropout_rate)
	{
		PL_CORE_ASSERT(dropout_rate >= 0 && dropout_rate < 1, "Dropout rate must be between 0 and 1.");
		this->dropout_rate = dropout_rate;
	}

	void NeuralNet::Feedforward(std::vector<double> features)
	{
		layers.front()->SetValues(features);
		std::for_each(layers.begin() + 1, layers.end(), [](std::shared_ptr<NeuronLayer> layer) { layer->Evaluate(); });
	}

	void NeuralNet::UpdateOnBatch(std::vector<FeatureLabelPair>& training_data, double learning_rate)
	{
		for (auto& elem : training_data)
		{
			this->Feedforward(elem.first);
			layers.back()->BackpropagateError(elem.second);
		}

		std::for_each(layers.begin() + 1, layers.end(), [&](std::shared_ptr<NeuronLayer> layer) { layer->UpdateWeights(learning_rate, training_data.size()); });
	}
}
