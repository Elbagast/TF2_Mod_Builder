#ifndef ALL_CONSTRAINTS
#define ALL_CONSTRAINTS

#include "constraint.h"
#include "constraint_bool.h"
#include "constraint_int.h"
#include "constraint_double.h"
#include "constraint_string.h"
#include "constraint_path.h"
#include "constraint_elementid.h"

#include "constraint_vector.h"

//#include <type_traits>

// Determine of a type can be constrained by checking if the Constraint<T> destructor is implemented.
//template <typename T>
//bool Saklib::is_constrainable()
//{
//    return std::is_destructible<Constraint<T>>();
//}

#endif // ALL_CONSTRAINTS

