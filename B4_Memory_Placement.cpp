#include <bits/stdc++.h>
using namespace std;

void firstFit(int b, vector<int> blockSize, int p, vector<int>  processSize ){
    vector<int> allc(p, -1);
   
    for(int i=0; i<p; i++){
        for(int j =0 ;j< b; j++){

            if(blockSize[j] >= processSize[i]){
                allc[i] = j;
                blockSize[j] -= processSize[i];
               
                break;
            }
        }

    }
   

    cout<<"\n Process No. \t Process Size \t Block No. \n";
    for(int i =0; i<p; i++){
       cout << " " << i+1 << " \t\t " << processSize[i] << " \t\t ";
    
    if(allc[i] != -1){
            cout << allc[i] + 1;
          
    }
        else 
            cout << "Not Allocated";
        cout << "\n";    
    }

    cout<<" Holes in blocks \n";
    for(int i =0; i<b; i++){
        cout<<" Block : "<< i+1 << "   | Hole   : "<< blockSize[i] << endl;
    }
}

void nextFit(int b, vector<int> blockSize, int p, vector<int>  processSize ){
    vector<int> allc(p, -1);
    
    int ptr =0;
    for(int i=0; i<p; i++){
        for(int j =ptr ;j< b; j++){

            if(blockSize[j] >= processSize[i]){
                allc[i] = j;
                blockSize[j] -= processSize[i];
                ptr = j;
               
                break;
            }
        }

    }

    cout<<"\n Process No. \t Process Size \t Block No. \n";
    for(int i =0; i<p; i++){
       cout << " " << i+1 << " \t\t " << processSize[i] << " \t\t ";
    
    if(allc[i] != -1){
            cout << allc[i] + 1;
           
    }
        else 
            cout << "Not Allocated";
        cout << "\n";    
    }

    
    cout<<" Holes in blocks \n";
    for(int i =0; i<b; i++){
        cout<<" Block : "<< i+1 << "   | Hole   : "<< blockSize[i] << endl;
    }
}

void bestFit(int b, vector<int> blockSize, int p, vector<int>  processSize ){
    vector<int> allc(p, -1);

    for(int i=0; i<p; i++){
        int idx = -1, size = INT_MAX;
        for(int j =0; j<b; j++){
            if(blockSize[j] >= processSize[i] && blockSize[j] < size){
                size = blockSize[j];;
                idx =j;
            }
        }

        if( idx != -1){
            allc[i] = idx;
            blockSize[idx] -= processSize[i];
        }
    }


    cout<<"\n Process No. \t Process Size \t Block No. \n";
    for(int i =0; i<p; i++){
       cout << " " << i+1 << " \t\t " << processSize[i] << " \t\t ";
    
    if(allc[i] != -1){
            cout << allc[i] + 1;
           
    }
        else 
            cout << "Not Allocated";
        cout << "\n";    
    }

    
    cout<<" Holes in blocks \n";
    for(int i =0; i<b; i++){
        cout<<" Block : "<< i+1 << "   | Hole   : "<< blockSize[i] << endl;
    }

}


void worstFit(int b, vector<int> blockSize, int p, vector<int>  processSize ){
    vector<int> allc(p, -1);
    vector<int> hole(b,-1);

    for(int i=0; i<p; i++){
        int idx = -1, size = -1;
        for(int j =0; j<b; j++){
            if(blockSize[j] >= processSize[i] && blockSize[j] > size){
                size = blockSize[j];;
                idx =j;
            }
        }

        if( idx != -1){
            allc[i] = idx;
            blockSize[idx] -= processSize[i];
        }
    }


    cout<<"\n Process No. \t Process Size \t Block No. \n";
    for(int i =0; i<p; i++){
       cout << " " << i+1 << " \t\t " << processSize[i] << " \t\t ";
    
    if(allc[i] != -1){
            cout << allc[i] + 1;
           
    }
        else 
            cout << "Not Allocated";
        cout << "\n";    
    }

    
    cout<<" Holes in blocks \n";
    for(int i =0; i<b; i++){
        cout<<" Block : "<< i+1 << "   | Hole   : "<< blockSize[i] << endl;
    }

}

int main()
{
    // int nump, numb;
    // vector<int> blockSize, processSize;
    
    // cout << "Enter the nuber of Memory blocks : ";
    // cin >> numb;

    // for (int i = 1; i <= numb; i++)
    // {
    //     cout << "Enter size of " << i << "th memory block :- ";
    //     int x;
    //     cin >> x;
    //     blockSize.push_back(x);
    // }

    // cout << "Enter the nuber of Process : ";
    // cin >> nump;

    // for (int i = 1; i <= nump; i++)
    // {
    //     cout << "Enter size of " << i << "th Process :- ";
    //     int x;
    //     cin >> x;
    //     processSize.push_back(x);
    // }

    vector<int> p ={ 4,3,2, 4, 8};
    vector<int> b = { 4,2,4,3,8};
    cout<< "        FIRST FIT       \n";
    firstFit(5,b,5,p);
    cout<< "        NEXT FIT       \n";
    nextFit(5,b,5,p);
    cout<< "        BEST FIT       \n";
    bestFit(5,b,5,p);
    cout<< "        WORST FIT       \n";
    worstFit(5,b,5,p);

    return 0;
}