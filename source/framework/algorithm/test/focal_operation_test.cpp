#define BOOST_TEST_MODULE lue framework algorithm focal_operation
#include "lue/framework/algorithm/kernel.hpp"
#include "lue/framework/algorithm/fill.hpp"
#include "lue/framework/algorithm/focal_operation.hpp"
#include "lue/framework/algorithm/policy/default_policies.hpp"
#include "lue/framework/algorithm/serialize/kernel.hpp"
#include "lue/framework/test/array.hpp"
#include "lue/framework/test/compare.hpp"
#include "lue/framework/test/hpx_unit_test.hpp"


template<
    typename OutputElement_,
    typename... InputElements>
class Functor
{

    public:

        using OutputElement = OutputElement_;

        Functor()=default;

        template<
            typename Kernel,
            typename Subspan1>
        OutputElement operator()(
            [[maybe_unused]] Kernel const& kernel,
            [[maybe_unused]] Subspan1 const& window1) const
        {
            // Just return the center value in window1
            lue::Radius const radius{kernel.radius()};

            return window1(radius, radius);
        }

        template<
            typename Kernel,
            typename Subspan1,
            typename Subspan2>
        OutputElement operator()(
            [[maybe_unused]] Kernel const& kernel,
            [[maybe_unused]] Subspan1 const& window1,
            [[maybe_unused]] Subspan2 const& window2) const
        {
            // Just return the center value in window2
            lue::Radius const radius{kernel.radius()};

            return window2(radius, radius);
        }

};


template<
    typename OutputElement,
    typename... InputElement>
using DefaultPolicies = lue::policy::DefaultFocalOperationPolicies<
    lue::policy::OutputElements<OutputElement>,
    lue::policy::InputElements<InputElement...>>;


BOOST_AUTO_TEST_CASE(unary_focal_operation_2d)
{
    using InputElement1 = std::int32_t;
    using OutputElement = InputElement1;

    using Functor = ::Functor<OutputElement, InputElement1>;
    using Policies = ::DefaultPolicies<OutputElement, InputElement1>;

    InputElement1 const fill_value1{0};

    std::size_t const rank = 2;

    using InputArray1 = lue::PartitionedArray<InputElement1, rank>;
    using OutputArray = lue::PartitionedArray<OutputElement, rank>;
    using Shape = lue::ShapeT<InputArray1>;

    Shape const array_shape{{9, 9}};
    Shape const partition_shape{{3, 3}};

    InputArray1 input_array1{array_shape, partition_shape};
    lue::fill(input_array1, 1).wait();
    auto const kernel = lue::box_kernel<bool, rank>(1, true);
    OutputArray output_array =
        lue::focal_operation(Policies{fill_value1}, input_array1, kernel, Functor{});

    auto array_we_want = lue::test::create_partitioned_array<OutputArray>(
        array_shape, partition_shape, {
            { 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        });

    lue::test::check_arrays_are_equal(output_array, array_we_want);
}


BOOST_AUTO_TEST_CASE(binary_focal_operation_2d)
{
    using InputElement1 = std::int32_t;
    using InputElement2 = float;
    using OutputElement = InputElement2;

    using Functor = ::Functor<OutputElement, InputElement1, InputElement2>;
    using Policies = ::DefaultPolicies<OutputElement, InputElement1, InputElement2>;

    InputElement1 const fill_value1{0};
    InputElement2 const fill_value2{0};

    std::size_t const rank = 2;

    using InputArray1 = lue::PartitionedArray<InputElement1, rank>;
    using InputArray2 = lue::PartitionedArray<InputElement2, rank>;
    using OutputArray = lue::PartitionedArray<OutputElement, rank>;
    using Shape = lue::ShapeT<InputArray1>;

    Shape const array_shape{{9, 9}};
    Shape const partition_shape{{3, 3}};

    InputArray1 input_array1{array_shape, partition_shape};
    lue::fill(input_array1, 1).wait();
    InputArray2 input_array2{array_shape, partition_shape};
    lue::fill(input_array2, 2.0f).wait();
    auto const kernel = lue::box_kernel<bool, rank>(1, true);
    OutputArray output_array =
        lue::focal_operation(
            Policies{fill_value1, fill_value2},
            input_array1, input_array2, kernel, Functor{});

    auto array_we_want = lue::test::create_partitioned_array<OutputArray>(
        array_shape, partition_shape, {
            { 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f },
            { 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f },
            { 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f },
            { 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f },
            { 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f },
            { 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f },
            { 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f },
            { 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f },
            { 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f },
        });

    lue::test::check_arrays_are_equal(output_array, array_we_want);
}
