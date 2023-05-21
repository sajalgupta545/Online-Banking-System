# Online-Banking-System
/* 
  Author : SAJAL GUPTA
  Roll No : MT2022096
  Created : 15/10/2022
  
*/   

PROJECT DESCRIPTION -- 
This project aims to develop a banking system that is user-friendly and multi-
functional. The project have the following functionalities:
  a. All account transactional details and customer information are stored in files.
  b. Account holders pass through a login system to enter their accounts.
  c. The application possess password-protected administrative access; thus
     preventing the whole management system from unauthorized access.
  d. Three types of login is created: normal user, joint account user; administrator;
  e. Once you login as administrator, you are able to add, delete, modify, search for a
     specific account details.
  f. Once the customer connect to the server, he can get login and password prompt.
     After successful login, user will get menu for example:
      Do you want to:
       Deposit
       Withdraw
       Balance Enquiry
       Password Change
       View details
       Exit
g. If you login as a joint account holder, proper file locking is implemented. If you
   want to view the account details then read lock is set else if you want to withdraw
   or deposit then write lock is used to protect the critical data section.
h. Used socket programming – Server maintains the data base and service multiple clients
   concurrently. Client program can connect to the server and access their specific account
   details.
i. Used system calls instead of Library functions wherever it is possible in the project:
   Process Management, File Management, File Locking, Multithreading and Inter Process Communication Mechanisms.
