/* Mini Project
  Name: Sajal Gupta
  Roll no: MT2022096 */
  
struct sequence{
	int seq_no;
};
struct user{
	char first_name[20];
	char second_name[20];
	long long int user_id;
	char password[10];
	char city[10];
	char state[10];
	char country[10];
	long long int pin_code;
	long long int mobile_no;
	char email[50];
	char user_type;               /*n-normal user, a-admin user*/
};

struct joint_user{
	struct user user1;
	struct user user2;
	long long int user_id[2];
	char password[10];
};

struct account{
	long long int account_no;
	double balance;
	char account_type;           /* c-current, s-saving */
	int seq_no;
	struct user user;
	int status;
	char history[1000];
};

struct joint_account{
	long long int account_no;
	double balance;
	int seq_no;
	struct joint_user user;
	int status;
	char history[1000];
};

struct packet{
	int action;
	struct account account;
	int result;
	char *result_msg;
};

struct joint_packet{
	int action;
	struct joint_account account;
	int result;
	char *result_msg;
};
