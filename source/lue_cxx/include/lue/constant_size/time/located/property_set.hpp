#pragma once
#include "lue/constant_size/property_set.hpp"
#include "lue/property_sets.hpp"


namespace lue {
namespace constant_size {
namespace time {
namespace located {

class PropertySet:
    public constant_size::PropertySet
{

public:

                   PropertySet         (hdf5::Identifier const& id);

                   PropertySet         (constant_size::PropertySet&&
                                            property_set);

                   PropertySet         (PropertySet const& other)=delete;

                   PropertySet         (PropertySet&& other)=default;

                   ~PropertySet        ()=default;

    PropertySet&   operator=           (PropertySet const& other)=delete;

    PropertySet&   operator=           (PropertySet&& other)=default;

private:

};


PropertySet        create_property_set (hdf5::Group& group,
                                        std::string const& name);

PropertySet        create_property_set (hdf5::Group& group,
                                        std::string const& name,
                                        omnipresent::same_shape::Value const&
                                            ids);

}  // namespace located
}  // namespace time
}  // namespace constant_size
}  // namespace lue