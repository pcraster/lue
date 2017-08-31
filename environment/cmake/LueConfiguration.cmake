# Short-cuts
option(LUE_BUILD_ALL
    "Build everything, except for documentation and tests"
    FALSE)
option(LUE_WITH_ALL
    "Support all features, except for MPI"
    FALSE)

# High level targets
option(LUE_BUILD_PYTHON_API
    "Build Python-API (implies LUE_BUILD_CXX_API)"
    FALSE)
option(LUE_BUILD_UTILITIES
    "Build LUE command line utilites (implies LUE_BUILD_HL_API)"
    TRUE)

# Lower level targets
option(LUE_BUILD_HL_API
    "Build HL-API (implies LUE_BUILD_CXX_API)"
    TRUE)
option(LUE_BUILD_CXX_API
    "Build CXX-API (implies LUE_BUILD_HDF5_API)"
    TRUE)
option(LUE_BUILD_HDF5_API
    "Build C++ wrapper library around HDF5 C-API"
    TRUE)

# Targets relevant for developers
option(LUE_BUILD_DOCUMENTATION
    "Build documentation"
    FALSE)
option(LUE_BUILD_TEST
    "Build tests"
    FALSE)

# Optional features
option(LUE_API_WITH_MPI
    "Include support for MPI"
    FALSE)


# Handle internal dependencies
if(LUE_BUILD_ALL)
    set(LUE_BUILD_PYTHON_API TRUE)
    set(LUE_BUILD_UTILITIES TRUE)
endif()

if(LUE_BUILD_PYTHON_API)
    set(LUE_BUILD_HL_API TRUE)
endif()

if(LUE_BUILD_UTILITIES)
    set(LUE_BUILD_HL_API TRUE)
endif()

if(LUE_BUILD_HL_API)
    set(LUE_BUILD_CXX_API TRUE)
endif()

if(LUE_BUILD_CXX_API)
    set(LUE_BUILD_HDF5_API TRUE)
endif()

if(LUE_BUILD_TEST)
    set(DEVBASE_BUILD_TEST TRUE)
endif()


if(LUE_WITH_ALL)
    # Turn on features when necessary.
    # ...
endif()


# Handle external dependencies.
if(LUE_BUILD_HDF5_API)
    set(DEVBASE_HDF5_REQUIRED TRUE)
    list(APPEND DEVBASE_REQUIRED_HDF5_COMPONENTS
        C)  # HL
endif()

if(LUE_BUILD_CXX_API)
    set(DEVBASE_BOOST_REQUIRED TRUE)
    list(APPEND DEVBASE_REQUIRED_BOOST_COMPONENTS
        filesystem system)

    if(LUE_API_WITH_MPI)
        set(DEVBASE_MPI_REQUIRED TRUE)
    endif()
endif()


if(LUE_BUILD_UTILITIES)
    set(DEVBASE_DOCOPT_REQUIRED TRUE)
    set(DEVBASE_GDAL_REQUIRED TRUE)
    set(DEVBASE_REQUIRED_GDAL_VERSION 2)
    set(DEVBASE_NLOHMANN_JSON_REQUIRED TRUE)

    set(LUE_BUILD_LUE_DUMP TRUE)
    set(LUE_BUILD_LUE_TRANSLATE TRUE)
    set(LUE_BUILD_LUE_UTILITY TRUE)
    set(LUE_BUILD_LUE_VALIDATE TRUE)
endif()


if(LUE_BUILD_PYTHON_API)
    set(DEVBASE_PYTHON_LIBS_REQUIRED TRUE)
    # set(DEVBASE_REQUIRED_PYTHON_VERSION 3)
    set(DEVBASE_NUMPY_REQUIRED TRUE)
    set(DEVBASE_PYBIND11_REQUIRED TRUE)
endif()


if(LUE_BUILD_TEST)
    set(DEVBASE_BOOST_REQUIRED TRUE)
    list(APPEND DEVBASE_REQUIRED_BOOST_COMPONENTS
        filesystem system unit_test_framework)
endif()


if(LUE_BUILD_DOCUMENTATION)
    set(DEVBASE_DOXYGEN_REQUIRED TRUE)
    set(DEVBASE_GRAPHVIZ_REQUIRED TRUE)
    set(DEVBASE_SPHINX_REQUIRED TRUE)

    find_program(EDIT_DOT_GRAPH
        edit_dot_graph.py
        PATHS ${PROJECT_SOURCE_DIR}/devbase/script
        NO_DEFAULT_PATH
    )
    if(NOT EDIT_DOT_GRAPH)
        message(FATAL_ERROR "edit_dot_graph.py not found")
    endif()
endif()
