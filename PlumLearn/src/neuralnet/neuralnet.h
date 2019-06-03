#pragma once
#include "activationfunctions.h"

namespace PlumLearn
{
	class NeuronLayer;

	typedef std::pair<std::vector<double>, std::vector<double>> FeatureLabelPair;

	/// <summary>
	/// Creates a neural network.
	/// </summary>
	class NeuralNet
	{
	public:
		NeuralNet(unsigned int n_inputs);
		virtual ~NeuralNet();
		//double Test(std::vector<FeatureLabelPair>& test_data);
		void SGD(std::vector<FeatureLabelPair>& training_data, unsigned mini_batch_size, unsigned epochs, double learning_rate);
		NeuralNet& AddLayer(int n_neurons, ActivationFunctions::Enum fn = ActivationFunctions::Logistic);
		//NeuralNet& InitialiseOutputLayer(int n_outputs, NNOutputType t_output = NNOutputType::Classification);
		std::vector<double> Evaluate(std::vector<double> features);
		void ApplyDropout(double dropout_rate);
	protected:
		void UpdateOnBatch(std::vector<FeatureLabelPair>& training_data, double learning_rate);
		std::vector<std::shared_ptr<NeuronLayer>> layers;
		void Feedforward(std::vector<double> features);
		double dropout_rate = 0;
	};
}
