#pragma once
#include <functional>
#include <algorithm>
#include <Core>
#include "neuralnetenums.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace PlumLearn
{
	class ActivationFunctionHelper
	{
	public:
		static const std::function<double(double)>& GetFunction(ActivationFunction function_type);
		static const std::function<double(double)>& GetFunctionDerivative(ActivationFunction function_type);

		static Eigen::VectorXd ApplyFunction(Eigen::VectorXd vector, ActivationFunction function);
		static Eigen::VectorXd ApplyFunctionDerivative(Eigen::VectorXd vector, ActivationFunction function);

	private:
		static const std::function<double(double)> logistic_fn;
		static const std::function<double(double)> logistic_derivative;
		static const std::function<double(double)> relu_fn;
		static const std::function<double(double)> relu_derivative;
		static const std::function<double(double)> tanh_fn;
		static const std::function<double(double)> tanh_derivative;
		static const std::function<double(double)> leaky_relu_fn;
		static const std::function<double(double)> leaky_relu_derivative;
	};
}