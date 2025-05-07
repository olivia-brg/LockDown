#include "LockDown/PasswordEntry.h"
#include "LockDown/CryptoAES.h"
#include "LockDown/FileStorage.h"
#include <iostream>

int main()
{
    // Clé de chiffrement simple (à remplacer plus tard par mot de passe maître)
    string cle = "motDePasseMaitre";

    // Fichier de sauvegarde
    string chemin = "vault.dat";

    // Création d'une liste d'entrées
    vector<PasswordEntry> liste;
    liste.emplace_back("site.com", "user1", "mdp123");
    liste.emplace_back("gmail.com", "moi@gmail.com", "secret");
    liste.emplace_back("github.com", "devuser", "gitpass");

    // Sauvegarde dans un fichier
    FileStorage::saveFile(liste, cle, chemin);
    cout << "Mots de passe enregistres dans '" << chemin << "' (chiffres)." << endl;

    // Chargement depuis le fichier
    auto charge = FileStorage::loadFile(cle, chemin);

    cout << "\nContenu du fichier (dechiffre) :\n";
    for (const auto& e : charge) {
        cout << e << endl;
    }

    return 0;
}