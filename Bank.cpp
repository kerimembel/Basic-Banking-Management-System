#include <iostream>
#include <fstream>
#include <string>
#include "Customer.cpp"
#include <stdlib.h>
#include <vector>

#define MAX_CUSTOMER 100
using namespace std;

class Bank{

private:
	string name;
	Customer customers[MAX_CUSTOMER];
	int cust_count;
	bool run;
	
	//User Menu creation
	void CustomerMenu(){		

		string account_number;
		string password;
		int c_index;
		cout << "Type 'exit' to return the main menu  " <<endl;
		cout << "Welcome, Please enter your Account ID : ";
		cin>>account_number;
		if(account_number=="exit"){
			run = false;
			system("CLS");

			return;
		}
		c_index = CheckAccountNumber(account_number);
		
		if(c_index == -1){
			cout << "No customer with this customer number!" <<endl;
			return;
		}
		system("CLS");

		customers[c_index].AddAccountActivity("login");
		cout << "Enter your password : ";
		cin>>password;
		while(customers[c_index].getPassword() != password){			
			if(password.size()!=4)
				cout<<"The password must be 4 digits long!!"<<endl;	
			else		
				cout << "Wrong Password !!"<<endl;	
			cout<<"Re-enter password :";
			cin>>password;		
		}
		UserScreen(c_index);
							
	}
	
	void _WithdrawMoney(int index){
		
		int money_amount;
		cout << "Enter the amount of money to withdraw : ";
		cin>>money_amount;
		customers[index].WithdrawMoney(money_amount);
	}
	
	void _DepositMoney(int index){
		
		int money_amount;
		cout << "Enter the amount of money to deposit : ";
		cin>>money_amount;
		customers[index].DepositMoney(money_amount);
	}
	
	void _LendMoney(int index){
		
		int money_amount;
		cout << "Enter the amount of money to lend on Interest : ";
		cin>>money_amount;
		customers[index].LendMoney(money_amount);
	}
	
	void _SendMoney(int index){	
	
		string receiver_AccNo;	
		int toSend,money_amount;

		cout << "Enter the account number to send money : ";
		cin>>receiver_AccNo;
		toSend = CheckAccountNumber(receiver_AccNo);
		if(toSend == -1){
			cout << "No customer with this customer number!" <<endl;
			return;				
		}			
		cout << "Enter the amount of money to send : ";
		cin>>money_amount;
			
		//Checking if balance is insufficient
		if(money_amount > customers[index].getBalance()){
			cout <<"Insufficient balance, only $ "<< customers[index].getBalance() << " in your account."<< endl;
			return ;
		}else{			
			customers[toSend].setBalance(customers[toSend].getBalance() + money_amount);
			customers[index].setBalance(customers[index].getBalance() - money_amount);
			customers[index].AddAccountActivity("s",money_amount,customers[toSend].getAccountNumber());
			customers[toSend].AddAccountActivity("r",money_amount,customers[toSend].getAccountNumber());
			customers[index].PrintAccountActivities();	
		}		
		
	}
   //Convert float to string to add stack and print
	string toStr(float number){
	    ostringstream buff;
	    buff<<number;
	    return buff.str();   
	}
	
	
	// for string delimiter
	vector<string>split (string s, string delimiter) {
		
	    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	    string token;
	    vector<string> res;
	
	    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
	        token = s.substr (pos_start, pos_end - pos_start);
	        pos_start = pos_end + delim_len;
	        res.push_back (token);
   		}

	    res.push_back (s.substr (pos_start));
	    return res;
	    
	}
	
	//Screen after user logs in
	void UserScreen(int index){
		int choice;
		
		cout << "\nWelcome, "+customers[index].getFullName() <<endl;		
		bool session = true;
		while(session){
			cout << "\n1.Withdraw Money" <<endl;
			cout << "2.Deposit Money" <<endl;
			cout << "3.Lend Money on Interest"<<endl;
			cout << "4.Send Money to Other Account"<<endl;
			cout << "5.Print Total Balance"<<endl;
			cout << "6.Print Account Activities"<<endl;
			cout << "9.Exit"<<endl;
			cout << "Please enter your choose : ";
			cin >> choice;	
			while (cin.fail()) {
				cin.clear();
        		cin.ignore(256,'\n');
				cin >> choice;			
				
			}
			switch(choice){
				case 1:
					_WithdrawMoney(index);
					break;
				case 2:
					_DepositMoney(index);
					break;
				case 3:
					_LendMoney(index);
					break;
				case 4:
					_SendMoney(index);
					break;
				case 5:
					customers[index].PrintBalance();
					break;
				case 6:
					customers[index].PrintAccountActivities();
					break;
				case 9:
					session = false;
					customers[index].AddAccountActivity("logout");
					system("CLS");
					break;
				default:
					cout << "There is no command like this!" << endl;
					break;
			}
			
		}
	
	}
	//Function to check account number exists on bank
	int CheckAccountNumber(string acc_no){
		
		for( int i = 0; i < cust_count; i = i + 1 ) {
      		if(customers[i].getAccountNumber()==acc_no){
      			return i;
			  }
   		}
   		return -1;
	
	}

