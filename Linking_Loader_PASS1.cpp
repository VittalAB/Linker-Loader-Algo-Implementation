#include <bits/stdc++.h>
#include "utils.h"
/*external variables linked*/
string PROGADDR, CSADDR, CSLTH;
estab ESTAB;
using namespace std;
int main()
{
    PROGADDR = get_program_address_from_os();
    CSADDR = PROGADDR;
    fstream objcode;
    objcode.open("objcode.txt", ios::in);
    if (objcode.is_open())
    {
        string op;
        while (getline(objcode, op))
        {
            read(op);
            bool found = search_estab(csect_name(op));
            if (found)
            {
                cout << "Error duplicate control section name ! \n";
            }
            else
            {
                enter_control_section_name_into_ESTAB_with_value_CSADDR(op);
            }
            while (record_type(op) != 'E')
            {
                getline(objcode, op);

                if (record_type(op) == 'D')
                {
                    process(op);
                }
            }
            CSADDR = int_to_hex(hex_to_int(CSADDR) + hex_to_int(CSLTH));
        }
        objcode.close();
    }

    display_ESTAB();

    return 0;
}

/* IMPLEMENTATION OF LINKING LOADER PASS-1 ALGORITHM */

/*
INPUT  :- OBJECT PROGRAM WITH CONTROL SECTIONS.

OUTPUT :- ESTAB i.e EXTERNAL SYMBOL TABLE WHICH HAS SYMBOL NAME AND ADDRESS ALONG WITH LENGTH.
*/

/*
CODER :- VITTAL A B
DATE  :- 08/12/21
TIME  :- 5:35 PM 
*/

/*

REFERENCE FOR ALGORITHM FOR IMPLEMENTATION
SYSTEM SOFTWARE :- INTRODUCTION TO SYSTEMS PROGRAMMING

*/

/*

PASS-1 ALGORTIHM 

BEGIN
    GET THE PROGRAM ADDRESS FROM OS
    SET CSADDR TO PROGRAM ADDRESS {FOR FIRST CONTROL SECTION}

    WHILE NOT END OF INPUT DO
        BEGIN
            READ NEXT INPUT RECORD {HEADER RECORD FOR CONTROL SECTION}
            SET CSLTH TO CONTROL SECTION LENGTH
            SEARCH ESTAB FRO CONTROL SECTION NAME

            IF FOUND THEN
                SET ERROR FLAG (DUPLICATE EXTERNAL SYMBOL)
            ELSE 
                ENTER CONTROL SECTION NAME INTO ESTAB WITH CSADDR AS VALUE
            WHILE RECORD TYPE !='E' DO
                BEGIN
                    READ NEXT INPUT RECORD
                    IF RECORD TYPE='D' THEN
                        FOR EACH SYMBOL IN THAT RECORD DO
                            BEGIN
                                SEARCH ESTAB FOR THE SYMBOL
                                IF FOUND THEN 
                                    SET ERROR FLAG DUPLICATE EXTERNAL SYMBOL FOUND
                                ELSE 
                                    ENTER SYMBOL TO ESTAB WITH THE VALUE AS {CSADDR + INDICATED ADDRESS}
                            END FOR
                END WHILE != 'E'
                    ADD CSLTH + CSADDR {STARTING ADDRESS FOR THE NEXT CONTROL SECTION}
        END {WHILE NOT EOF}
END PASS-1 
*/