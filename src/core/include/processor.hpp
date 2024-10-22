#pragma once
#include <string>
#include <vector>

namespace core {
class DataProcessor {
public:
    DataProcessor();
    std::vector<double> process_data(const std::vector<double>& input);
    bool validate_input(const std::vector<double>& input);
private:
    double threshold_;
};
}

