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

inline std::pair<std::vector<uint8_t>, std::vector<uint8_t>> generate_key_pair() {
    std::pair<std::vector<uint8_t>, std::vector<uint8_t>> key_pair;

    EC_KEY *ec_key = EC_KEY_new_by_curve_name(NID_secp256k1);

    if (EC_KEY_generate_key(ec_key) == 1) {
        const BIGNUM *private_key_bn = EC_KEY_get0_private_key(ec_key);

        const EC_POINT *public_key_point = EC_KEY_get0_public_key(ec_key);

        key_pair.first.resize(BN_num_bytes(private_key_bn));
        BN_bn2bin(private_key_bn, key_pair.first.data());

        EC_GROUP *group = EC_GROUP_new_by_curve_name(NID_secp256k1);
        size_t len = EC_POINT_point2oct(group, public_key_point, POINT_CONVERSION_UNCOMPRESSED, nullptr, 0, nullptr);
        key_pair.second.resize(len);
        EC_POINT_point2oct(group, public_key_point, POINT_CONVERSION_UNCOMPRESSED, key_pair.second.data(), len, nullptr);

        EC_GROUP_free(group);
    } else {
        std::cerr << "Error generating key pair." << std::endl;
    }

    EC_KEY_free(ec_key);

    return key_pair;
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
