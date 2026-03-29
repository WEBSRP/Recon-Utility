#include"scanner.h"
#include<iostream>
#include"string.h"
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
using namespace std;

string inputTarget(){
    string target;
    cout << "Enter the target:";
    cin >> target;
    return target;
}

int inputSinglePort(){
    int port;

    cout<<"Enter Port :";

    cin >> port;

    if(cin.fail()){
        cin.clear();
        cin.ignore(1000,'\n');
        return -1;
    }

    if(port < 1 || port > 65535){
        return -1;
    }

    return port;
}

void inputPortRangeValues(int &start, int &end){
    
    cout<<"Enter Starting Port:";
    cin>> start;
    cout<<"Enter Ending Port:";
    cin >> end;
    

}

int chooseMode(){
    int mode;
    int p;
    
    cout<<"1.Single port Scan"<<endl;
    cout<<"2.Range of port Scan"<<endl;
    cout<<"Choose Mode:";
    cin >> mode;
  return mode ;
} 

// void protocolinfo(int port){
//      if(port ==80){
//         cout<< "Protocol Used: HTTP"<< endl;
//         cout<< "Security note: webservice exposed"<<endl;
//     }else if(port == 21){
//         cout<< "Protocol Used: FTP"<< endl;
//         cout<< "Security note: File Transfer Protocol exposed"<<endl;
//         cout<< "Hint:Anonymous login maybe enabled"<< endl;
//     }else if(port==22){
//         cout<< "Protocol Used: SSH"<< endl;
//         cout<< "Security note: SSH exposed"<<endl;
//         cout<< "Hint:SSH Brute force"<< endl;
//     }else if(port == 23){
//         cout<< "Protocol Used: telnet"<< endl;
//         cout<< "Security note: telnet exposed"<<endl;
//         cout<< "Hint:Sends Plaintext"<< endl;
//     }else if(port==443){
//         cout<< "Protocol Used: HTTPS"<< endl;
//         cout<< "Security note: webservice exposed"<<endl;
//     }else{
//         cout<< "Protocol Used: Unknown commmon service"<<endl;
//     }



//     if(port >=1 && port<=1024){
//         cout << port <<"-> Well known port"<< endl;
//     }else if(port >=1025 && port<= 49151){

//         cout<<port<< "->Registered Port"<< endl;
//     }else{
//         cout <<port<< "->Dynamic port"<< endl;
//     }


//}

void riskInfo(int port){
    if(port==22){
        cout<<"Medium risk"<< endl;
    }else if(port == 80){
        cout<<"Medium risk"<< endl;
    }else if(port == 443){
        cout<<"low risk"<< endl;
    }else if(port == 21){
        cout<<"High risk"<< endl;
    }else if(port == 23){
        cout<<"High risk"<< endl;
    }else{
        cout<<"Unknown risk level"<<endl;
    }
}
void displayresult(string target,int port){
    cout << "\nTarget:"<< target << endl;
    cout<< "Port:"<< port << endl;
    // protocolinfo(port);  
}

bool ValidateIP(string target){
    int dot=0;
    string part="";

    for( char c : target){
        if(!(isdigit(c) || c=='.')){
            return false;
        }
        if(c == '.'){
            if(part==""|| stoi(part)>255){
                return false;
            }

            part="";
            dot++;

        }else{
            part +=c;

        }
    }if(dot!=3){
        return false;
    }

    if(part=="" || stoi(part)>255){
        return false;
    }
    return true;
}

void connectTarget(string target,int port){

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress={};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    inet_pton(AF_INET, target.c_str(), &serverAddress.sin_addr);

    if(connect(clientSocket,(sockaddr*)&serverAddress,sizeof(serverAddress))==0){
        cout<<"Connection successful"<<endl;
        char buffer[1024] = {0};
        recv(clientSocket, buffer, sizeof(buffer), 0);
        cout<<"Banner: "<<buffer<<endl;
    }
    else{
        cout<<"Connection failed"<<endl;
    }
    // cout << "Trying to connect ....."<< endl;

    close(clientSocket);
}


void scanRange(string target,int start,int end){

    for(int port = start; port <= end; port++){

        connectTarget(target,port);

    }
}