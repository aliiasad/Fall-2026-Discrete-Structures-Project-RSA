#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
typedef unsigned long long uint64;
uint64 mul_mod(uint64 a, uint64 b, uint64 m);
uint64 mod_exp(uint64 b, uint64 n, uint64 m);
uint64 gcd(uint64 a, uint64 b);
long long extended_gcd(long long a, long long b, long long &s, long long &t);
uint64 mod_inverse(uint64 a, uint64 m);
bool is_prime(uint64 n);
void generate_keys(uint64 p, uint64 q, uint64 e, uint64 &n, uint64 &d);
uint64 encrypt(uint64 M, uint64 n, uint64 e);
uint64 decrypt(uint64 C, uint64 n, uint64 d);
int block_size(uint64 n);
string encrypt_text(const string &text, uint64 n, uint64 e);
string decrypt_text(const string &blocks, uint64 n, uint64 d);
