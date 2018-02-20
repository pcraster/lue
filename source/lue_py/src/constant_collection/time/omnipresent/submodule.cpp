#include <pybind11/pybind11.h>


namespace py = pybind11;


namespace lue {
namespace constant_collection {
namespace time {
namespace omnipresent {
namespace different_shape {

void init_submodule(py::module& module);

}  // namespace different_shape


namespace same_shape {

void init_submodule(py::module& module);

}  // namespace same_shape


void init_property_class(py::module& module);
void init_space_box_domain_class(py::module& module);
void init_space_point_domain_class(py::module& module);


void init_submodule(
    py::module& module)
{
    py::module submodule = module.def_submodule(
        "omnipresent",
        R"(
    Module implementing the API for information that is omnipresent
    through time

    .. automodule:: lue.constant_collection.time.omnipresent.different_shape
    .. automodule:: lue.constant_collection.time.omnipresent.same_shape
)");

    init_property_class(submodule);

    different_shape::init_submodule(submodule);
    same_shape::init_submodule(submodule);

    init_space_box_domain_class(submodule);
    init_space_point_domain_class(submodule);
}

} // namespace omnipresent
} // namespace time
} // namespace constant_collection
} // namespace lue
