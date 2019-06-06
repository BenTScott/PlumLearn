#pragma once
#include "neuralnetenums.h"
#include <functional>
#include <Core>

namespace PlumLearn
{
	class CostFunctionHelper
	{
	public:
		static const std::function<Eigen::VectorXd(Eigen::VectorXd, Eigen::VectorXd)>& GetFunction(CostFunction function_type);
		static const std::function<Eigen::VectorXd(Eigen::VectorXd, Eigen::VectorXd)>& GetGradientFunction(CostFunction function_type);

	private:
		static const std::function<double(double)> quadratic_fn;
		static const std::function<double(double)> quadratic_derivative;
		static const std::function<double(double)> cross_entropy_fn;
		static const std::function<double(double)> cross_entropy_derivative;
	};
}