#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <chrono>
#include <thread>


#define COOLDOWN_MS 1000

using namespace std;


/*custom headers*/

#include "../headers/tools/bsd.h"


void check_data(size_t data){

    /*check if the result is more than 2 symbols and it's a multiple of 32*/
    if(data > 99 && (data%32==0)){

        cout << "[+] VALID NUMBER! :" << data<< '\n';
    }else{
        cout << "[-] Error! sum is not more than 2 digits and/or is not multiple of 32\n";
        cout << "the sum was : "<< data <<'\n';
    }

}


 
int main()
{
    
    while(1){
 
        /*1024 may be overkill, can be changed later*/
        char buffer[1024] = { 0 };

        /* recieve the data*/
        bsd_reciever bsd_obj;
        int ret = bsd_obj.recieve_data(buffer);

        /*start over after a cooldown, in a case of failure*/
        if(ret){
            this_thread::sleep_for(chrono::milliseconds(COOLDOWN_MS));
            continue;
        }

        /*deserialize the recieved message & check for final conditions*/
        int des_sum = atoi(buffer);

        check_data(des_sum);

    }
  
    return 0;
}