/*
 * HTTP/HTTPS GET v0.3
 * Usage: ./web <host> <path>
 *
 * v0.1: 06/11/17
 *   Initial release
 * v0.2: 06/12/17
 *   Optimize reading content
 * v0.3: 06/12/17
 *   Add https support
 */

/*
struct hostent {
	char        *h_name;
	char        **h_aliases;
	int	        h_addrtype;
	int	        h_length;
	char        **h_addr_list;
struct sockaddr_in {                                                                
    __uint8_t   sin_len;                                                            
    sa_family_t sin_family;                                                         
    in_port_t   sin_port;                                                                                                            
    struct      in_addr sin_addr;                                                       
    char        sin_zero[8];                                                        
};
struct sockaddr {
	__uint8_t	sa_len;
	sa_family_t	sa_family;
	char		sa_data[14];
};
 */
#include <unistd.h>     // close
#include <sys/socket.h> // socket
#include <netdb.h>      // hostent, gethostbyname
#include <arpa/inet.h>  // htons
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <openssl/ssl.h>
using namespace std;

struct URL {
    string protocol;
    string host;
    int    port;
    string path;
};

void usage();
void error(string s);
int read_more(int sockfd, string& response);
template<class T>
void get_response(T sockfd, string& header, string& body);
URL parse_url(string url);

