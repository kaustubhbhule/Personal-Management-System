#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

class Main
{
public:
    void banner()
    {
        cout << "____________________________________________\n\n\tPERSONAL MANAGEMENT SYSTEM\n____________________________________________";
    }
};

class Authentication : public Main
{
public:
    string username;
    string password;
    string ausername;
    string apassword;
    string cpassword;
    int j = 0;
    int k = 0;
    int status = 0;
    int log = 0;
    char choice;

    int login()
    {
        system("clear");
        banner();
        cout << "\n\n\n\n  Login - " << endl;
        cout << endl;
        cout << "  Username: ";
        cin >> username;
        cout << "  Password: ";
        cin >> password;

        fstream acc;
        acc.open("log2.txt", ios::in);
        int count = 1;
        acc >> ausername;
        acc >> apassword;

        if (username == ausername && password == apassword)
        {
            set_status(1);
            main_();
            return true;
        }
        else
        {
            system("clear");
            cout << endl
                 << "   Incorrect username or password" << endl;
            cout << endl
                 << "   Press Enter to continue...";
            cin.get();
            cin.get();
            login();
        }
        return false;
    }

    int signup()
    {
        system("clear");
        banner();
        cout << "\n\n\n\n  Signup - " << endl;
        cout << endl;
        cout << "  Username: ";
        cin >> username;
        cout << "  Password: ";
        cin >> password;
        cout << "  Confirm Password: ";
        cin >> cpassword;
        if (password == cpassword)
        {
            fstream acc;
            acc.open("log2.txt", ios::out);
            acc << username << endl
                << password;
            acc.close();
            set_signup_status(1);
            system("clear");
            cout << endl
                 << "   Account created successfully" << endl;
            cout << endl
                 << "   Press Enter to continue...";
            cin.get();
            cin.get();
            login();
            return true;
        }
        else
        {
            system("clear");
            cout << endl
                 << "   Password not matched!" << endl;
            cout << endl
                 << "   Press Enter to continue...";
            cin.get();
            cin.get();
            signup();
        }
        return true;
    }

    void edit_profile()
    {
        system("clear");
        banner();
        cout << "\n\n\n\n  Edit Profile - " << endl;
        cout << endl;
        cout << "  New Username: ";
        cin >> username;
        cout << "  New Password: ";
        cin >> password;
        cout << "  Confirm Password: ";
        cin >> cpassword;
        if (password == cpassword)
        {
            ofstream acc1;
            acc1.open("log2.txt", ofstream::out | ofstream::trunc);
            acc1.close();
            fstream acc;
            acc.open("log2.txt", ios::app);
            acc << username << endl;
            acc << password;
            acc.close();
            system("clear");
            cout << endl
                 << "   Your profile upadted successfully" << endl;
            cout << endl
                 << "   Press Enter to continue...";
            cin.get();
            cin.get();
            main_();
        }
        else
        {
            system("clear");
            cout << endl
                 << "   Password not matched!" << endl;
            cout << endl
                 << "   Press Enter to continue...";
            cin.get();
            cin.get();
            edit_profile();
        }
    }

    void all_data()
    {
        system("clear");
        banner();
        int i = 0;
        int j = 1;
        string title[100], data[100];
        fstream fdata;
        fdata.open("data.txt", ios::in);
        while (!fdata.eof())
        {
            fdata >> title[i];
            i++;
            fdata >> data[j];
            j++;
        }

        cout << "\n\n";
        for (int i = 0; title[i] != "\0"; i++)
        {
            cout << endl
                 << "   " << i + 1 << ". " << title[i] << endl;
        }

        int choice;
        cout << "\n   Select an option (Enter 0 for Back): ";
        cin >> choice;
        if (choice != 0)
        {
            system("clear");
            cout << "   " << title[choice - 1] << ": " << search_data(title[choice - 1]) << endl;
            cout << endl
                 << "   Press Enter to continue...";
            cin.get();
            cin.get();
            all_data();
        }
        else
        {
            main_();
        }
    }

    void add_data()
    {
        system("clear");
        banner();
        int i = 0;
        string n;
        string Title, Data;
        cout << "\n\n\n ";
        cout << "  How many records you want to add ? : ";
        cin >> i;

        for (int j = 0; j < i; j++)
        {
            if (j == 0)
            {
                getline(cin, n);
            }
            cout << "\n   Title: ";
            getline(cin, Title);

            cout << "   Data: ";
            getline(cin, Data);

            fstream file;
            file.open("data.txt", ios::app);
            file << Title << endl;
            file << Data << endl;
            file.close();
        }
        system("clear");
        cout << endl
             << "   Data saved successfully!" << endl;
        cout << endl
             << "   Press Enter to continue...";
        cin.get();
        main_();
    }

