#pragma once

#include <memory>
#include <vector>

namespace ps::ai {

class Matrix
{
public:
    Matrix(uint32_t rows, uint32_t cols);
    Matrix(uint32_t rows, uint32_t cols, const std::vector<double>& elements);

    Matrix(const Matrix& other);

    double& operator()(uint32_t row, uint32_t col) { return matrix_[row * cols_ + col]; }

    void apply_gaussian_elimination();

    void print() const;

private:
    uint32_t rows_;
    uint32_t cols_;
    std::unique_ptr<double[]> matrix_;
};

} // namespace ps::ai
