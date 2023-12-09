# Unlimited-Numbers-in-C++-
Course Project (COL106) under Prof. Rahul Garg [September 2023] : Enhanced C/C++ to handle large integers and rationals like Python, using string-based dynamic arrays for seamless arithmetic operations, bolstering numerical computing capabilities.
# UnlimitedInt
The UnlimitedInt class is a custom integer data type designed to handle integers of arbitrary size without any limitations on their magnitude. Unlike standard integer types in programming languages, such as int or long, which have fixed ranges, UnlimitedInt can represent extremely large or precise integer values. This class is a fundamental building block for working with integers in situations where traditional integer types fall short due to their size limitations.\
Class Description :\
The UnlimitedInt class has the following attributes and methods:\
• size: An integer that represents the size of the UnlimitedInt object.\
• capacity: An integer that represents the capacity of the UnlimitedInt object.\
• sign: An integer that indicates the sign of the UnlimitedInt object. It is set to 1 for positive numbers and -1 for negative numbers. For the UnlimitedInteger representing 0, you can set this to {-1,0,1}\
• unlimited int: An integer pointer that points to an array storing the unlimited integer.\
• get capacity(): Returns the capacity of the UnlimitedInt object.\
• get size(): Returns the size of the UnlimitedInt object.\
• get array(): Returns a pointer to the array storing the UnlimitedInt digits.\
• get sign(): Returns the sign of the UnlimitedInt object (1 for positive, -1 for negative).\
• to string(): Convert a UnlimitedInt object to its string representation. For eg. "5" for 5 and "-5" for -5.\
• Arithmetic operations such as addition, subtraction, multiplication, division, modulus for UnlimitedInt objects.\
# UnlimitedRational
A rational number is typically represented in the form p/q, where p and q are integers (Z), p and q are coprime (meaning they have no common divisors other than 1), and q ̸= 0.\
The UnlimitedRational class extends the concept of rational numbers by using the previously introduced UnlimitedInt class for its numerator and denominator. This allows you to accommodate even the most extensive calculations in scenarios where standard floating-point representations might suffer from precision loss.\
Class Description : \
The UnlimitedRational class includes the following attributes and methods:\
• p and q: Pointers to UnlimitedInt objects representing the numerator and denominator, respectively. (Remember, p and q must be coprime, or your implementation will not pass our tests.) Note if p is 0, any non-zero value of q will be acceptable for the denominator.\
• get p() and get q(): Methods to access the numerator and denominator as UnlimitedInt objects.\
• get p str() and get q str(): Methods to retrieve the numerator and denominator as string representations.\
• get frac str(): Method to return the rational number as a string in the form ”p/q”. If p/q is positive, then both ”p/q” and ”-p/-q” would be acceptable as answers. Similarly if p/q is negative, then the ”-”sign can be either in the numerator or the denominator.\
• Arithmetic operations such as addition, subtraction, multiplication, division for UnlimitedRational objects.\
Note the following error conditions:\
1. Incase of division by 0, the answer will be 0/0
2. Any operation with 0/0 as one of the operands must return 0/0 as the correct answer.
