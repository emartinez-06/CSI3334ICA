#include <algorithm>
#include <ctime>
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

/* A TrieNode object represents one node in the trie. A node represents one
 * letter of a word (not an entire word).
 *
 * Each TrieNode has two data members:
 *  - a vector of 26 child pointers corresponding to 26 letters, and
 *  - a boolean indicating whether or not this node is the end of a word
 *    (meaning that the path to get here from the root was a word)
 *
 * Note that this trie doesn't store any letters (a-z). We know that the first
 * child of each node corresponds to 'a', the second to 'b', etc.  Remember that
 * you can turn a letter a-z into an index of 0-25 by subtracting the character
 * constant 'a', e.g.:
 *
 *      char c = 'b';
 *      int ndx = c - 'a'; // now ndx contains 1
 *
 * For simplicity we're *not* using a separate Trie class (which would only have
 * the root pointer); we'll just use this class and keep our own pointer to the
 * root.
 */
class TrieNode {
   public:
    // every TrieNode has 26 child pointers for a-z
    enum { NUM_CHILDREN = 26 };

    // Construct a trie node with no children, which does not end a word
    TrieNode() : children(NUM_CHILDREN, nullptr), is_word(false) {}
    // Destroy a trie node by deleting all of its children
    ~TrieNode() {
        for (auto &c : children) {
            delete c;
        }
    }

    // You write insert() and find() -- see below the class declaration
    void insert(string const &word, int position = 0);
    bool find(string const &word, int position = 0) const;

   private:
    vector<TrieNode *> children;
    bool is_word;
};

/* insert() recursively inserts the given word into the trie, character by
 * character, creating nodes as needed. The last thing that it does is set
 * is_word to true.
 *
 * Here are suggestions for how to think about implementing this recursively:
 *  1. Base case: We reach the base case when we get to the end of the word.
 *     So this node is the end of a word, and we should indicate that.
 *  2. Non-base case: We are currently looking at word[position]. We need to
 *     recursively insert with the next letter (word[position + 1]) by calling
 *     this method on a child node. If the child node doesn't exist, we need to
 *     create it first.
 *
 * Parameters:
 *  - word: the word that we are inserting
 *  - position: the current index in the word
 *
 * Return value: none
 */
void TrieNode::insert(string const &word, int position) {
    // FILL IN CODE HERE
}

/* find() recursively searches for the given word and returns true if it is in
 * the trie, false otherwise.
 *
 * Here are suggestions for how to think about implementing this recursively:
 *  1. Base case: We've reached the recursion base case when we've reached the
 *     end of the word. Did we find a word in the trie or not?
 *  2. Non-base case: We are currently looking at word[position]. Does this node
 *     have a child for that letter?
 *      - If so, continue the search in that child, by recursing.
 *      - If not, then is the word in the tree?
 *
 * Parameters:
 *  - word: the word that we are searching for
 *  - position: the current index in the word where we are in the search
 *
 * Return value: true if the word is found in the trie, false otherwise
 */
bool TrieNode::find(string const &word, int position) const {
    // FILL IN CODE HERE
}

/* convert all characters in a string to lowercase, and also check that they are
 * alphabet characters a-z using islower().
 *
 * Parameters:
 *  - s: the string to modify
 * Return value: none
 */
void lowercase_string(string *s) {
    for (size_t i = 0; i < s->size(); ++i) {
        s->at(i) = tolower(s->at(i));
        assert(islower(s->at(i))); // we only allow letters
    }
}

/* Read in words from a file (week_05_words.txt). Divide those words into two
 * groups (in and not in the dictionary). Then time how long it takes to
 * spell-check each group of words using a trie and using an unordered vector.
 *
 * Parameters: none
 * Return value: 0 on success, non-zero otherwise
 */
int main() {
    string const input_filename("week_05_words.txt");
    cout << "reading input from " << input_filename << endl;

    ifstream input(input_filename);
    vector<string> all_words;
    string word;
    while (input >> word) {
        lowercase_string(&word);
        all_words.push_back(word);
    }
    size_t const num_words = all_words.size();
    cout << "read in " << num_words << " words" << endl;

    // divide the words into two groups: those in the dictionary, and those not
    // in the dictionary
    vector<string>::iterator halfway = all_words.begin() + num_words / 2;
    vector<string> in_dictionary(all_words.begin(), halfway);
    vector<string> not_in_dictionary(halfway, all_words.end());

    // construct the trie
    TrieNode *root = new TrieNode;
    clock_t start = clock();
    for (auto const &w : in_dictionary) {
        root->insert(w);
    }
    double seconds = ((double)(clock() - start) / CLOCKS_PER_SEC);
    cout << "inserting " << in_dictionary.size() << " words into the trie took "
         << fixed << setprecision(2) << seconds << " seconds\n";

    // spell-check all the words with the Trie (both those in and not in the
    // dictionary)
    start = clock();
    for (auto const &w : in_dictionary) {
        if (!root->find(w)) {
            cout << "error: could not find " << w << " in the trie\n";
        }
    }
    for (auto const &w : not_in_dictionary) {
        if (root->find(w)) {
            cout << "error: " << w << " should not be in the trie\n";
        }
    }
    seconds = ((double)(clock() - start) / CLOCKS_PER_SEC);
    cout << "spell-checking " << all_words.size()
         << " words with the trie took " << fixed << setprecision(2) << seconds
         << " seconds\n";

    delete root;

    // spell-check all the words with the vector (both those in and not in the
    // dictionary)
    start = clock();
    for (auto const &w : in_dictionary) {
        if (find(in_dictionary.begin(), in_dictionary.end(), w) ==
            in_dictionary.end()) {
            cout << "error: could not find " << w << " in the vector\n";
        }
    }
    for (auto const &w : not_in_dictionary) {
        if (find(in_dictionary.begin(), in_dictionary.end(), w) !=
            in_dictionary.end()) {
            cout << "error: " << w << " should not be in the vector\n";
        }
    }
    seconds = ((double)(clock() - start) / CLOCKS_PER_SEC);
    cout << "spell-checking " << all_words.size()
         << " words with the vector took " << fixed << setprecision(2)
         << seconds << " seconds\n";

    return 0;
}
