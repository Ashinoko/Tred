#include <iostream>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>


/*custom headers*/


#include "../headers/tools/bsd.h"

using namespace std;


int bsd_sender::send_data(char *msg,int port){

    /*socket address & descriptions struct*/
    struct sockaddr_in address;

    
    int opt;

    /*listening and connection file desctriptors*/
    int server_fd, new_socket;

    int addrlen = sizeof(address);
    opt = 1;

    /* buffer for reading the okay signal of client*/
    char buffer[1024] = { 0 };

    /*Creating socket file descriptor*/
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET,
                SO_REUSEADDR | SO_REUSEPORT, &opt,
                sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    /* attaching socket to the port 8080 */

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    /* binding the file descriptor to the address*/
    if (bind(server_fd, (struct sockaddr*)&address,
            sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    /*listening on the server file descriptor for connections*/
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket
        = accept(server_fd, (struct sockaddr*)&address,
                (socklen_t*)&addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    /*reading the okay from client*/
    int ret = read(new_socket, buffer, 1024);
    cout << buffer << '\n';

    /*sending the data*/


    send(new_socket, msg, strlen(msg), 0);
    cout << "[+] message sent\n";

    /* closing the connected socket */
    close(new_socket);
    /* closing the listening socket */
    shutdown(server_fd, SHUT_RDWR);
    return 0;

}
