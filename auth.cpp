#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;

static string hashPassword(const string &pwd)
{
    unsigned long hash = 5381;
    for (char c : pwd)
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);

    ostringstream oss;
    oss << hex << setw(16) << setfill('0') << hash;
    return oss.str();
}

class USER
{
private:
    string username;
    string hashedPassword;
    string role;
    bool active;

public:
    USER() : username(""), hashedPassword(""), role("User"), active(true) {}

    USER(const string &u, const string &rawPassword, const string &r)
        : username(u), hashedPassword(hashPassword(rawPassword)),
          role(r), active(true) {}

    USER(const string &u, const string &hashed, const string &r, bool a, bool)
        : username(u), hashedPassword(hashed), role(r), active(a) {}

    USER(const USER &other)
        : username(other.username), hashedPassword(other.hashedPassword),
          role(other.role), active(other.active) {}

    string getUsername() const { return username; }
    string getRole() const { return role; }
    string getHashedPassword() const { return hashedPassword; }
    bool isActive() const { return active; }

    bool login(const string &u, const string &rawPwd) const
    {
        return active && username == u && hashedPassword == hashPassword(rawPwd);
    }

    void changePassword(const string &newRawPwd)
    {
        hashedPassword = hashPassword(newRawPwd);
    }

    void deactivate() { active = false; }

    void displayInfo() const
    {
        cout << "  Username : " << username << "\n"
             << "  Role     : " << role << "\n"
             << "  Status   : " << (active ? "Active" : "Inactive") << "\n";
    }

    string serialize() const
    {
        return username + "|" + hashedPassword + "|" + role + "|" + (active ? "1" : "0");
    }

    static USER deserialize(const string &line)
    {
        istringstream ss(line);
        string u, h, r, a;
        getline(ss, u, '|');
        getline(ss, h, '|');
        getline(ss, r, '|');
        getline(ss, a, '|');
        return USER(u, h, r, a == "1", true);
    }

    ~USER() {}
};

class AuthSystem
{
private:
    static const string DATA_FILE;
    vector<USER> users;
    int loggedInIndex;

    void loadFromFile()
    {
        users.clear();
        ifstream fin(DATA_FILE);
        if (!fin.is_open())
            return;
        string line;
        while (getline(fin, line))
        {
            if (!line.empty())
                users.push_back(USER::deserialize(line));
        }
    }

    void saveToFile() const
    {
        ofstream fout(DATA_FILE);
        if (!fout.is_open())
        {
            cerr << "  [ERROR] Cannot write to " << DATA_FILE << "\n";
            return;
        }
        for (const auto &u : users)
            fout << u.serialize() << "\n";
    }

    bool usernameExists(const string &name) const
    {
        for (const auto &u : users)
            if (u.getUsername() == name)
                return true;
        return false;
    }

    int findIndex(const string &name) const
    {
        for (int i = 0; i < (int)users.size(); i++)
            if (users[i].getUsername() == name)
                return i;
        return -1;
    }

    string currentUsername() const
    {
        return (loggedInIndex >= 0) ? users[loggedInIndex].getUsername() : "";
    }

    string currentRole() const
    {
        return (loggedInIndex >= 0) ? users[loggedInIndex].getRole() : "";
    }

    static string getHiddenInput(const string &prompt)
    {

        cout << prompt;
        string input;
        getline(cin, input);
        return input;
    }

public:
    AuthSystem() : loggedInIndex(-1)
    {
        loadFromFile();

        if (users.empty())
        {
            users.push_back(USER("admin", "Admin@123", "Admin"));
            saveToFile();
            cout << "  [INFO] No users found. Default admin created.\n"
                 << "         Username: admin  |  Password: Admin@123\n\n";
        }
    }

    void registerUser()
    {
        cout << "\n┌-----------------------------┐\n"
             << "│        CREATE ACCOUNT       │\n"
             << "└-----------------------------┘\n";

        string uname, pwd, pwd2, role;

        cout << "  Username : ";
        getline(cin, uname);

        if (uname.empty())
        {
            cout << "  [!] Username cannot be empty.\n";
            return;
        }
        if (usernameExists(uname))
        {
            cout << "  [!] Username already taken.\n";
            return;
        }

        pwd = getHiddenInput("  Password : ");
        pwd2 = getHiddenInput("  Confirm  : ");

        if (pwd.length() < 6)
        {
            cout << "  [!] Password must be at least 6 characters.\n";
            return;
        }
        if (pwd != pwd2)
        {
            cout << "  [!] Passwords do not match.\n";
            return;
        }

        if (loggedInIndex >= 0 && currentRole() == "Admin")
        {
            cout << "  Role (Admin/User) [User]: ";
            getline(cin, role);
            if (role != "Admin" && role != "User")
                role = "User";
        }
        else
        {
            role = "User";
        }

        users.push_back(USER(uname, pwd, role));
        saveToFile();
        cout << "  [✓] Account '" << uname << "' registered as " << role << ".\n";
    }