int main(int argc, char** argv) {
    hostent* server;
    sockaddr_in serv_addr;
    int sockfd;
    int i = 0, j = 0, bytes = 0, cur = 0, total = 0;

    string url = "http://google.com";
    if (argc > 1) {
        url = argv[1];
    } else {
        usage();
        exit(1);
    }

    URL s_url       = parse_url(url);
    string protocol = s_url.protocol;
    string host     = s_url.host;
    int port        = s_url.port;
    string path     = s_url.path;

    cout << "* Rebuilt URL to " << protocol << "://" << host << path << endl;

    // server addr and socket addr
    server = gethostbyname(host.c_str());
    if (!server) {
        error("resolve host");
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port   = htons(port);
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    cout << "*   Trying " << inet_ntoa(serv_addr.sin_addr) << "..." << endl;

    // socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr));

    SSL_CTX* ssl_ctx = NULL;
    SSL* conn = NULL;
    // SSL
    if (protocol == "https") {
        SSL_load_error_strings();
        SSL_library_init();
        ssl_ctx = SSL_CTX_new(SSLv23_client_method());
        conn = SSL_new(ssl_ctx);
        SSL_set_fd(conn, sockfd);
        if (SSL_connect(conn) != 1) {
            error("SSL");
        }
    }

	string request;
    request += "GET " + path + " HTTP/1.1\r\n";
    request += "Host: " + host + "\r\n";
    request += "User-Agent: web\r\n";
    request += "Accept: */*\r\n";
    request += "\r\n";

    cur = 0;
    total = request.size();
    do {
        if (conn) {
            bytes = SSL_write(conn, &request[cur], total);
        } else {
            bytes = write(sockfd, &request[cur], total);
        }
        if (bytes < 0) {
            error("request");
        }
        cur += bytes;
    } while (cur < total && bytes > 0);

    i = 0, j = 0;
    while (i < request.size()) {
        j = request.find("\r\n", i);
        if (j == request.npos) {
            j = request.size();
        }
        cout << "> " << request.substr(i, j - i) << endl;
        i = j + 2;
    }

    string header, body;
    if (conn) {
        get_response<SSL*>(conn, header, body);
    } else {
        get_response<int>(sockfd, header, body);
    }

    if (conn) {
        SSL_shutdown(conn);
        SSL_free(conn);
    }
    close(sockfd);

    /*
    ofstream f;
    f.open("test.zip");
    f << body;
    f.close();
    */

    return 0;
}

void usage() {
    printf("Usage: http <host> <path>\n");
    exit(1);
}

void error(string s) {
    s.insert(0, "ERROR: ");
    perror(s.c_str());
    exit(1);
}

int read_more(int sockfd, string& response) {
    string buf(256, 0);
    int bytes = read(sockfd, &buf[0], buf.size());
    if (bytes > 0) {
        response += buf.substr(0, bytes);
    }
    return bytes;
}

int read_more(SSL* conn, string& response) {
    string buf(256, 0);
    int bytes = SSL_read(conn, &buf[0], buf.size());
    if (bytes > 0) {
        response += buf.substr(0, bytes);
    }
    return bytes;
}

template<class T>
void get_response(T conn, string& header, string& body) {
    string response, line, transfer_encoding;
    int i = 1, j = 0, bytes = 0, header_size = 0;
    int content_length = -1, chunked_size = 0;
    // 0 reading header, 1 reading chunked size, 2 reading content
    int reading_state = 0;
    while (true) {
        if (reading_state == 2) {
            while (i < response.size() && i - j < chunked_size + 1) {
                ++i;
            }
        } else {
            while (i < response.size() && (response[i-1] != '\r' || response[i] != '\n')) {
                ++i;
            }
        }
        if (i >= response.size()) {
            if (read_more(conn, response) <= 0) {
                return;
            } else {
                continue;
            }
        }
        if (i == j + 1) {
            // end of header
            reading_state = 1;
            cout << "<" << endl;
            header_size = j = i = i + 1;
            if (content_length >= 0) {
                while (response.size() < header.size() + content_length) {
                    if (read_more(conn, response) <= 0) {
                        return;
                    }
                }
                body = response.substr(header_size);
                cout << body << endl;
                break;
            }
            continue;
        }
        line = response.substr(j, i - j - 1);
        if (reading_state == 0) {
            cout << "< " << line << endl;
            header += line + ";";
            if (content_length < 0 && transfer_encoding.empty()) {
                int pos = line.find("Content-Length");
                if (pos != line.npos) {
                    while (!isdigit(line[pos])) {
                        ++pos;
                    }
                    content_length = stoi(line.substr(pos));
                } else {
                    pos = line.find("Transfer-Encoding");
                    if (pos != line.npos) {
                        while (!isalpha(line[pos])) {
                            ++pos;
                        }
                        transfer_encoding = line.substr(pos);
                    }
                }
            }
        } else if (reading_state == 1) {
            chunked_size = stoi(line, NULL, 16);
            if (chunked_size == 0) {
                break;
            }
            reading_state = 2;
        } else {
            body += line;
            reading_state = 1;
            cout << line << endl;
        }
        // ready for next line
        j = i = i + 1;
    }
}

URL parse_url(string url) {
    URL ret;
    ret.port = -1;

    if (url.substr(0, 7) == "http://") {
        ret.protocol = "http";
        url = url.substr(7);
    } else if (url.substr(0, 8) == "https://") {
        ret.protocol = "https";
        url = url.substr(8);
    }
    
    int pos1 = url.find(":"), pos2 = url.find("/");
    if (pos2 == url.npos) {
        pos2 = url.size();
    }
    if (pos1 == url.npos) {
        pos1 = url.size();
    }

    if (pos2 - pos1 - 1 > 0){
        ret.port = stoi(url.substr(pos1 + 1, pos2 - pos1 - 1));
    }

    ret.host = url.substr(0, min(pos1, pos2));

    if (pos2 < url.size()) {
        ret.path = url.substr(pos2);
    } else {
        ret.path = "/";
    }

    if ((ret.protocol == "http" && ret.port == 443) ||
        (ret.protocol == "http" && ret.port == 80 )) {
        error("Invalid URL");
    }

    if (ret.protocol == "http") {
        ret.port = 80;
    } else if (ret.protocol == "https") {
        ret.port = 443;
    }
    if (ret.port == 80) {
        ret.protocol = "http";
    } else if (ret.port == 443) {
        ret.protocol = "https";
    }

    if (ret.protocol.empty()) {
        ret.protocol = "http";
    }
    if (ret.port < 0) {
        ret.port = 80;
    }

    return ret;
}
