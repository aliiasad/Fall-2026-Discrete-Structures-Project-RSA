#include "rsa.h"
uint64 mul_mod(uint64 a, uint64 b, uint64 m) {
    a %= m;
    b %= m;
    uint64 result = 0;
    while (b > 0) {
        if (b % 2 == 1) result = (result + a) % m;
        a = (a + a) % m;
        b = b / 2;
    }
    return result;
}
uint64 mod_exp(uint64 b, uint64 n, uint64 m) {
    uint64 x = 1 % m, power = b % m;
    while (n > 0) {
        if (n % 2 == 1) x = mul_mod(x, power, m);
        power = mul_mod(power, power, m);
        n = n / 2;
    }
    return x;
}
uint64 gcd(uint64 a, uint64 b) {
    while (b != 0) {
        uint64 r = a % b;
        a = b;
        b = r;
    }
    return a;
}
long long extended_gcd(long long a, long long b, long long &s, long long &t) {
    if (b == 0) {
        s = 1;
        t = 0;
        return a;
    }
    long long s1, t1;
    long long g = extended_gcd(b, a % b, s1, t1);
    s = t1;
    t = s1 - (a / b) * t1;
    return g;
}
uint64 mod_inverse(uint64 a, uint64 m) {
    long long s, t;
    long long g = extended_gcd(a, m, s, t);
    if (g != 1) throw invalid_argument("no inverse");
    long long r = s % (long long)m;
    if (r < 0) r += m;
    return r;
}
bool is_prime(uint64 n) {
    if (n < 2) return false;
    for (uint64 d = 2; d <= n / d; d++)
        if (n % d == 0) return false;
    return true;
}
void generate_keys(uint64 p, uint64 q, uint64 e, uint64 &n, uint64 &d) {
    if (!is_prime(p) || !is_prime(q)) throw invalid_argument("p and q must be prime");
    if (p == q) throw invalid_argument("p and q must be different");
    uint64 phi = (p - 1) * (q - 1);
    if (e <= 1 || e >= phi || gcd(e, phi) != 1) throw invalid_argument("bad e");
    n = p * q;
    d = mod_inverse(e, phi);
}
uint64 encrypt(uint64 M, uint64 n, uint64 e) {
    if (M >= n) throw invalid_argument("M must be less than n");
    return mod_exp(M, e, n);
}
uint64 decrypt(uint64 C, uint64 n, uint64 d) {
    if (C >= n) throw invalid_argument("C must be less than n");
    return mod_exp(C, d, n);
}
int block_size(uint64 n) {
    uint64 z = 25;
    if (z >= n) throw invalid_argument("n is too small");
    int k = 1;
    while (k < 9) {
        z = z * 100 + 25;
        if (z >= n) break;
        k++;
    }
    return k;
}
string encrypt_text(const string &text, uint64 n, uint64 e) {
    int k = block_size(n);
    string clean;
    for (char c : text) {
        if (c >= 'a' && c <= 'z') clean += c - 'a' + 'A';
        else if (c >= 'A' && c <= 'Z') clean += c;
    }
    while (clean.length() % k != 0) clean += 'X';
    string out;
    for (size_t i = 0; i < clean.length(); i += k) {
        uint64 M = 0;
        for (int j = 0; j < k; j++) M = M * 100 + (clean[i + j] - 'A');
        string C = to_string(encrypt(M, n, e));
        while (C.length() < to_string(n).length()) C = "0" + C;
        if (i > 0) out += " ";
        out += C;
    }
    return out;
}
string decrypt_text(const string &blocks, uint64 n, uint64 d) {
    int k = block_size(n);
    string out;
    uint64 num = 0;
    bool inNum = false;
    for (size_t i = 0; i <= blocks.length(); i++) {
        if (i < blocks.length() && blocks[i] != ' ') {
            num = num * 10 + (blocks[i] - '0');
            inNum = true;
        } else if (inNum) {
            uint64 M = decrypt(num, n, d);
            string group(k, 'A');
            for (int j = k - 1; j >= 0; j--) {
                if (M % 100 > 25) throw invalid_argument("wrong key");
                group[j] = 'A' + M % 100;
                M = M / 100;
            }
            out += group;
            num = 0;
            inNum = false;
        }
    }
    return out;
}
