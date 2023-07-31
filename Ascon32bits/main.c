//
// Created by albertojor on 30/07/23.
//
#include <stdio.h>

unsigned long long rightRotate64(unsigned long long num, int rotationAmount) {
    rotationAmount = rotationAmount % 64; // Ensure rotationAmount is in the range [0, 63]

    // Perform the right rotation using bitwise operations
    return (num >> rotationAmount) | (num << (64 - rotationAmount));
}


typedef struct {
    unsigned int high;
    unsigned int low;
} Uint64Parts;

Uint64Parts rightRotate64Emulated(unsigned int highPart, unsigned int lowPart, int rotationAmount) {

 rotationAmount = rotationAmount % 64; // Ensure rotationAmount is in the range [0, 63]


     if (rotationAmount == 0) {
        // No rotation needed, return the original value
        Uint64Parts result = { highPart, lowPart };
        return result;
    } else {
        // Perform the right rotation using bitwise operations
        unsigned int combinedValueHigh = (highPart >> (rotationAmount % 32)) | (lowPart << (32 - (rotationAmount % 32)));
        unsigned int combinedValueLow = (lowPart >> (rotationAmount % 32)) | (highPart << (32 - (rotationAmount % 32)));

        // For rotationAmount >= 32, swap the high and low parts
        if (rotationAmount >= 32) {
            unsigned int temp = combinedValueHigh;
            combinedValueHigh = combinedValueLow;
            combinedValueLow = temp;
        }

        Uint64Parts result = { combinedValueHigh, combinedValueLow };
        return result;
    }

}
void ROR32(unsigned int highPart, unsigned int lowPart, int rotationAmount) {

 rotationAmount = rotationAmount % 64; // Ensure rotationAmount is in the range [0, 63]


     if (rotationAmount == 0) {
        // No rotation needed, return the original value
        Uint64Parts result = { highPart, lowPart };
        return result;
    } else {
        // Perform the right rotation using bitwise operations
        unsigned int combinedValueHigh = (highPart >> (rotationAmount % 32)) | (lowPart << (32 - (rotationAmount % 32)));
        unsigned int combinedValueLow = (lowPart >> (rotationAmount % 32)) | (highPart << (32 - (rotationAmount % 32)));

        // For rotationAmount >= 32, swap the high and low parts
        if (rotationAmount >= 32) {
            unsigned int temp = combinedValueHigh;
            combinedValueHigh = combinedValueLow;
            combinedValueLow = temp;
        }

        Uint64Parts result = { combinedValueHigh, combinedValueLow };
        return result;
    }

}

unsigned  long long int concat(unsigned int high, unsigned int low){
    unsigned long long int highL = high;
    unsigned long long int lowL  = low;
    unsigned long long int Res = highL << 32 | lowL;
    return  Res;
}

int main() {
    unsigned int highPart = 0x0A089F12; // Example high part (32 bits)
    unsigned int lowPart = 0x307eF08a;  // Example low part (32 bits)
    int rotationAmount = 14; // Number of positions to rotate right

    Uint64Parts result = rightRotate64Emulated(highPart, lowPart, rotationAmount);
    unsigned long long int result2 = rightRotate64(concat(highPart, lowPart), rotationAmount);
    printf("Original number: 0x%08X%08X\n", highPart, lowPart);
    printf("Right rotated by %d positions: 0x%08X%08X  0x%016llX\n", rotationAmount, result.high, result.low, result2);

    return 0;
}
