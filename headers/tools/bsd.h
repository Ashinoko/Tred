#ifndef BSD_H
#define BSD_H

class bsd_server{

    protected:

    int port;

    public:

};

/*server class*/
class bsd_sender: public bsd_server{

    public:
        int send_data(char *msg,int port = 8080);
};

/*client class*/
class bsd_reciever: public bsd_server{


    public:
        int recieve_data(char *msg,int port = 8080);
};

#endif