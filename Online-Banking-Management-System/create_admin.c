/* Mini Project
  Name: Sajal Gupta
  Roll no: MT2022096 */
  
#include <stdio.h>

#include "server_utilities.h"

int createAdmin(){
		struct account account= getDetails(-1);
		int status=updateRecord(account,0);
		if(status>0){
			printf("Admin Created ... Account details are\n");
			printAccountDetails(account);
		}else{
			printf("Sorry :: Account Creation Fail..\n");
		}			
}

int main(){
    int status = createAdmin();
    return 0;
}

