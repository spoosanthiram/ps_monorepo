#pragma once

#include "ai/deep_learning/logistic_regression/image_dataset.h"

#include <Eigen/Dense>

namespace ps::ai {

class LogisticRegressionModel
{
public:
    LogisticRegressionModel(const ImageDataset& train_dataset, const ImageDataset& test_dataset);

    void train(uint32_t num_iterations = 1000, double learning_rate = 0.009);

private:
    Eigen::MatrixXd train_set_x_;
    Eigen::MatrixXd train_set_y_;

    Eigen::MatrixXd test_set_x_;
    Eigen::MatrixXd test_set_y_;

    Eigen::MatrixXd w_;
    double b_{0.0};
};

} // namespace ps::ai
