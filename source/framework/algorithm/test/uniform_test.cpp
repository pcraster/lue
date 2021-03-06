#define BOOST_TEST_MODULE lue framework algorithm uniform
#include "lue/framework/algorithm/all.hpp"
#include "lue/framework/algorithm/comparison.hpp"
#include "lue/framework/algorithm/uniform.hpp"
#include "lue/framework/test/array.hpp"
#include "lue/framework/test/hpx_unit_test.hpp"


namespace detail {

template<
    typename Element,
    std::size_t rank>
void test_array()
{
    using Array = lue::PartitionedArray<Element, rank>;

    auto const shape{lue::Test<Array>::shape()};

    Array array1{shape};
    Array array2{shape};

    Element min_value{7};
    Element max_value{9};

    // Fill two arrays with values from a uniform distribution and check
    // whether
    // - All cells in these arrays are >= min_value
    // - All cells in these arrays are < max_value
    // (- All cells in these arrays are different)

    {
        array1 = lue::uniform(array1, min_value, max_value);

        // min_value <= array1 < max_value
        BOOST_CHECK(lue::all(array1 >= min_value).get());

        if constexpr(std::is_floating_point_v<Element>) {
            BOOST_CHECK(lue::all(array1 < max_value).get());
        }
        else if constexpr(std::is_integral_v<Element>) {
            BOOST_CHECK(lue::all(array1 <= max_value).get());
        }
    }

    {
        array2 = lue::uniform(array2, min_value, max_value);

        // min_value <= array2 < max_value
        BOOST_CHECK(lue::all(array2 >= min_value).get());

        if constexpr(std::is_floating_point_v<Element>) {
            BOOST_CHECK(lue::all(array2 < max_value).get());
        }
        else if constexpr(std::is_integral_v<Element>) {
            BOOST_CHECK(lue::all(array2 <= max_value).get());
        }
    }

    {
        auto result = lue::uniform(array1, min_value, max_value);

        // min_value <= result < max_value
        BOOST_CHECK(lue::all(result >= min_value).get());

        if constexpr(std::is_floating_point_v<Element>) {
            BOOST_CHECK(lue::all(result < max_value).get());
        }
        else if constexpr(std::is_integral_v<Element>) {
            BOOST_CHECK(lue::all(result <= max_value).get());
        }
    }
}

}  // namespace detail


#define TEST_CASE(                               \
    rank,                                        \
    Element)                                     \
                                                 \
BOOST_AUTO_TEST_CASE(array_##rank##d_##Element)  \
{                                                \
    detail::test_array<Element, rank>();         \
}

TEST_CASE(1, int32_t)
TEST_CASE(2, int32_t)

TEST_CASE(1, double)
TEST_CASE(2, double)

#undef TEST_CASE
