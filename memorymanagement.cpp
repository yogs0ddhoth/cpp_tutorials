/* Purpose: Demonstrate memory management in C++, based on examples provided in the sources:
    https://www.educative.io/blog/cpp-memory-management
    https://iamsorush.com/posts/weak-pointer-cpp/
*/

#include <iostream>
#include <memory>

using namespace std;

class ClassObj {
    public:
        int i;

        ClassObj() {
            cout << "ClassObj constructor called\n" << endl;
        };
        ~ClassObj() {
            cout << "ClassObj destructor called\n" << endl;
        };
};

int main()
{
    // declare pointer to an integer
    int *ptr;

    // allocate memory for an integer
    ptr = new int;

    cout << "\nMemory allocated for ptr\n" << endl;

    // assign a value to the allocated memory
    *ptr = 10;

    cout << "\n\tValue of ptr: " << *ptr << "\n" << endl;

    cout << "\n\tptr points to: " << ptr << "\n" << endl;

    cout << "------------------------------------------------------------\n";
    {   // scope for unique_ptr - only valid within this scope
        unique_ptr<ClassObj> smartPtr1(new ClassObj);

        // transfer ownership of the pointer from smartPtr1 to smartPtr2
        auto smartPtr2 = move(smartPtr1);

        smartPtr2->i = *ptr;

        cout << "\tUnique Pointer: " << smartPtr2->i << "\n" << endl;

        // unique_ptrs are automatically deallocated when they go out of scope
    }

    cout << "------------------------------------------------------------\n";
    {   // in resource constrained environments, manual deallocation is required

        unique_ptr<ClassObj> smartPtr1(new ClassObj);
        
        // release ownership of the pointer
        ClassObj* raw = smartPtr1.release();
        delete raw;
    }

    cout << "------------------------------------------------------------\n";
    {   // scope for shared_ptr

        // constructor for shared_ptr and type passed as argument
        shared_ptr<ClassObj> sharedPtr1 = make_shared<ClassObj>();

        // shared_ptr can be copied
        auto sharedPtr2 = sharedPtr1;

        // reset() deallocates the memory
        sharedPtr1.reset();

        sharedPtr2->i = *ptr;

        cout << "\tShared Pointer: " << sharedPtr2->i << "\n" << endl;
    }

    cout << "------------------------------------------------------------\n";
    {   // shared pointers can lead to circular dependencies
        // weak_ptr is used to break the circular dependency

        auto sharedPtr = make_shared<ClassObj>();
        sharedPtr->i = *ptr;

        // weak_ptr is created to observe the shared_ptr
        weak_ptr<ClassObj> weakPtr1 = sharedPtr;

        // lock() returns a shared_ptr to the object if the object is still alive
        if (auto sharedPtr2 = weakPtr1.lock()) {
            cout << "\tWeak pointer: " << sharedPtr2->i << "\n" << endl;
        };
    
    }

    // deallocate memory
    delete ptr;
    
    cout << "memory deallocated" << endl;

    cout << "\n\tValue of ptr: " << *ptr << "\n" << endl;
    cout << "\n\tptr points to: " << ptr << "\n" << endl;
    return 0;
}