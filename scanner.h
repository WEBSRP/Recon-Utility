#include <iostream>
using namespace std;

string inputTarget();
int inputPort();
bool ValidateIP(string target);
void protocolinfo(int port);
void riskInfo(int port);
void displayresult(string target,int port);
void connectTarget(string target,int port);