#include <iostream>
#include <fstream>
#include "Bank.cpp"



using namespace std;

void MainMenu();
Bank bank;
int main()
{
	bank = Bank("ABC");
	MainMenu();	
	
	return 0;
}

void MainMenu(){
	int choice;
	bool session = true;		
	cout<<"WELCOME TO THE BANK "<<bank.getName() <<endl;
	cout.flush();	
	while(session){
		cout << "\n1.Customer login"<<endl;
		cout << "2.Add Customer" <<endl;
		cout << "3.Export Customers"<<endl;
		cout << "4.Import Customers"<<endl;
		cout << "5.Print Customers" <<endl;
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
				bank.Run();
				break;
			case 2:
				bank.AddCustomer();
				break;
			case 3:
				bank.ExportCustomers();
				break;
			case 4:
				bank.ImportCustomers();
				break;
			case 5:
				bank.PrintCustomers();
				break;
			case 9:
				session = false;
				system("CLS");
				bank.ExportCustomers();
				break;
			default:
				cout << "There is no command like this!" << endl;
				break;
		}
	
	
}	}