public:
	
	//Constructor with only name
	Bank(string _name){
		this->cust_count = 0;
		this->name = _name;
	}
	Bank(){
		this->cust_count = 0;
	}
	
	//Runs the platform for customers
	void Run(){
		this->run = true;
		while(this->run)
			CustomerMenu();
	}
	
	//Export Customers from file to recognize user later
	void ExportCustomers(){
		
		ofstream myfile;
	  	myfile.open ("customer.bank");
	  	stack s;
	  	for(int i = 0; i<cust_count;i++){
	  		s=customers[i].getActivities();
	  		myfile << customers[i].getFirstName() + ","+customers[i].getLastName() + "," +customers[i].getAccountNumber()+ ",";
	  		myfile << customers[i].getPassword() + ","+ toStr(customers[i].getBalance()) + ",";
	  		while(!s.IsEmpty())
	  			myfile << s.pop() + ",";	  			
	  		myfile << endl;
		}	 
	 	myfile.close();	 
		cout<<"Exporting Customer Succesfull!!"<<endl;
		 	
	}

	//Import Customers from previous records
	void ImportCustomers(){
				
		string line,token;
	  	ifstream myfile ("customer.bank");
	  	vector<string> v;
	  	Customer cust;
	  	char* pEnd;
	  	stack s;
	  	if (myfile.is_open()){
	  		
	   		while ( getline (myfile,line) )
	    	{	
	    		s=cust.getActivities();
		    	v = split(line,",");
	      		cust.setFirstName(v[0]);
	      		cust.setLastName(v[1]);
	      		cust.setAccountNumber(v[2]);
	      		cust.setPassword(v[3]);
	      		cust.setBalance(strtod(v[4].data(),0));
	      		for(int i = 5; i < v.size();i++)
	      			if(v[i]!=v.back())	    
					  s.push(v[i]);  				
				
   				cust.setActivities(s);
				AddCustomer(cust);
	    	}
	    	myfile.close();
	    	cout<<"Importing Customer Succesfull!!"<<endl;
	  	}	
	 	else cout << "Unable to open customer records!!"; 	 	
	 	
	}
	
	//Adds new customer to a Bank
	void AddCustomer(){
		int control;
		string fname,lname,account_no,balance;
		cout<<"Enter Account No : ";
		cin >> account_no;
		control = CheckAccountNumber(account_no);
		if(control!=-1){
			cout<<"Account number exist !!" << endl;
			return;
		}
		cout<<"Enter First Name : ";
		cin>> fname;
		cout<<"Enter Last Name : ";
		cin>> lname;
		cout<<"Enter Balance : ";
		cin>>balance;
		
		
		Customer cust = Customer(fname,lname,strtod(balance.c_str(),0));
		cust.setAccountNumber(account_no);
		this->customers[cust_count] = cust;
		cust_count = cust_count + 1;
		
		cout<<"Customer Added succesfully!" << endl;

	}
	
	//Adds new customer to a Bank
	void AddCustomer(Customer cust){	
		int control;
		control = CheckAccountNumber(cust.getAccountNumber());
		if(control!=-1){
			cout<< cust.getAccountNumber()<< " numbered account exists!" <<endl;
			return ;
		}	
		this->customers[cust_count] = cust;
		cust_count = cust_count + 1;
	}
	//PrintCustomers Function
	void PrintCustomers(){
		if(cust_count==0){
			cout<<"No customer!!"<<endl;
			return;
		}
		cout << "FULLNAME    ACCOUNT NO" << endl;
		for(int i = 0; i < cust_count;i++){
			cout << customers[i].getFullName() << "  "<< customers[i].getAccountNumber()<< endl;
		}
	}
	
	string getName(){
		return this->name;
	}
	
	
};
