#ifndef CRYPTO_H
#define CRYPTO_H

#include <iostream>
#include <openssl/rsa.h>
#include <openssl/sha.h>
#include <iomanip>
#include <secp256k1.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/bn.h>
#include <openssl/ecdsa.h>
#include <openssl/pem.h>

namespace crypto
{
    namespace rsa
    {
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wdeprecated-declarations" // xd

        inline RSA* generate_private_key() {
            RSA* private_key = RSA_new();
            BIGNUM* bne = BN_new();
            unsigned long e = RSA_F4;

            if (BN_set_word(bne, e) != 1 || RSA_generate_key_ex(private_key, 2048, bne, nullptr) != 1)
            {
                throw "Failed to generate private key";
            }

            BN_free(bne);
            return private_key;
        }

        inline RSA* generate_public_key(RSA* private_key) {
            RSA* public_key = RSAPublicKey_dup(private_key);

            if (public_key == nullptr)
            {
                throw "Failed to generate public key.";
            }

            return public_key;
        }

        #pragma clang diagnostic pop
    };

    namespace sha
    {
        inline std::string sha256(std::string combin_data)
        {
            EVP_MD_CTX *mdctx;
            const EVP_MD *md;
            uint8_t hash[SHA256_DIGEST_LENGTH];

            md = EVP_sha256();
            mdctx = EVP_MD_CTX_new();
            EVP_DigestInit_ex(mdctx, md, nullptr);
            EVP_DigestUpdate(mdctx, combin_data.c_str(), combin_data.length());
            EVP_DigestFinal_ex(mdctx, hash, nullptr);
            EVP_MD_CTX_free(mdctx);

            std::stringstream ss;
            for(size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i)
            {
                ss << std::hex << std::setw(2) << std::setfill('0') << (size_t)hash[i];
            }
            return ss.str();
        }

        inline std::string sha384(std::string combin_data)
        {
            EVP_MD_CTX *mdctx;
            const EVP_MD *md;
            uint8_t hash[SHA384_DIGEST_LENGTH];

            md = EVP_sha384();
            mdctx = EVP_MD_CTX_new();
            EVP_DigestInit_ex(mdctx, md, nullptr);
            EVP_DigestUpdate(mdctx, combin_data.c_str(), combin_data.length());
            EVP_DigestFinal_ex(mdctx, hash, nullptr);
            EVP_MD_CTX_free(mdctx);

            std::stringstream ss;
            for(size_t i = 0; i < SHA384_DIGEST_LENGTH; ++i)
            {
                ss << std::hex << std::setw(2) << std::setfill('0') << (size_t)hash[i];
            }
            return ss.str();
        }

        inline std::string sha512(std::string combin_data)
        {
            EVP_MD_CTX *mdctx;
            const EVP_MD *md;
            uint8_t hash[SHA512_DIGEST_LENGTH];

            md = EVP_sha512();
            mdctx = EVP_MD_CTX_new();
            EVP_DigestInit_ex(mdctx, md, nullptr);
            EVP_DigestUpdate(mdctx, combin_data.c_str(), combin_data.length());
            EVP_DigestFinal_ex(mdctx, hash, nullptr);
            EVP_MD_CTX_free(mdctx);

            std::stringstream ss;
            for(size_t i = 0; i < SHA512_DIGEST_LENGTH; ++i)
            {
                ss << std::hex << std::setw(2) << std::setfill('0') << (size_t)hash[i];
            }

            return ss.str();
        }
    };
};

#endif
