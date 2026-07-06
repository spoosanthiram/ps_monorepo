#pragma once

#include <string_view>
#include <vector>

namespace ps::algo {

class TravelingSalesman
{
public:
    void read(std::string_view file_path);
    float tour();

private:
    void initialize_distance();
    void generate_subsets();
    unsigned int count_ones(unsigned int x);
    float compute_distance(unsigned int i, unsigned int j);

private:
    std::vector<std::pair<float, float>> vertices_;
    std::vector<std::vector<float>> distance_;
    std::vector<std::vector<unsigned int>> subsets_;
};

} // namespace ps::algo
