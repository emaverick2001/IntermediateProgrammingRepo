#ifndef HELPERFUNCT_H
#define HELPERFUNCT_H

#include "helperfunct.h"
#include <string.h>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>


struct Name {
  std::string last_name;
  std::string first_name;

  bool operator<(const Name& other) const {
    if (last_name != other.last_name) return last_name < other.last_name;
    return first_name < other.first_name;
  }
};

struct PhoneNumberCollection {
  std::string cell;
  std::string fax;
  std::string home;
  std::string voip;
  std::string work;
};

bool is_valid_phone_num(std::string phone_number);

void handleCreateContact(std::stringstream& ss,std::map<Name, PhoneNumberCollection> &phone_db, Name n, PhoneNumberCollection p);

void handleDeleteContact(std::stringstream& ss,std::map<Name, PhoneNumberCollection> &phone_db, Name n);

void listContacts(std::map<Name, PhoneNumberCollection> &phone_db);

void printPhoneNumbers(std::stringstream& ss,std::map<Name, PhoneNumberCollection> &phone_db, Name n);

void handlePhoneNumber(std::map<Name, PhoneNumberCollection>::iterator& it, std::string type, std::string phone_number);

bool deletePhoneNumber(PhoneNumberCollection& phoneNumberCollection, std::string type);

void saveToFile(std::ofstream& ofile, std::map<Name, PhoneNumberCollection> &phone_db);

void loadFromFile(std::map<Name, PhoneNumberCollection>& phone_db, std::map<Name, PhoneNumberCollection> phone_db_copy, Name n,std::stringstream& ss,PhoneNumberCollection p,std::ifstream& ifile,std::string line);

#endif 