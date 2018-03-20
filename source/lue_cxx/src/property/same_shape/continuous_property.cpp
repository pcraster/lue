#include "lue/property/same_shape/continuous_property.hpp"


namespace lue {
namespace same_shape {

ContinuousProperty::ContinuousProperty(
    hdf5::Group& parent,
    std::string const& name)

    : Property{parent, name},
      _value{*this, value_tag}

{
}


ContinuousValue& ContinuousProperty::value()
{
    return _value;
}


ContinuousProperty create_continuous_property(
    PropertySet& property_set,
    std::string const& name,
    hdf5::Datatype const& memory_datatype)
{
    auto& properties = property_set.properties();
    auto& property = properties.add(name,
        create_property(properties, name));
    auto value = create_continuous_value(property, value_tag, memory_datatype);

    return ContinuousProperty{properties, name};
}

}  // namespace same_shape
}  // namespace lue
