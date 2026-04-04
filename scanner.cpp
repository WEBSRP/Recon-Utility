#include"scanner.h"
#include<iostream>
#include"string.h"
#include<sys/socket.h>
#include<sys/time.h>
#include<arpa/inet.h>
#include"netdb.h"
#include<unistd.h>
#include"error.h"
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



string resolveHostname(string target){
    struct hostent *host=gethostbyname(target.c_str());
    if(host == NULL){
        return " ";
    }
    struct in_addr **addr_list = (struct in_addr**) host ->h_addr_list;
    if(addr_list[0] != NULL){
        return inet_ntoa(*addr_list[0]);

    }

    return "";
}

void connectTarget(string target,int port){

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct timeval timeout;
    timeout.tv_sec=0;
    timeout.tv_usec=500000;

    setsockopt(clientSocket, SOL_SOCKET,SO_RCVTIMEO,&timeout , sizeof(timeout));
    setsockopt(clientSocket, SOL_SOCKET,SO_SNDTIMEO,&timeout , sizeof(timeout));


    sockaddr_in serverAddress={};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    inet_pton(AF_INET, target.c_str(), &serverAddress.sin_addr);

    if(connect(clientSocket,(sockaddr*)&serverAddress,sizeof(serverAddress))==0){
        cout<<"Port:"<<port<<" ->Open"<<endl;
    
        char buffer[4096] = {0};

        if (port ==80||port==8080){
           send(clientSocket, "HEAD / HTTP/1.0\r\n\r\n", 18, 0); 
        }
        int byte = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (byte > 0){
            cout<<"Banner: "<<buffer<<endl;
        }
        cout<<"------------------------"<<endl;
        }
    else{
        if(errno == ETIMEDOUT){
               cout<<"Filtered"<<endl;
            }
          else if(errno == ECONNREFUSED){
               cout<<"Closed"<<endl;
            }
            else{
                cout<<"Unknown / Possibly Filtered"<<endl;
                }
        }
        

    

    close(clientSocket);
    return;
    }
        
    
        


void scanRange(string target,int start,int end){

    for(int port = start; port <= end; port++){

        connectTarget(target,port);

    }
}