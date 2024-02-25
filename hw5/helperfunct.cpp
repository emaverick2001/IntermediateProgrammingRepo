#include "helperfunct.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::map;
using std::ofstream;
using std::string;
using std::stringstream;

string line = "";
string first_name = "";
string last_name = "";
string type = "";
string phone_number = "";
stringstream ss;
Name n;
PhoneNumberCollection p;
string out_filename;
string in_filename;
map<Name, PhoneNumberCollection>::iterator it;
map<Name, PhoneNumberCollection> phone_db;
map<Name, PhoneNumberCollection> phone_db_copy;
ofstream ofile;
ifstream ifile;

// phone number consists of only digits and -
// cant start with or end with -
bool is_valid_phone_num(string phone_number) {
  bool val = false;

  for (int i = 0; i < (int)phone_number.length(); i++) {
    if (isdigit(phone_number[i]) || phone_number[i] == '-') {
      val = true;
    } else {
      val = false;
      break;
    }
  }

  if (phone_number.front() == '-' || phone_number.back() == '-') {
    val = false;
  }

  return val;
}

void handleCreateContact(std::stringstream& ss,
                         std::map<Name, PhoneNumberCollection>& phone_db,
                         Name n, PhoneNumberCollection p) {
  ss >> last_name >> first_name;
  n = {last_name, first_name};
  it = phone_db.find(n);
  if (it != phone_db.end()) {  // if contact already exists
    cout << "Contact already exists" << endl;
  } else {
    phone_db[n] = p;
    cout << "Result: Contact created" << endl;
  }
}

void handleDeleteContact(std::stringstream& ss,
                         std::map<Name, PhoneNumberCollection>& phone_db,
                         Name n) {
  ss >> last_name >> first_name;
  n = {last_name, first_name};
  it = phone_db.find(n);
  if (it != phone_db.end()) {  // found contact
    phone_db.erase(n);
    cout << "Result: Contact deleted" << endl;
  } else {
    cout << "Contact not found" << endl;
  }
}

void listContacts(std::map<Name, PhoneNumberCollection>& phone_db) {
  for (map<Name, PhoneNumberCollection>::iterator it = phone_db.begin();
       it != phone_db.end(); ++it) {
    cout << "Result: " << it->first.last_name << "," << it->first.first_name
         << endl;
  }
  cout << "Info: There are " << phone_db.size() << " contact(s)" << endl;
}

void printPhoneNumbers(std::stringstream& ss,
                       std::map<Name, PhoneNumberCollection>& phone_db,
                       Name n) {
  ss >> last_name >> first_name;
  n = {last_name, first_name};
  it = phone_db.find(n);
  if (it != phone_db.end()) {  // if contact exists

    int count = 0;
    if ((*it).second.cell != "") {
      cout << "Result: CELL," << (*it).second.cell << endl;
      count++;
    }
    if ((*it).second.fax != "") {
      cout << "Result: FAX," << (*it).second.fax << endl;
      count++;
    }
    if ((*it).second.home != "") {
      cout << "Result: HOME," << (*it).second.home << endl;
      count++;
    }
    if ((*it).second.voip != "") {
      cout << "Result: VOIP," << (*it).second.voip << endl;
      count++;
    }
    if ((*it).second.work != "") {
      cout << "Result: WORK," << (*it).second.work << endl;
      count++;
    }
    cout << "Info: Found " << count << " phone number(s) for this contact"
         << endl;
  } else {
    cout << "Error: Contact not found" << endl;
  }
}

