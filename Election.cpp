#include<bits/stdc++.h>
using namespace std;
// we define MAX as the maximum number of processes our program can simulate
// we declare array pStatus[MAX] to store the process status; 0 for dead and 1 for alive
// we declare n as the number of processes
// we declare coordinator to store the winner of election

#define MAX 20

int pStatus[MAX],n,coordinator;

void bully();
void ring();
void display();

int main(){
    int choice;
    cout<<"Enter number of processes: "<<endl;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cout<<"Enter process "<<i<< " is alive or not(0/1)"<<endl;
        cin>>pStatus[i];
        if(pStatus[i]) coordinator=i;
    }
    display();
    do{
        cout<<"----------------------------------"<<endl;
        cout<<"1.Bully\n2.Ring\n3.Display\n4.Exit"<<endl;
        cout<<"----------------------------------\n\n"<<endl;
        cout<<"Enter your choice: "<<endl;
        cin>>choice;
        switch(choice){
            case 1:
                   bully();
                   break;
            case 2:
                   ring();
                   break;
            case 3:
                   display();
                   break;
            case 4:
                   exit(1);
                   break;
        }
    }while(choice!=4);
    return 0;
}

void display(){
    cout<<"--------------------------------------"<<endl;
    cout<<"Process: ";
    cout<<"\t";
    for(int i=1;i<=n;i++)
    {
        cout<<i<<"\t";
    }
    cout<<endl;
    cout<<"Alive:  \t";
    for(int i=1;i<=n;i++)
    {
        cout<<pStatus[i]<<"\t";
    }
    cout<<"\n----------------------------------------\n";
    cout<<"Coordinator is: "<<coordinator<<endl;
}

void bully(){
    int schoice,crash,activate,gid,flag,subcoordinator;
    do{
        cout<<"--------------------------------------"<<endl;
        cout<<"1.Crash\n2.Activate\n3.Display\n4.Exit\n";
        cout<<"--------------------------------------"<<endl;
        cout<<"Enter your choice: "<<endl;
        cin>>schoice;
        switch(schoice){
        case 1:
               //we manually crash a process to check if our algorithm is able to elect a new coordinator or not
               cout<<"Enter process to crash: "<<endl;
               cin>>crash;
               //if process is alive, set its status to dead
               if(pStatus[crash]) pStatus[crash]=0;
               else cout<<"Process "<<crash<<" is already dead"<<endl;
               do{
                //enter another process to initiate the election
                cout<<"Enter election generator id: "<<endl;
                cin>>gid;
                if(gid==coordinator||pStatus[gid]==0) cout<<"Enter a valid election generator id!"<<endl;
               }while(gid==coordinator||pStatus[gid]==0);
               flag=0;
               //if the coordinator has crashed, we need to elect another coordinator
               if(crash==coordinator)
               {
                //the election generator id will send an election message to all the higher ups..
                for(int i=gid+1;i<=n;i++)
                {
                    cout<<"Message is sent from "<<gid<<" to "<<i<<endl;
                    //if the higher process is alive, then it will respond
                    if(pStatus[i]){
                        subcoordinator=i;
                        cout<<"Response is sent from "<<i<<" to "<<gid<<endl;
                        flag=1;
                    }
                }
                //the highest responsding process is selected as coordinator
                if(flag==1) coordinator=subcoordinator;
                //if no higher process responds election generator itself becomes the coordinator
                else coordinator=gid;
               }
               display();
               break;
        case 2:

             cout<<"Enter process id to be activated: "<<endl;
                   cin>>activate;
                   if(!pStatus[activate]){
					 pStatus[activate]=1;
					 coordinator = max(coordinator,activate);
				   }
                   else cout<<"Process "<<activate<<" is already alive!"<<endl;break;
            //    cout<<"Enter the process ID to be activated: ";
            //    cin>>activate;
            //    //if process is dead, we make it alive
            //    if(!pStatus[activate]) pStatus[activate]=1;
            //    else cout<<"Process "<<activate<<" is already alive!"<<endl;
            //    //if the process activated is a higher process it becomes the coordinator
            //    if(activate==n) coordinator=n; break;
            //    flag=0;
            //    //else the process activated sends a message to all higher process
            //    for(int i=activate+1;i<=n;i++)
            //    {
            //     cout<<"Message from "<<activate<<" to "<<i<<endl;
            //     if(pStatus[i])
            //     {
            //         subcoordinator=i;
            //         cout<<"Response from "<<i<<" to "<<activate<<endl;
            //         flag=1;
            //     }
            //    }
            //    if(flag==1) coordinator=subcoordinator;
            //    //if no higher process responds , activated process is elected as coordinator
            //    else coordinator=activate;
            
               display();
               break;
        case 3:
               display();
               break;
        case 4:break;
    }

  }while(schoice!=4);
}


