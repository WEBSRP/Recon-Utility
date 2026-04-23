#include "scanner.h"
#include <iostream>
#include <string>
#include "string.h"
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include "netdb.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <errno.h>
#include<iomanip>
using namespace std;



void showBanner() {
    cout << R"(

███╗   ██╗      ███████╗ ██████╗  █████╗ ███╗   ██╗
████╗  ██║      ██╔════╝██╔════╝ ██╔══██╗████╗  ██║
██╔██╗ ██║█████╗███████╗██║      ███████║██╔██╗ ██║
██║╚██╗██║╚════╝╚════██║██║      ██╔══██║██║╚██╗██║
██║ ╚████║      ███████║╚██████╗ ██║  ██║██║ ╚████║
╚═╝  ╚═══╝      ╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝

N-SCAN v1.3
----------------------------------------
Made by   : websrp
LinkedIn  : https://www.linkedin.com/in/websrp/
----------------------------------------

)";
}

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
    int result = connect(clientSocket,(sockaddr*)&serverAddress,sizeof(serverAddress));

    if(result == 0){

    timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    char buffer[1024] = {0};

    int bytes = recv(clientSocket, buffer, sizeof(buffer), 0);

    if(bytes > 0){
        string banner = buffer;

        cout << left
             << setw(10) << port
             << setw(12) << "OPEN"
             << setw(15) << "Connected"
             << setw(25) << banner.substr(0,20)
             << endl;
    }
    else{
        cout << left
             << setw(10) << port
             << setw(12) << "OPEN"
             << setw(15) << "Connected"
             << setw(25) << "No banner"
             << endl;
    }
}
        
        
    else{
    int err = errno;
   

    if(err == ECONNREFUSED){
        cout << left
             << setw(10) << port
             << setw(12) << "CLOSED"
             << setw(15) << "-"
             << setw(30) << "-"
             << endl;
    }
    else if(err == ETIMEDOUT){
        cout << left
             << setw(10) << port
             << setw(12) << "FILTERED"
             << setw(15) << "-"
             << setw(30) << "-"
             << endl;
    }
    else if(err == EINPROGRESS){
        // cout << "Port:" << port << " -> Filtered (Connection Pending)" << endl;
    }
    else if(err == EHOSTUNREACH || err == ENETUNREACH){
        cout << "Port:" << port << " -> Filtered / Unreachable" << endl;
    }
    else{
        cout << "Port:" << port << " -> Unknown (" << err << ")" << endl;
    }
}
        

    

    close(clientSocket);
    return;
    }


    void showProgress(int current, int total) {
    int width = 30;
    float ratio = (float)current / total;
    int pos = ratio * width;

    cout << "\r[";
    for(int i = 0; i < width; i++) {
        if(i < pos) cout << "=";
        else if(i == pos) cout << ">";
        else cout << " ";
    }

    cout << "] " << int(ratio * 100) << "%";
    cout.flush();
}


void scanRange(string target,int start,int end){
    int port;
    cout << left
         << setw(10) << "PORT"
         << setw(12) << "STATE"
         << setw(15) << "STATUS"
         << setw(30) << "BANNER"
         << endl;

cout << "--------------------------------------------------------------" << endl;
   
    
int total = end - start + 1;
int current = 0;

for(int port = start; port <= end; port++){

    connectTarget(target, port);

    current++;
}

showProgress(total, total);
cout << endl;

    
}