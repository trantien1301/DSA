#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;
struct Company
{
    string name;
    string profit_tax;
    string address;
};
struct HashTable
{
  vector<Company> Companylist[2000];
};
vector<Company> readCompanyList(string file_name)
{
    ifstream If(file_name);
    vector<Company> companies;
    string line;
    if(If.is_open())
{
    getline(If,line);
    while (getline(If,line))
    {
        stringstream ss(line);
        Company company;
        getline(ss,company.name,'|');
        getline(ss,company.profit_tax,'|');
        getline(ss,company.address,'|');
        companies.push_back(company);
    }
}

    If.close();
    return companies;    
}
long long hashString(string companyName) {
    long long res = 0;
    long long pow = 1;
    string s;
if(companyName.size()>20)
{
    s = companyName.substr(companyName.size() - 20);
}
else 
{
    s = companyName; 
}
    // string s = (companyName.size() > 20) ? companyName.substr(companyName.size() - 20) : companyName;

    for (int i = 0; i < s.length(); i++) {
        res = (res + (s[i] * pow)) % 2000;
        pow = (pow * 31) % 2000;  
    }

    return res;
}


 HashTable* createHashTable(vector<Company> list_company)
 {
 HashTable* hash_table= new HashTable;
  for (Company comp: list_company)
  {
    int index= hashString(comp.name);
    hash_table->Companylist[index].push_back(comp);
  }
  return hash_table;
 }
 void insert(HashTable* hash_table, Company company) {
    int index = hashString(company.name);
    hash_table->Companylist[index].push_back(company);
}
Company* search(HashTable* hash_table, string company_name)
{
    int key= hashString(company_name);
    for(Company& comp : hash_table->Companylist[key])
    {
        if (comp.name == company_name) 
        {
            return &comp;
        }
    }
    return nullptr;
}

void writeOutput(string output_file, vector<string> company_names, HashTable* hash_table) {
    ofstream Of(output_file);
    if (Of.is_open()) {
        for (string name : company_names) {
            Company* result = search(hash_table, name);
            if (result) {
                Of << result->name << "|" << result->profit_tax << "|" << result->address << endl;
            }
        }
        Of.close();
    }
}
vector<string> readSearchList(string input_file) {
    vector<string> search_list;
    ifstream If(input_file);
    string line;
    while (getline(If, line)) {
        search_list.push_back(line);
    }
    If.close();
    return search_list;
}

void deleteHashTable(HashTable* hash_table) {
    delete hash_table;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }

    string mst_file = argv[1];
    string input_file = argv[2];
    string output_file = argv[3];

    vector<Company> companies = readCompanyList(mst_file);
    HashTable* hash_table = createHashTable(companies);
    vector<string> search_list = readSearchList(input_file);

    writeOutput(output_file, search_list, hash_table);

    deleteHashTable(hash_table);

    return 0;
}

