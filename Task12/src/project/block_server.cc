#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<iostream>
#include <signal.h>
#include <poll.h>


volatile sig_atomic_t flag = 0;
void quit_func(int server_fd){
    flag = 1;
}

int main(){
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
        std::cout<<"Failed to create server socket "<<errno<<std::endl;
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(22222);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (bind(server_fd, (struct sockaddr *) &addr, sizeof(addr)) == -1){
        std::cout<<"Failed to bind server socket "<<errno<<std::endl;
        return 1;
    }
    if (listen(server_fd, SOMAXCONN)==-1){
        std::cout<<"Failed to listen on server socket "<<errno<<std::endl;
        return 1;
    }
    pollfd server{server_fd, POLLIN};
    char buff[500];
    int buff_state;
    std::cout<<"Ready to work"<<std::endl;
    signal(SIGINT, quit_func);
    while(true){
        poll(&server, 1, -1);
        if (flag){
            goto end;
        }
        // std::cout<<"handle new client... "<<std::endl;
        int client_fd = accept(server_fd, nullptr, nullptr); 
        if (client_fd == -1){
               std::cout << "can't add new client"<< std::endl;
        }
        else{
            buff_state = false;
            pollfd client{client_fd, POLLIN|POLLOUT|POLLHUP};
            // std::cout << "new client added successfully"<< std::endl;
            while(true){
                if (flag){
                    close(client.fd);
                    goto end;
                }
                poll(&client, 1, -1);
                if (client.revents == 0) { continue; }
                if (client.revents & POLLIN) {  
                    // int r =  read(client.fd, buff, sizeof(buff));
                    int r = recv(client.fd, buff, sizeof(buff), 0);
                    if (r == 0){
                        close(client.fd);
                        // std::cout<<"client disconnected"<<std::endl;
                        break;
                    }
                    if (r<0){
                        std::cout <<"read err "<< errno<<std::endl;
                    }
                    else
                        buff_state = true;
                }
                if (client.revents & POLLOUT && buff_state) {
                    int w = write(client.fd, buff, sizeof(buff));
                    buff_state = false;
                    if (w<0){
                        std::cout <<"write err "<< errno<<std::endl;
                    }    
                }
                if (client.revents & POLLHUP) { 
                    close(client.fd);
                    // std::cout<<"client disconnected"<<std::endl;
                    break;
                }
            }
        }
               
    }
    end:

    std::cout<<"switched off";
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}