#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define WR 1
#define RD 0
int main(int argc,char* argv[]){
    int pipe_p_to_c[2];
    int pipe_c_to_p[2];
    char buf;
    pipe(pipe_p_to_c);
    pipe(pipe_c_to_p);
    if(fork()==0){//child
        close(pipe_p_to_c[WR]);
        close(pipe_c_to_p[RD]);
        if(read(pipe_p_to_c[RD],&buf,1)!=1){
            fprintf(2,"child read error\n");
            exit(1);
        }
        fprintf(1,"%d: received ping\n",getpid());
        if(write(pipe_c_to_p[WR],&buf,1)!=1){
            fprintf(2,"child write error\n");
            exit(1);
        }
        close(pipe_p_to_c[RD]);
        close(pipe_c_to_p[WR]);
    }
    else{//parent
        close(pipe_p_to_c[RD]);
        close(pipe_c_to_p[WR]);
        if(write(pipe_p_to_c[WR],&buf,1)!=1){
            fprintf(2,"parent write error\n");
            exit(1);
        }
        if(read(pipe_c_to_p[RD],&buf,1)!=1){
            fprintf(2,"parent read error\n");
            exit(1);
        }
        fprintf(1,"%d: received pong\n",getpid());
        close(pipe_p_to_c[WR]);
        close(pipe_c_to_p[RD]);
    }
    exit(0);
}