    bool loginUser()
    {
        if (loggedInIndex >= 0)
        {
            cout << "  [!] Already logged in as '" << currentUsername() << "'.\n";
            return false;
        }

        cout << "\n┌-----------------------------┐\n"
             << "│            LOGIN            │\n"
             << "└-----------------------------┘\n";

        string uname = "", pwd = "";
        cout << "  Username : ";
        getline(cin, uname);
        pwd = getHiddenInput("  Password : ");

        for (int i = 0; i < (int)users.size(); i++)
        {
            if (users[i].login(uname, pwd))
            {
                loggedInIndex = i;
                cout << "  [✓] Welcome, " << uname << "! Role: " << users[i].getRole() << "\n";
                return true;
            }
        }
        cout << "  [✗] Invalid credentials or account inactive.\n";
        return false;
    }

    void logoutUser()
    {
        if (loggedInIndex < 0)
        {
            cout << "  [!] No active session.\n";
            return;
        }
        cout << "  [✓] Goodbye, " << currentUsername() << ".\n";
        loggedInIndex = -1;
    }

    void changePassword()
    {
        if (loggedInIndex < 0)
        {
            cout << "  [!] You must be logged in.\n";
            return;
        }

        cout << "\n┌-----------------------------┐\n"
             << "│       CHANGE PASSWORD       │\n"
             << "└-----------------------------┘\n";

        string old = getHiddenInput("  Current Password : ");
        if (!users[loggedInIndex].login(currentUsername(), old))
        {
            cout << "  [✗] Incorrect current password.\n";
            return;
        }

        string n1 = getHiddenInput("  New Password     : ");
        string n2 = getHiddenInput("  Confirm New      : ");

        if (n1.length() < 6)
        {
            cout << "  [!] Password must be at least 6 characters.\n";
            return;
        }
        if (n1 != n2)
        {
            cout << "  [!] Passwords do not match.\n";
            return;
        }

        users[loggedInIndex].changePassword(n1);
        saveToFile();
        cout << "  [✓] Password updated successfully.\n";
    }

    void showProfile() const
    {
        if (loggedInIndex < 0)
        {
            cout << "  [!] You must be logged in.\n";
            return;
        }
        cout << "\n-- My Profile ------------------\n";
        users[loggedInIndex].displayInfo();
    }

    void listUsers() const
    {
        if (currentRole() != "Admin")
        {
            cout << "  [✗] Access denied. Admins only.\n";
            return;
        }
        cout << "\n-- All Users -------------------\n";
        for (const auto &u : users)
        {
            cout << "  ┌--------------------------\n";
            u.displayInfo();
        }
        cout << "  └--------------------------\n";
    }

    void deleteUser()
    {
        if (currentRole() != "Admin")
        {
            cout << "  [✗] Access denied. Admins only.\n";
            return;
        }

        cout << "\n┌-----------------------------┐\n"
             << "│         DELETE USER         │\n"
             << "└-----------------------------┘\n";

        cout << "  Username to delete: ";
        string name;
        getline(cin, name);

        if (name == currentUsername())
        {
            cout << "  [!] Cannot delete yourself.\n";
            return;
        }

        int idx = findIndex(name);
        if (idx == -1)
        {
            cout << "  [!] User not found.\n";
            return;
        }

        users[idx].deactivate();
        saveToFile();
        cout << "  [✓] User '" << name << "' deactivated.\n";
    }

    void run()
    {
        while (true)
        {
            cout << "\n╔=================================╗\n"
                 << "║       AUTHENTICATION SYSTEM     ║\n"
                 << "╚=================================╝\n";

            if (loggedInIndex < 0)
            {
                cout << "  [1] Login\n"
                     << "  [2] Register\n"
                     << "  [0] Exit\n";
            }
            else
            {
                cout << "  Logged in as: " << currentUsername()
                     << " (" << currentRole() << ")\n\n"
                     << "  [1] My Profile\n"
                     << "  [2] Change Password\n"
                     << "  [3] Logout\n";
                if (currentRole() == "Admin")
                {
                    cout << "  [4] List All Users  (Admin)\n"
                         << "  [5] Delete User     (Admin)\n"
                         << "  [6] Register New User\n";
                }
                cout << "  [0] Exit\n";
            }

            cout << "\n  > ";
            string choice;
            getline(cin, choice);

            if (loggedInIndex < 0)
            {
                if (choice == "1")
                    loginUser();
                else if (choice == "2")
                    registerUser();
                else if (choice == "0")
                {
                    cout << "  Bye!\n";
                    break;
                }
                else
                    cout << "  [!] Invalid option.\n";
            }
            else
            {
                if (choice == "1")
                    showProfile();
                else if (choice == "2")
                    changePassword();
                else if (choice == "3")
                    logoutUser();
                else if (choice == "4")
                    listUsers();
                else if (choice == "5")
                    deleteUser();
                else if (choice == "6")
                    registerUser();
                else if (choice == "0")
                {
                    logoutUser();
                    cout << "  Bye!\n";
                    break;
                }
                else
                    cout << "  [!] Invalid option.\n";
            }
        }
    }
};

const string AuthSystem::DATA_FILE = "users.file";

int main()
{
    AuthSystem app;
    app.run();
    return 0;
}