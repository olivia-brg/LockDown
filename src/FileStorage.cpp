#include <fstream>
#include <cryptopp/hex.h>
#include <cryptopp/base64.h>
#include "LockDown/FileStorage.h"
#include "LockDown/CryptoAES.h"

using namespace CryptoAES;

void FileStorage::saveFile(const vector<LogEntry>& entries, const string& key, const string& path)
{
    ofstream file(path.c_str(), ios::binary);

    for (const auto& entry : entries) {
        string line = entry.serialize();
        string encrypted = encryptAES(line, key);
        string base64;
        CryptoPP::StringSource ss(encrypted, true,
            new CryptoPP::Base64Encoder(new CryptoPP::StringSink(base64), false) // false = pas de line breaks
        );
        file << base64 << "\n";
    }

    file.close();
}

vector<LogEntry> FileStorage::loadFile(const string& key, const string& path)
{
    ifstream file(path.c_str(), ios::binary);
    vector<LogEntry> results;
    string base64Line;

    while (getline(file, base64Line)) {
        if (base64Line.empty()) continue;

        try {
            string encrypted;
            CryptoPP::StringSource ss(base64Line, true,
                new CryptoPP::Base64Decoder(new CryptoPP::StringSink(encrypted))
            );

            string decrypted = decryptAES(encrypted, key);
            LogEntry entry = LogEntry::deserialize(decrypted);
            results.push_back(entry);
        }
        catch (const CryptoPP::Exception& e) {
            cerr << "Erreur de déchiffrement : " << e.what() << "\n";
            // Possibilité de continuer ou de stopper ici
        }
    }

    file.close();
    return results;
}
