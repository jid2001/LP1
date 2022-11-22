#include <bits/stdc++.h>
using namespace std;

struct OpTab
{
    string opcode;
    string mclass;
    string mnum;
};

// Hard-coding the class and mnemonic for respective opcode

struct OpTab optab[18] = {
    {"STOP", "IS", "00"},
    {"ADD", "IS", "01"},
    {"SUB", "IS", "02"},
    {"MULT", "IS", "03"},
    {"MOVER", "IS", "04"},
    {"MOVEM", "IS", "05"},
    {"COMP", "IS", "06"},
    {"BC", "IS", "07"},
    {"DIV", "IS", "08"},
    {"READ", "IS", "09"},
    {"PRINT", "IS", "10"},
    {"START", "AD", "01"},
    {"END", "AD", "02"},
    {"EQU", "AD", "03"},
    {"ORIGIN", "AD", "04"},
    {"LTORG", "AD", "05"},
    {"DC", "DL", "01"},
    {"DS", "DL", "02"},

};

// Function to fetch the opcode entry

int getOP(string s)
{
    for (int i = 0; i < 18; i++)
    {
        if (optab[i].opcode == s)
            return i;
    }
    return -1;
}

// Function to fetch the register code

int getRegID(string s)
{
    if (s == "AREG")
        return 1;
    else if (s == "BREG")
        return 2;
    else if (s == "CREG")
        return 3;
    else if (s == "DREG")
        return 4;
    return -1;
}

// Function to fetch conditional code

int getCondCode(string s)
{
    if (s == "LT")
        return 1;
    else if (s == "LE")
        return 2;
    else if (s == "EQ")
        return 3;
    else if (s == "GT")
        return 4;
    else if (s == "GE")
        return 5;
    else if (s == "ANY")
        return 6;
    return -1;
}

struct symTable
{
    int no;
    string sname;
    string addr;
};

struct symTable ST[10];

// Function to fetch the symbol entry

int getSymID(string s)
{
    for (int i = 0; i < 10; i++)
    {
        if (ST[i].sname == s)
            return i;
    }
    return -1;
}

// To store Literal Table output

struct litTable
{
    int lno;
    string lname;
    string addr;
};

struct litTable LT[10];

// Function to fetch the literal entry

int getLitID(string s)
{
    for (int i = 0; i < 10; i++)
    {
        if (LT[i].lname == s)
            return i;
    }
    return -1;
}

// To store Pool Table output

struct poolTable
{
    int no;
    string pno;
};

struct poolTable PT[10];

