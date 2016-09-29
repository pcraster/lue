#pragma once
#include "lue/cxx_api/time/omnipresent/constant_shape/item.h"
#include "lue/cxx_api/time/omnipresent/constant_shape/property.h"
#include "lue/cxx_api/time/omnipresent/variable_shape/property.h"
#include "lue/cxx_api/time/property_set.h"
#include "lue/cxx_api/array.h"


namespace lue {
namespace time {
namespace omnipresent {

/*!
    @ingroup    lue_cxx_api_group
*/
class PropertySet:
    public time::PropertySet
{

public:

                   PropertySet         (lue::PropertySet& group);

                   PropertySet         (PropertySet const& other)=delete;

                   PropertySet         (PropertySet&& other)=default;

                   ~PropertySet        ()=default;

    PropertySet&   operator=           (PropertySet const& other)=delete;

    PropertySet&   operator=           (PropertySet&& other)=default;

    // Array&         reserve_items       (hsize_t const nr_items);

    // Array&         items               ();

    constant_shape::Item&
                   reserve_items       (hsize_t const nr_items);

    constant_shape::Item&
                   ids                 ();

    constant_shape::Property&
                   add_property        (std::string const& name,
                                        hid_t const file_type_id,
                                        hid_t const memory_type_id,
                                        Shape const& shape,
                                        Chunks const& chunks);

    variable_shape::Property&
                   add_property        (std::string const& name,
                                        // hid_t const memory_type_id,
                                        hid_t const file_type_id,
                                        size_t const rank);

private:

    // std::unique_ptr<Array> _items;

    std::unique_ptr<constant_shape::Item> _ids;

    std::vector<std::unique_ptr<constant_shape::Property>>
        _constant_shape_properties;

    std::vector<std::unique_ptr<variable_shape::Property>>
        _variable_shape_properties;

};


void               configure_property_set(
                                        hdf5::Identifier const& location,
                                        std::string const& name,
                                        SpaceDomainConfiguration const&
                                            domain_configuration);

}  // namespace omnipresent
}  // namespace time
}  // namespace lue