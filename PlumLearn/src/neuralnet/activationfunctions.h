#pragma once
#include <functional>
#include <algorithm>

#define _USE_MATH_DEFINES
#include <math.h>

namespace PlumLearn
{
	class ActivationFunctions
	{
	public:
		enum Enum
		{
			Null,
			Logistic,
			Relu,
			Softmax,
			TanH,
			LeakyRelu
		};

		static const std::function<double(double)>& GetFunction(Enum function_type);
		static const std::function<double(double)>& GetFunctionDerivative(Enum function_type);

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