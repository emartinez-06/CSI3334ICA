#include <iostream>
#include <cassert>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

// declare "vii" to be a short hand name for an iterator over an integer vector
typedef vector<int>::iterator vii;

// convenience function to print a vector from beginning up to (but not
// including) end iterator
void print(vector<int>::const_iterator begin, vector<int>::const_iterator end) {
    for (auto i = begin; i != end; ++i)
        cout << " " << *i;
    cout << endl;
}

// Parent class which has a "runTest" method, but does not actually do any
// sorting. Subclasses will override the "name" and "do_sort" methods to
// specialize.
class SortingTest {
   public:
    virtual ~SortingTest() {}

    // Each subclass overrides this method to give its name.
    virtual string name() const = 0;

    // Each subclass overrides this method to implement an actual sorting
    // algorithm.
    virtual void do_sort(vii begin, vii end) = 0;

    // This method does most of the work to run a bunch of timed tests, and
    // then check that the data are actually being sorted properly.
    clock_t runTest(vector<int> const &orig, int trials) {
        // run "trials" tests, and time it
        vector<int> v(orig.size());
        clock_t start = clock();
        while (trials--) {
            v = orig;
            do_sort(v.begin(), v.end());
        }
        clock_t length = clock() - start;

        // now, check for correctness for the last one sorted
        vector<int> correct(orig);
        sort(correct.begin(), correct.end());
        if (correct != v) {
            cout << "Error in " << name() << endl;
            cout << "Correct:   ";
            print(correct.begin(), correct.end());
            cout << "Incorrect: ";
            print(v.begin(), v.end());
            assert(false);
        }

        return length;
    }
};

class CountingSortTest : public SortingTest {
   public:
    virtual ~CountingSortTest() {}
    virtual string name() const { return "Counting Sort"; }
    virtual void do_sort(vii begin, vii end) {
        // FILL IN HERE -- MY CODE IS ABOUT 10 LINES LONG
        auto lo = *min_element(begin, end);
        auto hi = *max_element(begin, end);
        vector<int> count(hi - lo + 1, 0);

        for (auto i = begin; i != end; ++i) {
            count[*i - lo]++;
        }

        for (int i = 0; i < count.size(); ++i) {
            for (int j = 0; j < count[i]; ++j) {
                *begin++ = i + lo;
            }
        }
    }
};

class InsertionSortTest : public SortingTest {
   public:
    virtual ~InsertionSortTest() {}
    virtual string name() const { return "Insertion Sort"; }
    virtual void do_sort(vii begin, vii end) {
        // FILL IN HERE -- MY CODE IS 3 LINES LONG
        for (vii i = begin + 1; i != end; ++i) {
            for (vii j = i; begin < i && *j < *(j - 1); --j) {
                swap(*(j - 1), *j);
            }
        }
    }
};

class StdlibSortTest : public SortingTest {
   public:
    virtual ~StdlibSortTest() {}
    virtual string name() const { return "C++ Standard Library Test"; }
    virtual void do_sort(vii begin, vii end) {
        // call the standard library's sorting algorithm
        sort(begin, end);
    }
};

int main(int argc, char **argv) {
    // set up random numbers, with a seed (for reproducible results)
    mt19937 random_number_generator(1845);

    const int TRIALS = 50;
    const int MAX_LENGTH = 10000;

    const int MAX_VALUE = (argc > 1) ? stoi(argv[1]) : 1000;
    const int OFFSET = (argc > 2) ? stoi(argv[2]) : 1000;

    cout << "Using MAX_VALUE = " << MAX_VALUE << " and OFFSET = " << OFFSET
         << endl;

    // create the tests
    vector<SortingTest *> tests = {new CountingSortTest, new StdlibSortTest,
                                   new InsertionSortTest};

    for (int length = 10; length <= MAX_LENGTH; length *= 2) {
        cout << "length = " << length << endl;

        // Create a randomly-filled vector
        vector<int> v(length);
        for (auto &vi : v)
            vi = random_number_generator() % MAX_VALUE + OFFSET;

        for (auto test : tests) {
            auto t = test->runTest(v, TRIALS);
            cout << setw(15) << right << t << "  " << test->name() << endl;
        }
    }

    for (auto test : tests)
        delete test;

    return 0;
}
