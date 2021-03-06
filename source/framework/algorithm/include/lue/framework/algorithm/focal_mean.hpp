#pragma once
#include "lue/framework/algorithm/focal_operation.hpp"
#include "lue/framework/algorithm/policy/default_policies.hpp"
#include <cmath>
#include <limits>


namespace lue {
namespace detail {

template<
    typename InputElement>
class FocalMean
{

public:

    // If not, an OutputElement type must be passed in
    static_assert(std::is_floating_point_v<InputElement>);

    static_assert(std::numeric_limits<InputElement>::has_quiet_NaN);

    using OutputElement = InputElement;

    FocalMean()=default;

    template<
        typename Kernel,
        typename Subspan>
    OutputElement operator()(
        Kernel const& kernel,
        Subspan const& window) const
    {
        static_assert(rank<Kernel> == 2);

        using Weight = ElementT<Kernel>;

        // TODO Add traits to grab typename of elements in Subspan
        // static_assert(std::is_same_v<ElementT<Subspan>, InputElement>);
        static_assert(std::is_same_v<Weight, bool> || std::is_floating_point_v<Weight>);

        OutputElement sum{0};
        double sum_of_weights{0};

        lue_assert(window.extent(0) == kernel.size());
        lue_assert(window.extent(1) == kernel.size());

        for(Index r = 0; r < window.extent(0); ++r) {
            for(Index c = 0; c < window.extent(1); ++c)
            {
                Weight const weight{kernel(r, c)};
                InputElement const value{window(r, c)};

                if constexpr(std::is_same_v<Weight, bool>) {
                    if(weight && !std::isnan(value)) {
                        sum += value;
                        sum_of_weights += 1.0;
                    }
                }
                else {
                    if(!std::isnan(value)) {
                        sum += weight * value;
                        sum_of_weights += weight;
                    }
                }
            }
        }

        return sum_of_weights > 0.0
            ? sum / sum_of_weights
            : std::numeric_limits<InputElement>::quiet_NaN();
    }

};

}  // namespace detail


namespace policy {
namespace focal_mean {

template<
    typename OutputElement,
    typename InputElement>
using DefaultPolicies = policy::DefaultFocalOperationPolicies<
    OutputElements<OutputElement>,
    InputElements<InputElement>>;

}  // namespace focal_mean
}  // namespace policy


template<
    typename Element,
    Rank rank,
    typename Kernel>
PartitionedArray<Element, rank> focal_mean(
    PartitionedArray<Element, rank> const& array,
    Kernel const& kernel)
{
    using Functor = detail::FocalMean<Element>;
    using OutputElement = OutputElementT<Functor>;
    using InputElement = Element;
    using Policies = policy::focal_mean::DefaultPolicies<OutputElement, InputElement>;

    InputElement const fill_value{std::numeric_limits<InputElement>::quiet_NaN()};

    return focal_operation(Policies{fill_value}, array, kernel, Functor{});
}

}  // namespace lue
