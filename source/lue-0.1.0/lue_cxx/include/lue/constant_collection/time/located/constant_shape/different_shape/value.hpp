#pragma once
#include "lue/constant_collection/value.hpp"
#include "lue/item/different_shape/constant_shape/constant_collection/synchronous_value.hpp"


namespace lue {
namespace constant_collection {
namespace time {
namespace located {
namespace constant_shape {
namespace different_shape {

class Value:
    public lue::different_shape::constant_shape::constant_collection::SynchronousValue,
    public constant_collection::Value
{

public:

                   Value               (hdf5::Group const& parent,
                                        std::string const& name);

                   Value               (hdf5::Group const& parent,
                                        std::string const& name,
                                        hdf5::Datatype const& memory_datatype);

                   Value               (
    lue::different_shape::constant_shape::constant_collection::SynchronousValue&&
        collection);

                   Value               (Value const&)=delete;

                   Value               (Value&&)=default;

                   ~Value              ()=default;

    Value&         operator=           (Value const&)=delete;

    Value&         operator=           (Value&&)=default;

    hsize_t        nr_items            () const final;

private:

};


Value              create_value        (hdf5::Group& parent,
                                        std::string const& name,
                                        hdf5::Datatype const& file_datatype,
                                        hdf5::Datatype const& memory_datatype,
                                        int rank);

}  // namespace different_shape
}  // namespace constant_shape
}  // namespace located
}  // namespace time
}  // namespace constant_collection
}  // namespace lue