#include <fstream>
#include <cryptopp/hex.h>
#include <cryptopp/base64.h>
#include "LockDown/FileStorage.h"
#include "LockDown/CryptoAES.h"

using namespace CryptoAES;

bool FileStorage::saveFile(const vector<LogEntry>& entries, const string& key, const string& path)
{
    ofstream file(path.c_str(), ios::binary);
	if (!file) {
		cerr << "saveFile : Erreur d'ouverture du fichier pour l'écriture : " << path << endl;
		return false;
	}

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
	return true;
}

vector<LogEntry> FileStorage::loadFile(const string& key, const string& path)
{
    ifstream file(path.c_str(), ios::binary);
	if (!file) {
		cerr << "loadFile : Erreur d'ouverture du fichier pour la lecture : " << path << endl;
		return {};
	}

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

bool FileStorage::saveUser(const UserAccount& user, const string& path) {
	ofstream file(path.c_str(), ios::binary | ios::app);
	if (!file) {
		cerr << "saveUser : Erreur d'ouverture du fichier pour l'écriture : " << path << endl;
		return false;
	}
	string line = user.username + ":" + user.password + "\n";
	file.write(line.c_str(), line.size());
	file.close();
	return true;
}

vector<UserAccount> FileStorage::loadUsers(const string& path) {
	ifstream file(path.c_str(), ios::binary);
	if (!file) {
		cerr << "loadUser : Erreur d'ouverture du fichier pour la lecture : " << path << endl;
		return {};
	}

	vector<UserAccount> users;
	string line;

	while (getline(file, line)) {
		if (line.empty()) continue;

		size_t pos = line.find(':');
		if (pos == string::npos) continue;

		UserAccount user;
		user.username = line.substr(0, pos);
		user.password = line.substr(pos + 1);
		users.push_back(user);
	}
	file.close();
	return users;
}