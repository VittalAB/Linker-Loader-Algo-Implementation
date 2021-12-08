#include<bits/stdc++.h>
using namespace std;

string int_to_hex(int my_integer)
{
    std::stringstream sstream;
    sstream << std::hex << my_integer;
    std::string result = sstream.str();
    return result;
}

int hex_to_int(string my_hex)
{
    unsigned int x;
    std::stringstream ss;
    ss << std::hex << my_hex;
    ss >> x;
    return x;
}