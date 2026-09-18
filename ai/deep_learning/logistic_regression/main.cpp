#include "ai/deep_learning/logistic_regression/image_dataset.h"
#include "ai/deep_learning/logistic_regression/logistic_regression_model.h"

#include <iostream>

int main()
{
    std::unique_ptr<ps::ai::LogisticRegressionModel> model;
    try {
        const auto train_image_dataset = ps::ai::load_train_image_dataset();
        std::cout << "Number of images in training dataset: " << train_image_dataset.num_images << '\n';
        // const auto image_0 = train_image_dataset.get_image(0);
        // write_ppm(image_0, "/Users/saravanan/Downloads/image_0.ppm");

        const auto test_image_dataset = ps::ai::load_test_image_dataset();
        std::cout << "Number of images in test dataset: " << test_image_dataset.num_images << '\n';
        // const auto image_0 = test_image_dataset.get_image(0);
        // write_ppm(image_0, "/Users/saravanan/Downloads/image_0.ppm");

        model = std::make_unique<ps::ai::LogisticRegressionModel>(train_image_dataset, test_image_dataset);
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << '\n';
        return 1;
    }

    model->train(2000, 0.005);

    return 0;
}
