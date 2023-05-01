#include <iostream>
#include <vector>

using namespace std;

//-------------------------------------------------------------------------------------//
//                                                                                     //
// Task 11 Addition Subtraction Multiplication of two polynomials Velychko Pavlo PI-22 //
//                                                                                     //
//-------------------------------------------------------------------------------------//

// The code defines three functions for adding, subtracting, and multiplying polynomials, respectively. 
// Each of these functions takes two vectors as inputs, where each vector represents a polynomial. 
// The coefficients of the polynomials are stored in the vector, starting from the coefficient of the highest degree term to the constant term.

// The "add" function first checks which polynomial has more terms, then initializes a new vector to store the result of the addition.
// It then adds the corresponding coefficients of both polynomials, taking care to perform the operation modulo a large prime number N. 
// The function returns the result vector.
 
// The "sub" function is similar to the "add" function, but it subtracts the second polynomial from the first polynomial.

// The "mul" function multiplies two polynomials using the standard polynomial multiplication algorithm. 
// It initializes a new vector with the appropriate size to store the result, 
// and then multiplies the corresponding terms of both polynomials and accumulates the products in the appropriate positions in the result vector.

// <int> in case if it is not included in the main program, I also wrote a part for which this code can be tested.
// It demonstrates the use of these functions by creating two polynomials a and b and performing the add, subtract, and multiply operations on them.



/*
const int N = 1000000007; // prime number, module for the system of long modular arithmetic

typedef vector<int> vi;  // <vi> you can choose any

// function for adding two polynomials
vi add(vi a, vi b) {
    int n = a.size(), m = b.size();
    if (n < m) {
        swap(n, m);
        swap(a, b);
    }
    vi c(n);
    for (int i = 0; i < n; i++) {
        c[i] = a[i];
        if (i < m) c[i] = (c[i] + b[i]) % N;
    }
    return c;
}

// function for subtracting two polynomials
vi sub(vi a, vi b) {
    int n = a.size(), m = b.size();
    vi c(n);
    for (int i = 0; i < n; i++) {
        c[i] = a[i];
        if (i < m) c[i] = (c[i] - b[i] + N) % N;
    }
    while (c.size() > 1 && c.back() == 0) c.pop_back();
    return c;
}

// function for multiplying two polynomials
vi mul(vi a, vi b) {
    int n = a.size(), m = b.size();
    vi c(n + m - 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[i + j] = (c[i + j] + 1ll * a[i] * b[j]) % N;
        }
    }
    return c;
}

// test part
int main() {
    vi a = { 1, 2, 4 }; // polynomial a = x^2 + 2x + 4
    vi b = { 3, 2, 1 }; // polynomial b = x^2 + 2x + 3

    vi c = add(a, b); // addition a and b
    for (int i = 0; i < c.size(); i++) {
        cout << c[i] << " ";
    }
    cout << endl;

    vi d = sub(a, b); // subtraction b from a
    for (int i = 0; i < d.size(); i++) {
        cout << d[i] << " ";
    }
    cout << endl;

    vi e = mul(a, b); // multiplication a and b
    for (int i = 0; i < e.size(); i++) {
        cout << e[i] << " ";
    }
    cout << endl;

    return
        0;
}

*/