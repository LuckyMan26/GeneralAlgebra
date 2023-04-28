﻿//------------------------------------------------------------------------//
//                                                                        //
// Task 6 Calculation of the square root of a number Velychko Pavlo PI-22 //
//                                                                        //
//------------------------------------------------------------------------//


// This program asks the user for the value of a number and a prime number p,
// and then calls the tonelli_shanks function to calculate the square root of a modulo the prime p.
// 
// The result of the program execution will be both possible values ​​of the square roots of the number a modulo the prime number p.
// 
// 
// For example, let's take a = 25 p = 101
// The program correctly calculated the square roots of 25 modulo 101 using the Tonelli-Shanks algorithm and found them to be 5 and 96.
// This is because 25 is a quadratic remainder modulo 101
// (that is, there exists an integer x such that x^2 ≡ 25 modulo 101), and so it has two square roots modulo 101.
//  
// 
// It can be seen that the program works correctly and finds the roots of the quadratic equation for arbitrary numbers a and prime p.

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Calculates a^b mod n
long long power_mod(long long a, long long b, long long n) {     // power_mod modulo exponentiation calculation
    long long res = 1;
    while (b > 0) {
        if (b & 1) {
            res = (res * a) % n;
        }
        a = (a * a) % n;
        b >>= 1;
    }
    return res;
}

// Finds a^((p+1)/2) mod p, where p is a prime number
long long tonelli_shanks(long long a, long long p) {            // tonelli_shanks to calculate the square root
    long long q = p - 1;                                        // long long: represents an integer in the range from -9223372036854775808 to +9223372036854775807.
    int s = 0;                                                  
    while (q % 2 == 0) {
        q /= 2;
        s += 1;
    }
    if (s == 1) {
        return power_mod(a, (p + 1) / 4, p);
    }
    long long h;
    for (h = 2; power_mod(h, (p - 1) / 2, p) != p - 1; h++) {}
    long long c = power_mod(h, q, p);
    long long r = power_mod(a, (q + 1) / 2, p);
    long long t = power_mod(a, q, p);
    int n = s;
    while (t != 1) {
        long long tt = t;
        int i;
        for (i = 1; i < n; i++) {
            tt = (tt * tt) % p;
            if (tt == 1) {
                break;
            }
        }
        long long b = power_mod(c, 1LL << (n - i - 1), p);
        r = (r * b) % p;
        c = (b * b) % p;
        t = (t * c) % p;
        n = i;
    }
    return r;
}

int main() {                                                                
    long long a, p;
    cout << "Enter a and p: ";                              // It is necessary to enter the value of the number a and the prime number p
    cin >> a >> p;
    if (power_mod(a, (p - 1) / 2, p) != 1) { 
        cout << "a is not a quadratic residue mod p" << endl;      // In case a is not a quadratic remainder mod p
        return 0;
    }
    long long root1 = tonelli_shanks(a, p);
    long long root2 = p - root1;
    cout << "The square roots of " << a << " mod " << p << " are " << root1 << " and " << root2 << endl;            // Get an answer
    return 0;
}

