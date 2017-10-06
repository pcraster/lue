#pragma once
#include "lue/hdf5/file.hpp"
#include "lue/hdf5/issues.hpp"


namespace lue {

void               validate            (hdf5::File const& file,
                                        hdf5::Issues& issues);

void               validate            (std::string const& name,
                                        hdf5::Issues& issues);

void               assert_is_valid     (hdf5::File const& file,
                                        bool const fail_on_warning=true);

void               assert_is_valid     (std::string const& name,
                                        bool const fail_on_warning=true);

}  // namespace lue