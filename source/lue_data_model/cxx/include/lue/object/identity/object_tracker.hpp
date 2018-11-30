#pragma once
#include "lue/info/identity/active_object_id.hpp"
#include "lue/info/identity/active_object_index.hpp"
#include "lue/info/identity/active_set_index.hpp"


namespace lue {

/*!
    @brief      Class for storing object tracking information for all
                temporal object array kinds

    Object array kind | Tracking
    ----------------- | --------
    same_shape::constant_shape::Value | ActiveSetIndex, ActiveObjectID
    same_shape::variable_shape::Value | ActiveSetIndex, ActiveObjectID
    different_shape::constant_shape::Value | ActiveSetIndex, ActiveObjectIndex, ActiveObjectID
    different_shape::variable_shape::Value | -
*/
class ObjectTracker
{

public:

    explicit       ObjectTracker       (hdf5::Group& parent);

                   ObjectTracker       (ObjectTracker const&)=delete;

                   ObjectTracker       (ObjectTracker&&)=default;

                   ~ObjectTracker      ()=default;

    ObjectTracker& operator=           (ObjectTracker const&)=delete;

    ObjectTracker& operator=           (ObjectTracker&&)=default;

    ActiveSetIndex const&
                   active_set_index    () const;

    ActiveSetIndex&
                   active_set_index    ();

    ActiveObjectIndex const&
                   active_object_index () const;

    ActiveObjectIndex&
                   active_object_index ();

    ActiveObjectID const&
                   active_object_id    () const;

    ActiveObjectID&
                   active_object_id    ();

private:

    ActiveObjectID _active_object_id;

    ActiveSetIndex _active_set_index;

    ActiveObjectIndex _active_object_index;

};


ObjectTracker         create_object_tracker(
                                        hdf5::Group& parent);

// void               link_object_tracker (hdf5::Group& parent,
//                                         TimeDomain& domain);
// 
// bool               has_linked_object_tracker(
//                                         hdf5::Group const& parent);

}  // namespace lue
