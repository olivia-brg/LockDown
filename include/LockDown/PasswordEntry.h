#pragma once

#include <string>
#include <vector>

using namespace std;

class PasswordEntry {
    public:
        PasswordEntry(const string& site, const string& username, const string& password);

        string getSite() const;
        string getUsername() const;
        string getPassword() const;

        void setPassword(const string& newPassword);

        string serialize() const;
        static PasswordEntry deserialize(const string& ligne);

    private:
        string m_site;
        string m_username;
        string m_password;

        friend ostream& operator<<(ostream& flux, PasswordEntry const& passwordEntry);
};

