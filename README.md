# RSA Project, Part B (Discrete Structures, Fall 2026)
 
Roll no: 25L-0519
 
## Files
 
| File | Contents |
|---|---|
| `rsa.h` | Declarations for B0 to B8 |
| `rsa.cpp` | Implementation of B0 to B8 |
| `test_rsa.cpp` | Runs every assert from the project statement (B9) |
| `demo.cpp` | Interactive demo (B9) |
| `break_key.cpp` | Breaks the toy key by trial division (B10) |
 
Only `+ - * / %` on integers are used. No `__int128`, `pow`, GMP, Boost or OpenSSL.
 
## Compile and run (C++17)
 
Tests:
 
    g++ -std=c++17 -O2 rsa.cpp test_rsa.cpp -o test_rsa
    ./test_rsa
 
Expected output: `All tests passed`
 
Demo:
 
    g++ -std=c++17 -O2 rsa.cpp demo.cpp -o demo
    ./demo
 
Break the toy key:
 
    g++ -std=c++17 -O2 rsa.cpp break_key.cpp -o break_key
    ./break_key
 
## Output of the demo (p = 43, q = 59, e = 13, message "Stop!")
 
    Enter p q e: 43 59 13
    Public key: n = 2537, e = 13
    Private key: d = 937
    Block size: 2 letters
    Message: Stop!
    Cleaned: STOP
    Plaintext blocks: 1819 1415
    Ciphertext: 2081 2182
    Decrypted: STOP
 
## Output of break_key (B10)
 
    p = 1000003
    q = 1000033
    Private key d = 983264276609
    Message: NUMBERTHEORYISFUNX
 
The message is **NUMBERTHEORYISFUN**. The final `X` is padding added so the length is a multiple of the block size k = 6.
 
The attack works only because n is small. Trial division needs about 10^6 steps here, but about 10^308 steps for a real 2048-bit key.
 
## Notes on the design
 
- `mul_mod` uses repeated doubling, so a product is never formed directly and cannot overflow (every modulus is below 2^63).
- `mod_inverse` casts to `long long` before `%`, so a negative `s` is reduced correctly (for a = 43, m = 600 the answer is 307, not 323).
- `is_prime` uses `d <= n / d` instead of `d * d <= n` to avoid overflow.
- `extended_gcd` does not use a `std::vector` of quotients, as the statement describes. Vectors have not been covered formally in our course, so I used recursion instead. Each recursive call does one forward division (`a / b`, `a % b`), and each call remembers its own quotient while it waits for the result of the next call. When the calls return, the back-substitution is done one step at a time: `s = t1` and `t = s1 - (a / b) * t1`. This is the same update `(x, y) -> (y, x - q*y)` as in the statement, so the results are identical (for example 18 = 4*252 - 5*198).
- `encrypt_text` does not use `isalpha` and `toupper`, as the statement suggests. These library functions have not been covered in our course, so I used plain character comparisons instead. A character is kept only if it is between `'a'` and `'z'` or between `'A'` and `'Z'`. A lower-case letter is converted to upper case with `c - 'a' + 'A'`. Every other character (spaces, digits, punctuation) is dropped. `demo.cpp` cleans the message in the same way.
- `decrypt_text` throws `std::invalid_argument` if a block number is not less than n, or if a two-digit letter code is above 25, which signals a wrong key.
## Sources
 
Rosen, Discrete Mathematics and Its Applications, sections 4.1 to 4.4 and 4.6, and the two lecture slides on number theory for RSA. No other sources.
 
