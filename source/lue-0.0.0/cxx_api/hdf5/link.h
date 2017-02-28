#pragma once
#include "lue/cxx_api/hdf5/identifier.h"
#include <string>


namespace lue {
namespace hdf5 {

bool               link_exists         (Identifier const& id,
                                        std::string const& name);

bool               soft_link_exists    (Identifier const& id,
                                        std::string const& name);

}  // namespace hdf5
}  // namespace lue