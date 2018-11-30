#include <unistd.h>
#include <sys/socket.h>
#include <vector>
#include <map>
#include <arpa/inet.h>
#include <poll.h>
#include<iostream>
#include <signal.h>


volatile sig_atomic_t flag = 0;
void quit_func(int server_fd){
    flag = 1;
}


int main(){
    int server_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
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
    std::vector<pollfd> fds{{server_fd, POLLIN}};
    std::map<int, char[500]> buffs;
    std::map<int, bool> buff_states;
    std::cout<<"Ready to work"<<std::endl;
    signal(SIGINT, quit_func);
    while(true){
        if (flag){
            break;
        }
        poll(fds.data(), fds.size(), -1);
        for (pollfd& f : fds) {
            if (f.revents == 0) { continue; }
            if (f.fd == server_fd){
                // std::cout<<"handle new client... "<<std::endl;
                int client_fd = accept4(server_fd, 0, 0, SOCK_NONBLOCK); 
                if (client_fd == -1){
                //    std::cout << "can't add new client"<< std::endl; 
                }
                else{
                    fds.push_back({client_fd, POLLIN|POLLOUT|POLLHUP});
                    buff_states[client_fd] = false;
                    // std::cout << "new client added successfully"<< std::endl;
                    break;
                }
            }
            else{
                if (f.revents & POLLIN) {
                    // int r =  read(f.fd, buffs[f.fd], sizeof(buffs[f.fd]));
                    int r = recv(f.fd, buffs[f.fd], sizeof(buffs[f.fd]),0);
                    if (r==0){
                        close(f.fd);
                        f.revents = 0;
                        std::cout<<"client disconnected"<<std::endl;
                    }
                    if (r>0)
                        buff_states[f.fd] = true;       
                    // std::cout<<buff_states[f.fd]<<" client: "<<f.fd<<" message: "<< buffs[f.fd]<<std::endl;
                }
                if (f.revents & POLLOUT && buff_states[f.fd]) {
                    int w = write(f.fd, buffs[f.fd], sizeof(buffs[f.fd]));
                    buff_states[f.fd] = false;
                    // std::cout <<buff_states[f.fd]<<" try to send "<< buffs[f.fd]<<std::endl;
                    // if (w<0){
                    //     std::cout <<"write err "<< errno<<std::endl;
                        
                    // }
                }
                if (f.revents & POLLHUP) { 
                    close(f.fd);
                    f.revents = 0;
                    std::cout<<"client disconnected"<<std::endl;
                }
            }
        }
    }
    std::cout<<"switched of";
    shutdown(server_fd, SHUT_RDWR);
     for (pollfd& f : fds) 
        if (f.revents!=0)
            close(f.fd);
    return 0;
}