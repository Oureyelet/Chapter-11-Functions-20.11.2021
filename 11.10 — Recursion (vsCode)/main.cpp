#include <iostream>
#include <vector>

void countDown(int count)
{
    std::cout << "push " << count << '\n';
    countDown(count-1); // countDown() calls itself recursively
}

void countDown_plus(int count)
{   
    std::cout << "push " << count << '\n';

    if( count > 1 )// termination condition
        countDown_plus(count-1);
    
    std::cout << "pop " << count << '\n';
}

// return the sum of all the integers between 1 (inclusive) and sumto (inclusive)
// returns 0 for negative numbers
int sumTo(int sumto)
{
    if(sumto <= 0)
        return 0;// base case (termination condition) when user passed in an unexpected parameter (0 or negative)
    else if(sumto == 1)
        return 1;// normal base case (termination condition)
    else
        return sumTo(sumto-1) + sumto;// recursive function call
}

std::size_t Fibonacci(std::size_t x)
{
    //F(n) =	0 if n = 0
    //1 if n = 1
    //f(n-1) + f(n-2) if n > 1

    if(x == 0)// base case (termination condition)
        return 0;
    else if(x == 1)// base case (termination condition)
        return 1;
    else
        return (Fibonacci(x-1) + Fibonacci(x-2));
 }

// h/t to potterman28wxcv for a variant of this code
std::size_t Fibonacci_memoized_version(std::size_t x)
{
    // We'll use a static std::vector to cache calculated results
    static std::vector<int> results{0, 1};

    if(x < static_cast<int>(std::size(results)))
        return results[x];
    else
    {
        // Otherwise calculate the new result and add it
        results.push_back(Fibonacci(x - 1) + Fibonacci(x - 2));
        return results[x];
    }
}

int factorial_of_an_integer_N(int x)
{
    if(x <= 1)
        return 1;
    else
        return x * factorial_of_an_integer_N(x - 1);
}



int quesion_two(int x)
{
    if(x < 10)
        return x;
    else
        return quesion_two(x / 10) + x % 10;
}

void question_three(int x)
{
    // Termination cas
    if(x == 0)
        return;
    
    // Recurse to the next bit
    question_three(x/2);

    // Print out the remainders (in reverse order)
    std::cout << x % 2;
}

unsigned int question_threeB(unsigned int x)
{
    if(x == 0)
        return 0;
    
        question_three(x/2);

        std::cout << x % 2;
}


