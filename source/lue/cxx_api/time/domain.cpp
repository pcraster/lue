#include "lue/cxx_api/time/domain.h"


namespace lue {
namespace time {

Domain::Domain(
    lue::Domain& group)

    : _group{std::ref(group)}

{
}


TimeDomain& Domain::time_domain() const
{
    return _group.get().time_domain();
}


SpaceDomain& Domain::space_domain() const
{
    return _group.get().space_domain();
}


DomainConfiguration const& Domain::configuration() const
{
    return _group.get().configuration();
}

} // namespace time
} // namespace lue