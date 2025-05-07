#include "LockDown/CryptoAES.h"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>

using namespace CryptoPP;

string CryptoAES::encryptAES(const string& plaintext, const string& key) {
    string ciphered;
    CryptoPP::byte iv[AES::BLOCKSIZE] = { 0 };

    CBC_Mode<AES>::Encryption enc;
    enc.SetKeyWithIV((const CryptoPP::byte*)key.data(), key.size(), iv);

    StringSource(plaintext, true,
        new StreamTransformationFilter(enc,
            new StringSink(ciphered)
        )
    );
    return ciphered;
}

string CryptoAES::decryptAES(const string& ciphertext, const string& key) {
    string plaintext;
    CryptoPP::byte iv[AES::BLOCKSIZE] = { 0 };

    CBC_Mode<AES>::Decryption dec;
    dec.SetKeyWithIV((const CryptoPP::byte*)key.data(), key.size(), iv);

    StringSource(ciphertext, true,
        new StreamTransformationFilter(dec,
            new StringSink(plaintext)
        )
    );
    return plaintext;
}