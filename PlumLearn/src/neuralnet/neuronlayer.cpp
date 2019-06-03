#include "plpch.h"
#include "neuronlayer.h"
#include "utils/activationfunctionutils.h"
#include "utils/range.hpp"

using namespace Eigen;
using namespace util::lang;

namespace PlumLearn
{
	NeuronLayer::~NeuronLayer()
	{
	}

	void NeuronLayer::Evaluate()
	{
		if (!is_input)
		{
			VectorXd raw(VectorXd::Zero(n_neurons));
			for (auto& layer : previous_layers)
			{
				raw += layer.weights * layer.ptr->values;
			}
			this->values = ApplyFunction(raw, fn);
			this->derivative_values = ApplyFunctionDerivative(raw, fn);
		}
	}

	void NeuronLayer::SetValues(std::vector<double> values)
	{
		this->values = Map<VectorXd>(values.data(), values.size());
	}

	void NeuronLayer::BackpropagateError(std::vector<double> training_labels)
	{
		Map<VectorXd> labels(&training_labels[0], training_labels.size());
		auto delta = this->CalculateError(labels);
		BackpropagateErrorImpl(delta);
	}

	void NeuronLayer::ResetBackpropagation()
	{
		for (auto& layer : previous_layers)
		{
			layer.dC_dw.setZero();
		}
		dC_db = VectorXd::Zero(n_neurons);
	}

	void NeuronLayer::Connect(std::shared_ptr<NeuronLayer> layer_ptr)
	{
		ConnectedLayer con = ConnectedLayer(n_neurons, layer_ptr);
		previous_layers.emplace_back(con);
	}

	void NeuronLayer::UpdateWeights(double learning_rate, std::size_t batch_size)
	{
		if (!is_input)
		{
			for (auto& layer : previous_layers)
			{
				layer.weights = layer.weights - layer.dC_dw * (learning_rate / batch_size);
			}

			biases = biases - dC_db * (learning_rate / batch_size);

			this->ResetBackpropagation();
		}
	}

	std::vector<double> NeuronLayer::GetValues()
	{
		std::vector<double> out;
		for (auto& val : this->values)
		{
			out.push_back(val);
		}
		return out;
	}

	MatrixXd NeuronLayer::CalculateError(const VectorXd& training_labels)
	{
		MatrixXd error = (this->values - training_labels).cwiseProduct(this->derivative_values);
		return error;
	}

	void NeuronLayer::BackpropagateErrorImpl(const MatrixXd& delta)
	{
		this->dC_db += delta;
		for (auto& layer : previous_layers)
		{
			layer.dC_dw += delta * layer.ptr->values.transpose();
			if (!layer.ptr->is_input)
			{
				layer.ptr->BackpropagateErrorImpl(
					(layer.weights.transpose() * delta)
					.cwiseProduct(layer.ptr->derivative_values));
			}
		}
	}
}