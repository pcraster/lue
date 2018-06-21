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


/*!
    @brief      Space domain items can be stationary or mobile through
                time
*/
enum class Mobility
{
    //! Space domain items stay in the same location for the whole time domain
    stationary,

    //! Space domain items move around through time
    mobile
};


enum class SpaceDomainItemType
{

    point,

    box,

    // line,

    // region,

    // cell

};

} // namespace lue