int main()
{
    std::cout << std::endl;
    ////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Recursion" << '\n';
    std::cout << "////////////////////////////////////////////////////////////////////" << '\n';
    ////////////////////////////////////////////////////////////////////////////////////////////
    /*
    A recursive function in C++ is a function that calls itself. Here is an example of a poorly-written recursive function:
    */

    //countDown(77);

    /*
    When countDown(5) is called, “push 5” is printed, and countDown(4) is called. countDown(4) prints “push 4” and calls 
    countDown(3). countDown(3) prints “push 3” and calls countDown(2). The sequence of countDown(n) calling countDown(n-1) 
    is repeated indefinitely, effectively forming the recursive equivalent of an infinite loop.

    In lesson 11.8 -- The stack and the heap, you learned that every function call causes data to be placed on the call stack. 
    Because the countDown() function never returns (it just calls countDown() again), this information is never being popped off 
    the stack! Consequently, at some point, the computer will run out of stack memory, stack overflow will result, and the 
    program will crash or terminate. On the author’s machine, this program counted down to -11732 before terminating!
    */


    std::cout << std::endl;
    ////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Recursive termination conditions" << '\n';
    std::cout << "////////////////////////////////////////////////////////////////////" << '\n';
    ////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Recursive function calls generally work just like normal function calls. However, the program above illustrates the 
    most important difference with recursive functions: you must include a recursive termination condition, or they will 
    run “forever” (actually, until the call stack runs out of memory). A recursive termination is a condition that, when met, 
    will cause the recursive function to stop calling itself.

    Recursive termination generally involves using an if statement. Here is our function redesigned with a termination 
    condition (and some extra output):
    */
    countDown_plus(5);

    /*
    Now when we run our program, countDown() will start by outputting the following:

    push 5
    push 4
    push 3
    push 2
    push 1

    If you were to look at the call stack at this point, you would see the following:

    countDown(1)
    countDown(2)
    countDown(3)
    countDown(4)
    countDown(5)
    main()

    Because of the termination condition, countDown(1) does not call countDown(0) -- instead, the “if statement” does 
    not execute, so it prints “pop 1” and then terminates. At this point, countDown(1) is popped off the stack, 
    and control returns to countDown(2). countDown(2) resumes execution at the point after countDown(1) was called, 
    so it prints “pop 2” and then terminates. The recursive function calls get subsequently popped off the stack until 
    all instances of countDown have been removed.

    Thus, this program in total outputs:

    push 5
    push 4
    push 3
    push 2
    push 1
    pop 1
    pop 2
    pop 3
    pop 4
    pop 5

    It’s worth noting that the “push” outputs happen in forward order since they occur before the recursive function call. 
    The “pop” outputs occur in reverse order because they occur after the recursive function call, as the functions are 
    being popped off the stack (which happens in the reverse order that they were put on).
    */


    std::cout << std::endl;
    ////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "A more useful example" << '\n';
    std::cout << "////////////////////////////////////////////////////////////////////" << '\n';
    ////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Now that we’ve discussed the basic mechanics of recursive function calls, let’s take a look at another recursive 
    function that is slightly more typical:
    */
    std::cout << sumTo(5) << '\n';

    /*
    Recursive programs are often hard to figure out just by looking at them. It’s often instructive to see what 
    happens when we call a recursive function with a particular value. So let’s see what happens when we call this 
    function with parameter sumto = 5.

    sumTo(5) called, 5 <= 1 is false, so we return sumTo(4) + 5.
    sumTo(4) called, 4 <= 1 is false, so we return sumTo(3) + 4.
    sumTo(3) called, 3 <= 1 is false, so we return sumTo(2) + 3.
    sumTo(2) called, 2 <= 1 is false, so we return sumTo(1) + 2.
    sumTo(1) called, 1 <= 1 is true, so we return 1.  This is the termination condition.

    Now we unwind the call stack (popping each function off the call stack as it returns):

    sumTo(1) returns 1.
    sumTo(2) returns sumTo(1) + 2, which is 1 + 2 = 3.
    sumTo(3) returns sumTo(2) + 3, which is 3 + 3 = 6.
    sumTo(4) returns sumTo(3) + 4, which is 6 + 4 = 10.
    sumTo(5) returns sumTo(4) + 5, which is 10 + 5 = 15.

    At this point, it’s easier to see that we’re adding numbers between 1 and the value passed in (both inclusive).

    Because recursive functions can be hard to understand by looking at them, good comments are particularly important.

    Note that in the above code, we recurse with value sumto - 1 rather than --sumto. We do this because operator- has a 
    side effect, and using a variable that has a side effect applied more than once in a given expression will result in 
    undefined behavior. Using sumto - 1 avoids side effects, making sumto safe to use more than once in the expression.
    */
    

    std::cout << std::endl;
    ////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Recursive algorithms" << '\n';
    std::cout << "////////////////////////////////////////////////////////////////////" << '\n';
    ////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Recursive functions typically solve a problem by first finding the solution to a subset of the problem (recursively), 
    and then modifying that sub-solution to get to a solution. In the above algorithm, sumTo(value) first solves sumTo(value-1), 
    and then adds the value of variable value to find the solution for sumTo(value).

    In many recursive algorithms, some inputs produce trivial outputs. For example, sumTo(1) has the trivial output 1 (you can 
    calculate this in your head), and does not benefit from further recursion. Inputs for which an algorithm trivially produces 
    an output is called a base case. Base cases act as termination conditions for the algorithm. Base cases can often 
    be identified by considering the output for an input of 0, 1, “”, ”, or null.
    */


    std::cout << std::endl;
    ////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Fibonacci numbers" << '\n';
    std::cout << "////////////////////////////////////////////////////////////////////" << '\n';
    ////////////////////////////////////////////////////////////////////////////////////////////
    /*
    One of the most famous mathematical recursive algorithms is the Fibonacci sequence. Fibonacci sequences appear in many places in nature, such as branching of trees, the spiral of shells, the fruitlets of a pineapple, an uncurling fern frond, and the arrangement of a pine cone.

    Here is a picture of a Fibonacci spiral:

    https://www.learncpp.com/cpp-tutorial/recursion/

    Each of the Fibonacci numbers is the length of the side of the square that the number appears in.

    Fibonacci numbers are defined mathematically as:

    F(n) =	0 if n = 0
    1 if n = 1
    f(n-1) + f(n-2) if n > 1
    */
    for(std::size_t i{ 0 }; i < 13; ++i)
    {
        std::cout << Fibonacci(i) << ' ';
    }
    std::cout << std::endl;

    /*
    Running the program produces the following result:

    0 1 1 2 3 5 8 13 21 34 55 89 144

    Which you will note are exactly the numbers that appear in the Fibonacci spiral diagram.
    */


    std::cout << std::endl;
    ////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Memoization algorithms" << '\n';
    std::cout << "////////////////////////////////////////////////////////////////////" << '\n';
    ////////////////////////////////////////////////////////////////////////////////////////////
    /*
    The above recursive Fibonacci algorithm isn’t very efficient, in part because each call to a Fibonacci non-base case 
    results in two more Fibonacci calls. This produces an exponential number of function calls (in fact, the above example 
    calls fibonacci() 1205 times!). There are techniques that can be used to reduce the number of calls necessary. 
    One technique, called memoization, caches the results of expensive function calls so the result can be returned when 
    the same input occurs again.

    Here’s a memoized version of the recursive Fibonacci algorithm:
    */
    for(std::size_t i{ 0 }; i < 20; ++i)
    {
        std::cout << Fibonacci_memoized_version(i) << ' ';
    }
    std::cout << std::endl;

    /*
    This memoized version makes 35 function calls, which is much better than the 1205 of the original algorithm.
    */


    std::cout << std::endl;
    ////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Recursive vs iterative" << '\n';
    std::cout << "////////////////////////////////////////////////////////////////////" << '\n';
    ////////////////////////////////////////////////////////////////////////////////////////////
    /*
    One question that is often asked about recursive functions is, “Why use a recursive function if you can do many of 
    the same tasks iteratively (using a for loop or while loop)?”. It turns out that you can always solve a recursive 
    problem iteratively -- however, for non-trivial problems, the recursive version is often much simpler to write (and read). 
    For example, while it’s possible to write the Fibonacci function iteratively, it’s a little more difficult! (Try it!)

    Iterative functions (those using a for-loop or while-loop) are almost always more efficient than their recursive counterparts. 
    This is because every time you call a function there is some amount of overhead that takes place in pushing and popping 
    stack frames. Iterative functions avoid this overhead.

    That’s not to say iterative functions are always a better choice. Sometimes the recursive implementation of a function 
    is so much cleaner and easier to follow that incurring a little extra overhead is more than worth it for the benefit in 
    maintainability, particularly if the algorithm doesn’t need to recurse too many times to find a solution.

    In general, recursion is a good choice when most of the following are true:

        The recursive code is much simpler to implement.
        The recursion depth can be limited (e.g. there’s no way to provide an input that will cause it to recurse down 
        100,000 levels).
        The iterative version of the algorithm requires managing a stack of data.
        This isn’t a performance-critical section of code.

    However, if the recursive algorithm is simpler to implement, it may make sense to start recursively and then optimize 
    to an iterative algorithm later.

    Best practice

    Generally favor iteration over recursion, except when recursion really makes sense.
    */


    std::cout << std::endl;
    ////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Quiz time" << '\n';
    std::cout << "////////////////////////////////////////////////////////////////////" << '\n';
    ////////////////////////////////////////////////////////////////////////////////////////////
    /*
    1)     
    A factorial of an integer N (written N!) is defined as the product (multiplication) of all the numbers 
    between 1 and N (0! = 1). Write a recursive function called factorial that returns the factorial of the input. 
    Test it with the first 7 factorials.

    Hint: Remember that (x * y) = (y * x), so the product of all the numbers between 1 and N is the same as the product 
    of all the numbers between N and 1.
    */
    std::cout << factorial_of_an_integer_N(6) << '\n';    

    /*
    2)
    Write a recursive function that takes an integer as input and returns the sum of each individual digit 
    in the integer (e.g. 357 = 3 + 5 + 7 = 15). Print the answer for input 93427 (which is 25). 
    Assume the input values are positive.
    */
    
    std::cout << quesion_two(123) << '\n';


    /*
    3a) This one is slightly trickier. Write a program that asks the user to enter a positive integer, and then uses a 
    recursive function to print out the binary representation for that number. 
    Use method 1 from lesson O.4 -- Converting between binary and decimal.

    Hint: Using method 1, we want to print the bits from the “bottom up”, which means in reverse order. 
    This means your print statement should be after the recursive call.
    */
    int x_q{};
    std::cout << "Enter a positive integer: ";
    std::cin >> x_q;

    question_three(x_q);

    std::cout << '\n';

    /*
    3b) Update your code from 3a to handle the case where the user may enter 0 or a negative number.

    Here’s a sample output (assuming 32-bit integers):

    Enter an integer: -15
    11111111111111111111111111110001

    Hint: You can turn a negative integer into a positive one by converting it to an unsigned integer. These have 
    identical bit representations (the type is used to determine how to interpret the number into decimal).
    */
    unsigned int x_qq{};
    std::cout << "Enter a negative integer: ";
    std::cin >> x_qq;

    question_threeB(x_qq);


    return 0;
}