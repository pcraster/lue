#define BOOST_TEST_MODULE lue case_study gps_track
#include <boost/test/unit_test.hpp>
#include "lue/lue.hpp"
#include "lue/test.hpp"
#include <numeric>


BOOST_AUTO_TEST_CASE(create_and_read_gps_track)
{
    namespace omnipresent = lue::constant_collection::time::omnipresent;

    std::string const dataset_name = "birds.lue";
    std::string const phenomenon_name = "birds";
    std::string const property_set_name = "birds";

    hsize_t const nr_birds = 10;
    std::vector<hsize_t> const ids{2, 4, 6, 8, 10, 9, 7, 5, 3, 1};

    // Per track the number of (time) points
    std::vector<std::size_t> nr_time_points{
        10, 11, 12, 13, 14, 15, 20, 21, 22, 23};

    using CoordinateType = double;
    lue::hdf5::Datatype const coordinate_datatype{
        lue::hdf5::NativeDatatypeTraits<CoordinateType>::type_id()};
    std::size_t const rank = 3;  // lat, lon, alt
    // Per track a collection of space points
    std::vector<std::vector<CoordinateType>> locations(nr_birds);
    lue::test::generate_values(locations, nr_time_points, rank);

    std::string const property_name = "pm10";
    using ValueType = double;
    lue::hdf5::Datatype const value_datatype{
        lue::hdf5::NativeDatatypeTraits<ValueType>::type_id()};
    std::vector<std::vector<ValueType>> pm10_values_written(nr_birds);
    lue::test::generate_values(pm10_values_written, nr_time_points);

    lue::test::DatasetFixture fixture{dataset_name};

    // Create
    {
        auto dataset = lue::create_dataset(dataset_name);
        auto& phenomenon = dataset.add_phenomenon(phenomenon_name);
        auto areas = lue::constant_collection::create_property_set(
            phenomenon, property_set_name);

        // Ids
        {
            auto& ids_ = areas.ids();
            ids_.reserve(nr_birds);
            ids_.write(ids.data());
        }

    //     // Domain
    //     {
    //         // Space domain
    //         {
    //             auto space_domain = omnipresent::create_space_box_domain(
    //                 areas, coordinate_datatype, rank);
    //             auto& boxes_ = space_domain.items();
    //             boxes_.reserve(nr_birds);
    //             boxes_.write(boxes.data());
    //         }
    //     }

    //     // Properties
    //     {

    //         // Field property
    //         {
    //             auto elevation = omnipresent::different_shape::create_property(
    //                 areas, elevation_property_name, value_datatype, rank);
    //             auto& elevation_fields_ = elevation.values();
    //             elevation_fields_.reserve(nr_birds, counts.data());
    //             for(hsize_t i = 0; i < nr_birds; ++i) {
    //                 elevation_fields_.write(i, elevation_fields[i].data());
    //             }

    //             // Discretization property
    //             {
    //                 auto discretization = omnipresent::same_shape::create_property(
    //                     areas, discretization_property_name, count_datatype,
    //                     lue::hdf5::Shape{rank});
    //                 auto& counts_ = discretization.values();
    //                 counts_.reserve(nr_birds);
    //                 counts_.write(counts.data());

    //                 elevation.discretize_space(discretization);
    //             }
    //         }
    //     }
    }

    lue::assert_is_valid(dataset_name);

    // Read
    {
        auto const dataset = lue::Dataset(dataset_name);
        auto const& phenomenon = dataset.phenomena()[phenomenon_name];
        auto const& property_set = phenomenon.property_sets()[property_set_name];

    //     BOOST_CHECK(
    //         property_set.configuration().type<lue::CollectionVariability>() ==
    //         lue::CollectionVariability::constant);

    //     lue::constant_collection::PropertySet areas{property_set.id()};

    //     // Ids
    //     {
    //         BOOST_CHECK_EQUAL(areas.ids().nr_items(), nr_birds);

    //         std::vector<hsize_t> ids_(nr_birds);
    //         areas.ids().read(ids_.data());

    //         BOOST_CHECK_EQUAL_COLLECTIONS(
    //             ids_.begin(), ids_.end(),
    //             ids.begin(), ids.end());
    //     }

    //     // Domain
    //     {
    //         auto const& domain = areas.domain();

    //         // Time domain
    //         {
    //             BOOST_CHECK(!time_domain_exists(domain));
    //         }

    //         // Space domain
    //         {
    //             BOOST_CHECK(space_domain_exists(domain));

    //             lue::SpaceDomain const space_domain{domain};
    //             auto const& configuration{space_domain.configuration()};

    //             BOOST_CHECK(
    //                 configuration.type<lue::CollectionVariability>() ==
    //                 lue::CollectionVariability::constant);
    //             BOOST_CHECK(
    //                 configuration.type<lue::Mobility>() ==
    //                 lue::Mobility::stationary);
    //             BOOST_CHECK(
    //                 configuration.type<lue::SpaceDomainItemType>() ==
    //                 lue::SpaceDomainItemType::box);

    //             omnipresent::SpaceBoxDomain space_box_domain{
    //                 lue::constant_collection::SpaceDomain{domain}};

    //             BOOST_CHECK_EQUAL(
    //                 space_box_domain.items().nr_items(), nr_birds);

    //             std::vector<CoordinateType> boxes_(nr_birds * 2 * rank);

    //             space_box_domain.items().read(boxes_.data());

    //             BOOST_CHECK_EQUAL_COLLECTIONS(
    //                 boxes_.begin(), boxes_.end(),
    //                 boxes.begin(), boxes.end());
    //         }
    //     }

    //     // Properties
    //     {

    //         // Field property
    //         {
    //             auto const& property =
    //                 areas.properties()[elevation_property_name];
    //             auto const configuration = property.configuration();

    //             BOOST_CHECK(
    //                 configuration.type<lue::CollectionVariability>() ==
    //                 lue::CollectionVariability::constant);
    //             BOOST_CHECK(
    //                 configuration.type<lue::ShapeVariability>() ==
    //                 lue::ShapeVariability::constant);
    //             BOOST_CHECK(
    //                 configuration.type<lue::ShapePerItem>() ==
    //                 lue::ShapePerItem::different);
    //             BOOST_CHECK(
    //                 configuration.type<lue::ValueVariability>() ==
    //                 lue::ValueVariability::constant);

    //             BOOST_CHECK(property.space_is_discretized());

    //             BOOST_CHECK(
    //                 omnipresent::different_shape::Property::file_datatype(
    //                     lue::hdf5::Group{property.id()}) ==
    //                 lue::hdf5::Datatype{H5T_IEEE_F32LE});

    //             omnipresent::different_shape::Property elevation_property{
    //                 lue::hdf5::Group{property.id()}, value_datatype};

    //             BOOST_CHECK_EQUAL(
    //                 elevation_property.values().nr_items(), nr_birds);

    //             for(std::size_t i = 0; i < nr_birds; ++i) {
    //                 lue::hdf5::Shape shape_written{
    //                     counts.begin() + (i * rank),
    //                     counts.begin() + ((i + 1) * rank)};
    //                 auto const shape_read{
    //                     elevation_property.values().value_shape(i)};
    //                 BOOST_CHECK(shape_read == shape_written);

    //                 auto const& values_written{elevation_fields[i]};
    //                 std::vector<ValueType> values_read(
    //                     std::accumulate(shape_read.begin(), shape_read.end(),
    //                         1, std::multiplies<hsize_t>()));
    //                 elevation_property.values().read(i, values_read.data());

    //                 BOOST_CHECK_EQUAL_COLLECTIONS(
    //                     values_read.begin(), values_read.end(),
    //                     values_written.begin(), values_written.end());
    //             }

    //             // Discretization property
    //             {
    //                 auto const& property =
    //                     elevation_property.space_discretization();
    //                 BOOST_CHECK_EQUAL(
    //                     property.id().name(),
    //                     lue::space_discretization_tag);
    //                 auto const configuration =
    //                     property.configuration();

    //                 BOOST_CHECK(
    //                     configuration.type<lue::CollectionVariability>() ==
    //                     lue::CollectionVariability::constant);
    //                 BOOST_CHECK(
    //                     configuration.type<lue::ShapeVariability>() ==
    //                     lue::ShapeVariability::constant);
    //                 BOOST_CHECK(
    //                     configuration.type<lue::ShapePerItem>() ==
    //                     lue::ShapePerItem::same);
    //                 BOOST_CHECK(
    //                     configuration.type<lue::ValueVariability>() ==
    //                     lue::ValueVariability::constant);

    //                 BOOST_CHECK(
    //                     omnipresent::same_shape::Property::file_datatype(
    //                         lue::hdf5::Group{property.id()}) ==
    //                     lue::hdf5::Datatype{
    //                         lue::hdf5::StandardDatatypeTraits<CountType>::
    //                             type_id()});

    //                 omnipresent::same_shape::Property discretization_property{
    //                     lue::hdf5::Group{property.id()}, count_datatype};

    //                 BOOST_CHECK_EQUAL(
    //                     discretization_property.values().nr_items(), nr_birds);

    //                 std::vector<CountType> values_read(nr_birds * rank);
    //                 discretization_property.values().read(values_read.data());

    //                 BOOST_CHECK_EQUAL_COLLECTIONS(
    //                     values_read.begin(), values_read.end(),
    //                     counts.begin(), counts.end());
    //             }
    //         }
    //     }
    }
}
