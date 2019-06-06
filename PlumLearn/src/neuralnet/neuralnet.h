#pragma once
#include "neuralnetenums.h"
#include <vector>
#include <memory>

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
		/// <summary>
		/// 
		/// </summary>
		/// <param name="n_inputs"></param>
		NeuralNet(unsigned int n_inputs);

		virtual ~NeuralNet();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="training_data"></param>
		/// <param name="mini_batch_size"></param>
		/// <param name="epochs"></param>
		/// <param name="learning_rate"></param>
		void SGD(std::vector<FeatureLabelPair>& training_data, unsigned mini_batch_size, unsigned epochs, double learning_rate);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="n_neurons"></param>
		/// <param name="fn"></param>
		/// <returns></returns>
		NeuralNet& AddLayer(int n_neurons, ActivationFunction fn = ActivationFunction::Logistic);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="features"></param>
		/// <returns></returns>
		std::vector<double> Evaluate(std::vector<double> features);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="dropout_rate"></param>
		void ApplyDropout(double dropout_rate);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="discrete_output"></param>
		/// <returns></returns>
		NeuralNet& DiscreteOutput(bool discrete_output = true);
	//	double CalculateLoss(std::vector<FeatureLabelPair>& testing_data);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="cost"></param>
		/// <returns></returns>
		NeuralNet& SetCostFunction(CostFunction cost);
	protected:
		void UpdateOnBatch(std::vector<FeatureLabelPair>& training_data, double learning_rate);
		std::vector<std::shared_ptr<NeuronLayer>> layers;
		void Feedforward(std::vector<double> features);
<<<<<<< HEAD
		double dropout_rate = 0;
		bool d_out = false;
		CostFunction cost_function = CostFunction::Cross_Entropy;

=======
		double dropout_rate = 0.0;
>>>>>>> 18488e2079cecb7e4386ebab0166f1c022de5a41
	};
}
