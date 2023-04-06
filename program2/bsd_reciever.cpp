#include <iostream>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>



/*custom headers*/


#include "../headers/tools/bsd.h"

using namespace std;


int bsd_reciever::recieve_data(char *buffer, int port){


    struct sockaddr_in serv_addr;/*server address and desc struct*/

    int client_fd;/* client side file descriptor */

    int sock = 0; /*connecting socket file descriptor*/
    


    /*making the socket*/
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {

        cout << "\n[-] Error in Socket Creation, trying again...\n" ;

        return -1;
    }

    /*asiging the port (default 8080)*/
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {

        cout << "\n[-] Error in finding the address,  trying again... \n" ;
            
        return -1;
    }
    


    /*trying to connect to other server, this will fail if the other is down
    the program  will try again after some cooldown(which is const variable)*/
    if ((client_fd
        = connect(sock, (struct sockaddr*)&serv_addr,
                sizeof(serv_addr)))
        < 0) {
        
        return -1;
    }
    
    /*sending cinfirmation in the case of success*/
    send(sock,"Okay from client" , strlen("Okay from client"), 0);

    /*client file descriptor is not needed anymore, which is need to be closed*/   
    close(client_fd);


    /*read in chunks of 1024 bytes until there is nothing left to read*/
    int ret = 0;

    ret = read(sock, buffer, sizeof(buffer));

    /*0 is successful return*/
    return 0;    
}
