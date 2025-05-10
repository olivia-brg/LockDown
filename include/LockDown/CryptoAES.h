#pragma once
#include <string>

using namespace std;

namespace CryptoAES {
    string encryptAES(const string& plaintext, const string& key);
    string decryptAES(const string& ciphertext, const string& key);
	string hashPassword(const string& password);
}
