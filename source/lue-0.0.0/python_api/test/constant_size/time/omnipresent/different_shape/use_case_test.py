import os.path
import numpy
import lue
import lue_test


class UseCaseTest(lue_test.TestCase):


    def verify_property_set_1(self,
            property_set):

        self.assertEqual(type(property_set),
            lue.constant_size.time.omnipresent.PropertySet)

        self.assertEqual(
            property_set.configuration.size_of_item_collection_type,
            lue.size_of_item_collection.constant)

        self.assertEqual(property_set.domain.configuration.time.type,
            lue.time_domain.omnipresent)
        self.assertEqual(property_set.domain.configuration.time.item_type,
            lue.time_domain_item.none)
        self.assertEqual(property_set.domain.configuration.space.type,
            lue.space_domain.located)
        self.assertEqual(property_set.domain.configuration.space.item_type,
            lue.space_domain_item.box)
        self.assertEqual(property_set.domain.configuration.space.mobility,
            lue.mobility.stationary)

        self.assertEqual(property_set.ids.dtype, numpy.uint64)
        self.assertEqual(len(property_set.ids.shape), 1)


    def test_1(self):

        dataset_name = self.relative_pathname(os.path.dirname(__file__),
            "my_dataset.lue")
        universe_name = "my_universe"
        phenomenon_name = "my_phenomenon"
        property_set_name = "my_property_set"
        property_name = "my_property"

        dataset = self.create_dataset(dataset_name)
        universe = dataset.add_universe(universe_name)
        phenomenon = universe.add_phenomenon(phenomenon_name)


        # Add a new property set. This returns a type with a special API,
        # which is dependent on the item/time domain configuration.
        property_set_configuration = lue.PropertySetConfiguration(
            lue.size_of_item_collection.constant)
        space_configuration = lue.SpaceDomainConfiguration(
            lue.space_domain.located, lue.space_domain_item.box)
        property_set = phenomenon.add_property_set(property_set_name,
            property_set_configuration, space_configuration)

        self.verify_property_set_1(property_set)
        self.assertEqual(property_set.ids.shape[0], 0)



        ### rank = 2

        ### space_domain = property_set.domain.space_domain
        ### self.assertEqual(space_domain.boxes.dtype, numpy.float64)
        ### self.assertEqual(len(space_domain.boxes.shape), 2)
        ### self.assertEqual(space_domain.boxes.shape[0], 0)
        ### self.assertEqual(space_domain.boxes.shape[1], 2 * rank)


        ### # Add items. This is independent of whether or not there are
        ### # properties added to the set.
        ### nr_items = 500
        ### items = property_set.reserve_items(nr_items)
        ### space_domain.boxes.reserve_items(nr_items)

        ### self.assertEqual(items.shape[0], nr_items)
        ### self.assertEqual(space_domain.boxes.shape[0], nr_items)

        ### items_ = numpy.array([id for id in range(nr_items)], numpy.uint64)
        ### items[:] = items_

        ### self.assertArraysEqual(items[:], items_)

        ### nr_coordinates_per_box = space_domain.boxes.shape[1]
        ### box_shape = (nr_coordinates_per_box,)
        ### boxes = numpy.arange(nr_items * nr_coordinates_per_box,
        ###     dtype=numpy.float64).reshape(nr_items, nr_coordinates_per_box)
        ### space_domain.boxes[:] = boxes

        ### self.assertArraysEqual(space_domain.boxes[:], boxes)


        ### #  # Now, add a property, whose values all have different shapes.
        ### #  # To simulate storing a number of spatial rasters, we first add
        ### #  # a discretization property and link it from the value property.
        ### #  value_shape = (2,)
        ### #  chunk_shape = (2,)
        ### #  value_type = numpy.uint32
        ### #  discretization_property = property_set.add_property(
        ### #      "space discretization", value_type, value_shape, chunk_shape)
        ### #  self.assertEqual(discretization_property.name, "space discretization")
        ### #  self.assertEqual(discretization_property.values.dtype, value_type)
        ### #  self.assertEqual(len(discretization_property.values.shape), 2)
        ### #  self.assertEqual(discretization_property.values.shape[0], 0)
        ### #  self.assertEqual(discretization_property.values.shape[1], 2)

        ### #  nr_cells = discretization_property.reserve_items(nr_items)
        ### #  self.assertEqual(discretization_property.values.shape[0], nr_items)

        ### #  nr_cells_ = numpy.arange(nr_items * 2, dtype=value_type).reshape(
        ### #      (nr_items, 2))
        ### #  nr_cells[:] = nr_cells_
        ### #  self.assertArraysEqual(nr_cells[:], nr_cells_)


        ### value_type = numpy.int32
        ### value_property = property_set.add_property(property_name, value_type,
        ###     rank)

        ### self.assertEqual(value_property.name, property_name)
        ### self.assertEqual(value_property.values.dtype, numpy.int32)
        ### self.assertEqual(value_property.values.rank, 2)
        ### self.assertEqual(len(value_property.values), 0)

        ### #  value_property.link_space_discretization(discretization_property)

        ### value_shapes = (10 * (numpy.random.rand(nr_items, rank) + 1)).astype(
        ###     numpy.uint64)

        ### values = value_property.reserve_items(value_shapes)

        ### self.assertEqual(len(values), nr_items)

        ### for i in range(nr_items):
        ###     for r in range(rank):
        ###         self.assertEqual(value_property.values[i].shape[r],
        ###             value_shapes[i][r])


        ### for i in range(nr_items):
        ###     shape = value_property.values[i].shape
        ###     values_ = (10 * numpy.random.rand(*shape)).astype(value_type)
        ###     values[i][:] = values_
        ###     self.assertArraysEqual(values[i][:], values_)


        ### # To discretize the item values, we need to create a new phenomenon.
        ### # This phenomenon will contain the information needed to decipher
        ### # the value.
        ### discr_phenomenon = universe.add_phenomenon("globals")
        ### discr_property_set = discr_phenomenon.add_property_set("discretization")

        ### self.assertEqual(discr_property_set.domain.configuration.time.type,
        ###     lue.time_domain.omnipresent)
        ### self.assertEqual(discr_property_set.domain.configuration.time.item_type,
        ###     lue.time_domain_item.none)
        ### self.assertEqual(discr_property_set.domain.configuration.space.type,
        ###     lue.space_domain.omnipresent)
        ### self.assertEqual(discr_property_set.domain.configuration.space.item_type,
        ###     lue.space_domain_item.none)
        ### self.assertEqual(discr_property_set.ids.dtype, numpy.uint64)
        ### self.assertEqual(len(discr_property_set.ids.shape), 1)
        ### self.assertEqual(discr_property_set.ids.shape[0], 0)

        ### # Add the same number of ids as there are space domain items.
        ### discr_nr_items = space_domain.boxes.shape[0]
        ### discr_items = discr_property_set.reserve_items(discr_nr_items)
        ### discr_items_ = numpy.array([id for id in range(discr_nr_items)],
        ###     numpy.uint64)
        ### discr_items[:] = discr_items_

        ### self.assertArraysEqual(discr_items[:], discr_items_)

        ### discr_value_type = numpy.uint32
        ### discr_value_shape = (2,)
        ### discr_chunk_shape = (2,)
        ### discr_property = discr_property_set.add_property("space discretization",
        ###     discr_value_type, discr_value_shape, discr_chunk_shape)

        ### self.assertEqual(discr_property.name, "space discretization")
        ### self.assertEqual(discr_property.values.dtype, discr_value_type)
        ### self.assertEqual(len(discr_property.values.shape), 2)
        ### self.assertEqual(discr_property.values.shape[0], 0)
        ### self.assertEqual(discr_property.values.shape[1], 2)

        ### shapes = discr_property.reserve_items(discr_nr_items)

        ### self.assertEqual(discr_property.values.shape[0], discr_nr_items)

        ### shapes_ = value_shapes.astype(discr_value_type)
        ### shapes[:] = shapes_
        ### self.assertArraysEqual(shapes[:], shapes_)

        ### value_property.link_space_discretization(discr_property)


        # Open and read the dataset. -------------------------------------------
        dataset = lue.open_dataset(dataset_name, "r")

        phenomena = dataset.phenomena
        self.assertEqual(len(phenomena), 0)

        universes = dataset.universes
        self.assertEqual(len(universes), 1)
        self.assertTrue(universe_name in universes)

        universe = universes[universe_name]
        phenomena = universe.phenomena
        self.assertEqual(len(phenomena), 1)
        self.assertTrue(phenomenon_name in phenomena)

        phenomenon = phenomena[phenomenon_name]
        property_sets = phenomenon.property_sets
        self.assertEqual(len(property_sets), 1)
        self.assertTrue(property_set_name in property_sets)

        property_set = property_sets[property_set_name]

        self.verify_property_set_1(property_set)
        ### self.assertEqual(property_set.ids.shape[0], nr_items)

        ### ids = property_set.ids

        ### self.assertEqual(ids.shape[0], nr_items)
        ### self.assertArraysEqual(ids[:], ids_)

        ### properties = property_set.properties
        ### print(properties)
        ### self.assertEqual(len(properties), 1)
        ### self.assertTrue(property_name in properties)

        ### property = properties[property_name]
        ### print(property)

        ### self.assertEqual(property.name, property_name)
        ### self.verify_property_1(property)