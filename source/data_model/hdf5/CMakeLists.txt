add_test_conditionally(test)

configure_file(
    include/lue/hdf5/configure.hpp.in
    include/lue/hdf5/configure.hpp
)

add_library(lue_hdf5 STATIC
    src/attribute
    src/attributes
    src/chunk
    src/dataset
    src/dataspace
    src/datatype
    src/error_stack
    src/file
    src/group
    src/hard_link
    src/hyperslab
    src/identifier
    src/issue
    src/issues
    src/link
    src/object_info
    src/primary_data_object
    src/property_list
    src/shape
    src/soft_link
    src/validate
    src/vlen_memory
)

add_library(lue::hdf5 ALIAS lue_hdf5)

target_compile_definitions(lue_hdf5
    PUBLIC
        # FIXME Contains -D, which trips the compiler
        # ${HDF5_C_DEFINITIONS}
        H5_USE_110_API
)

target_include_directories(lue_hdf5 SYSTEM
    PUBLIC
        ${Boost_INCLUDE_DIRS}
        $<$<BOOL:${LUE_HAVE_HDF5}>:${HDF5_C_INCLUDE_DIRS}>
)

target_include_directories(lue_hdf5
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(lue_hdf5
    PUBLIC
        lue::shared
        $<$<BOOL:${LUE_HAVE_HDF5}>:${HDF5_C_LIBRARIES}>
        $<$<NOT:$<BOOL:${LUE_HAVE_HDF5}>>:CONAN_PKG::hdf5>
    PRIVATE
        Boost::filesystem
        CONAN_PKG::fmt
)

if(HDF5_IS_PARALLEL)
    target_include_directories(lue_hdf5 SYSTEM
        PUBLIC
            ${MPI_CXX_INCLUDE_PATH}
    )
    target_link_libraries(lue_hdf5
        PRIVATE
            MPI::MPI_CXX
    )
endif()

install(
    TARGETS
        lue_hdf5
    EXPORT
        lue_targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
    DIRECTORY
        include
        ${CMAKE_CURRENT_BINARY_DIR}/include
    DESTINATION .
)
