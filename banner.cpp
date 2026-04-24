#include"banner.h"
#include<iostream>
#include<string>
#include<cstring>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

using namespace std;

string grabHTTPbanner(const string& ip , int port){
    
    int sock=socket(AF_INET,SOCK_STREAM,0);
   
    timeval timeout;
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;

setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    if(sock<0){
    return "Socket Creating Failed";
    }

    sockaddr_in target{};

    target.sin_family=AF_INET;//IPV4 Family
    target.sin_port=htons(port);//convert port into network type byte 

    // cout << "IP received = [" << ip << "]" << endl;

    if(inet_pton(AF_INET,ip.c_str(),&target.sin_addr)<=0){
        
        close(sock);
        return "Invalid IP";
    }
    // cout << "IP converted" << endl;
    if(connect(sock, (sockaddr*)&target, sizeof(target)) < 0){
    close(sock);
    return "Connection failed";
}

    string request =
        "HEAD / HTTP/1.1\r\n"
        "Host: " + ip + "\r\n"
        "Connection: close\r\n\r\n";

    int sent = send(sock, request.c_str(), request.size(), 0);
            


    
  
    string response;
    char buffer[4096];

    while (true)
    {
            int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);

            if (bytes <= 0)
                    break;

            buffer[bytes] = '\0';
        response += buffer;
}

    close(sock);
    if(response.empty())
    return "No response";


    // cout << "\nResponse size = " << response.size() << endl;
    // cout << "\nRAW RESPONSE:\n" << response << endl;
    // cout << "\nRAW RESPONSE:\n" << response << endl;

    size_t serverPos = response.find ("Server:");

    if (serverPos != string::npos ){
        size_t end= response.find("\r\n",serverPos);
        return response.substr(serverPos,end-serverPos);
    }

    return "Server Header not found";



    
}


