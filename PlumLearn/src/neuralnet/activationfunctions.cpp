#include "plpch.h"
#include "activationfunctions.h"

namespace PlumLearn {
	const std::function<double(double)> ActivationFunctions::logistic_fn = [](double x) { return 1.0 / (1.0 + pow(M_E, -x)); };
	const std::function<double(double)> ActivationFunctions::logistic_derivative = [&](double x) { return logistic_fn(x) * (1.0 - logistic_fn(x)); };
	const std::function<double(double)> ActivationFunctions::relu_fn = [&](double x) { return std::max(0.0, x); };
	const std::function<double(double)> ActivationFunctions::relu_derivative = [&](double x) { return x <= 0 ? 0.0 : 1.0; };
	const std::function<double(double)> ActivationFunctions::tanh_fn = [](double x) { return tanh(x); };
	const std::function<double(double)> ActivationFunctions::tanh_derivative = [&](double x) { return 1 - pow(tanh(x), 2); };
	const std::function<double(double)> ActivationFunctions::leaky_relu_fn = [](double x) { return std::max(0.1 * x, x); };
	const std::function<double(double)> ActivationFunctions::leaky_relu_derivative = [&](double x) { return x <= 0 ? 0.1 : 1.0; };

	const std::function<double(double)>& ActivationFunctions::GetFunction(Enum function_type)
	{
		switch (function_type)
		{
		case ActivationFunctions::Relu:
			return relu_fn;
		case ActivationFunctions::LeakyRelu:
			return leaky_relu_fn;
		case ActivationFunctions::TanH:
			return tanh_fn;
		case ActivationFunctions::Logistic:
		default:
			return logistic_fn;
		}
	}
	const std::function<double(double)>& ActivationFunctions::GetFunctionDerivative(Enum function_type)
	{
		switch (function_type)
		{
		case ActivationFunctions::Relu:
			return relu_derivative;
		case ActivationFunctions::LeakyRelu:
			return leaky_relu_derivative;
		case ActivationFunctions::TanH:
			return tanh_derivative;
		case ActivationFunctions::Logistic:
		default:
			return logistic_derivative;
		}
	}
}
