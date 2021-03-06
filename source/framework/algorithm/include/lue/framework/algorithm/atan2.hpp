#pragma once
#include "lue/framework/algorithm/binary_local_operation.hpp"
#include "lue/framework/algorithm/policy/default_policies.hpp"
#include <cmath>


namespace lue {
namespace detail {

template<
    typename InputElement>
class ATan2
{

public:

    static_assert(std::is_floating_point_v<InputElement>);

    using OutputElement = InputElement;

    OutputElement operator()(
        InputElement const input_element1,
        InputElement const input_element2) const noexcept
    {
        return std::atan2(input_element1, input_element2);
    }

};

}  // namespace detail


namespace policy {
namespace atan2 {

template<
    typename Element>
using DefaultPolicies = policy::DefaultPolicies<
    OutputElements<Element>,
    InputElements<Element, Element>>;


}  // namespace atan2
}  // namespace policy


template<
    typename Element,
    Rank rank>
PartitionedArray<Element, rank> atan2(
    PartitionedArray<Element, rank> const& array1,
    PartitionedArray<Element, rank> const& array2)
{
    using Functor = detail::ATan2<Element>;
    using Policies = policy::atan2::DefaultPolicies<Element>;

    return binary_local_operation(Policies{}, array1, array2, Functor{});
}

}  // namespace lue
