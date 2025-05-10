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
    std::cout << "Mot de passe ma�tre : ";
    std::getline(std::cin, user.password);

    bool authenticated = auth.authenticate(user);

    if (!authenticated) {
        std::cout << "Utilisateur inconnu. Cr�er un nouveau compte ? (y/n) : ";
        std::string choix;
        std::getline(std::cin, choix);

        if (choix == "y" || choix == "Y") {
            if (!auth.registerUser(user)) {
                std::cerr << "Erreur : utilisateur d�j� existant." << std::endl;
                return 1;
            }
            std::cout << "Compte cr�� avec succ�s.\n";
        }
        else {
            std::cout << "Acc�s refus�.\n";
            return 1;
        }
    }
    else {
        std::cout << "Authentification r�ussie.\n";
    }

    // Fichier de l'utilisateur : vault_username.dat
    std::string vaultPath = "vaults/vault_" + user.username + ".dat";
	string key = CryptoAES::hashPassword(user.password);
    Controller controller(key, vaultPath);

    return 0;
}