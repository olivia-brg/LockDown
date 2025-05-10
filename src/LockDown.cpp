#include <LockDown/Controller.h>
#include <iostream>
#include <LockDown/MasterAuth.h>
#include <LockDown/CryptoAES.h>

int main()
{
    const std::string userDb = "users.dat";

    MasterAuth auth(userDb);


    UserAccount user;
    std::cout << "Nom d'utilisateur : ";
    std::getline(std::cin, user.username);
    std::cout << "Mot de passe maître : ";
    std::getline(std::cin, user.password);

    bool authenticated = auth.authenticate(user);

    if (!authenticated) {
        std::cout << "Utilisateur inconnu. Créer un nouveau compte ? (y/n) : ";
        std::string choix;
        std::getline(std::cin, choix);

        if (choix == "y" || choix == "Y") {
            if (!auth.registerUser(user)) {
                std::cerr << "Erreur : utilisateur déjà existant." << std::endl;
                return 1;
            }
            std::cout << "Compte créé avec succès.\n";
        }
        else {
            std::cout << "Accès refusé.\n";
            return 1;
        }
    }
    else {
        std::cout << "Authentification réussie.\n";
    }

    // Fichier de l'utilisateur : vault_username.dat
    std::string vaultPath = "vaults/vault_" + user.username + ".dat";
	string key = CryptoAES::hashPassword(user.password);
    Controller controller(key, vaultPath);

    return 0;
}