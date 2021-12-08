#include <bits/stdc++.h>
#include "convert.h"
using namespace std;

extern string PROGADDR, CSADDR, CSLTH;
typedef map<string, vector<string>> estab;
extern estab ESTAB;

vector<string> sym;
vector<string> address;

string get_program_address_from_os()
{
    cout << "Enter Load Address \n";
    string add;
    cin >> add;
    return add;
}

void read(string op)
{
    if (op[0] == 'H')
    {
        CSLTH = op.substr(16, 6);
    }
}

string csect_name(string op)
{
    return op.substr(2, 6);
}

bool search_estab(string csect_name)
{
    estab::iterator itr;
    for (itr = ESTAB.begin(); itr != ESTAB.end(); itr++)
    {
        if (itr->second[0] == csect_name)
        {
            return true;
        }
    }
    return false;
}

char record_type(string op)
{
    if (op[0] == 'E')
    {
        return 'E';
    }
    else if (op[0] == 'D')
    {
        return 'D';
    }
    else if (op[0] == 'R')
    {
        return 'R';
    }
}

bool search_estab_for_symbol(string sym)
{
    estab::iterator itr;

    for (itr = ESTAB.begin(); itr != ESTAB.end(); itr++)
    {
        if (itr->second[1] == sym)
        {
            return true;
        }
    }
    return false;
}

void process(string op)
{

    for (int i = 2; i < op.size(); i = i + 14)
    {
        string symb;
        symb = op.substr(i, 6);
        sym.push_back(symb);
    }

    for (int i = 9; i < op.size(); i = i + 14)
    {
        string add;
        add = op.substr(i, 6);
        address.push_back(add);
    }

    for (int i = 0; i < sym.size(); i++)
    {

        bool found = search_estab_for_symbol(sym[i]);

        if (found)
        {
            cout << "Error duplicate symbols found! \n";
        }
        else
        {
            string caddr = int_to_hex(hex_to_int(CSADDR) + hex_to_int(address[i]));
            vector<string> field;

            field.push_back("      ");
            field.push_back(sym[i]);
            field.push_back(caddr);
            field.push_back("      ");

            ESTAB[caddr] = field;
        }
    }

    sym.clear();
    address.clear();
}

void enter_control_section_name_into_ESTAB_with_value_CSADDR(string op)
{
    vector<string> field;
    field.push_back(csect_name(op));
    field.push_back("      ");
    field.push_back(CSADDR);
    field.push_back(CSLTH);

    ESTAB[CSADDR] = field;
}

void display_ESTAB(){
    estab::iterator itr;
    cout << "ESTAB contents :- \n";

    cout << "control "
         << "symbol "
         << "addr "
         << "len " << endl;
    cout << "section "
         << "name " << endl;
    for (itr = ESTAB.begin(); itr != ESTAB.end(); itr++)
    {
        for (int i = 0; i < itr->second.size(); i++)
        {
            cout << itr->second[i] + " ";
        }
        cout << "\n";
    }
}