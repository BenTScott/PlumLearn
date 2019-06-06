#include "plpch.h"
#include "csvdatahelper.h"
#include <fstream>

namespace PlumLearn
{
	std::vector<FeatureLabelPair> CSVDataHelper::ReadTrainingData(const char* filename, unsigned int n_features, unsigned int n_labels)
	{
		std::vector<FeatureLabelPair> data;
		
		std::ifstream in(filename, std::ifstream::in);
		if (!in)
		{
			PL_CORE_ERROR("Cannot open file {0}", filename);
			exit(1);
		}

		std::string line;

		while (getline(in, line))
		{
			double value;
			std::istringstream v(line);

			std::vector<double> labels;
			for (unsigned i = 0; i < n_labels; i++)
			{
				v >> value;
				labels.push_back(value);
			}

			std::vector<double> features;
			for (unsigned i = 0; i < n_features; i++)
			{
				v >> value;
				features.push_back(value);
			}

			data.push_back(std::make_pair(features, labels));
		}

		in.close();

		return data;
	}
}