void handlePhoneNumber(std::map<Name, PhoneNumberCollection>::iterator& it,
                       std::string type, std::string phone_number) {
  if (is_valid_phone_num(phone_number)) {  // check to see if actual
                                           // number enetered is valid
    if (type == "CELL") {                  // access second variable element
      if ((*it).second.cell == "") {
        cout << "Result: Phone number added" << endl;
      } else {
        cout << "Result: Phone number replaced" << endl;
      }
      (*it).second.cell = {phone_number};

    } else if (type == "FAX") {
      if ((*it).second.fax == "") {
        cout << "Result: Phone number added" << endl;
      } else {
        cout << "Result: Phone number replaced" << endl;
      }
      (*it).second.fax = {phone_number};
    } else if (type == "HOME") {
      if ((*it).second.home == "") {
        cout << "Result: Phone number added" << endl;
      } else {
        cout << "Result: Phone number replaced" << endl;
      }
      (*it).second.home = {phone_number};
    } else if (type == "VOIP") {
      if ((*it).second.voip == "") {
        cout << "Result: Phone number added" << endl;
      } else {
        cout << "Result: Phone number replaced" << endl;
      }
      (*it).second.voip = {phone_number};
    } else if (type == "WORK") {
      if ((*it).second.work == "") {
        cout << "Result: Phone number added" << endl;
      } else {
        cout << "Result: Phone number replaced" << endl;
      }
      (*it).second.work = {phone_number};
    } else {
      cout << "Error: Invalid phone number type"
           << endl;  // if cell type isnt valid
    }
  } else {
    cout << "Error: Not a valid phone number" << endl;
  }
}

bool deletePhoneNumber(PhoneNumberCollection& phoneNumberCollection,
                       string type) {
  if (type == "CELL" && !phoneNumberCollection.cell.empty()) {
    phoneNumberCollection.cell = "";
    return true;
  } else if (type == "FAX" && !phoneNumberCollection.fax.empty()) {
    phoneNumberCollection.fax = "";
    return true;
  } else if (type == "HOME" && !phoneNumberCollection.home.empty()) {
    phoneNumberCollection.home = "";
    return true;
  } else if (type == "VOIP" && !phoneNumberCollection.voip.empty()) {
    phoneNumberCollection.voip = "";
    return true;
  } else if (type == "WORK" && !phoneNumberCollection.work.empty()) {
    phoneNumberCollection.work = "";
    return true;
  } else {
    return false;
  }
}

void saveToFile(std::ofstream& ofile,
                std::map<Name, PhoneNumberCollection>& phone_db) {
  for (map<Name, PhoneNumberCollection>::iterator it = phone_db.begin();
       it != phone_db.end(); ++it) {
    ofile << it->first.last_name << ' ' << it->first.first_name << ' ';
    if (it->second.cell == "") {
      ofile << "NA" << ' ';
    } else {
      ofile << it->second.cell << ' ';
    }
    if (it->second.fax == "") {
      ofile << "NA" << ' ';
    } else {
      ofile << it->second.fax << ' ';
    }
    if (it->second.home == "") {
      ofile << "NA" << ' ';
    } else {
      ofile << it->second.home << ' ';
    }
    if (it->second.voip == "") {
      ofile << "NA" << ' ';
    } else {
      ofile << it->second.voip << ' ';
    }
    if (it->second.work == "") {
      ofile << "NA" << endl;
    } else {
      ofile << it->second.work << endl;
    }
  }
}

void loadFromFile(std::map<Name, PhoneNumberCollection>& phone_db, std::map<Name, PhoneNumberCollection> phone_db_copy, Name n,std::stringstream& ss,PhoneNumberCollection p,std::ifstream& ifile,std::string line){
  while (getline(ifile, line)) {
          ss.clear();
          ss.str(line);
          ss >> last_name >> first_name >> p.cell >> p.fax >> p.home >>
              p.voip >> p.work;
          n = {last_name, first_name};

          if (p.cell == "NA") {
            p.cell = "";
          }
          if (p.fax == "NA") {
            p.fax = "";
          }
          if (p.home == "NA") {
            p.home = "";
          }
          if (p.voip == "NA") {
            p.voip = "";
          }
          if (p.work == "NA") {
            p.work = "";
          }
          phone_db_copy[n] = p;
        }

        phone_db = phone_db_copy;
}