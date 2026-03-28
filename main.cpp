#include<iostream>
#include"scanner.h"
using namespace std;

int main(){
    string target = inputTarget();
    if(ValidateIP(target)==true){
          int port = inputPort();
     
    
        if (port!=-1){
            displayresult(target,port);
            riskInfo(port);
            // cout<<"before connection"<<endl;
            cout<<"Checking for connections...."<< endl;
            //cout<<"After connection"<<endl;
            connectTarget(target,port);
        }else{
            cout<< "Invalid Port"<< endl;
        }

    }else{
        cout << "Invalid IP, Can't proceed further"<< endl;
    
    }
   

    

    return 0;
}