#include "rsa.h"
int main() {
    uint64 p, q, e, n, d;
    while (true) {
        cout << "Enter p q e: ";
        if (!(cin >> p >> q >> e)) {
            // input ended, or something that is not a number was typed
            if (cin.eof()) {
                cout << endl << "No more input. Bye." << endl;
                return 1;
            }
            cin.clear();              // clear the error flag
            cin.ignore(1000, '\n');   // throw away the bad line
            cout << "Please enter three numbers." << endl;
            continue;                 // ask again
        }
        try {
            generate_keys(p, q, e, n, d);
            break;
        } catch (const invalid_argument &ex) {
            cout << ex.what() << endl;
        }
    }
    int k = block_size(n);
    cout << "Public key: n = " << n << ", e = " << e << endl;
    cout << "Private key: d = " << d << endl;
    cout << "Block size: " << k << " letters" << endl;
    cin.ignore(1000, '\n');           // skip the rest of the line with p q e
    cout << "Message: ";
    string msg;
    getline(cin, msg);
    string clean;
    for (char c : msg) {
        if (c >= 'a' && c <= 'z') clean += c - 'a' + 'A';
        else if (c >= 'A' && c <= 'Z') clean += c;
    }
    while (clean.length() % k != 0) clean += 'X';
    cout << "Cleaned: " << clean << endl;
    cout << "Plaintext blocks:";
    for (size_t i = 0; i < clean.length(); i += k) {
        uint64 M = 0;
        for (int j = 0; j < k; j++) M = M * 100 + (clean[i + j] - 'A');
        cout << " " << M;
    }
    cout << endl;
    string cipher = encrypt_text(msg, n, e);
    cout << "Ciphertext: " << cipher << endl;
    cout << "Decrypted: " << decrypt_text(cipher, n, d) << endl;
}
