#include <iostream>
#include "scanner.h"

using namespace std;

int main(){

    showBanner();

    string target = inputTarget();   // take target input (IP or hostname)

    if(ValidateIP(target) == false){   // if input is NOT a valid IP, try hostname resolution

        string resolved = resolveHostname(target);   // convert hostname to IPv4

        if(!resolved.empty()){   // if resolution successful
            cout<<"Resolved IP: "<<resolved<<endl;
            target = resolved;   // replace hostname with resolved IP
        }
        else{   // if hostname also invalid
            cout<<"Invalid Address !"<<endl;
            return 0;   // stop program
        }
    }   // IMPORTANT: resolution block ends here

    int mode = chooseMode();   // mode selection must happen OUTSIDE resolution block

    if(mode == 1){   // single port scan mode

        int port = inputSinglePort();

        if(port != -1){   // valid port entered

            displayresult(target, port);
            riskInfo(port);

            cout<<"Checking for connections..."<<endl;

            connectTarget(target, port);
        }
        else{
            cout<<"Invalid Port"<<endl;
        }
    }

    else if(mode == 2){   // range scan mode

        int start, end;

        inputPortRangeValues(start, end);

        scanRange(target, start, end);
    }

    else{   // invalid mode selection
        cout<<"Invalid Mode"<<endl;
    }

    return 0;
}