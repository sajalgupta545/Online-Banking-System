/* Mini Project
  Name: Sajal Gupta
  Roll no: MT2022096 */
  
#include "admin_action.h"

void request_handler(struct packet response, int choice, int login_type){
    switch(choice){
        case Deposit:{
            double amount;
            printf("Enter Deposit Amount\n");
            scanf("%lf",&amount);
            if(amount>=0){
                struct packet cur_request,cur_response={0};
                cur_request.account.account_no = response.account.account_no;
                cur_request.action = GET_ACC;
                cur_request.result = -1;
                cur_response = request_to_server(cur_request);
                if(cur_response.result > 0 && cur_response.account.status > 0){
                    cur_response.account.balance = cur_response.account.balance + amount;
                    cur_response.action = UPDATE;
                    cur_response.result = -1;
                    response = request_to_server(cur_response);
                    if(response.result>0){
                        printf("Transaction Success\n");
                        printf("Current balance is : %lf\n\n", cur_response.account.balance);
                    }
                    else{printf("Sorry !! Transaction Failed\n");}
                }else{
                    printf("Sorry !! Unable To Fetch Account Details To Deposit.\n");
                }
            }else{
                printf("Sorry !! Please enter the valid amount for Deposit\n");
            }
            break;}
        case Withdraw:{
            double amount;
            printf("Enter Withdraw Amount\n");
            scanf("%lf",&amount);
            struct packet cur_request,cur_response={0};
            cur_request.account.account_no = response.account.account_no;
            cur_request.action = GET_ACC;
            cur_request.result = -1;
            cur_response = request_to_server(cur_request);
            if(cur_response.result > 0&& cur_response.account.status > 0){
                response = cur_response;
                if(response.account.balance>=amount){
                    response.account.balance=response.account.balance-amount;
                    response.action=UPDATE;
                    response.result=-1;
                    response=request_to_server(response);
                    if(response.result>0){
                        printf("Transaction Success\n");
                        printf("Current balance is : %lf\n\n", response.account.balance);}
                    else{printf("Sorry !! Transaction Failed\n");}
                }
                else{
                    printf("Sorry !! There is No Enough Balance to Withdraw\n");
                }
                }
            else{
                printf("Sorry !! Unable To Fetch Account Details To Withdraw.\n");
            }
            break;}
        case Balance_Enquiry:{
            response.action = GET_ACC;
            response.result = -1;
            response = request_to_server(response);
            if(response.result > 0){
                printf("Transaction Success\n");
                printf("Available Balance Is INR %lf\n", response.account.balance);
            }
            else{
                printf("Sorry !! Transaction Failed\n");
            }
            break;}
        case Password_Change:{
            char password[10];
            printf("Enter New Password\n");
            scanf(" %10[^\n]", response.account.user.password);
            printf("Confirm Password\n");
            scanf(" %10[^\n]", password);
            if(strcmp(password,response.account.user.password) == 0){
                response.action = UPDATE;
                response.result = -1;
                response = request_to_server(response);
                if(response.result > 0){
                    printf("Transaction Success !! Password Changed Successfully\n");
                }
                else{
                    printf("Sorry !! Transaction Failed.\n");
                }
            }else{
                printf("Sorry !! Passwords are not Matching\n");
            }
            break;}
        case View_details:{
            response.action=GET_ACC;
            response.result=-1;
            response=request_to_server(response);
            printAccountDetails(response.account);
            break;}
        case Exit:{
            exit(0);
            break;}
        default:{
            printf("Invalid Choice :: %d\n",choice);
           }
        }
}
