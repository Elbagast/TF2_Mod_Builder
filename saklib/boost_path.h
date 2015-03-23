#ifndef BOOST_PATH_H
#define BOOST_PATH_H

#ifndef Q_MOC_RUN
#include <boost/filesystem.hpp>
#endif // Q_MOC_RUN

namespace Mod
{

using path_type = boost::filesystem::path; // worth it?
//namespace bfs = boost::filesystem; // not sure this is wise

} // namespace Mod

#endif // TYPES_H
