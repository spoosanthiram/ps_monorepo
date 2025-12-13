#pragma once

#include "GeoLocation.h"

#include "core/utils/ClassHelper.h"

#include <string>
#include <unordered_map>

namespace Ps::Graphics {

class EpsgData
{
public:
    struct ProjectionInfo
    {
        std::string name;
        std::string proj4_text;
        // std::pair<GeoLocation, GeoLocation> lat_lon_min_max;
        // int epsg{0};
    };

public:
    static const EpsgData& get_instance();

    MOVE_CONSTRUCTOR(EpsgData) = default;
    MOVE_ASSIGNMENT(EpsgData) = default;

    COPY_CONSTRUCTOR(EpsgData) = delete;
    COPY_ASSIGNMENT(EpsgData) = delete;

    const std::unordered_map<int32_t, ProjectionInfo>& get_proj_info_map() const { return proj_info_map_; }
    const ProjectionInfo& get_proj_info(int32_t epsg) const;

private:
    EpsgData();

    std::unordered_map<int32_t, ProjectionInfo> proj_info_map_;
};

}  // namespace Ps::Graphics
