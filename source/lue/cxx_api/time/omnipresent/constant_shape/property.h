#pragma once
#include "lue/cxx_api/time/property.h"
#include "lue/cxx_api/time/omnipresent/constant_shape/item.h"
#include <memory>


namespace lue {
namespace time {
namespace omnipresent {
namespace constant_shape {


/*!
    @ingroup    lue_cxx_api_group
*/
class Property:
    public time::Property
{

public:

                   Property            (lue::Property& group,
                                        hid_t const type_id);

                   Property            (Property const& other)=delete;

                   Property            (Property&& other)=default;

                   ~Property           ()=default;

    Property&      operator=           (Property const& other)=delete;

    Property&      operator=           (Property&& other)=default;

    Item&          reserve_items       (hsize_t const nr_items);

    Item&          values              ();

private:

    std::unique_ptr<constant_shape::Item> _values;

};


void               configure_property  (lue::Property const& location,
                                        hid_t const file_type_id,
                                        hid_t const memory_type_id,
                                        Shape const& shape,
                                        Chunks const& chunks);

}  // namespace constant_shape
}  // namespace omnipresent
}  // namespace time
}  // namespace lue