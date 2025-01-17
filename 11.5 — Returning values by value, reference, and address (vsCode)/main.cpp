#include <iostream>
#include <array>
#include <tuple>
#include  <string>
#include <utility> // for std::pair
#include <vector>

//function protytypes for Quiz time:
int sumTo(int);
void printEmployeeName(const struct Employee& emp);
std::pair<int, int> minmax(int,int);
int getIndexOfLargestValue(const std::vector<int>& array);
const std::string& getElement(const std::vector<std::string>& vec_str, std::size_t index);

int doubleValue(int x)
{
    int value{ x * 2 };

    return value;// A copy of value will be returned here
}// value goes out of scope here

int* allotaceArray(int size)
{
    return new int[size];
}

// Returns a reference to the index element of array
int& getElement(std::array<int, 25>& array, int index)
{
    /*
    We know that array[index] will not be destroyed when we return to the caller (since the caller 
    passed in the array in the first place!)so it's okay to return it by reference
    */
    return array[index];
}

int returnByValue()
{
    return 5;
}

int& returnByReference()
{
    static int x{ 5 };
    return x;
}

const int returnByValue_2()
{
    return 5;
}

struct S
{
    int m_x;
    double m_y;
};

S returnStruct()
{
    S s;
    s.m_x = 5;
    s.m_y = 7.8;
    return s;
};

std::tuple<int, double, float, int> returnTuple()// return a tuple that contains an int and a double
{
    return {5, 7.8, 1.2, 123};
}

struct Employee
{
    //just for instance...
    int x; 
    std::string name;
};


