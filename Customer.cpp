#include <iostream>
#include <string>
#include "Stack.h"
#include <ctime>
#include <sstream>

using namespace std;

class Customer
{
private:
	//Private customer variables
    string account_number;
    string first_name;
    string last_name;
    string password;
    float total_balance;
    stack account_activities;
    
    //Convert float to string to add stack and print
	string toStr(float number){
	    ostringstream buff;
	    buff<<number;
	    return buff.str();   
	}

	//Getting time information for account activity log
	const string currentDateTime() {
	    time_t     now = time(0);
	    struct tm  tstruct;
	    char       buf[80];
	    tstruct = *localtime(&now);
	   
	    strftime(buf, sizeof(buf), "%d-%m-%Y | %X", &tstruct);
	    return buf;
	}
	
	
	
public:
	
	
	//Empty Constructor
	Customer(){
		this->first_name = "";	
		this->last_name = "";		
		this->password = "0000";
		this->total_balance = 0;
		this->account_number="111111";

	}
	//Constructor with name and balance only
	Customer(string first_name,string last_name,float balance){
		this->first_name = first_name;	
		this->last_name = last_name;		
		this->password = "0000";
		this->total_balance = balance;
		this->account_number="111111";
	}
	
	//Print Only Total Balance
	void PrintBalance(){
		cout<< "Customer Balance : " << this->total_balance << endl;
	}
	//WithdrawMoney function
	void WithdrawMoney(float money_amount){
		//Checking if balance is insufficient
		if(money_amount > this->total_balance){	
			cout <<"Insufficient balance, only $ "<<this->total_balance << " in your account.\n"  << endl;
			return;
		}else{
			
			this->total_balance = this->total_balance - money_amount;
			this->AddAccountActivity("w",money_amount);
			this->PrintAccountActivities();
		}
	}
	//Deposit Money Function
	void DepositMoney(float money_amount){
		
		this->total_balance = this->total_balance + money_amount;
		this->AddAccountActivity("d",money_amount);
		this->PrintAccountActivities();


	}
	
	//Lend Money on Interest function
	void LendMoney(float invesment_amount){
		//Checking if balance is insufficient
		if(invesment_amount > this->total_balance){
			cout <<"Insufficient balance, only $ "<<this->total_balance << " in your account."<< endl;
			return ;
		}else{
		
			this->AddAccountActivity("l",invesment_amount);
			this->PrintAccountActivities();	
		}
	}
	
	//This function adds user activity to the stack after every operation.
	void AddAccountActivity(string type,float amount=0,string account_no=""){
		
		string activity = currentDateTime() +" -> the customer ";
		
		if(type=="w")
			activity.append("withdraws $"+toStr(amount)+" from account.");
		else if(type=="d")
			activity.append("deposits $"+toStr(amount)+" into account.");
		else if(type=="l")
			activity.append("lends $"+toStr(amount)+" at interest.");
		else if(type=="s")
			activity.append("sent $" +toStr(amount)+ " to Account no : "+account_no+" account.");
		else if(type=="r")
			activity.append("received $" +toStr(amount)+ " from Account no : "+account_no+" account.");		
		else if(type=="login")
			activity.append("logged into the system.");	
		else if(type=="logout")
			activity.append("logged out from system.");
		
	
		account_activities.push(activity);
	}	
	//Prints Account Activities
	void PrintAccountActivities(){
		cout<< "\nCustomer Name : " << this->first_name << endl;
		cout<< "Customer Surname : " << this->last_name << endl;
		cout<< "Customer ID : " << this->account_number << endl;
		cout<< "Customer Balance : " << this->total_balance << endl;

		cout<< "Account Movements/Statements : " << endl;

		stack temp = this->account_activities;
		while(!temp.IsEmpty())
			cout <<  temp.pop() <<endl;		
		
			cout << "---------------------------------------------------------------------\n\n"<<endl;
	}
	
	//Getters and Setters
	void setFirstName(string firstname) {
      this->first_name = firstname;
    }
    
    string getFirstName() {
      return this->first_name;
    } 
    
	void setLastName(string last_name) {
      this->last_name = last_name;
    } 
	  
    string getLastName() {
      return this->last_name;
    } 
    
    string getFullName(){
    	return this->first_name + " " + this->last_name;
	}
     
	void setAccountNumber(string account_number) {
      this->account_number = account_number;
    }   
   
    string getAccountNumber() {
      return this->account_number;
    } 
    
    void setPassword(string password) {
      this->password = password;
    } 
	  
    string getPassword() {
      return this->password;
    } 
    
     void setBalance(float total_balance) {
      this->total_balance = total_balance;
    } 
	  
    float getBalance() {
      return this->total_balance;
    } 
    
    void setActivities(stack activity){
    	this->account_activities = activity;
	}
	
	stack getActivities(){
		return this->account_activities;
	}
    
};
