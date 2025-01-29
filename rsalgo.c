#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a % b);
}

int computeD(int e, int phi) {
    int d = 0, x1 = 0, x2 = 1, y1 = 1, tempPhi = phi;

    while (e > 0) {
        int q = tempPhi / e;
        int r = tempPhi - q * e;
        tempPhi = e;
        e = r;

        int x = x2 - q * x1;
        x2 = x1;
        x1 = x;

        int y = d - q * y1;
        d = y1;
        y1 = y;
    }

    if (tempPhi == 1) {
        return (d + phi) % phi; // Ensure d is positive
    }
    fprintf(stderr, "No valid private exponent found.\n");
    exit(EXIT_FAILURE);
}

long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    int p, q;
    printf("Enter first prime number (p): ");
    scanf("%d", &p);

    printf("Enter second prime number (q): ");
    scanf("%d", &q);

    // Step 2: Compute n and φ(n)
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    printf("The value of φ(n) = %d\n", phi);

    // Step 3: Input public exponent 'e'
    int e;
    while (1) {
        printf("Enter the public exponent (e): ");
        scanf("%d", &e);
        if (gcd(e, phi) == 1) {
            break; // Valid e
        } else {
            printf("Invalid e! It must be coprime with %d\n", phi);
        }
    }
    printf("The public exponent (e) = %d\n", e);

    // Step 4: Compute private exponent 'd'
    int d = computeD(e, phi);
    printf("The private exponent (d) = %d\n", d);

    // Print the public and private keys
    printf("Public Key: (%d, %d)\n", e, n);
    printf("Private Key: (%d, %d)\n", d, n);

    // Step 5: Encrypt & decrypt a number
    int num;
    printf("Enter a number to encrypt: ");
    scanf("%d", &num);
    long long encryptedNum = modPow(num, e, n);
    printf("Encrypted number: %lld\n", encryptedNum);

    int decryptedNum = modPow(encryptedNum, d, n);
    printf("Decrypted number: %d\n", decryptedNum);

    return 0;
}

