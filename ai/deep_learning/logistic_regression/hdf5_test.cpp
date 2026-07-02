#include <H5Cpp.h>

#include <iostream>
#include <vector>

int main()
{
    H5::H5File file("ai/deep_learning/dataset/test_catvnoncat.h5", H5F_ACC_RDONLY);
    H5::DataSet dataset = file.openDataSet("test_set_x");
    H5::DataSpace dataspace = dataset.getSpace();

    const auto rank = dataspace.getSimpleExtentNdims();
    std::cout << "Rank: " << rank << std::endl;

    std::vector<hsize_t> dims(rank);
    dataspace.getSimpleExtentDims(dims.data());
    std::cout << "Dimensions: ";
    for (const auto& dim : dims) {
        std::cout << dim << " ";
    }
    std::cout << '\n';

    return 0;
}
