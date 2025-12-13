#pragma once

#include "GpkgMapList.h"
#include "GpkgRasterReader.h"
#include "GpkgVectorReader.h"

namespace Ps::Graphics {

class PriorMap
{
public:
    PriorMap(const std::shared_ptr<GpkgMapList::MapInfo>& map_info);

    GraphicsGeometry get_segment_geometry();

private:
    std::shared_ptr<GpkgMapList::MapInfo> map_info_;
    GpkgVectorReader vector_reader_;
    GpkgRasterReader raster_reader_;
};

}  // namespace Ps::Graphics
