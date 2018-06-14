#pragma once
#include "lue/hdf5.hpp"
#include <vector>


namespace lue {

using Index = hsize_t;

using ID = hsize_t;
using IDs = std::vector<ID>;

using Rank = int;

using Count = hsize_t;
using Counts = std::vector<Count>;

using Shapes = std::vector<hdf5::Shape>;

} // namespace lue