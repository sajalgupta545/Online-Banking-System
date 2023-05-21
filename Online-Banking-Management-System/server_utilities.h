/* Mini Project
  Name: Sajal Gupta
  Roll no: MT2022096 */
  
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "account_handler.h"
#include "macros.h"




int addAccount(struct account account){
	int fd = open("account",O_WRONLY|O_APPEND);
	ssize_t s = write(fd,&account,sizeof(account));
	close(fd);
	if(s>0){printf("Write Success\n");return 1;}
	else return -1;
}
int openAccount(struct account account){
	int result1 = addAccount(account);
	return (result1);
}


void print_all(){
	int fd=fd=open("account",O_RDONLY);
	struct account account;
	while(read(fd,&account,sizeof(account))){
		printAccountDetails(account);
	}
	close(fd);
}

struct account searchByAccountNo(long long int account_no){	
	int fd = open("account",O_RDONLY);
	struct account account={0},answer={0};
	while(read(fd,&account,sizeof(account))){
		if(account.account_no == account_no && account.status>0){
		answer = account;
		break;}
	}
	close(fd);
	return answer;
}
int getRecordNoByUserId(long long int user_id){	
	int fd = open("account",O_RDONLY);
	struct account account={0},acc={0};
	int record_no=-1,i=-1;
	while(read(fd,&account,sizeof(account))){
		i++;
		if(account.user.user_id==user_id){
		record_no=i;
		break;}
	}
	close(fd);
	return record_no;
}
int getRecordNoByAccountNo(long long int account_no){	
	int fd = open("account",O_RDONLY);
	struct account account={0},acc={0};
	int record_no=-1,i=-1;
	while(read(fd,&account,sizeof(account))){
		i++;
		if(account.account_no==account_no){
		record_no=i;
		break;}
	}
	close(fd);
	return record_no;
}

struct account getRecord(int record_no){
	int fd;
	struct account account;
	fd=open("account",O_RDONLY);
	struct flock lock;
	size_t s=0;
	
	off_t off=lseek(fd,(record_no*sizeof(struct account)),SEEK_SET);
	lock.l_type=F_RDLCK;
	lock.l_whence=SEEK_CUR;
	lock.l_start=0;
	lock.l_len=sizeof(struct account);
	lock.l_pid=getpid();
	printf("File Discripter value :: %d, Process id %ld\n",fd,(long)getpid());
	printf("Before Entering To Critical Section\n");
	int i = fcntl(fd,F_SETLKW,&lock);
	if(i!=-1){
		printf("Locking Status :: %d\n",i);
		printf("Entering Critical Section\n");
		s = read(fd,&account,sizeof(struct account));
		lock.l_type = F_UNLCK;
		int u = fcntl(fd,F_SETLK,&lock);
		printf("Exiting CS... Unlocking Status :: %d\n",u);
		}else{
		printf("Lock Not Accquired");
		}
		close(fd);
		return account;
}
int createNewAccount(){
		struct sequence seq;
		int seq_no=readSequence();
		if(seq_no>=0){
			seq.seq_no = seq_no+1;
			seq_no = get_Sequence(seq);
		}	
		if(seq_no>0){
			struct account account= getDetails(seq_no);
			int status = openAccount(account);
			if(status>0){
				printf("Account Created Successfully... Account details are:\n");
				printAccountDetails(account);
				return 1;
			}else{
				printf("Sorry !! Account Creation Failed..\n");
				return -1;
			}
		}else{printf("Sorry !! Account Creation Failed..\n"); return -1;}
}
