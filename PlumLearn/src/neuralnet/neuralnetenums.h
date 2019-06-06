#pragma once

namespace PlumLearn {

	enum class CostFunction
	{
		Quadratic,
		Cross_Entropy
	};

	enum class ActivationFunction
	{
		Null,
		Logistic,
		Relu,
		Softmax,
		TanH,
		LeakyRelu
	};
}