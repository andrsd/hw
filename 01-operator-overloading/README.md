Operator overloading
====================

1. build a class that will represent a mathematical vector of n elements
   - have a method for setting values into the vector
   - have a method for getting/setting one element
     - do the same via an operator ()
   - a method for computing l2-norm
   - a method for multiplying the vector by a scalar

2. build a class that will represent an (m, n) matrix
   - have a method for setting values
   - have a method for getting/setting a single value from the matrix
     - do the same via an operator ()
   - a method for multiplying the matrix by a vector

3. overload operator `+` for vector addition
                     `*` for scalar product
                     `*` for matrix * vector

4. show that the implemented methods work :-)
