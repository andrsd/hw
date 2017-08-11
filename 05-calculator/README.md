Calculator
==========

Write a all-purpose class that will take a string with math and evaluates it.
Support operator `+`, `-`, `*`, `/`. Support only positive real numbers and zero (i.e. ignore
negative numbers). Support operator priority.

Extra credit:
- support parenthesis
- support exponents (use `^` for it, so `2^8` it `2` to the power of eighth)
- support scientific notation for numbers, i.e. `1e5`

Example:
```
Calculator c("1 +2* 3");
double result = c.eval();
std::cerr << result << std::endl;
```

Your code will print `7`, not `9`.
Notice, that the class can deal with white spaces.
