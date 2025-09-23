#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    int n, sum = 0, x;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        sum += x;
        cout << x << " " << sum << " \n";
    }
    return 0;
}