int main()
{

    // Take input as text file

    ifstream fin;
    fin.open("input.txt");

    // Objects to write into ic, st,lt,

    ofstream ic, st, lt;

    ic.open("ic1.txt");
    st.open("symtab1.txt");
    lt.open("lit1.txt");

    string lable, opcode, op1, op2;

    int scnt = 0, lcnt = 0, nlcnt = 0, pcnt = 0, LC = 0;

    cout << "\n**********  ASSEMBLER PASS-1 OUTPUT  ************ \n";
    cout << " \n LABLE\tOPCODE\tOP1\tOP2\tINTERMIDIATE CODE  \n";

    while (!fin.eof())
    {
        fin >> lable >> opcode >> op1 >> op2;

        int id;
        string IC, lc;

        id = getOP(opcode);

        IC = "(" + optab[id].mclass + "," + optab[id].mnum + ")";

        // Individual cases for Assembly Directives (AD) - START, END, ORIGIN, EQU, LTORG
        // no LC processing for AD so lc = "---"
        if (opcode == "START")
        {

            lc = "---";
            if (op1 != "NAN")
            {

                LC = stoi(op1);
                IC += "(C," + op1 + ")  NAN";
            }
            // goto print;
        }

        if (opcode == "EQU")
        {
            lc = "---";
            IC += " NAN      NAN";

            if (getSymID(lable) != -1)
            {
                ST[getSymID(lable)].addr = ST[getSymID(op1)].addr;
            }
            else
            {
                ST[scnt].no = scnt + 1;
                ST[scnt].sname = lable;
                ST[scnt].addr = ST[getSymID(op1)].addr;
                scnt++;
            }
        }
        else if (lable != "NAN")
        {
            if (getSymID(lable) != -1)
            {
                ST[getSymID(lable)].addr = to_string(LC);
            }
            else
            {
                ST[scnt].no = scnt + 1;
                ST[scnt].sname = lable;
                ST[scnt].addr = to_string(LC);
                scnt++;
            }
        }

        if (opcode == "ORIGIN")
        {

            string tk1, tk2;
            char op;
            stringstream ss(op1);
            size_t found = op1.find('+');
            if (found != string ::npos)
            {
                op = '+';
            }
            else
                op = '-';

            getline(ss, tk1, op);
            getline(ss, tk2, op);
            lc = "---";

            if (op == '+')
            {
                LC = stoi(ST[getSymID(tk1)].addr) + stoi(tk2);
                IC += "(S,0" + to_string(ST[getSymID(tk1)].no) + ")+" + tk2 + "NAN";
            }
            else
            {
                LC = stoi(ST[getSymID(tk1)].addr) - stoi(tk2);
                IC += "(S,0" + to_string(ST[getSymID(tk1)].no) + ")+" + tk2 + "NAN";
            }
        }

        if(opcode == "LTORG"){

            cout<<"  "<< lable << "\t" << opcode << "\t" << op1 << "\t" << op2 << "\t";

            for(int i = lcnt -nlcnt; i< lcnt; i++){
                lc = to_string(LC);
                string c(1, LT[i].lname[2]);
                IC = "(DL,01) (C," + c + ")  NAN";
                LT[i].addr = to_string(LC);
                LC++;
                if(i <lcnt -1){
					cout << lc << "\t" << IC << "\n\t\t\t\t";

                }
                else
                    cout<< lc<<"\t"<<IC<<endl;

                ic <<lc<< "\t"<< IC << endl;

                
            }

			// managing pool table in LTORG

            PT[pcnt].pno = "#" + to_string(LT[lcnt -nlcnt].lno);
            PT[pcnt].no = ++pcnt;
            nlcnt =0;
            continue;
        }


        if(opcode == "END")
        {
            lc ="---";
            IC += " NAN     NAN";
            cout<< "  "<< lable << "\t" << opcode << "\t" << op1 << "\t" << op2 << "\t"<< lc << "\t" << IC  << endl;

            ic << lc << "\t" << IC << endl;

            if(nlcnt){

                for( int i = lcnt-nlcnt ; i <lcnt ; i++){

                    lc = to_string(LC);
                    IC = "(DL,01)  (C,";
                    string c(1, LT[ i].lname[2]);
                    IC += c + ")    NAN";

                    LT[i].addr = to_string(LC);
                    LC++;

                    cout<< "\t\t\t\t" << lc<< "\t" << IC << endl;

                    ic << lc << "\t" << IC << endl;
                }
				// managing pool table after END (if any literals are left)

                PT[pcnt].pno = "#" + to_string(LT[lcnt -nlcnt].lno);
                PT[pcnt].no = ++pcnt;

            } 
            break;
        }

        // Declarative Statement (DL)

        if(opcode == "DC" || opcode == "DS"){
            lc = to_string(LC);
            if(opcode =="DS"){
                IC += "(C," + op1 + ")     NAN";
                LC += stoi(op1);
            }
            else{
                string c = op1.substr(1,1);
                 IC += "(C," + c + ")     NAN";
                 LC++;
            }
        }


		// if not AD or DL then, Imperative Statements (IS)
        // 

        if(opcode != "START" && opcode != "END" && opcode != "ORIGIN" && opcode != "EQU" && opcode != "LTORG" && opcode != "DC" && opcode != "DS"){
            if(op2 == "NAN"){
                if( op1 == "NAN"){
                    lc = to_string(LC);
                    LC++;
                    IC += " NAN     NAN";
                }
                else {
                    if(getSymID(op1) != -1){
                        IC += "(S,0" + to_string(ST[getSymID(op1)].no)  + ")";
                        lc  = to_string(LC);
                        LC++;
                    }
                    else{
                        
                        ST[scnt].no = scnt+1;
                        ST[scnt].sname = op1;
                        scnt++; 
                        IC += "(S,0" + to_string(ST[getSymID(op1)].no) + ")";
                        lc = to_string(LC);
                        LC++;
                        
                    }
                }
            }
            else{
                if(opcode == "BC")
                    IC += "(" + to_string(getCondCode(op1)) + ")        ";
                
                else 
                    IC += "(" + to_string(getRegID(op1)) + ")        ";

                // if operand 2 is literal
                if(op2[0] == '='){

                        LT[lcnt].lno = lcnt+1;
                        LT[lcnt].lname = op2;
                        lcnt++;
                        nlcnt++;

                        IC += "(L,0" + to_string(LT[getLitID(op2)].lno)   + ")";


                }
                else    // operand 2 is symbol
                {
                    if(getSymID(op2) != -1){
                        IC +=  "(S,0" + to_string(ST[getSymID(op2)].no) + ")";
                    }
                    else{
                    ST[scnt].no = scnt+1;
                    ST[scnt].sname = op2;
                    scnt++;
                    IC += "(S,0" + to_string(ST[getSymID(op2)].no) + ")";
                }

                }
                lc = to_string(LC);
                LC++;
                    
            }
        }

        //console output

        cout<< " "<< lable << "\t" << opcode <<"\t" << op1<< "\t" << op2 << "\t" << lc << "\t" << IC <<endl;
        ic<<lc<<"\t" <<IC  << endl;

        
        }
    cout << "\n----------------------------------------------------------------" << endl;
	cout << " -- SYMBOL TABLE --" << endl;
	cout << "\n <NO.\tSYMBOL\tADDRESS>" << endl;
	for(int i = 0; i < scnt; ++i)
	{
		cout << "  " << ST[i].no << "\t " << ST[i].sname << "\t  " << ST[i].addr << endl;
		st << ST[i].no << "\t " << ST[i].sname << "\t  " << ST[i].addr << endl;
	}
cout << "\n----------------------------------------------------------------" << endl;
	cout << " -- LITERAL TABLE --" << endl;
	cout << "\n <NO.\tLITERAL\tADDRESS>" << endl;
	for(int i = 0; i < lcnt; ++i)
	{
		cout << "  " << LT[i].lno << "\t " << LT[i].lname << "\t  " << LT[i].addr << endl;
		lt << LT[i].lno << "\t " << LT[i].lname << "\t  " << LT[i].addr << endl;
	}

	cout << "\n----------------------------------------------------------------" << endl;
	cout << " -- POOL TABLE --" << endl;
	cout << "\n <NO.\tLITERAL_NO.>" << endl;
	for(int i = 0; i < pcnt; ++i)
	{
		cout << "  " << PT[i].no << "\t   " << PT[i].pno << endl;
        
	}
    return 0;
}