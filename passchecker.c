#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple custom hashing function
unsigned long simpleHash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }

    return hash;
}

// Function to read the stored hash from a file
unsigned long getStoredPasswordHash() {
    FILE *file = fopen("password_hash.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open password hash file.\n");
        exit(1);
    }

    unsigned long storedHash;
    fscanf(file, "%lu", &storedHash);
    fclose(file);

    return storedHash;
}

int main() {
    char password[256];
    unsigned long hash;
    unsigned long storedHash;

    // Read the stored hashed password
    storedHash = getStoredPasswordHash();

    printf("Enter your password: ");
    scanf("%255s", password);

    // Hash the entered password
    hash = simpleHash(password);

    // Compare the hashed password with the stored hash
    if (hash == storedHash) {
        printf("Access Granted!\n");
    } else {
        printf("Access Denied!\n");
    }

    return 0;
}
