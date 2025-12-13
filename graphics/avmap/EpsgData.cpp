#include "EpsgData.h"

#include <filesystem>
#include <fstream>
#include <regex>

using namespace units::literals;
namespace fs = std::filesystem;

namespace Ps::Graphics {

// constexpr int kUtm_North_To_Epsg_Offset{32600};
// constexpr int kUtm_South_To_Epsg_Offset{32700};
// constexpr int kUtm_Max_Zone_Number{60};
// constexpr units::angle::degree_t kUtm_Zone_Logitude_Span{6};

const EpsgData& EpsgData::get_instance()
{
    static EpsgData instace;
    return instace;
}

const EpsgData::ProjectionInfo& EpsgData::get_proj_info(int32_t epsg) const
{
    const auto it = proj_info_map_.find(epsg);
    if (it == proj_info_map_.end()) {
        throw std::runtime_error{"No projection found for " + epsg};
    }
    return it->second;
}

EpsgData::EpsgData()
{
    fs::path data_path{"graphics/data/maps/epsg.data"};
    if (!fs::exists(data_path)) {
        throw std::runtime_error{"EPSG data file does not exist"};
    }

    std::ifstream data_stream{data_path};
    if (!data_stream.is_open()) {
        throw std::runtime_error{"Could not open EPSG data file"};
    }

    const auto epsg_regex = std::regex{R"(<(\d+)>\s(.+)<>)"};
    std::smatch matches;

    std::string name;
    std::string line;
    while (!data_stream.eof()) {
        std::getline(data_stream, line);
        if (line.empty()) {
            continue;
        }
        if (line.starts_with('#')) {
            name = line;
        }
        else {
            if (std::regex_match(line, matches, epsg_regex)) {
                if (matches.size() == 3) {
                    const auto epsg = std::stoi(matches[1].str());
                    auto& proj_info = proj_info_map_[epsg];
                    proj_info.name = name;
                    proj_info.proj4_text = matches[2].str();

                    // // Prefill UTM based LatLonMinMax
                    // auto getBoundLatLon =
                    //     [](const units::angle::degree_t& minLat, const units::angle::degree_t& maxLat, int utmZone) {
                    //         return std::make_pair<GeoLocation, GeoLocation>(
                    //             {minLat, -180_deg + ((utmZone - 1) * kUtm_Zone_Logitude_Span)},
                    //             {maxLat, -180_deg + (utmZone * kUtm_Zone_Logitude_Span)});
                    //     };
                    // int utmNorthZone = epsg - kUtm_North_To_Epsg_Offset;
                    // int utmSouthZone = epsg - kUtm_South_To_Epsg_Offset;
                    // if (utmNorthZone > 0 && utmNorthZone <= kUtm_Max_Zone_Number) {
                    //     proj_info.lat_lon_min_max = getBoundLatLon(0_deg, 84_deg, utmNorthZone);
                    // }
                    // else if (utmSouthZone > 0 && utmSouthZone <= kUtm_Max_Zone_Number) {
                    //     proj_info.lat_lon_min_max = getBoundLatLon(-80_deg, 0_deg, utmSouthZone);
                    // }

                    // proj_info.epsg = epsg;
                }
                else {
                    std::cerr << "Format error!\n";
                }
            }
        }
    }
}

}  // namespace Ps::Graphics
