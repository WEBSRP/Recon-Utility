#include<iostream>
#include"scanner.h"
using namespace std;

int main(){

    string target = inputTarget();

    if(ValidateIP(target)==false){

        string resolved= resolveHostname(target);
        if (resolved != ""){
            cout << "Resolved IP:"<<resolved<<endl;
            target = resolved;

        }else{
            cout<<"Invalid Address !"<<endl;
            return 0;
        }

        int mode = chooseMode();

        if(mode == 1){

            int port = inputSinglePort();

            if(port != -1){
                displayresult(target,port);
                riskInfo(port);
                cout<<"Checking for connections..."<<endl;
                connectTarget(target,port);
            }
            else{
                cout<<"Invalid Port"<<endl;
            }

        }
        else if(mode == 2){

            int start,end;

            inputPortRangeValues(start,end);

            scanRange(target,start,end);

        }
        else{
            cout<<"Invalid Mode"<<endl;
        }

    }
    else{
        cout<<"Invalid IP, Can't proceed further"<<endl;
    }

    return 0;
}