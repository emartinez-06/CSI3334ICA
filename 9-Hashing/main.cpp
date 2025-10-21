#include <iostream>
#include <vector>
#include <list>

using namespace std;

// Specialize a default HashFunc for int type.
struct DefaultIntHash {
    int operator()(int x) const { return x; }
};

// Uncomment this and make your own hash function that behaves better for this
// program
// struct YourIntHash { int operator()(int x) const { return /* fill in here */;
// } };

// hash table with a default hash function type
template <typename T, typename Hash>
class HashTable {
   public:
    HashTable(int size) : table(size), numItems(0) {}

    void insert(T const &item) {
        // fill in here
    }

    void remove(T const &item) {
        // fill in here
    }

    void dump(ostream &os) const {
        for (int i = 0; i < table.size(); ++i) {
            os << i << ":";
            for (auto const &entry : table[i]) {
                os << " " << entry;
            }
            os << endl;
        }
    }

    double loadFactor() const { return /* fill in here */; }

   private:
    vector<list<T>> table;
    int numItems;
    Hash hash;
};

int main(int argc, char **argv) {
    HashTable<int, DefaultIntHash> ht(7);

    // create a sequence to insert (and then remove)
    vector<int> sequence;
    for (int i = 1; i <= 5; ++i) {
        sequence.push_back(i * 3);
        sequence.push_back(i * 7 + 1);
    }

    // insert everything
    for (auto x : sequence) {
        ht.insert(x);
    }

    ht.dump(cout);
    cout << "Load factor: " << ht.loadFactor() << endl;

    // remove half of the things we inserted
    for (int i = 0; i < sequence.size() / 2; ++i) {
        ht.remove(sequence[i]);
    }

    ht.dump(cout);
    cout << "Load factor: " << ht.loadFactor() << endl;

    return 0;
}
