#ifndef CRYPTO_H
#define CRYPTO_H

#include <iostream>
#include <openssl/rsa.h>
#include <openssl/sha.h>
#include <iomanip>
#include <vector>
#include <secp256k1.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/bn.h>
#include <openssl/ecdsa.h>
#include <openssl/pem.h>

inline std::string sha256(std::string combin_data)
{
    uint8_t hash[SHA256_DIGEST_LENGTH];

    SHA256_CTX context;
    SHA256_Init(&context);
    SHA256_Update(&context, combin_data.c_str(), combin_data.length());
    SHA256_Final(hash, &context);

    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}

inline std::string sha384(std::string combin_data)
{
    uint8_t hash[SHA384_DIGEST_LENGTH];
    
    SHA512_CTX context;
    SHA384_Init(&context);
    SHA384_Update(&context, combin_data.c_str(), combin_data.length());
    SHA384_Final(hash, &context);

    std::stringstream ss;
    for(int i = 0; i < SHA384_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}

inline std::string sha512(std::string combin_data)
{
    uint8_t hash[SHA512_DIGEST_LENGTH];

    SHA512_CTX context;
    SHA512_Init(&context);
    SHA512_Update(&context, combin_data.c_str(), combin_data.length());
    SHA512_Final(hash, &context);

    std::stringstream ss;
    for(int i = 0; i < SHA512_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    
    return ss.str();
}

inline RSA* generate_private_key() {
    RSA* private_key = RSA_new();
    BIGNUM* bne = BN_new();
    unsigned long e = RSA_F4;

    if (BN_set_word(bne, e) != 1 || RSA_generate_key_ex(private_key, 2048, bne, NULL) != 1) {
        std::cerr << "Erorr: failed to generate private key" << std::endl;
    }

    BN_free(bne);
    return private_key;
}

inline RSA* generate_public_key(RSA* private_key) {
    RSA* public_key = RSAPublicKey_dup(private_key);

    if (public_key == NULL) {
        std::cerr << "Error: failed to generate public key" << std::endl;
    }

    return public_key;
}

#endif
