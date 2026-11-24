#include "rsa.h"
int main() {
   uint64 n = 1000036000099ULL, e = 65537;
   string cipher = "0614157364221 0502078796304 0031583460315";
   uint64 p = 2;
   while (n % p != 0) p++;
   uint64 q = n / p;
   uint64 phi = (p - 1) * (q - 1);
   uint64 d = mod_inverse(e, phi);
   cout << "p = " << p << endl;
   cout << "q = " << q << endl;
   cout << "Private key d = " << d << endl;
   cout << "Message: " << decrypt_text(cipher, n, d) << endl;
}
