#include <unistd.h>     // close
#include <sys/socket.h> // socket
#include <netinet/in.h>
#include <arpa/inet.h>  // inet_addr, inet_ntoa
#include <netdb.h>      // hostent

#include <cstdio>       // printf
#include <cstring>      // memset, memcpy
#include <cstdlib>      // exit

#include <iostream>     // cout
#include <string>       // string
using namespace std;

int main() {
    sockaddr_in serv_addr;
    int sockfd, port = 5000;
    string ip = "127.0.0.1";
    hostent* host;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cerr << "ERROR: socket: " << sockfd << endl;
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_port        = htons(port);
    // serv_addr.sin_addr.s_addr = inet_addr(ip.c_str()); // INADDR_ANY
    host = gethostbyname("localhost");
    memcpy(&serv_addr.sin_addr.s_addr, host->h_addr, host->h_length);

    // client use connect:
    // connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr));
    bind(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr));
    if (listen(sockfd, 10) < 0) {
        cerr << "ERROR: listen" << endl;
        exit(1);
    }

    cout << "Listening at " << inet_ntoa(serv_addr.sin_addr) << " port " << port << endl;
    while (true) {
        string buf(256, 0);
        sockaddr_in client_addr;
        socklen_t len;
        int clientfd = accept(sockfd, (sockaddr*)&client_addr, &len);
        cout << "Accept: " << inet_ntoa(client_addr.sin_addr) << endl;
        read(clientfd, &buf[0], buf.size());
        cout << buf << endl;
        string body = "<h1>Hello, it works!</h1>";
        buf = "HTTP/1.1 200 OK\r\nContent-Length: ";
        buf += to_string(body.size()) + "\r\n\r\n" + body;
        write(clientfd, &buf[0], buf.size());
        close(clientfd);
    }
    close(sockfd);

    return 0;
}
