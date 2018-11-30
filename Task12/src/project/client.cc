#include <unistd.h>
#include <sys/socket.h>
#include <vector>
#include <map>
#include <arpa/inet.h>
#include <iostream>
#include <poll.h>
#include <signal.h>
#include <chrono>


int main(int argc, char* argv[]){
    int fd = socket(AF_INET, SOCK_STREAM|SOCK_NONBLOCK, 0);
    struct sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(22222);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    sockaddr any{};
    if (bind(fd, &any, sizeof(any)) == -1){
        std::cout<<"Failed to bind server socket "<<errno<<std::endl; 
        return 1;
    }
    for(;;) {
        int res = connect(fd, (struct sockaddr*)&addr, sizeof(addr));
        std::cout<<"called connect, res="<< res;
        if(res < 0) {
            std::cout<<"    errno= "<<errno;
            switch(errno) {
                case EINPROGRESS:
                    std::cout<<"        in progress "<< std::endl;
                    continue;
                case EALREADY:
                    std::cout<<"        already in progress "<< std::endl;
                    continue;
                case EISCONN:
                    std::cout<<"        is connected "<< std::endl;
                    goto done;
                default:
                    std::cout<<"        something else, bailing out"<< std::endl;
                    return 1;
                    goto done;
            }
        }
    }
    done:
    char buff[500];
    std::vector<pollfd> fds{{fd, POLLIN|POLLOUT}};
    bool waiting_for_answer = false;            
    std::cout<<"Connection established"<<std::endl;
    while(true){
        poll(fds.data(), fds.size(), -1);
        for (pollfd& f : fds) {
            if (f.revents == 0) { continue; }
            if (f.revents & POLLIN){
                int r = read(f.fd, buff, sizeof(buff));
                waiting_for_answer = false;
                if (r<0)
                    std::cout <<"read err "<< errno<<std::endl;
                else{
                    std::cout<< "Server: "<<buff<<std::endl;
                }
             }
            if (f.revents & POLLOUT && !waiting_for_answer) { 
                std::cout << "You: ";
                std::cin >> buff;
                int w = write(f.fd, buff, sizeof(buff));
                if (w<0)
                    std::cout <<"write err "<< errno<<std::endl;    
                else
                    waiting_for_answer = true; 
                
                   
             } 
            if (f.revents & POLLHUP) { 
                close(f.fd);
                f.revents = 0;
             } 
        }
    }
    shutdown(fd, SHUT_RDWR);
    close(fd);
    return 0;
}