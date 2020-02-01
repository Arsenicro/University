#include "stack.h"

int main() {
#if 1
    for (unsigned int i = 0; i < 1000000; i++) {
        stack s1 = { 1, 2, 3, 4, 5 };
        stack s2 = s1; // Copy constructor.

        // j is not size_t, because multiplying size_t with itself is unnatural:
        for (unsigned int j = 0; j < 20; j++)
			s2.push(j * j);

        s1 = s2; // Assignment.
        s1 = s1; // Self assignemnt should always be checked.
        s1 = { 100, 101, 102, 103 }; // Works because the compiler inserts constructor
                                     // and calls assignment with the result.

        #if 1
            // Won’t compile. In order to get it compiled, remove const:
            stack& s = s1;
            s.top() = 20;
            s.push(15);
        #endif
    }
#endif

    stack foo;
    for (int i = 0; i < 15; i++) foo.push(i);
    for (int i = 0; i < 5; i++) foo.pop();
	foo.push(100);
    std::cout << "Standard constructor (push, pop): " << foo << std::endl;
    stack bar = {43, 13, 69, 21, 37 };
    std::cout << "Initializer list constructor: " << bar << std::endl;

    stack qux = bar;
	std::cout << "Copy, reset: " << qux << std::endl;


    return 0;
}