void ring(){
    int tchoice,crash,flag,activate,gid,subcoordinator;
	vector<int> tknlist;

    do{
        cout<<"--------------------------------------"<<endl;
        cout<<"1.Crash\n2.Activate\n3.Display\n4.Exit\n";
        cout<<"--------------------------------------"<<endl;
        cout<<"Enter your choice: "<<endl;
        cin>>tchoice;
        switch(tchoice){
            case 1:
                   cout<<"Enter process to be crashed: "<<endl;
                   cin>>crash;
                   //if the process entered is alive,we crash it
                   if(pStatus[crash]) pStatus[crash]=0;
                   else cout<<"Process "<<crash<<" is already dead!"<<endl;
                   do{
                    cout<<"Enter the election generator id: "<<endl;
                    cin>>gid;
                    if(gid==coordinator || pStatus[gid] == 0){
                        cout<<"Enter valid eleciton generator id!"<<endl;
                    }
                   }while(gid==coordinator || pStatus[gid] == 0);
                   //if the coordinator crashed,elect new coordinator
                   if(crash==coordinator){
                    //the election generator id will send message to higher process for election
                    subcoordinator = gid;

					int s = gid;
					int r = gid+1;
					while(r != gid){
						if(r == 0){
							r++;
							continue;
						}
						if(pStatus[r]){
							tknlist.push_back(s);
							cout << "Election message sent from " << s << ": #Msg" <<r << endl;
							subcoordinator = max(subcoordinator,s);
							s = r; r = (r+1)%n;
							cout<<"Tokent list received : \n";
							for(auto x : tknlist){
								cout<<x<<" ";

						}
						cout<<endl;
					}
					else r = (r+1)%n;
					}
					if(r == gid && pStatus[s]){
							cout << "Election message sent from " << s << ": #Msg" <<r << endl;
							subcoordinator = max(subcoordinator,s);
							tknlist.push_back(s);
							cout<<"Tokent list received : \n";
							for(auto x : tknlist){
								cout<<x<<" ";
							}
							cout<<endl;



					}
                    coordinator=subcoordinator;
					tknlist.clear();
                   }
                   display();
                   break;
            case 2:
                   cout<<"Enter process id to be activated: "<<endl;
                   cin>>activate;
                   if(!pStatus[activate]){
					 pStatus[activate]=1;
					 coordinator = max(coordinator,activate);
				   }
                   else cout<<"Process "<<activate<<" is already alive!"<<endl;break;
                //    subcoordinator=activate;
                //    for(int i=0;i<n+1;i++)
                //    {
                //     int pid=(i+activate)%(n+1);
                //     if(pid!=0)
                //     {
                //         if(pStatus[pid]&&subcoordinator<pid){
                //             subcoordinator=pid;
                //         }
                //         cout << "Election message sent from " << pid << ": #Msg" << subcoordinator << endl;
                //     }
                //    }
				
						
				display();
				
                   break;
            case 3:
                   display();
                   break;
            case 4:break;

        }

    }while(tchoice!=4);
}
