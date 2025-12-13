#include "algo/other/TravelingSalesman.h"

#include "core/utils/Utils.h"

#include <cmath>

namespace Ps::Algo {

void TravelingSalesman::read(std::string_view file_path)
{
    auto stream = Ps::Core::open_stream(file_path);

    std::string line;
    std::getline(stream, line); // number of points

    char* tmp;
    while (stream) {
        std::getline(stream, line);
        if (line.size() == 0) {
            continue;
        }
        float x = std::strtof(line.data(), &tmp);
        float y = std::stof(tmp + 1);
        vertices_.emplace_back(x, y);
    }
}

float TravelingSalesman::tour()
{
    initialize_distance();

    generate_subsets();

    for (auto& subset : subsets_) {
        for (unsigned int s : subset) {
            for (unsigned int j = 1; j < vertices_.size(); ++j) {
                if (s & (0x1 << j)) {
                    unsigned int s_j = (s ^ (0x1 << j)) / 2;
                    for (unsigned int k = 0; k < vertices_.size(); ++k) {
                        if (k == j) {
                            continue;
                        }
                        if (distance_[k][s_j] != std::numeric_limits<float>::infinity())
                            distance_[j][s / 2] =
                                std::min(distance_[j][s / 2], distance_[k][s_j] + compute_distance(k, j));
                    }
                }
            }
        }
    }

    float distance = std::numeric_limits<float>::infinity();

    unsigned int s = ((0x1u << vertices_.size()) / 2) - 1;
    for (unsigned int j = 1; j < vertices_.size(); ++j) {
        distance = std::min(distance, distance_[j][s] + compute_distance(j, 0));
    }

    return distance;
}

void TravelingSalesman::initialize_distance()
{
    distance_.resize(vertices_.size());

    unsigned int size = 0x1u << (vertices_.size() - 1);
    for (auto& v : distance_) {
        v.reserve(size);
        v.assign(size, std::numeric_limits<float>::infinity());
    }

    distance_[0][0x1 / 2] = 0;
}

void TravelingSalesman::generate_subsets()
{
    subsets_.resize(vertices_.size() - 1);

    unsigned int set_size = 0x1u << vertices_.size();

    // we care subset size (one bits) starting with 2 and need to have LSB of 1
    for (unsigned int s = 3; s < set_size; s += 2) {
        unsigned int nones = count_ones(s);
        if (nones > 1) {
            subsets_[nones - 2].push_back(s);
        }
    }
}

unsigned int TravelingSalesman::count_ones(unsigned int x)
{
    unsigned int ones = 0;
    while (x) {
        x = x & (x - 1);
        ++ones;
    }
    return ones;
}

float TravelingSalesman::compute_distance(unsigned int i, unsigned int j)
{
    float x1_x2 = vertices_[i].first - vertices_[j].first;
    float y1_y2 = vertices_[i].second - vertices_[j].second;

    return std::sqrt(x1_x2 * x1_x2 + y1_y2 * y1_y2);
}

} // namespace Ps::Algo
