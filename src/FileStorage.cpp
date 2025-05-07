#include <fstream>

#include "LockDown/FileStorage.h"
#include "LockDown/CryptoAES.h"

using namespace CryptoAES;

void FileStorage::saveFile(const vector<PasswordEntry>& entries, const string& key, const string& path)
{
    ofstream file(path.c_str());
    for (const auto& entry : entries) {
        string line = entry.serialize();
        string encryptedLine = encryptAES(line, key);
        file << encryptedLine << endl;
    }
    file.close();
}

vector<PasswordEntry> FileStorage::loadFile(const string& key, const string& path)
{
    ifstream file(path.c_str());
    vector<PasswordEntry> results;
    string line;
    while (getline(file, line)) {
        string decipheredLine = decipherAES(line, key);
        results.push_back(PasswordEntry::deserialize(decipheredLine));
    }
    file.close();
    return results;
}