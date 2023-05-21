/* Mini Project
  Name: Sajal Gupta
  Roll no: MT2022096 */
  
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "server_utilities.h"

int main(){
	struct sockaddr_in server,client;
	int socket_descriptor,nsocket_descriptor;
	pid_t pid;

	socket_descriptor=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(13980);

	int bind_result=bind(socket_descriptor,(void *)(&server),sizeof(server));
	int listen_result=listen(socket_descriptor,5);
	int sz=sizeof(client);
	printf("Starting the server...\nSocket returns :: %d\n",socket_descriptor);
	printf("Bind result:: %d\nListening status :: %d\n", bind_result, listen_result);
	for(;;){
	nsocket_descriptor=accept(socket_descriptor,(void *)(&client),&sz);
	if ( (pid = fork()) == 0 ) {
		close(socket_descriptor);
		ssize_t s=0;
		struct packet request={0},response={0};
		read(nsocket_descriptor,&request,sizeof(request));
		printf("Message Recieved From client ... Action %d\n",request.result);
		switch(request.action){
		case CREATE:{
			response.action=request.action;
			response.result=openAccount(request.account);
			response.account=request.account;
			response.result_msg="CREATE_OK";
			break;}
		case UPDATE:{
			response.action=request.action;
			int record_no=getRecordNoByAccountNo(request.account.account_no);
			response.result=updateRecord(request.account,record_no);
			response.account=request.account;
			response.result_msg="DELETE_OK";
			break;}
		case GET_ACC:{
			response.result=1;
			response.action=request.action;
			int record_no=getRecordNoByAccountNo(request.account.account_no);
			response.account=getRecord(record_no);
			break;}
		case GET_USR:{
			response.result=1;
			response.action=request.action;
			int record_no=getRecordNoByUserId(request.account.user.user_id);
			response.account=getRecord(record_no);
			break;}
		default:{
			response.result=0;
			response.action=request.action;
			response.account=request.account;
			response.result_msg="INVALID_ACTION";
		}
		}
		s=write(nsocket_descriptor,&response,sizeof(response));
		close(nsocket_descriptor);
		printf("Message  sent to client :: %d\n Write Response %d",response.result,(int)s);
		exit(0);
		}
		close(nsocket_descriptor);
	}
}
