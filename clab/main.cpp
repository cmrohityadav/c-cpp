#include <iostream>
#include <memory>

using namespace std;

class Student
{
public:
    Student()
    {
        cout << "Student created\n";
    }

    ~Student()
    {
        cout << "Student destroyed\n";
    }
};

int main()
{
    // ==================================================
    // 1. BASIC shared_ptr
    // ==================================================

    shared_ptr<int> p = make_shared<int>(100);

    cout << *p << endl;  // 100
    cout << p.use_count() << endl; // 1


    // ==================================================
    // 2. COPY - Multiple owners
    // ==================================================

    shared_ptr<int> q = p;

    cout << *p << endl; // 100
    cout << *q << endl; // 100
    cout << p.use_count() << endl; // 2

    // ==================================================
    // 3. Another owner
    // ==================================================

    shared_ptr<int> r = q;

    cout << p.use_count() << endl; // 3
    cout << q.use_count() << endl; // 3
    cout << r.use_count() << endl; // 3


    // ==================================================
    // 4. reset()
    // ==================================================

    p.reset();

    cout << p.get() << endl; // 0
    cout << q.use_count() << endl; // 2


    /*
        p ownership chhod chuka hai.

            q ----\
                   ---> int(100)
            r ----/

        count = 2
    */


    // ==================================================
    // 5. Scope
    // ==================================================

    {
        shared_ptr<int> x = q;

        cout << q.use_count() << endl; // 3 


    } // x destroy -> count 3 -> 2

    cout << q.use_count() << endl; // 2


    // ==================================================
    // 6. get()
    // ==================================================

    int* raw = q.get();

    cout << *raw << endl; // 100

    // delete raw;   // ❌ NEVER DO THIS


    // ==================================================
    // 7. move()
    // ==================================================

    shared_ptr<int> a = make_shared<int>(500);

    shared_ptr<int> b = move(a);

    cout << a.get() << endl; // 0
    cout << *b << endl; // 500



    // ==================================================
    // 8. shared_ptr with class
    // ==================================================

    {
        shared_ptr<Student> s1 = make_shared<Student>();

        // OUTPUT:
        // Student created

        {
            shared_ptr<Student> s2 = s1;

            cout << s1.use_count() << endl;

            // OUTPUT:
            // 2
        }

        cout << s1.use_count() << endl;

        // OUTPUT:
        // 1

    } // last owner destroyed

    // OUTPUT:
    // Student destroyed


    // ==================================================
    // 9. Final ownership example
    // ==================================================

    shared_ptr<int> first = make_shared<int>(100);

    cout << first.use_count() << endl;

    // OUTPUT:
    // 1

    {
        shared_ptr<int> second = first;

        cout << first.use_count() << endl;

        // OUTPUT:
        // 2

        {
            shared_ptr<int> third = second;

            cout << first.use_count() << endl;

            // OUTPUT:
            // 3
        }

        cout << first.use_count() << endl;

        // OUTPUT:
        // 2
    }

    cout << first.use_count() << endl;

    // OUTPUT:
    // 1


    return 0;
}

