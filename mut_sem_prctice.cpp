#include<bits/stdc++.h> 
using namespace std;

class Mutex{
     // 0 = unlock
     // 1 = lock
    int mutex ;
    int currItemNum;
    int itemNum = 1;
    int consumedItem = itemNum;
    
  

public:
 Mutex(){
        mutex = 0;
        currItemNum = 0;
    }

    void lock(){
        mutex =1;
    }

    void unlock( ) {
        mutex =  0;
    }

void produce(){

    if(mutex == 1){
        cout<<"Thread is busy ... ! \n";
        return;
    }
    else{
         lock();
         cout << "Item " << itemNum << " produced" << "\n";
        currItemNum++;
        itemNum++;


    }
    return;

}


void consume(){
    if(mutex == 1){
        cout<<"Thread is busy ... ! \n";
        return;
    }
    else{

        lock();

        if(currItemNum <= 0){
            cout << "!!! No item available !!!" << "\n";
          unlock();
            return;
        }
         cout << "Item " << itemNum - currItemNum << " consumed" << "\n";
        currItemNum--;
        consumedItem--;
        return;
    }
    
}

void stop_Process(){
    unlock();
    cout<<"Current Process is Stoped....! \n";
    return;
}

 void itemsAvailable(){
        cout << "Total :- " << currItemNum << " items available" << "\n";
        return;
    }

};

class Semaphore{
    int* arr;
    int semaphore;
    int res;
    public:
    Semaphore(int x){
        arr = new int[x];
        for(int i =0; i<x; i++) arr[i] == 0;
        semaphore = 0;
        res = x;
    }
    
void wait(int &x)
{
    int(x>0);
    x--;
}
void signal(int &x)
{
    x++;
}

void produce(){
    if(semaphore < res ){
        arr[semaphore] = 1;
        cout<<"Resource "<< semaphore +1 <<" is Aquired \n";
         signal(semaphore);
    } 
    else{
        cout<<" All Resources are busy.... ! \n";
    }
}

void consume(){
    if( semaphore >= 0){
        arr[semaphore] = 0;
        cout<<"Resource "<< semaphore  <<" is Released \n";
        wait(semaphore);
    }
    else{
        cout << " No item Available \n";
    }
}

void Display(){
    cout<< "Items available = " << semaphore<<endl;
}
};


int main(){
    while(1){
cout<<"Enter Choice \n 1. Mutex \n  2. Semaphore \n";
int ch ; cin>>ch;
if(ch ==1){
     cout << "------------MUTEX--------------" << "\n";  
     Mutex mt;
     bool flag = true;
      while(flag){
        cout << "1. Produce" << "\n";
        cout << "2. Consume" << "\n";
        cout << "3.Stop Current Process" << "\n";
        cout << "4. Items available" << "\n";
        cout << "5. Exit" << "\n";

        int op;
        cout << "Enter your choice :- ";
        cin >> op;

        bool flag = 1;
        switch(op){
            case 1:
            {
                mt.produce();
                break;
            }
            case 2:
            {
                mt.consume();
                break;
            }
            case 3:
            {
                mt.stop_Process();
                break;
            }
            
            case 4:
            {
                mt.itemsAvailable();
                break;
            }
            case 5:
                flag = 0;
                break;
            default:
                cout << "Enter valid input" << "\n";
        }
        if(!flag) break;
    }
}
else{

         cout<<"------------- Semaphore  --------------------"<<endl;
         cout<<"Enter number of resorces :" ;
         int n ; cin>>n;
        Semaphore sem(n);
        bool flag = 1;
       while(flag)
    {
        //  cout<<"Empty"<<n<<"Full"<<sem.get_cnt()<<endl;
         cout<<"Enter your choice \n1.Produce \n 2.Consume \n 3.Display\n 4.Exit"<<endl;
         int x;
         cin>>x;
        switch (x)
        {
        case 1:
            sem.produce();
            
            break;
        case 2:
            sem.consume();
        case 3:
            sem.Display();
            break;
        case 4:
            flag =0;
            break;
        default:
            cout<<"enter valid Choice \n";
            break;
        }
    
    }
}
    }
    return 0;
}