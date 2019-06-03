#pragma once

#include <vector>
#include <memory>
#include "activationfunctions.h"
#include <Core>

namespace PlumLearn
{

	class NeuronLayer
	{
	public:
		NeuronLayer(unsigned int n_neurons, ActivationFunctions::Enum fn)
			:	n_neurons(n_neurons),
				fn(fn),
				is_input(false),
				dC_db(Eigen::VectorXd::Zero(n_neurons)),
				values(Eigen::VectorXd::Zero(n_neurons)),
				derivative_values(Eigen::VectorXd::Zero(n_neurons)),
				biases(Eigen::VectorXd::Random(n_neurons))
		{};

		NeuronLayer(unsigned int n_neurons)
			:	n_neurons(n_neurons),
				fn(ActivationFunctions::Null),
				is_input(true),
				dC_db(Eigen::VectorXd::Zero(n_neurons)),
				values(Eigen::VectorXd::Zero(n_neurons)),
				derivative_values(Eigen::VectorXd::Zero(n_neurons)),
				biases(Eigen::VectorXd::Random(n_neurons))
		{};

		~NeuronLayer();
		void Evaluate();
		void SetValues(std::vector<double> values);
		void BackpropagateError(std::vector<double> training_labels);
		void Connect(std::shared_ptr<NeuronLayer> layer_ptr);
		void UpdateWeights(double learning_rate, std::size_t batch_size);
		std::vector<double> GetValues();

	protected:
		//std::vector<Neuron> neurons;
		unsigned int n_neurons;
		ActivationFunctions::Enum fn;

		struct ConnectedLayer
		{
			ConnectedLayer(unsigned int n_neurons, std::shared_ptr<NeuronLayer> connecting_layer) :
				ptr(connecting_layer),
				weights(Eigen::MatrixXd::Random(n_neurons, ptr->n_neurons)), 
				dC_dw(Eigen::MatrixXd::Zero(n_neurons, ptr->n_neurons) ){};
			std::shared_ptr<NeuronLayer> ptr;
			Eigen::MatrixXd weights;
			Eigen::MatrixXd dC_dw;
		};

		[[deprecated("Deprecated: to be generalised to any cost function")]]
		Eigen::MatrixXd CalculateError(const Eigen::VectorXd& training_labels);

		std::vector<Eigen::MatrixXd> weights;
		Eigen::VectorXd biases;
		Eigen::VectorXd values;
		Eigen::VectorXd derivative_values;
		void ResetBackpropagation();
		bool is_input;

		void BackpropagateErrorImpl(const Eigen::MatrixXd& delta);

		// The sum of the gradients of the cost functions over current training examples
		Eigen::VectorXd dC_db;

		std::vector<ConnectedLayer> previous_layers;
		unsigned int connected_neurons = 0;
	};

}