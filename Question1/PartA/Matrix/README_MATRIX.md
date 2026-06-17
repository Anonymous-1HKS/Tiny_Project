# Matrix Code Structure and Functionality

### Lines 4-7: Private Members
Defines `mNumRows` and `mNumCols` to store the matrix dimensions, and `mData` as a double pointer (`double**`) to handle a dynamic 2D array.

### Lines 9-22: Parameterized Constructor
Validates dimensions using `assert`, allocates memory for rows and columns dynamically using `new`, and initializes all entries to `0.0`.

### Lines 23-30: Destructor
Safely loops through each allocated row to free the column memory buffers, then deletes the main row pointer array to prevent memory leaks.

### Lines 31-42: Copy Constructor
Enables deep copying by allocating a completely separate 2D memory block for a new matrix and copying all structural values from an existing one.

### Lines 43-63: Assignment Operator (`operator=`)
Handles data copying between two existing matrix objects. It prevents self-assignment, deallocates old memory, and performs a clean deep copy.

### Lines 64-69: Row and Column Getters (`getNumRows`, `getNumCols`)
Public accessor methods that safely return the private matrix dimensions to external functions.

### Lines 70-83: Function Call Operators (`operator()`)
Provides mathematical 1-based indexing for both reading and writing. Uses `assert` to check bounds and maps internally to `mData[i - 1][j - 1]`.

### Lines 84-93: Unary Minus Operator (`operator-`)
Inverts the mathematical sign of every element within the matrix and returns the result as a new temporary `Matrix` object.

### Lines 94-105: Binary Addition Operator (`operator+`)
Ensures matching matrix dimensions via `assert` and performs element-by-element addition into a new matrix object.

### Lines 106-117: Binary Subtraction Operator (`operator-`)
Ensures matching matrix dimensions via `assert` and performs element-by-element subtraction into a new matrix object.

### Lines 118-133: Matrix Multiplication Operator (`operator*`)
Asserts that the column count of the first matrix matches the row count of the second, then performs the standard dot-product matrix multiplication.

### Lines 134-143: Scalar Multiplication Operator (`operator*`)
Multiplies each individual element within the 2D array by a single `double` scalar value.

### Lines 144-153: Transpose Method (`transpose`)
Flips the matrix over its diagonal, switching its row and column indices to generate a new transposed matrix object.

### Lines 154-188: Determinant Method (`determinant`)
Computes the determinant of a square matrix using Gaussian elimination with partial pivoting. Returns `0.0` if the matrix is singular.

### Lines 189-228: Inverse Method (`inverse`)
Computes the exact multiplicative inverse of a square matrix by applying the Gauss-Jordan elimination method on an augmented matrix setup.

### Lines 229-238: Pseudo-Inverse Method (`pseudoInverse`)
Computes the Moore-Penrose pseudo-inverse using the formula $(A^T A)^{-1} A^T$ for tall matrices or $A^T (A A^T)^{-1}$ for wide matrices.

### Lines 239-247: Print Method
Iterates through rows and columns to output the matrix elements to the console in a clean grid format.

### Lines 249-277: Main Function (`main`)
The program entry point that prompts the user for matrix dimensions, captures input element-by-element, and demonstrates the mathematical methods.