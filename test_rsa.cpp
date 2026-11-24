#include "rsa.h"
int main()
{
   if (!(mul_mod(7, 8, 5) == 1))
   {
       cout << "FAILED test 1" << endl;
       return 1;
   }
   if (!(mul_mod(0, 99, 7) == 0))
   {
       cout << "FAILED test 2" << endl;
       return 1;
   }
   if (!(mul_mod(123456789012ULL, 987654321098ULL, 1000036000099ULL) == 813538246183ULL))
   {
       cout << "FAILED test 3" << endl;
       return 1;
   }
   if (!(mod_exp(3, 644, 645) == 36))
   {
       cout << "FAILED test 4" << endl;
       return 1;
   }
   if (!(mod_exp(1819, 13, 2537) == 2081))
   {
       cout << "FAILED test 5" << endl;
       return 1;
   }
   if (!(mod_exp(5, 0, 7) == 1))
   {
       cout << "FAILED test 6" << endl;
       return 1;
   }
   if (!(mod_exp(2, 1000000000ULL, 1000000007ULL) == 140625001ULL))
   {
       cout << "FAILED test 7" << endl;
       return 1;
   }
   if (!(gcd(252, 198) == 18))
   {
       cout << "FAILED test 8" << endl;
       return 1;
   }
   if (!(gcd(13, 2436) == 1))
   {
       cout << "FAILED test 9" << endl;
       return 1;
   }
   if (!(gcd(17, 0) == 17))
   {
       cout << "FAILED test 10" << endl;
       return 1;
   }
   long long s, t;
   long long g = extended_gcd(252, 198, s, t);
   if (!(g == 18 && s == 4 && t == -5))
   {
       cout << "FAILED test 11" << endl;
       return 1;
   }
   g = extended_gcd(4620, 101, s, t);
   if (!(g == 1 && s == -35 && t == 1601))
   {
       cout << "FAILED test 12" << endl;
       return 1;
   }
   if (!(mod_inverse(3, 7) == 5))
   {
       cout << "FAILED test 13" << endl;
       return 1;
   }
   if (!(mod_inverse(101, 4620) == 1601))
   {
       cout << "FAILED test 14" << endl;
       return 1;
   }
   if (!(mod_inverse(13, 2436) == 937))
   {
       cout << "FAILED test 15" << endl;
       return 1;
   }
   bool threw = false;
   try
   {
       mod_inverse(2, 6);
   }
   catch (const invalid_argument &)
   {
       threw = true;
   }
   if (!(threw))
   {
       cout << "FAILED test 16" << endl;
       return 1;
   }
   if (!(is_prime(2) && is_prime(2539) && is_prime(1000003)))
   {
       cout << "FAILED test 17" << endl;
       return 1;
   }
   if (!(!is_prime(0) && !is_prime(1) && !is_prime(2537) && !is_prime(561)))
   {
       cout << "FAILED test 18" << endl;
       return 1;
   }
   uint64 n, d;
   generate_keys(43, 59, 13, n, d);
   if (!(n == 2537 && d == 937))
   {
       cout << "FAILED test 19" << endl;
       return 1;
   }
   threw = false;
   try
   {
       generate_keys(42, 59, 13, n, d);
   }
   catch (const invalid_argument &)
   {
       threw = true;
   }
   if (!(threw))
   {
       cout << "FAILED test 20" << endl;
       return 1;
   }
   threw = false;
   try
   {
       generate_keys(43, 43, 13, n, d);
   }
   catch (const invalid_argument &)
   {
       threw = true;
   }
   if (!(threw))
   {
       cout << "FAILED test 21" << endl;
       return 1;
   }
   threw = false;
   try
   {
       generate_keys(43, 59, 2, n, d);
   }
   catch (const invalid_argument &)
   {
       threw = true;
   }
   if (!(threw))
   {
       cout << "FAILED test 22" << endl;
       return 1;
   }
   if (!(encrypt(1819, 2537, 13) == 2081))
   {
       cout << "FAILED test 23" << endl;
       return 1;
   }
   if (!(encrypt(1415, 2537, 13) == 2182))
   {
       cout << "FAILED test 24" << endl;
       return 1;
   }
   if (!(decrypt(981, 2537, 937) == 704))
   {
       cout << "FAILED test 25" << endl;
       return 1;
   }
   if (!(decrypt(461, 2537, 937) == 1115))
   {
       cout << "FAILED test 26" << endl;
       return 1;
   }
   if (!(encrypt_text("STOP", 2537, 13) == "2081 2182"))
   {
       cout << "FAILED test 27" << endl;
       return 1;
   }
   if (!(encrypt_text("Stop!", 2537, 13) == "2081 2182"))
   {
       cout << "FAILED test 28" << endl;
       return 1;
   }
   if (!(encrypt_text("abc", 2537, 13) == "0001 0027"))
   {
       cout << "FAILED test 29" << endl;
       return 1;
   }
   if (!(decrypt_text("0981 0461", 2537, 937) == "HELP"))
   {
       cout << "FAILED test 30" << endl;
       return 1;
   }
   if (!(decrypt_text(encrypt_text("DISCRETE", 2537, 13), 2537, 937) == "DISCRETE"))
   {
       cout << "FAILED test 31" << endl;
       return 1;
   }
   cout << "All tests passed" << endl;
}