    void update_data()
    {
        system("clear");
        banner();
        string title, data, n;
        int flag = 0;
        getline(cin, n);
        cout << "\n\n\n   Title: ";
        getline(cin, title);
        cout << "   Data: ";
        getline(cin, data);
        int updateline1 = get_line(title);
        int updateline2 = get_line(search_data(title));
        string fdata = search_data(title);
        string line, line2;
        int count = 0;
        ifstream fin;
        fin.open("data.txt");
        ofstream temp;
        temp.open("temp.txt");

        if (repeat_check(title))
        {
            k++;
            while (!fin.eof())
            {
                if (flag == 1)
                {
                    temp << data << endl;
                    flag = 0;
                }

                count++;
                fin >> line;
                if (count == updateline2)
                {
                    flag = 1;
                    continue;
                }
                else
                {
                    if (line2 != line && line != fdata)
                    {
                        temp << line << endl;
                    }
                }
                line2 = line;
            }

            temp.close();
            fin.close();
            remove("data.txt");
            rename("temp.txt", "data.txt");
            system("clear");
            cout << endl
                 << "   Data Updated successfully" << endl;
            cout << endl
                 << "   Press Enter to continue...";
            cin.get();
            main_();
        }
        else
        {
            k++;
            system("clear");
            cout << endl
                 << "   Not found!" << endl;
            cout << endl
                 << "   Press Enter to continue...";
            cin.get();
            update_data();
        }
    }

    void delete_data()
    {
        system("clear");
        banner();
        string title, n;
        if (j == 0)
        {
            getline(cin, n);
        }
        cout << "\n\n\n   Title: ";
        getline(cin, title);
        int deleteline1 = get_line(title);
        int deleteline2 = get_line(search_data(title));
        string fdata = search_data(title);
        string line, line2;
        int count = 0;
        ifstream fin;
        fin.open("data.txt");
        ofstream temp;
        temp.open("temp.txt");

        if (repeat_check(title))
        {
            j++;
            while (!fin.eof())
            {

                count++;
                fin >> line;
                if (count == deleteline1 || count == deleteline2)
                {
                    continue;
                }
                else
                {
                    if (line2 != line && line != fdata)
                    {
                        temp << line << endl;
                    }
                }
                line2 = line;
            }

            temp.close();
            fin.close();
            remove("data.txt");
            rename("temp.txt", "data.txt");
            system("clear");
            cout << endl
                 << "   Data deleted successfully" << endl;
            cout << endl
                 << "   Press Enter to continue...";
            cin.get();
            main_();
        }
        else
        {
            j++;
            system("clear");
            cout << endl
                 << "   Not found!" << endl;
            cout << endl
                 << "   Press Enter to continue...";
            cin.get();
            delete_data();
        }
    }

    string search_data(string title)
    {
        string data;
        fstream fdata;
        fdata.open("data.txt", ios::in);
        while (!fdata.eof())
        {
            fdata >> data;
            if (data == title)
            {
                fdata >> data;
                return data;
            }
        }

        return data;
    }

    int repeat_check(string title)
    {
        string data;
        fstream fdata;
        fdata.open("data.txt", ios::in);
        while (!fdata.eof())
        {
            fdata >> data;
            if (data == title)
            {
                fdata >> data;
                return true;
            }
        }

        return false;
    }

    int get_line(string title)
    {
        string data;
        fstream fdata;
        int line = 0;
        fdata.open("data.txt", ios::in);
        while (!fdata.eof())
        {
            fdata >> data;
            line++;
            if (data == title)
            {
                fdata >> data;
                return line;
            }
        }

        return 0;
    }

    void logout()
    {
        set_status(0);
        login();
    }

    void auth()
    {
        if (get_signup_status())
        {
            login();
        }
        else
        {
            signup();
        }
    }

    int set_status(int status_val)
    {
        fstream status;
        status.open("log1.txt", ios::out);
        status << status_val;
        return true;
    }

    int get_status()
    {
        fstream fstatus;
        fstatus.open("log1.txt", ios::in);
        fstatus >> status;
        return status;
    }

    int get_signup_status()
    {
        fstream fstatus;
        fstatus.open("log.txt", ios::in);
        fstatus >> log;
        return log;
    }

    int set_signup_status(int status_val)
    {
        fstream fstatus;
        fstatus.open("log.txt", ios::out);
        fstatus << status_val;
        return true;
    }

    void main_()
    {
        system("clear");
        banner();
        cout << "\n\n\n"
             << "  1.Edit Proile\n\n  2.Add Data\n\n  3.View Data\n\n  4.Update Data\n\n  5.Delete Data\n\n  6.Logout\n\n  7.Exit\n\n  Select an option: ";
        cin >> choice;
        switch (choice)
        {
        case '1':
            edit_profile();
            break;

        case '2':
            add_data();
            break;

        case '3':
            all_data();
            break;

        case '4':
            update_data();
            break;

        case '5':
            delete_data();
            break;

        case '6':
            logout();
            break;

        case '7':
            exit(0);
            break;

        default:
            system("clear");
            cout << endl
                 << "Invalid option!" << endl;
            cout << endl
                 << "Press Enter to continue...";
            cin.get();
            cin.get();
            main_();
            break;
        }
    }
};

int main()
{
    Authentication admin;

    if (admin.get_status())
    {
        system("clear");
        admin.main_();
    }
    else
    {
        admin.auth();
    }

    return 0;
}