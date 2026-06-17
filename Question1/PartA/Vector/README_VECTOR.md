# Vector Code Structure and Functionality

### Lines 4-6: Private Members
Defines `mSize` to store the vector length and `mData` as a raw double pointer to manage the dynamic array.

### Lines 8-19: Parameterized Constructor
Allocates dynamic memory for a specific size using `new double[mSize]` and explicitly sets every element to `0.0` using a standard `for` loop.

### Lines 20-24: Destructor
Safely frees the allocated heap memory using `delete[]` when the object is destroyed to prevent memory leaks.

### Lines 25-36: Copy Constructor
Enables deep copying by allocating a separate memory block for a new vector and copying all values from an existing one.

### Lines 37-54: Assignment Operator (`operator=`)
Handles copying data between two existing vectors. It checks for self-assignment, deletes the old memory buffer, and performs a deep copy.

### Lines 55-61: Unary Minus Operator (`operator-`)
Inverts the mathematical sign of each element and returns the result as a new temporary `Vector` object.

### Lines 62-68: Binary Addition Operator (`operator+`)
Performs element-by-element addition between two vectors and outputs the calculated sum into a new vector.

### Lines 69-75: Binary Subtraction Operator (`operator-`)
Performs element-by-element subtraction between two vectors and outputs the calculated difference into a new vector.

### Lines 76-82: Scalar Multiplication Operator (`operator*`)
Multiplies each individual element within the array by a single `double` scalar value.

### Lines 83-85: Subscript Operator (`operator[]`)
Provides standard 0-based array indexing to read or modify values directly in memory.

### Lines 86-88: Function Call Operator (`operator()`)
Provides mathematical 1-based indexing by internally shifting the requested index to `index - 1`.

### Lines 89-91: Size Getter (`getSize`)
A public accessor method that safely returns the private `mSize` value to external functions.

### Lines 92-99: Print Method
Iterates through the data array and prints the vector elements to the console in a structured `[ x y z ]` format.

### Lines 101-118: Main Function (`main`)
The program entry point that prompts the user for a vector size, accepts dynamic console inputs using a loop, and tests the class implementation.