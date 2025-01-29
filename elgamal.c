//elgamal in c
#include <stdio.h>
#include <math.h>


long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {  // If exp is odd
            result = (result * base) % mod;
        }
        exp = exp >> 1;  // Divide exp by 2
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    long long p;  
    long long e1, e2, r, d;  
    long long m;  
    long long c1, c2, decrypted_message;

    // Input values
    printf("\nEnter a prime number (p): ");
    scanf("%lld", &p);

    printf("Enter e1 (primitive root modulo p): ");
    scanf("%lld", &e1);

    printf("Enter d (private key): ");
    scanf("%lld", &d);
    e2 = mod_exp(e1, d, p);

    printf("Value of e2 (public key e2 = e1^d mod p): %lld\n",e2);

    printf("Enter r (random number): ");
    scanf("%lld", &r);

    printf("\nEnter the message to encrypt (m): ");
    scanf("%lld", &m);

    // Encryption
    c1 = mod_exp(e1, r, p);              
    c2 = (mod_exp(e2, r, p) * m) % p;    

    printf("\nEncrypted values:\n");
    printf("c1 = %lld\n", c1);
    printf("c2 = %lld\n", c2);

    // Decryption
    long long temp = mod_exp(c1, d, p);          
    long long temp_inverse = mod_exp(temp, p - 2, p);  
    decrypted_message = (c2 * temp_inverse) % p; 

    printf("\nDecrypted message: %lld\n\n", decrypted_message);

    return 0;
}