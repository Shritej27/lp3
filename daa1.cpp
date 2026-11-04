#include <iostream>
using namespace std;

// Recursive method
long long fibonacciRecursive(int n) {
    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    return fibonacciRecursive(n - 1)
         + fibonacciRecursive(n - 2);
}

// Non-recursive (iterative) method
long long fibonacciIterative(int n) {
    if (n == 0)
        return 0;

    long long a = 0, b = 1;

    for (int i = 2; i <= n; i++) {
        long long c = a + b;
        a = b;
        b = c;
    }

    return b;
}

int main() {
    int n;

    cout << "Enter the position n: ";
    cin >> n;

    if (n < 0 || n > 92) {
        cout << "Please enter n between 0 and 92."
             << endl;
        return 0;
    }

    cout << "Recursive Fibonacci: "
         << fibonacciRecursive(n) << endl;

    cout << "Non-recursive Fibonacci: "
         << fibonacciIterative(n) << endl;

    return 0;
}