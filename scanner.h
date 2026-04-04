#include <iostream>
using namespace std;

string inputTarget();
string resolveHostname(string target);
int inputSinglePort();
void inputPortRangeValues(int &start, int &end);
int chooseMode();
bool ValidateIP(string target);
void protocolinfo(int port);
void riskInfo(int port);
void displayresult(string target,int port);
void connectTarget(string target,int port);
void scanRange(string target,int start,int end);
