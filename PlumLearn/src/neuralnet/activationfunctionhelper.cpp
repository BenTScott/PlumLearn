#include "plpch.h"
#include "activationfunctionhelper.h"

namespace PlumLearn {
	const std::function<double(double)> ActivationFunctionHelper::logistic_fn = [](double x) { return 1.0 / (1.0 + pow(M_E, -x)); };
	const std::function<double(double)> ActivationFunctionHelper::logistic_derivative = [&](double x) { return logistic_fn(x) * (1.0 - logistic_fn(x)); };
	const std::function<double(double)> ActivationFunctionHelper::relu_fn = [&](double x) { return std::max(0.0, x); };
	const std::function<double(double)> ActivationFunctionHelper::relu_derivative = [&](double x) { return x <= 0 ? 0.0 : 1.0; };
	const std::function<double(double)> ActivationFunctionHelper::tanh_fn = [](double x) { return tanh(x); };
	const std::function<double(double)> ActivationFunctionHelper::tanh_derivative = [&](double x) { return 1 - pow(tanh(x), 2); };
	const std::function<double(double)> ActivationFunctionHelper::leaky_relu_fn = [](double x) { return std::max(0.1 * x, x); };
	const std::function<double(double)> ActivationFunctionHelper::leaky_relu_derivative = [&](double x) { return x <= 0 ? 0.1 : 1.0; };

	const std::function<double(double)>& ActivationFunctionHelper::GetFunction(ActivationFunction function_type)
	{
		switch (function_type)
		{
		case ActivationFunction::Relu:
			return relu_fn;
		case ActivationFunction::LeakyRelu:
			return leaky_relu_fn;
		case ActivationFunction::TanH:
			return tanh_fn;
		case ActivationFunction::Logistic:
		default:
			return logistic_fn;
		}
	}

	const std::function<double(double)>& ActivationFunctionHelper::GetFunctionDerivative(ActivationFunction function_type)
	{
		switch (function_type)
		{
		case ActivationFunction::Relu:
			return relu_derivative;
		case ActivationFunction::LeakyRelu:
			return leaky_relu_derivative;
		case ActivationFunction::TanH:
			return tanh_derivative;
		case ActivationFunction::Logistic:
		default:
			return logistic_derivative;
		}
	}

	Eigen::VectorXd ActivationFunctionHelper::ApplyFunction(Eigen::VectorXd vector, ActivationFunction function)
	{
		switch (function)
		{
		case ActivationFunction::Softmax:
			return vector.array().exp() / vector.array().exp().sum();
		default:
			return vector.unaryExpr(ActivationFunctionHelper::GetFunction(function));
		}
	}

	Eigen::VectorXd ActivationFunctionHelper::ApplyFunctionDerivative(Eigen::VectorXd vector, ActivationFunction function)
	{
		switch (function)
		{
		case ActivationFunction::Softmax:
		{
			auto smax = vector.array().exp() / vector.array().exp().sum();
			return smax * (1 - smax);
		}
		default:
			return vector.unaryExpr(ActivationFunctionHelper::GetFunctionDerivative(function));
		}
	}
}
