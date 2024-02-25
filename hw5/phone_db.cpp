#include <string.h>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include "helperfunct.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::map;
using std::ofstream;
using std::string;
using std::stringstream;

int main() {
  string line = "";
  char option = ' ';
  string first_name = "";
  string last_name = "";
  string type = "";
  string phone_number = "";
  stringstream ss;  // main
  Name n;
  PhoneNumberCollection p;
  string in_filename;
  map<Name, PhoneNumberCollection>::iterator it;
  map<Name, PhoneNumberCollection> phone_db;  // main
  map<Name, PhoneNumberCollection> phone_db_copy;
  ofstream ofile;
  ifstream ifile;

  cout << "Info: Welcome to the Phone Database!" << endl;
  cout << "Info: Please enter a command" << endl;

  while (getline(cin, line)) {
    ss.clear();
    ss.str(line);  // Load the current line into the stringstream

    ss >> option;
    switch (toupper(option)) {
      case 'C':
        handleCreateContact(ss, phone_db, n, p);
        break;

      case 'D':
        handleDeleteContact(ss, phone_db, n);
        break;

      case 'L':
        listContacts(phone_db);
        break;

      case 'P':
        printPhoneNumbers(ss, phone_db, n);
        break;

      case 'N':
        ss >> last_name >> first_name >> type >> phone_number;

        n = {last_name, first_name};

        // if contact isnt found display an error
        it = phone_db.find(n);
        if (it == phone_db.end()) {
          cout << "Error: Contact not found" << endl;
          break;
        }
        handlePhoneNumber(it, type, phone_number);
        break;

      case 'X':  // deletes contact phone number
        ss >> last_name >> first_name >> type;
        n = {last_name, first_name};
        it = phone_db.find(n);

        if (it != phone_db.end()) {  // found contact
          bool phoneNumberDeleted = deletePhoneNumber((*it).second, type);
          if (phoneNumberDeleted) {
            cout << "Result: Phone number deleted" << endl;
          } else {
            cout << "Error: No phone number of that type" << endl;
          }
        } else {
          cout << "Error: Contact not found" << endl;
        }
        break;

      case 'S':
        ss >> in_filename;

        ofile.open(in_filename);
        if (!ofile.is_open()) {
          cout << "Error: Could not open output file" << endl;
          break;
        }
        saveToFile(ofile,phone_db);
        break;

      case 'R':
        ss >> in_filename;
        // ss.clear();

        ifile.open(in_filename);
        if (!ifile.is_open()) {
          cout << "Error: Could not open input file" << endl;
          break;
        }
        loadFromFile(phone_db,phone_db_copy,n,ss,p,ifile,line);
        break;
      case 'Q':
        cout << "Info: Thank you for using the Phone Database!" << endl;
        return 0;

      default:
        cout << "Error, option: " << option << " doesn't exist" << endl;
    }

    cout << "Info: Please enter a command" << endl;
  }
  return 0;
}
