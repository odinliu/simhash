/**
 * @author Liu Yiding(odinushuaia@gmail.com)
 */
#include "simhash.h"

ul_int sh_hash(const char *arKey, unsigned int nKeyLength)
{
    register ul_int hash = 5381;

    for(; nKeyLength >= 8; nKeyLength -= 8) {
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
    }
    switch(nKeyLength) {
        case 7: hash = ((hash << 5) + hash) + *arKey++;
        case 6: hash = ((hash << 5) + hash) + *arKey++;
        case 5: hash = ((hash << 5) + hash) + *arKey++;
        case 4: hash = ((hash << 5) + hash) + *arKey++;
        case 3: hash = ((hash << 5) + hash) + *arKey++;
        case 2: hash = ((hash << 5) + hash) + *arKey++;
        case 1: hash = ((hash << 5) + hash) + *arKey++;break;
        case 0: break;
    }

    return hash;
}

ul_int sh_simhash(const char *tokens[], unsigned int length)
{
    float hash_vector[SIMHASH_BIT];
    memset(hash_vector, 0, SIMHASH_BIT * sizeof(float));
    ul_int token_hash = 0;
    ul_int simhash = 0;
    int current_bit = 0;

    for(int i=0; i<length; i++) {
        token_hash = sh_hash(tokens[i], strlen(tokens[i]));
        for(int j=SIMHASH_BIT-1; j>=0; j--) {
            current_bit = token_hash & 0x1;
            if(current_bit == 1) {
                hash_vector[j] += 1;
            } else {
                hash_vector[j] -= 1;
            }
            token_hash = token_hash >> 1;
        }
    }

    for(int i=0; i<SIMHASH_BIT; i++) {
        if(hash_vector[i] > 0) {
            simhash = (simhash << 1) + 0x1;
        } else {
            simhash = simhash << 1;
        }
    }

    return simhash;
}
