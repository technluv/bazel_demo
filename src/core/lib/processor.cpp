#include "processor.hpp"
#include <algorithm>
#include <stdexcept>
#include <cmath>

namespace core {

DataProcessor::DataProcessor() : threshold_(0.5) {}

std::vector<double> DataProcessor::process_data(const std::vector<double>& input) {
    if (!validate_input(input)) {
        throw std::invalid_argument("Invalid input data");
    }

    std::vector<double> result;
    result.reserve(input.size());

    for (const auto& val : input) {
        result.push_back(val * threshold_);
    }

    return result;
}

bool DataProcessor::validate_input(const std::vector<double>& input) {
    return !input.empty() && 
           std::all_of(input.begin(), input.end(), 
                      [](double x) { return std::isfinite(x); });
}

} // namespace core

extern "C" {

void process_data(double* input, int length, double* output) {
    try {
        core::DataProcessor processor;
        std::vector<double> input_vec(input, input + length);
        std::vector<double> output_vec = processor.process_data(input_vec);
        std::copy(output_vec.begin(), output_vec.end(), output);
    } catch (const std::exception& e) {
        // Handle exceptions as needed
    }
}

}
