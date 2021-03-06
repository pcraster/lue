Quick start
===========
The be able to use LUE, you have to import it::

    import lue

All code is documented using docstrings, so you can use Python's help function to find out about the module::

    help(lue)

The help function can also be used to find out about classes and instances::

    help(lue.Dataset)

    help(dataset)  # Assuming the instance exists...

Instances of the various LUE classes can be printed. This results in a terse information message, e.g.::

    >>> print(dataset)
    Dataset(name='planets.lue')

To get you started, we describe the general workflow for interacting with LUE datasets. For details, check out the docstrings of the LUE Python objects mentioned.

LUE information is stored in a dataset (see :py:class:`lue.Dataset`). Each dataset contains a collection of universes (:py:class:`lue.Universes` instance containing :py:class:`lue.Universe` instances) and a collection of phenomena (:py:class:`lue.Phenomena` instance containing :py:class:`lue.Phenomenon` instances). Each universe also contains a collection of phenomena. Each phenomenon contains a collection of property sets (:py:class:`lue.PropertySets` instance containing :py:class:`lue.PropertySet` instances). Each property set contains a single time domain (:py:class:`lue.TimeDomain`) and a single space domain (:py:class:`lue.SpaceDomain`), and contains a collection of properties (:py:class:`lue.Properties` instance).

The next sections will show you how to create and query a LUE dataset. It will use a subset of the LUE API. Use the pointers given above to find out about the rest of the API.


Create a new LUE dataset
------------------------
To create a new dataset from scratch we can use the free function called :py:func:`lue.create_dataset()`, which takes the name of the new dataset as an argument::

    >>> dataset = lue.create_dataset("planets.lue")

A LUE dataset contains universes and phenomena. Here, we will add a new phenomenon, called 'planets', to the phenomena collection::

    >>> planets = dataset.add_phenomenon("planets")

..
    A phenomenon contains property sets. A property set is an aggregate of a domain and zero or more properties sharing the domain. A domain can be created given a domain configuration. A domain configuration is an aggregate of a time domain configuration and a space domain configuration. To keep things simple, we assume an omnipresent time and omnipresent space domain. This means we don't have to explicitly create a domain configuration since an omnipresent spatio-temporal domain is the default domain. The property set created here is named 'omnipresent'.

    ::

        >>> properties = planets.add_property_set("omnipresent")


Query an existing LUE dataset
-----------------------------
In this section we will open de dataset created above and query it for its contents. To open an existing dataset we can use the free function called :py:func:`lue.open_dataset()`::

    >>> dataset = lue.open_dataset("planets.lue", "r")

To query the contents of a dataset, we can use the :py:attr:`lue.Dataset.universes` and :py:attr:`lue.Dataset.phenomena` attributes of the dataset instance. Here, we use the :py:attr:`lue.Dataset.phenomena` attribute to find out the names of the phenomena it contains::

    >>> print(dataset.phenomena.names)
    [u'planets']

The :py:class:`lue.Phenomena` class inherits functionality from the :py:class:`lue.PhenomenonCollection` class. To obtain an item from a collection we can use the subscript operator ``[]``, which takes the name of the item as an argument. Subscripting the :py:attr:`lue.Dataset.phenomena` attribute of the :py:class:`lue.Dataset` instance provides us with the phenomenon::

    >>> planets = dataset.phenomena["planets"]

A phenomenon has a :py:attr:`lue.Phenomenon.property_sets` attribute which represent the collection of property sets in the phenomenon. Subscripting the :py:attr:`lue.Phenomenon.property_sets` attributes provides us with the property set::

    >>> print(planets.property_sets.names)
    [u'constant']
    >>> constant = planets.property_sets["constant"]
