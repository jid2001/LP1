#include<bits/stdc++.h> 
using namespace std;

string getAddr( ifstream &fin, string s){
    string sno, sname, addr;
    while(fin >> sno>>sname>>addr){
        if(sno == s){
            fin.seekg(0,ios :: beg );
            return addr;
        }
    }
    fin.seekg(0,ios :: beg );
    return "NAN";
}

int main(){

    // obj to read ic input
    ifstream ic,st,lt;
    ic.open("ic1.txt");
    st.open("st2.txt");
    lt.open("lit.txt");


ofstream mout;
mout.open("machine_code.txt");
string lc, op1,op2,op3;                       // (IS,02)
while(!ic.eof()){

string mc;
    ic >> lc>>op1>>op2>>op3;
    if(op1.substr(1,2) == "AD" || (op1.substr(1,2) == "DL" && op1.substr(4,2) == "02")){
        mc = "- NO MACHINE CODE -";

    }
    else if(op1.substr(1,2) == "DL" && op1.substr(4,2) == "01"){
        mc = "00\t0\t00" + op2.substr(3,1);
    }

    else{
        if( op1 == "(IS,00)")
                mc += op1.substr(4,2) + "\t0\t000";
        else if(op3.substr(1,1)== "S" ){
            mc += op1.substr(4,2) + "\t" + op2.substr(1,1) + "\t" + getAddr(st, op3.substr(4,1));
        }
        else {
            mc += op1.substr(4,2) + "\t" + op2.substr(1,1) + "\t" + getAddr(lt, op3.substr(4,1));
        }


    }
    if( op1 == "(AD,03)"){
        cout<< " "<< lc << op1 << "\t" << op2<< " "<<op3 << "\t\t\t" << lc<< "\t" << mc<<endl;
        mout << lc << "\t" << mc << endl;
        continue;

    }
    // console output;
        cout<< " "<< lc << op1 << "\t" << op2<< "\t" <<op3 << "\t\t\t" << lc<< "\t" << mc<<endl;
        mout << lc << "\t" << mc << endl;

    
}

    
    return 0;
}