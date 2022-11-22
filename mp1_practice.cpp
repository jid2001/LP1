#include<bits/stdc++.h> 
using namespace std;

int main(){
    
    // Source file
    ifstream fin;
    fin.open("source.txt");
    ofstream mnt, mdt, kpdt,pnt;
    mnt.open("mnt.txt");
    mdt.open("mdt.txt");
    kpdt.open("kpdt.txt");
    pnt.open("pnt.txt");

    vector<vector<string> > mntab;
    vector<pair<string,string> > kpdtab;
    map<string,int> pntab;
    
    int mdtpte =1;
    bool macroStart =false;
    string line, w;
    while(getline(fin, line)){
        stringstream ss(line);
        ss >> w;
        if(w == "MACRO") {
            macroStart =true;
            continue;
        }

        if(macroStart){
            vector<string> temp(5);
            temp[0] = w;
            temp[3] = to_string(mdtpte);


            pnt << "PNTAB FOR " << w << "\n";

            int pp =0, kp =0;
            while(ss >> w){
                w = w.substr(1);
                if(w[w.size()-1] == ','){
                    w = w.substr(0,w.size()-1);
                }
                int bind =-1;
                for(int i= 0; i<w.size(); i++){
                    if(w[i] == '='){
                        bind = i;
                        break;
                    }
                }

                if(bind != -1){
                    kp++;
                    pair<string, string> pr;
                    pr = { w.substr(0,bind), w.substr(bind+1)};

                    kpdtab.push_back(pr);

                    pntab[pr.first] =  pntab.size()+1;
                    pnt << pntab[pr.first] << " \t" << pr.first<<endl;
                }
                else{
                    pp++;

                    pntab[w] = pntab.size()+1;
                    pnt  << pntab[w] << " \t" << w<<endl;
                }
            }
            temp[1] = to_string(pp);
            temp[2] = to_string(kp);
            if(kp > 0) temp[4] = to_string(kpdtab.size() - kp +1);

            mntab.push_back(temp);
            macroStart = false;
            continue;
        }

        if(w == "MEND"){
            mdt << "MEND"   <<"\n";
                 pntab.clear();
            

        }
        else{
            mdt << w << " ";
            bool f = true;
            while(ss>>w){
                if(!f) mdt << ",";
            
            if(w[0] =='&'){
                w = w.substr(1);
                if(w[w.size()-1] == ','){
                    w = w.substr(0,w.size()-1);
                }

                mdt <<"(P," << pntab[w]  << ")" ;
            }
            else {
               if(w[w.size()-1] == ','){
                    w = w.substr(0,w.size()-1);
                }

                mdt <<"(P" << pntab[w]  << ")" ;
            }
            f =false;
        }
        mdt <<"\n";
    }
    mdtpte++;

    }

    for(auto x : mntab){
        for(int i = 0; i < x.size(); i++){
            mnt << x[i] <<" ";
            cout<< x[i] << " ";
        }
        mnt <<"\n";
        cout <<"\n";
    }

    for(auto x : kpdtab){
        kpdt << x.first << " " << x.second <<endl;
    }
    return 0;
}