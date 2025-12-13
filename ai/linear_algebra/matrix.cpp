#include "ai/linear_algebra/matrix.h"

#include <iostream>
#include <format>

namespace ps::ai {

Matrix::Matrix(uint32_t rows, uint32_t cols)
    : rows_{rows}
    , cols_{cols}
{
    matrix_ = std::make_unique<double[]>(rows_ * cols_);
}

Matrix::Matrix(uint32_t rows, uint32_t cols, const std::vector<double>& elements)
    : rows_{rows}
    , cols_{cols}
{
    matrix_ = std::make_unique<double[]>(rows_ * cols_);
    std::copy(elements.begin(), elements.end(), &matrix_[0]);
}

Matrix::Matrix(const Matrix& other)
    : rows_{other.rows_}
    , cols_{other.cols_}
{
    matrix_ = std::make_unique<double[]>(rows_ * cols_);
    std::copy(&other.matrix_[0], &other.matrix_[rows_ * cols_], &matrix_[0]);
}

void Matrix::apply_gaussian_elimination()
{
    for (uint32_t i = 0; i < rows_ - 1; ++i) {
        auto pivot = (*this)(i, i);
        for (uint32_t j = i + 1; j < rows_; ++j) {
            auto multiplier = (*this)(j, i) / pivot;
            for (uint32_t k = 0; k < cols_; ++k) {
                (*this)(j, k) = (*this)(j, k) - multiplier * (*this)(i, k);
            }
        }
    }
}

void Matrix::print() const
{
    for (uint32_t i = 0; i < rows_; ++i) {
        for (uint32_t j = 0; j < cols_; ++j) {
            std::cout << std::format("{:+5.0f}",matrix_[i * cols_ + j]) << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

} // namespace ps::ai
