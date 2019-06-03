#pragma once

#include "neuralnet/activationfunctions.h"
#include <Core>

namespace PlumLearn
{

	Eigen::VectorXd ApplyFunction(Eigen::VectorXd vector, ActivationFunctions::Enum function)
	{
		switch (function)
		{
		case ActivationFunctions::Softmax:
			return vector.array().exp() / vector.array().exp().sum();
		default:
			return vector.unaryExpr(ActivationFunctions::GetFunction(function));
		}
	};

	Eigen::VectorXd ApplyFunctionDerivative(Eigen::VectorXd vector, ActivationFunctions::Enum function)
	{
		switch (function)
		{
		case ActivationFunctions::Softmax:
		{
			auto smax = vector.array().exp() / vector.array().exp().sum();
			return smax * (1 - smax);
		}
		default:
			return vector.unaryExpr(ActivationFunctions::GetFunctionDerivative(function));
		}
	};

}