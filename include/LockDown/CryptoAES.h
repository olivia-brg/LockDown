#pragma once
#include <string>

using namespace std;

namespace CryptoAES {
    string encryptAES(const string& texte, const string& cle);
    string decipherAES(const string& chiffre, const string& cle);
}
