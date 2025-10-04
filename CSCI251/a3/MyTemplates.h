#ifndef MYTEMPLATES_H
#define MYTEMPLATES_H

// template to calc the difference between scalar values.
// Assumes T is going to be an object
// implemented as per assignment requirements
template <typename T>
double scalar_difference(T a, T b)
{
    return abs(a.getScalarValue() - b.getScalarValue());
}

// template function to check equality betwen two objects of type T
template <typename T>
bool equals(T a, T b)
{
    return a == b;
}

#endif
