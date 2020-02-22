#include <iostream>
#include <string>

#define MAX 100
 
class stack
{
	private:
    std::string arr[MAX];   // Contains all the Data
    int top;        //Contains location of Topmost Data pushed onto Stack

	public:
	stack()         //Constructor
	{
		top=-1;      //Sets the Top Location to -1 indicating an empty stack
	}

	bool IsFull(){
		if(top == MAX - 1)
			return true;
		else 
			return false;
	}

	bool IsEmpty(){
		if(top== -1)
			return true;
		else 
			return false;
	}

	void push(std::string a){  	  // Push ie. Add Value Function
		top++;        	  // increment to by 1
			if (IsFull()==(!true)){
				arr[top]=a;  //If Stack is Vacant store Value in Array
			}
			else
			{
				std::cout<<"STACK FULL!!"<<std::endl;
				top--;
			}
	}

	std::string pop()                  // Delete Item. Returns the deleted item
	{
		if (IsEmpty()==(true))
		{
			std::cout<<"STACK IS EMPTY!!!"<<std::endl;
			return NULL;
		}
		else
		{
			std::string data=arr[top];     //Set Topmost Value in data
			arr[top]="";       //Set Original Location to NULL
			top--;               // Decrement top by 1
			return data;         // Return deleted item
		}
	}
};


