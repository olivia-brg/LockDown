#include "LockDown/CryptoAES.h"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>

using namespace CryptoPP;

string CryptoAES::encryptAES(const string& texte, const string& cle) {
    string chiffre;
    CryptoPP::byte iv[AES::BLOCKSIZE] = { 0 };

    CBC_Mode<AES>::Encryption enc;
    enc.SetKeyWithIV((const CryptoPP::byte*)cle.data(), cle.size(), iv);

    StringSource(texte, true,
        new StreamTransformationFilter(enc,
            new StringSink(chiffre)
        )
    );
    return chiffre;
}

string CryptoAES::decipherAES(const string& chiffre, const string& cle) {
    string clair;  
    CryptoPP::byte iv[AES::BLOCKSIZE] = { 0 };

    CBC_Mode<AES>::Decryption dec;
    dec.SetKeyWithIV((const CryptoPP::byte*)cle.data(), cle.size(), iv);

    StringSource(chiffre, true,
        new StreamTransformationFilter(dec,
            new StringSink(clair)
        )
    );
    return clair;
}
