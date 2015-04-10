#ifndef ALL_CONSTRAINTS
#define ALL_CONSTRAINTS

#include "constraint_type.h"
#include "constraint_type_bool.h"
#include "constraint_type_int.h"
#include "constraint_type_double.h"
#include "constraint_type_string.h"
#include "constraint_type_path.h"
#include "constraint_type_elementid.h"

#include "constraint_type_vector.h"

//#include <type_traits>

// Determine of a type can be constrained by checking if the Constraint_Type<T> destructor is implemented.
//template <typename T>
//bool Saklib::is_constrainable()
//{
//    return std::is_destructible<Constraint_Type<T>>();
//}

#endif // ALL_CONSTRAINTS

