#pragma once

#include <H5Cpp.h>

#include <span>
#include <string_view>
#include <vector>

namespace ps::ai {

struct Image
{
    std::span<const unsigned char> data;
    int32_t width;
    int32_t height;
};
void write_ppm(const Image& image, std::string_view filename);

struct ImageDataset
{
    ImageDataset(const H5::DataSet& x_dataset, const H5::DataSet& y_dataset);

    ImageDataset(const ImageDataset&) = delete;            // Disable copy constructor
    ImageDataset& operator=(const ImageDataset&) = delete; // Disable copy assignment operator

    Image get_image(int32_t index) const;

    int32_t num_images{0};
    int32_t image_height{0}; // Number of rows in the image
    int32_t image_width{0};  // Number of columns in the image
    int32_t image_size_bytes{0};
    std::vector<unsigned char> x_data;

    std::vector<int64_t> y_data; // Labels for the images (0 or 1)
};

ImageDataset load_train_image_dataset();
ImageDataset load_test_image_dataset();

} // namespace ps::ai
