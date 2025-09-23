#include <iostream>
#include <sstream>
#include <stack>
#include <cassert>

using namespace std;

int main() {
    stack<int> operands;
    string line;

    // to finish the input (and get out of this loop),
    // type control-D on a blank line (linux/macos) and hit return
    while (getline(cin, line)) {
        istringstream line_tokenizer(line);
        string token;

        while (line_tokenizer >> token) {
            try { /*operand*/
                operands.push(stoi(token));

            } catch (std::invalid_argument) {
                int val1, val2, result;

                val1 = operands.top();
                operands.pop();

                val2 = operands.top();
                operands.pop();

                if (token == "*") {
                    result = val1 * val2;

                } else if (token == "+") {
                    result = val1 + val2;

                } else {
                    result = val1 - val2;
                }
                operands.push(result);
            }
        }

        if (operands.size() != 1) {
            cout << "the expression was not well-formed" << endl;
        }

        while (not operands.empty()) {
            cout << operands.top() << endl;
            operands.pop();
        }
    }

    return 0;
}
