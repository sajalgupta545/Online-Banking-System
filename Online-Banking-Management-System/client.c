/* Mini Project
  Name: Sajal Gupta
  Roll no: MT2022096 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <string.h>

#include "request_handler.h"


int main(){
	struct packet request,response={0};
	printf("----------------- WELCOME TO ONLINE BANKING --------------------\n\n\n");
	int enter_choice;
	do{
		printf("Please Enter how do you want to login\nPress\n1- normal user\n2- joint account user\n3- admin\n");
		scanf("%d", &enter_choice);
		if(enter_choice>=1 && enter_choice <= 3){break;}
		else{printf("Please follow instructions correctly\n");}
	}while(enter_choice<1 || enter_choice>3); 
	if(enter_choice == 1){
		printf("ENTER USER ID: \t");
		scanf("%lld",&request.account.user.user_id);
		printf("ENTER PASSWORD: \t");
		scanf(" %10[^\n]",request.account.user.password);
		request.action=GET_USR;
		request.result=-1;
		response = request_to_server(request);
		printf("\nResponse Status :: %d\n",response.result);

		if(request.account.user.user_id == response.account.user.user_id){
			if(strcmp(request.account.user.password,response.account.user.password) == 0){
				printf("LOGIN SUCCESS : Account Details Are\n");
				printf("Weclome User :: %s\n",response.account.user.first_name);
				int choice,ch;
				do{
					printf("Enter Choice\n");
					printf("1.Deposit\n");
					printf("2.Withdraw\n");
					printf("3.Balance Enquiry\n");
					printf("4.Password Change\n");
					printf("5.View details\n");
					printf("6.Exit\n");
					scanf("%d",&choice);

					request_handler(response, choice, 1);

					printf("If You Want To Continue - Press 1 else Press 2\n");
					scanf("%d",&ch);
					if(ch == 2){break;}
				}while(ch==1);
			}else{
				printf("Invalid Credentials\n");
			}
		}else{
			printf("Invalid Credentials\n");
		}
	}
	else if(enter_choice == 2){
		printf("ENTER Joint USER ID: \t");
		scanf("%lld",&request.account.user.user_id);
		printf("ENTER PASSWORD: \t");
		scanf(" %10[^\n]",request.account.user.password);
		
		request.action = GET_USR;
		request.result = -1;
		response = request_to_server(request);
		printf("\nResponse Status :: %d\n",response.result);
		if(request.account.user.user_id==response.account.user.user_id){
			if(strcmp(request.account.user.password,response.account.user.password) == 0){
				printf("LOGIN SUCCESS : Account Details Are\n");
				printf("Weclome Users :: %s \t %s\n",response.account.user.first_name, response.account.user.second_name);
				int choice,ch;
				do{
					printf("Enter Choice\n");
					printf("1.Deposit\n");
					printf("2.Withdraw\n");
					printf("3.Balance Enquiry\n");
					printf("4.Password Change\n");
					printf("5.View details\n");
					printf("6.Exit\n");
					scanf("%d",&choice);

					request_handler(response, choice, 2);

					printf("If You Want To Continue - Press 1 else Press 2\n");
					scanf("%d",&ch);
					if(ch == 2){break;}
				}while(ch==1);
			}else{
				printf("Invalid Credentials\n");
			}
		}else{
			printf("Invalid Credentials\n");
		}
	}else{
		printf("ENTER ADMIN ID: \t");
		scanf("%lld",&request.account.user.user_id);
		printf("ENTER PASSWORD: \t");
		scanf(" %10[^\n]",request.account.user.password);
		request.action=GET_ACC;
		request.result=-1;
		response = request_to_server(request);
		printf("\nResponse Status :: %d\n",response.result);
		if(request.account.user.user_id==response.account.user.user_id){
			if(strcmp(request.account.user.password,response.account.user.password) == 0){
				int choice,ch;
				printf("***********Weclome Admin******\n");
				do{
				printf("Enter Choice\n");
				printf("1.Add New Account\n");
				printf("2.Delete An Account\n");
				printf("3.Modify\n");
				printf("4.Search An Account\n");
				printf("5.Exit\n");
				scanf("%d",&choice);

				admin_handling(response, choice);

				printf("If You Want To Continue - Press 1 else Press 2\n ");
				scanf("%d",&ch);
				if(ch == 2){ break; }
				}while(ch==1);
			}else{
				printf("Invalid Credentials\n");
			}
		}else{
			printf("Invalid Credentials\n");
		}
	}
	return 0;
}
