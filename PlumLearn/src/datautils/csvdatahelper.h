#pragma once
#include <vector>

typedef std::pair<std::vector<double>, std::vector<double>> FeatureLabelPair;

namespace PlumLearn 
{

	class CSVDataHelper
	{
	public:
		static std::vector<FeatureLabelPair> ReadTrainingData(const char* filename, unsigned int n_features, unsigned int n_labels);
	};
}

