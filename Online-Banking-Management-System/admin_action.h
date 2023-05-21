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

#include "macros.h"
#include "account_handler.h"

struct data{
  int action;
  int result;
  char *result_msg;
};

struct packet request_to_server(struct packet request_packet){
	struct packet response_packet={0};
	struct sockaddr_in server,client;
	struct data d;
	int sd=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(13980);
	int result=connect(sd,(const struct sockaddr *)(&server),sizeof(server));
	if(result<0){printf("connection status :: %d\t\n",result);}
	ssize_t s=write(sd,&request_packet,sizeof(struct packet));
	ssize_t r=read(sd,&response_packet,sizeof(struct packet));
	close(sd);
	return response_packet;
}

int admin_handling(struct packet response, int choice){
    switch(choice){
			case ADD:{
				struct account account = getNewAccountDetails();
				if(account.account_no>0){
				struct packet cur_request,cur_response={0};
				cur_request.action = CREATE;
				cur_request.result = -1;
				cur_request.account= account;
				cur_response=request_to_server(cur_request);
                    if(response.result>0){
                        printf("Process Success !! New Account Successfully Created\nDetails Are..\n");
                        printAccountDetails(cur_response.account);
                    }
                    else{
                        printf("Sorry !! Process Failed. Account Creating Failed\n");
                    }
				}
				else{printf("Sorry !! Account Creating Failed \n");}
				break;}
			case DELETE:{
				struct packet cur_request,cur_response={0};
				printf("Enter Account No To Delete\n");
				scanf("%lld",&cur_request.account.account_no);
				cur_request.action=GET_ACC;
				cur_request.result=-1;
				cur_response=request_to_server(cur_request);
				if(cur_response.result>0&&cur_response.account.status>0){
					cur_response.account.status=0;
					cur_request=cur_response;
					cur_request.action=UPDATE;
					cur_request.result=-1;
					cur_response=request_to_server(cur_request);
					if(cur_response.result>0){
					printf("Process Success !! Account Deleted Successfully\n");
					}
					else{printf("Sorry !! Unable To Delete Account For Account No %lld\n",cur_request.account.account_no);}
				}
				else{printf("Sorry !! Unable To Fetch details For Account No %lld\n",cur_request.account.account_no);}
				break;}
			case MODIFY:{
				int m_choice,m_ch;
				do{
					printf("Choose What you want To Update\n");
					printf("1.Name\n");
					printf("2.City\n");
					printf("3.State\n");
					printf("4.Country\n");
					printf("5.Pin Code\n");
					printf("6.Mobile No\n");
					printf("7.Email\n");
					printf("8.Exit\n");
					scanf("%d",&m_choice);
					switch(m_choice){
					case 1:{
						struct packet cur_request,cur_response={0};
						printf("Enter Account No To Update Name\n");
						scanf("%lld",&cur_request.account.account_no);
						cur_request.action = GET_ACC;
						cur_request.result = -1;
						cur_response = request_to_server(cur_request);
						if(cur_response.result>0&&cur_response.account.status>0){
							if(cur_response.account.account_type=='j'){
							printf("Enter User Name\n");
							scanf(" %20[^\n]",cur_response.account.user.first_name);
							printf("Enter Second User Name\n");
							scanf(" %20[^\n]",cur_response.account.user.second_name);
							}else{
							printf("Enter User Name\n");
							scanf(" %20[^\n]",cur_response.account.user.first_name);
							}
							cur_request=cur_response;
							cur_request.action=UPDATE;
							cur_request.result=-1;
							cur_response=request_to_server(cur_request);
							if(cur_response.result>0){
							printf("Transaction Success !! Name Updated Successfully\n");
							}
							else{printf("Sorry !! Unable To Update Name For Account No %lld\n",cur_request.account.account_no);}
						}
						else{printf("Sorry !! Unable To Fetch For Account No %lld\n",cur_request.account.account_no);}		
					break;}
					case 2:{
						struct packet cur_request,cur_response={0};
						printf("Enter Account No To Update City\n");
						scanf("%lld",&cur_request.account.account_no);
						cur_request.action=GET_ACC;
						cur_request.result=-1;
						cur_response=request_to_server(cur_request);
						if(cur_response.result>0&&cur_response.account.status>0){
							printf("Enter City\n");
							scanf(" %10[^\n]",cur_response.account.user.city);
							cur_request=cur_response;
							cur_request.action=UPDATE;
							cur_request.result=-1;
							cur_response=request_to_server(cur_request);
							if(cur_response.result>0){
							printf("Transaction Success !! City Updated Successfully\n");
							}
							else{printf("Sorry !! Unable To Update City For Account No %lld\n",cur_request.account.account_no);}
						}
						else{printf("Sorry !! Unable To Fetch For Account No %lld\n",cur_request.account.account_no);}							
					break;}
					case 3:{
						struct packet cur_request,cur_response={0};
						printf("Enter Account No To Update State\n");
						scanf("%lld",&cur_request.account.account_no);
						cur_request.action=GET_ACC;
						cur_request.result=-1;
						cur_response=request_to_server(cur_request);
						if(cur_response.result>0&&cur_response.account.status>0){
							printf("Enter State\n");
							scanf(" %10[^\n]",cur_response.account.user.state);
							cur_request=cur_response;
							cur_request.action=UPDATE;
							cur_request.result=-1;
							cur_response=request_to_server(cur_request);
							if(cur_response.result>0){
							printf("Transaction Success !! State Updated Successfully\n");
							}
							else{printf("Sorry !! Unable To Update State For Account No %lld\n",cur_request.account.account_no);}
						}
						else{printf("Sorry !! Unable To Fetch  For Account No %lld\n",cur_request.account.account_no);}		
				
					break;}
					case 4:{
						struct packet cur_request,cur_response={0};
						printf("Enter Account No To Update Country\n");
						scanf("%lld",&cur_request.account.account_no);
						cur_request.action=GET_ACC;
						cur_request.result=-1;
						cur_response=request_to_server(cur_request);
						if(cur_response.result>0&&cur_response.account.status>0){
							printf("Enter Country\n");
							scanf(" %10[^\n]",cur_response.account.user.country);
							cur_request=cur_response;
							cur_request.action=UPDATE;
							cur_request.result=-1;
							cur_response=request_to_server(cur_request);
							if(cur_response.result>0){
							printf("Transaction Success !! Country Updated Successfully\n");
							}
							else{printf("Sorry !! Unable To Update Country For Account No %lld\n",cur_request.account.account_no);}
						}
						else{printf("Sorry !! Unable To Fetch For Account No %lld\n",cur_request.account.account_no);}		
				
					break;}
					case 5:{
						struct packet cur_request,cur_response={0};
						printf("Enter Account No To Update Pin Code\n");
						scanf("%lld",&cur_request.account.account_no);
						cur_request.action=GET_ACC;
						cur_request.result=-1;
						cur_response=request_to_server(cur_request);
						if(cur_response.result>0&&cur_response.account.status>0){
							printf("Enter Pin Code\n");
							scanf("%lld",&cur_response.account.user.pin_code);
							cur_request=cur_response;
							cur_request.action=UPDATE;
							cur_request.result=-1;
							cur_response=request_to_server(cur_request);
							if(cur_response.result>0){
							printf("Transaction Success !! Pin Code Updated Successfully\n");
							}
							else{printf("Sorry !! Unable To Update Pin Code For Account No %lld\n",cur_request.account.account_no);}
						}
						else{printf("Sorry !! Unable To Fetch For Account No %lld\n",cur_request.account.account_no);}		

					break;}
					case 6:{
						struct packet cur_request,cur_response={0};
						printf("Enter Account No To Update Mobile No\n");
						scanf("%lld",&cur_request.account.account_no);
						cur_request.action=GET_ACC;
						cur_request.result=-1;
						cur_response=request_to_server(cur_request);
						if(cur_response.result>0&&cur_response.account.status>0){
							printf("Enter Mobile No\n");
							scanf("%lld",&cur_response.account.user.mobile_no);
							cur_request=cur_response;
							cur_request.action=UPDATE;
							cur_request.result=-1;
							cur_response=request_to_server(cur_request);
							if(cur_response.result>0){
							printf("Transaction Success !! Mobile No Updated Successfully\n");
							}
							else{printf("Sorry !! Unable To Update Mobile No For Account No %lld\n",cur_request.account.account_no);}
						}
						else{printf("Sorry !! Unable To Fetch For Account No %lld\n",cur_request.account.account_no);}		
					
					break;}
					case 7:{
						struct packet cur_request,cur_response={0};
						printf("Enter Account No To Update Email\n");
						scanf("%lld",&cur_request.account.account_no);
						cur_request.action=GET_ACC;
						cur_request.result=-1;
						cur_response=request_to_server(cur_request);
						if(cur_response.result>0&&cur_response.account.status>0){
							printf("Enter Email Id\n");
							scanf(" %50[^\n]",cur_response.account.user.email);
							cur_request=cur_response;
							cur_request.action=UPDATE;
							cur_request.result=-1;
							cur_response=request_to_server(cur_request);
							if(cur_response.result>0){
							printf("Transaction Success !! Email Updated Successfully\n");
							}
							else{printf("Sorry !! Unable To Update Email For Account No %lld\n",cur_request.account.account_no);}
						}
						else{printf("Sorry !! Unable To Fetch Account For Account No %lld\n",cur_request.account.account_no);}		
					break;}
					case 8:{
						exit(0);
					break;}
					default:{printf("Invalid Choice :: %d\n",m_choice);}
					}
					printf("Do You Want To Continue Press 1 else Press 2\n");
					scanf("%d",&m_ch);
                    if(m_ch == 2){break;}
					}while(m_ch==1);			
				break;}
			case SEARCH:{	
				struct packet cur_request,cur_response={0};
				printf("Enter Account No To Search\n");
				scanf("%lld",&cur_request.account.account_no);
				cur_request.action=GET_ACC;
				cur_request.result=-1;
				cur_response=request_to_server(cur_request);
				if(cur_response.result>0 && cur_response.account.user.user_type!='a' && (cur_response.account.account_no == cur_request.account.account_no) && cur_response.account.status>0){
				printf("Transaction Success !! Account Found\n");
				printAccountDetails(cur_response.account);
				}
				else if(cur_response.account.user.user_type == 'a'){
					printf("Sorry !! Unable To Fetch For Account No %lld\n",cur_request.account.account_no);
				}
				else{printf("Sorry !! Unable To Fetch For Account No %lld\n",cur_request.account.account_no);}
				break;}
			case ADMIN_EXIT:{
				exit(0);
				break;}
			default:{printf("Invalid Choice :: %d\n",choice);}
			}
}
