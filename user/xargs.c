#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int
main(int argc,char* argv[]){
    char buf;
    char tmp[MAXARG][100];
    char* p;
    int exec_argc=argc-1;
    char* exec_argv[MAXARG];
    for(int i=0;i<exec_argc;++i){
    	exec_argv[i]=argv[i+1];
    }
    int j=0;
    p=tmp[j];
    while(read(0,&buf,1)==1){
    	if(buf!=' '&&buf!='\n'){//usual char
	    *p=buf;
	    p++;
	}// end if
	else if(buf==' '){//get one arg
	    *p=0;
	    exec_argv[exec_argc++]=tmp[j];
	    p=tmp[++j];
	}// end if
	else if(buf=='\n'){//exec one order
	    if(fork()==0){
		*p=0;
		exec_argv[exec_argc++]=tmp[j];
	    	exec_argv[exec_argc]=0;
		exec(exec_argv[0],exec_argv);
		exit(0);
	    }

    	    else{
	    	wait(0);
		exec_argc=argc-1;
		j=0;
		p=tmp[j];
	    }
	}// end if
    }// end while
    exit(0);
}
