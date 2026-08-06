#include "image_dataset.h"

#include <filesystem>
#include <format>
#include <fstream>

namespace ps::ai {

void write_ppm(const Image& image, std::string_view filename)
{
    std::ofstream file_stream{filename.data()};
    if (!file_stream) {
        throw std::runtime_error("Could not open file for writing.");
    }

    file_stream << "P3\n";
    file_stream << std::format("{} {}", image.width, image.height) << '\n';
    file_stream << "255\n";

    for (int32_t i = 0; i < image.height; ++i) {
        for (int32_t j = 0; j < image.width; ++j) {
            const auto idx = (i * image.width + j) * 3;
            file_stream << std::format("{} {} {}", image.data[idx], image.data[idx + 1], image.data[idx + 2]) << '\n';
        }
        file_stream << '\n';
    }
}

ImageDataset::ImageDataset(const H5::DataSet& x_dataset, const H5::DataSet& y_dataset)
{
    // Read the dataset "train_set_x" from the HDF5 file
    {
        H5::DataSpace dataspace = x_dataset.getSpace();
        auto rank = dataspace.getSimpleExtentNdims();
        if (rank != 4) {
            throw std::runtime_error(std::format("Unexpected rank, {}, for dataset 'train_set_x'! Expected: 4", rank));
        }

        std::vector<hsize_t> dims;
        dims.resize(rank);
        dataspace.getSimpleExtentDims(dims.data());

        num_images = static_cast<int32_t>(dims[0]);
        image_height = static_cast<int32_t>(dims[1]);
        image_width = static_cast<int32_t>(dims[2]);
        image_size_bytes = static_cast<int32_t>(image_height * image_width * dims[3]);

        auto data_type = x_dataset.getDataType();
        if (data_type != H5::PredType::NATIVE_UCHAR) {
            throw std::runtime_error(std::format("Data type is not NATIVE_UCHAR for dataset 'train_set_x'!"));
        }

        x_data.resize(num_images * image_size_bytes);
        x_dataset.read(x_data.data(), H5::PredType::NATIVE_UCHAR);
    }

    // Read the dataset "train_set_y" from the HDF5 file
    {
        H5::DataSpace dataspace = y_dataset.getSpace();
        auto rank = dataspace.getSimpleExtentNdims();
        if (rank != 1) {
            throw std::runtime_error(std::format("Unexpected rank, {}, for dataset 'train_set_y'! Expected: 1", rank));
        }

        std::vector<hsize_t> dims;
        dims.resize(rank);
        dataspace.getSimpleExtentDims(dims.data());
        if (dims[0] != static_cast<hsize_t>(num_images)) {
            throw std::runtime_error(std::format(
                "Number of labels in 'train_set_y' ({}) does not match number of images ({})", dims[0], num_images));
        }

        auto data_type = y_dataset.getDataType();
        if (data_type != H5::PredType::NATIVE_INT64) {
            throw std::runtime_error(std::format("Data type is not NATIVE_INT64 for dataset 'train_set_y'!"));
        }

        y_data.resize(num_images);
        y_dataset.read(y_data.data(), H5::PredType::NATIVE_INT64);
    }
}

Image ImageDataset::get_image(int32_t index) const
{
    if (index < 0 || index >= num_images) {
        throw std::out_of_range(std::format("Index {} is out of range. Valid range: [0, {})", index, num_images));
    }
    return Image{std::span<const unsigned char>(x_data.data() + (index * image_size_bytes), image_size_bytes),
                 image_width,
                 image_height};
}

ImageDataset load_train_image_dataset()
{
    const auto file_path = "ai/deep_learning/dataset/train_cat_and_non-cat.h5";
    if (!std::filesystem::exists(file_path)) {
        throw std::runtime_error(std::format("File does not exist: {}", file_path));
    }

    H5::H5File file(file_path, H5F_ACC_RDONLY);

    return ImageDataset{file.openDataSet("train_set_x"), file.openDataSet("train_set_y")};
}

ImageDataset load_test_image_dataset()
{
    const auto file_path = "ai/deep_learning/dataset/test_cat_and_non-cat.h5";
    if (!std::filesystem::exists(file_path)) {
        throw std::runtime_error(std::format("File does not exist: {}", file_path));
    }

    H5::H5File file(file_path, H5F_ACC_RDONLY);

    return ImageDataset{file.openDataSet("test_set_x"), file.openDataSet("test_set_y")};
}

} // namespace ps::ai
