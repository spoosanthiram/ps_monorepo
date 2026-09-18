#include "logistic_regression_model.h"

#include <iostream>

namespace ps::ai {

LogisticRegressionModel::LogisticRegressionModel(const ImageDataset& train_dataset, const ImageDataset& test_dataset)
{
    train_set_x_.resize(train_dataset.image_size_bytes, train_dataset.num_images);
    train_set_y_.resize(1, train_dataset.num_images);

    for (int32_t i = 0; i < train_dataset.num_images; ++i) {
        const auto image = train_dataset.get_image(i);
        for (int32_t j = 0; j < train_dataset.image_size_bytes; ++j) {
            train_set_x_(j, i) = static_cast<double>(image.data[j]) / 255.0; // Normalize pixel values to [0, 1]
        }
        train_set_y_(0, i) = static_cast<double>(train_dataset.y_data[i]);
    }

    test_set_x_.resize(test_dataset.image_size_bytes, test_dataset.num_images);
    test_set_y_.resize(1, test_dataset.num_images);

    for (int32_t i = 0; i < test_dataset.num_images; ++i) {
        const auto image = test_dataset.get_image(i);
        for (int32_t j = 0; j < test_dataset.image_size_bytes; ++j) {
            test_set_x_(j, i) = static_cast<double>(image.data[j]) / 255.0; // Normalize pixel values to [0, 1]
        }
        test_set_y_(0, i) = static_cast<double>(test_dataset.y_data[i]);
    }

    w_.resize(train_dataset.image_size_bytes, 1);
    w_.setZero();
}

void LogisticRegressionModel::train(uint32_t num_iterations, double learning_rate)
{
    for (uint32_t i = 0; i < num_iterations; ++i) {
        // Forward propagation
        Eigen::MatrixXd z = w_.transpose() * train_set_x_;
        z = z.array() + b_; // Add bias term

        Eigen::MatrixXd a = 1.0 / (1.0 + (-z.array()).exp()); // Sigmoid activation

        // Compute cost
        Eigen::MatrixXd cost_matrix =
            -train_set_y_.array() * a.array().log() - (1 - train_set_y_.array()) * (1 - a.array()).log();
        double cost = cost_matrix.mean();

        // Backward propagation
        Eigen::MatrixXd dz = a - train_set_y_;
        Eigen::MatrixXd dw = (train_set_x_ * dz.transpose()) / train_set_x_.cols();
        double db = dz.mean();

        // Update parameters
        w_ -= learning_rate * dw;
        b_ -= learning_rate * db;

        if (i % 100 == 0) {
            std::cout << "Iteration " << i << ", Cost: " << cost << '\n';
        }
    }
}

} // namespace ps::ai
