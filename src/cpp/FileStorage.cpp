#include "../headers/FileStorage.h"
#include "../headers/CryptoAES.h"
#include "../MY_GLOBALS_H.h"

#include <fstream>
#include <cryptopp/hex.h>
#include <cryptopp/base64.h>
#include <filesystem>

using namespace CryptoAES;

bool FileStorage::saveFile(const vector<LogEntry>& entries, const UserAccount& user)
{
	struct stat info;

	if (!filesystem::is_directory(FOLDER_PATH))
		filesystem::create_directories(FOLDER_PATH);

	string vaultPath = FOLDER_PATH + "/vault_" + user.getUsername() + ".dat";


	ofstream file(vaultPath.c_str(), ios::binary);
	if (!file) {
		cerr << "saveFile : Erreur d'ouverture du fichier pour l'écriture : " << vaultPath << endl;
		return false;
	}

    for (const auto& entry : entries) {
        string line = entry.serialize();
        string encrypted = encryptAES(line, user.getPassword());
        string base64;
        CryptoPP::StringSource ss(encrypted, true,
            new CryptoPP::Base64Encoder(new CryptoPP::StringSink(base64), false) // false = pas de line breaks
        );
        file << base64 << "\n";
    }

    file.close();
	return true;
}

vector<LogEntry> FileStorage::loadFile(const UserAccount& user)
{
	string vaultPath = FOLDER_PATH + "/vault_" + user.getUsername() + ".dat";

    ifstream file(vaultPath.c_str(), ios::binary);
	if (!file) {
		cerr << "loadFile : Erreur d'ouverture du fichier pour la lecture : " << vaultPath << endl;
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

            string decrypted = decryptAES(encrypted, user.getPassword());
            LogEntry entry = LogEntry::deserialize(decrypted);
            results.push_back(entry);
        }
        catch (const CryptoPP::Exception& e) {
            cerr << "Erreur de dechiffrement : " << e.what() << "\n";
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
	string line = user.getUsername() + ":" + user.getPassword() + "\n";
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

		UserAccount user(line.substr(0, pos), line.substr(pos + 1));
		users.push_back(user);
	}
	file.close();
	return users;
}