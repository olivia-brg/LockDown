#include "LockDown/PasswordEntry.h"
#include "LockDown/CryptoAES.h"
#include "LockDown/FileStorage.h"
#include <iostream>

int main()
{
    // Clé de chiffrement simple (à remplacer plus tard par mot de passe maître)
    string key = "motDePasseMaitre";

    // Fichier de sauvegarde
    string path = "vault.dat";

    // Création d'une liste d'entrées
    PasswordEntry site1("site.com", "user1", "mdp123");
    PasswordEntry site2("gmail.com", "moi@gmail.com", "secret");
    PasswordEntry site3("github.com", "devuser", "gitpass");

    // Sauvegarde dans un fichier
	vector<PasswordEntry> entries = { site1, site2, site3 };
	FileStorage::saveFile(entries, key, path);
    cout << "Mots de passe enregistres dans '" << path << "' (chiffres)." << endl;

    // Chargement depuis le fichier
    vector<PasswordEntry> charge = FileStorage::loadFile(key, path);

    cout << "\nContenu du fichier (dechiffre) :\n";
    for (const auto& e : charge) {
        cout << e << endl;
    }

    return 0;
}