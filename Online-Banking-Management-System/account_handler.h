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
#include <unistd.h>

#include "structure_utilities.h"

void printAccountDetails(struct account account){
	if(account.user.user_type == 'a'){
		printf("Welcome to admin\n");
		printf("Admin ID: %lld\n", account.user.user_id);
		printf("Admin password: %s\n", account.user.password);
		return;
	}
	if(account.account_type == 'j'){
		printf("****************Welcome to  %s and %s joint account******************\n",account.user.first_name, account.user.second_name);
	}
	else{
		printf("****************Welcome to  %s Personal account******************\n",account.user.first_name);
	}
    printf("Account_No\t :: %lld\n", account.account_no);
    printf("User_Id\t\t :: %lld\n", account.user.user_id);
    printf("Password\t :: %s\n", account.user.password);
	printf("Email\t\t :: %s\n",account.user.email);
	if(account.account_type=='j'){
        printf("Name\t\t :: %s\nName\t\t :: %s\n",account.user.first_name,account.user.second_name);
    }
	else{
        printf("Name\t\t :: %s\n",account.user.first_name);
    }
    printf("City \t\t :: %s\n", account.user.city);
    printf("State \t\t :: %s\nCountry \t :: %s\n", account.user.state,account.user.country);
    printf("Mobile no \t :: %lld\nPin code \t :: %lld\n", account.user.mobile_no,account.user.pin_code);
	printf("Sequence No \t :: %d\nBalance \t :: %lf\nStatus \t\t :: %d\n",account.seq_no,account.balance,account.status);
}
long long int generateAccountNo(){
	srand(time(0));
 	long long int random=rand()%10000000;
	return random;
}

long long int generateUserID(){
	srand(time(0));
 	long long int random=rand()%10000000;
	return random;
}

int readSequence(){
	int fd;
	size_t s;
	fd = open("sequence",O_RDWR);
	struct sequence ds;
	struct flock lock;
	lock.l_type=F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=0;
	lock.l_len=0;
	lock.l_pid=getpid();
	int i=fcntl(fd,F_SETLKW,&lock);
	if(i!=-1){
		s = read(fd,&ds,sizeof(ds));
		lock.l_type = F_UNLCK;
		int u = fcntl(fd,F_SETLK,&lock);
	}
	close(fd);
	if(s<=0){
		ds.seq_no = 1;
		write(fd, &ds, sizeof(ds));
	}
	return ds.seq_no;
}

int get_Sequence(struct sequence ds){
	int fd;
	size_t s;
	fd=open("sequence",O_WRONLY);
	struct flock lock;
	lock.l_type=F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=0;
	lock.l_len=0;
	lock.l_pid=getpid();
	int i=fcntl(fd,F_SETLKW,&lock);
	if(i!=-1){
		s=write(fd,&ds,sizeof(ds));
		lock.l_type=F_UNLCK;
		int u=fcntl(fd,F_SETLK,&lock);
		close(fd);
	}
	if(s>0)return ds.seq_no;
	else return -1;
}

struct account getDetails(int seq_no){
		struct account account;
		printf("------------------------- Enter User Details --------------------------\n\n");
		account.account_no = generateAccountNo();
		account.seq_no=seq_no;
		account.status=1;
		if(seq_no == -1){
			account.user.user_type = 'a';
			account.user.user_id = generateUserID();
			printf("Enter password\n");
			scanf(" %10[^\n]", account.user.password);
			return account;
		}
		struct user user;
			while(1){
                 printf("Enter Account Type\nc - Current Account\ns - Saving Account\nj - Joint Account\n");
				 scanf(" %c", &account.account_type);
                 if(account.account_type=='c'||account.account_type=='s'||account.account_type=='j'){break;}
			}
		if(account.account_type=='j'){
			printf("Enter First User Name\n");
			scanf(" %20[^\n]",user.first_name);
			printf("Enter Second User Name\n");
			scanf(" %20[^\n]",user.second_name);
		}else{
			printf("Enter User Name\n");
			scanf(" %20[^\n]",user.first_name);
		}
		user.user_id = generateUserID();
		printf("Enter Password\n");
		scanf(" %10[^\n]",user.password);
		printf("Enter City\n");
		scanf(" %10[^\n]",user.city);
		printf("Enter State\n");
		scanf(" %10[^\n]",user.state);
		printf("Enter Country\n");
		scanf(" %10[^\n]",user.country);
		printf("Enter Pin Code\n");
		scanf("%lld",&user.pin_code);
		printf("Enter Mobile No\n");
		scanf("%lld",&user.mobile_no);
		printf("Enter Email Id\n");
		scanf(" %50[^\n]",user.email);
		if(seq_no == -1){
			user.user_type = 'a';
		}else if(account.account_type == 'j'){
			user.user_type = 'j';
		}
		else{
			user.user_type = 'n';
		}
		account.user = user;
		return account;
}

int updateRecord(struct account account,int record_no){
	int fd = open("account",O_WRONLY);
	struct flock lock;
	size_t s=0;
	off_t off = lseek(fd,(record_no*sizeof(struct account)),SEEK_SET);
	lock.l_type=F_WRLCK;
	lock.l_whence=SEEK_CUR;
	lock.l_start=0;
	lock.l_len=sizeof(struct account);
	lock.l_pid=getpid();
	printf("File Discripter value :: %d, Process id %ld\n",fd,(long)getpid());
	printf("Before Entering To Critical Section\n");
	int i=fcntl(fd,F_SETLKW,&lock);
	if(i!=-1){
		printf("Locking Status :: %d\n",i);
		printf("Entering Critical Section\n");
		s=write(fd,&account,sizeof(struct account));
		lock.l_type=F_UNLCK;
		int u=fcntl(fd,F_SETLK,&lock);
		printf("Exiting CS... Unlocking Status :: %d\n",u);
	}else{
		printf("Lock Not Accquired");
	}
		close(fd);
		return s;
}
struct account getNewAccountDetails(){
	struct sequence seq;
	struct account account={0};
	int seq_no = readSequence();
	if(seq_no>=0){
		seq.seq_no = seq_no+1;
		seq_no = get_Sequence(seq);
	}	
	if(seq_no>0){
		account= getDetails(seq_no);
	}
	return account;
}