int main()
{
    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Returning values by value, reference, and address" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////
    /*
    n the three previous lessons, you learned about passing arguments to functions by value, reference, and address. 
    In this section, we’ll consider the issue of returning values back to the caller via all three methods.

    As it turns out, returning values from a function to its caller by value, address, or reference works almost exactly the 
    same way as passing arguments to a function does. All of the same upsides and downsides for each method are present. The 
    primary difference between the two is simply that the direction of data flow is reversed. However, there is one more added 
    bit of complexity -- because local variables in a function go out of scope and are destroyed when the function returns, we 
    need to consider the effect of this on each return type.
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Return by value" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////
    /*
    Return by value is the simplest and safest return type to use. When a value is returned by value, a copy of that value is 
    returned to the caller. As with pass by value, you can return by value literals (e.g. 5), variables (e.g. x), or expressions 
    (e.g. x+1), which makes return by value very flexible.

    Another advantage of return by value is that you can return variables (or expressions) that involve local variables declared 
    within the function without having to worry about scoping issues. Because the variables are evaluated before the function 
    returns, and a copy of the value is returned to the caller, there are no problems when the function’s variable goes out of 
    scope at the end of the function.
    */
    std::cout << doubleValue(12345) << '\n';

    /*
    Return by value is the most appropriate when returning variables that were declared inside the function, or 
    for returning function arguments that were passed by value. However, like pass by value, return by value is slow for 
    structs and large classes.

    When to use return by value:

        When returning variables that were declared inside the function
        When returning function arguments that were passed by value

    When not to use return by value:

        When returning a built-in array or pointer (use return by address)
        When returning a large struct or class (use return by reference)
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Return by address" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////
    /*
    Returning by address involves returning the address of a variable to the caller. Similar to pass by address, return by 
    address can only return the address of a variable, not a literal or an expression (which don’t have addresses). Because 
    return by address just copies an address from the function to the caller, return by address is fast.

    However, return by address has one additional downside that return by value doesn’t -- if you try to return the address 
    of a variable local to the function, your program will exhibit undefined behavior. Consider the following example:

    int* doubleValue(int x)
    {
        int value{ x * 2 };
        return &value; // return value by address here
    } // value destroyed here

    As you can see here, value is destroyed just after its address is returned to the caller. The end result is that the 
    caller ends up with the address of non-allocated memory (a dangling pointer), which will cause problems if used. This is a 
    common mistake that new programmers make. Many newer compilers will give a warning (not an error) if the programmer tries to 
    return a local variable by address -- however, there are quite a few ways to trick the compiler into letting you do something 
    illegal without generating a warning, so the burden is on the programmer to ensure the pointer they are returning will 
    point to a valid variable after the function returns.

    Return by address was often used to return dynamically allocated memory to the caller:
    */
    int* array{ allotaceArray(12) };

    // do stuff here

    delete[] array;

    /*
    This works because dynamically allocated memory is not destroyed at the end of the block in which it is allocated, so that 
    memory will still exist when the address is returned back to the caller. Keeping track of manual allocations can be difficult. 
    Separating the allocation and deletion into different functions makes it even harder to understand who’s responsible for 
    deleting the resource or if the resource needs to be deleted at all. Smart pointers (covered later) and types that clean 
    up after themselves should be used instead of manual allocations.

    When to use return by address:

        When returning dynamically allocated memory and you can’t use a type that handles allocations for you
        When returning function arguments that were passed by address

    When not to use return by address:

        When returning variables that were declared inside the function or parameters that were 
            passed by value (use return by value)
        When returning a large struct or class that was passed by reference (use return by reference)
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Return by reference" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////
    /*
    Similar to return by address, values returned by reference must be variables (you should not return a reference to a 
    literal or an expression that resolves to a temporary value, as those will go out of scope at the end of the function 
    and you’ll end up returning a dangling reference). When a variable is returned by reference, a reference to the variable 
    is passed back to the caller. The caller can then use this reference to continue modifying the variable, which can be 
    useful at times. Return by reference is also fast, which can be useful when returning structs and classes.

    However, just like return by address, you should not return local variables by reference. Consider the following example:
    
    int& doubleValue(int x)
    {
        int value{ x * 2 };
        return value; // return a reference to value here
    } // value is destroyed here
        
    In the above program, the program is returning a reference to a value that will be destroyed when the function returns. 
    This would mean the caller receives a reference to garbage. Fortunately, your compiler will probably give you a warning 
    or error if you try to do this.

    Return by reference is typically used to return arguments passed by reference to the function back to the caller. In the 
    following example, we return (by reference) an element of an array that was passed to our function by reference:    
    */
    std::array<int, 25> std_array;

    // Set the element of array with index 10 to the value 5
    getElement(std_array, 10) = 5;
 
    std::cout << "our array index 10: " << std_array[10] << '\n';

    /*
    When we call getElement(array, 10), getElement() returns a reference to the array element with index 10. 
    main() then uses this reference to assign that element the value 5.

    Although this is somewhat of a contrived example (because you can access array[10] directly), once you learn about 
    classes you will find a lot more uses for returning values by reference.

    When to use return by reference:

        When returning a reference parameter
        When returning a member of an object that was passed into the function by reference or address
        When returning a large struct or class that will not be destroyed at the end of the function (e.g. one that was 
        passed in by reference)

    When not to use return by reference:

        When returning variables that were declared inside the function or parameters that were passed by value (use return 
        by value)
        When returning a built-in array or pointer value (use return by address)
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Mixing return references and values" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////
    /*
    Although a function may return a value or a reference, the caller may or may not assign the result to a variable or 
    reference accordingly. Let’s look at what happens when we mix value and reference types.
    */

    int giana{ returnByReference() }; // case A -- ok, treated as return by value
    //int& ref{ returnByValue() }; // case B -- compile error since the value is an r-value, and an r-value can't bind to a non-const reference
    const int& cref{ returnByValue() }; // case C -- ok, the lifetime of the return value is extended to the lifetime of cref

    /*
    In case A, we’re assigning a reference return value to a non-reference variable. Because giana isn’t a reference, 
    the return value is copied into giana, as if returnByReference() had returned by value.

    In case B, we’re trying to initialize reference ref with the copy of the return value returned by returnByValue(). 
    However, because the value being returned doesn’t have an address (it’s an r-value), this will cause a compile error.

    In case C, we’re trying to initialize const reference cref with the copy of the return value returned by returnByValue(). 
    Because const references can bind to r-values, there’s no problem here. Normally, r-values expire at the end of the 
    expression in which they are created -- however, when bound to a const reference, the lifetime of the r-value (in this case, 
    the return value of the function) is extended to match the lifetime of the reference (in this case, cref)
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Lifetime extension doesn’t save dangling references" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////
    /*
    Consider the following program:

    const int& returnByReference()
    {
        return 5;
    }

    int main()
    {
        const int& ref { returnByReference() }; // runtime error
    }

    In the above program, returnByReference() is returning a const reference to a value that will go out of scope when the 
    function ends. This is normally a no-no, as it will result in a dangling reference. However, we also know that assigning 
    a value to a const reference can extend the lifetime of that value. So which takes precedence here? Does 5 go out of 
    scope first, or does ref extend the lifetime of 5?

    The answer is that 5 goes out of scope first, then the reference to 5 is copied back to the caller, and then ref extends 
    the lifetime of the now-dangling reference.

    However, the following does work as expected:
    */

    const int& ref_2{ returnByValue_2() };// ok, we're extending the lifetime of the copy passed back to main
    /*
    In this case, the literal value 5 is first copied back into the scope of the caller (main), and then ref extends the 
    lifetime of that copy.
    */

    
    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Returning multiple values" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////
    /*
    C++ doesn’t contain a direct method for passing multiple values back to the caller. While you can sometimes restructure 
    your code in such a way that you can pass back each data item separately (e.g. instead of having a single function return 
    two values, have two functions each return a single value), this can be cumbersome and unintuitive.

    Fortunately, there are several indirect methods that can be used.

    As covered in lesson 11.3 -- Passing arguments by reference, out parameters provide one method for passing multiple bits 
    of data back to the caller. We don’t recommend this method.

    A second method involves using a data-only struct:
    */
    S s{ returnStruct() };
    std::cout << s.m_x << ' ' << s.m_y << '\n';

    /*
    A third way is to use std::tuple. A tuple is a sequence of elements that may be different types, where the type of 
    each element must be explicitly specified.

    Here’s an example that returns a tuple, and uses std::get to get the nth element of the tuple (counting from 0):
    */

    std::tuple s2{ returnTuple() };// get our tuple
    std::cout << std::get<0>(s2) << ' ' << std::get<1>(s2) << ' ' << std::get<3>(s2) << '\n';// use std::get<n> to get the nth element of the tuple (counting from 0)


    /*
    This works identically to the prior example.

    You can also use std::tie to unpack the tuple into predefined variables, like so:
    */
    int a;
    double b;
    float c;
    int d;
    std::tie(a, b, c, d) = returnTuple();// put elements of tuple in variables a and b and c and d
    std::cout << a << ' ' << b << ' ' << c << ' ' << d <<'\n';

    /*
    As of C++17, a structured binding declaration can be used to simplify splitting multiple returned values into 
    separate variables:
    */
    auto [a2, b2, c2, d2]{ returnTuple() };// used structured binding declaration to put results of tuple in variables a,b,c,d

    /*
    Using a struct is a better option than a tuple if you’re using the struct in multiple places. 
    However, for cases where you’re just packaging up these values to return and there would be no reuse from defining 
    a new struct, a tuple is a bit cleaner since it doesn’t introduce a new user-defined data type.
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Conclusion" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////
    /*
    Most of the time, return by value will be sufficient for your needs. It’s also the most flexible and safest way to 
    return information to the caller. However, return by reference or address can also be useful, particularly when 
    working with dynamically allocated classes or structs. When using return by reference or address, make sure you 
    are not returning a reference to, or the address of, a variable that will go out of scope when the function returns!
    */

    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Conclusion" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////
    /*
    Write function prototypes for each of the following functions. Use the most appropriate parameter and return types 
    (by value, by address, or by reference), including use of const where appropriate.
    */

    /*
    1) A function named sumTo() that takes an integer parameter and returns the sum of 
    all the numbers between 1 and the input number. 
    */
    std::cout << "Please give me number for task nr 1: ";
    int tNR{};
    std::cin >> tNR;
    std::cout << "Sum between 1 and " << tNR << " is: " << sumTo(tNR) << '\n';


    /*
    2) A function named printEmployeeName() that takes an Employee struct as input. 
    */
    Employee emp;


    /*
    3) A function named minmax() that takes two integers as input and returns back to the caller the smaller and larger 
    number in a std::pair. A std::pair works identical to a std::tuple but stores exactly two elements. 
    */
    minmax(4, 7);

    /*
    4) A function named getIndexOfLargestValue() that takes an integer array (as a std::vector), and returns the index of 
    the largest element in the array. 
    */
    std::vector array_quiz{23, 56, 67, 34, 56, 89, 123};
    std::cout << "The largest element is: " << getIndexOfLargestValue(array_quiz) << '\n';

    /*
    5) A function named getElement() that takes an array of std::string (as a std::vector) and an index and returns the array 
    element at that index (not a copy). Assume the index is valid, and the return value is const.
    */
    std::vector<std::string> vec_str{"Jezus", "Chrystus", "jest", "Bogiem", "i", "Panem"};

    std::cout << getElement(vec_str, 10) << '\n';


    return 0;
}

int sumTo(int x)
{
    if(x == 1)
    {
        return 1;
    }
    else
    {   
        return x + sumTo(x-1);
    }
}
void printEmployeeName(const Employee& emp)
{

}

std::pair<int, int> minmax(int x, int y)
{
    return {x-y, x+y};
}

int getIndexOfLargestValue(const std::vector<int>& array)
{
    std::size_t lenght{ array.size() };

    int theBigestIndex{ 0 };

    for(int i{ 0 }; i < lenght; ++i)
    {
        if(array[i] > theBigestIndex)
        {
            theBigestIndex = array[i];
        }
    }

    return theBigestIndex;
}

const std::string& getElement(const std::vector<std::string>& vec_str, std::size_t index)
{
    std::size_t x{ index };

    static std::string oj{ "error" };

    if((index > 0) && (index < vec_str.size()))
    {
        return vec_str[x];
    }
    else
    {
        return oj;
    }
}