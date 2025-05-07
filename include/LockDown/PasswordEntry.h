#pragma once

#include <string>
#include <vector>

using namespace std;

class PasswordEntry {
    public:
        PasswordEntry(string site, string username, string password);

        const string getSite() const;
        const string getUsername() const;
        const string getPassword() const;

        void setPassword(const string& newPassword);

        string serialize() const;
        static PasswordEntry deserialize(const string& ligne);

    private:
        string m_site;
        string m_username;
        string m_password;

        friend ostream& operator<<(ostream& flux, PasswordEntry const& passwordEntry);
};

