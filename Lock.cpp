#include "stdafx.h"
#include "class.h"
using namespace std;

#define KB_LEFT 75			//input values for left
#define KB_RIGHT 77			//input values for right

int main() {

	int num1;
	int num2;
	int num3;
	char user_selection;	//choice of user input or defaults
	bool choice;			//validity of choice
	lock myLock;

	
	do{						//get user input until the choice is valid
		cout << "(S)et Combo or (U)se Defaults: ";
		cin >> user_selection;
		if (user_selection == 'S' || user_selection== 's') {
			cout << "\nValid Selections 1-39: \n";
			cout << "Number 1: ";
			cin >> num1;
			cout << "Number 2: ";
			cin >> num2;
			cout << "Number 3: ";
			cin >> num3;
			if (num1 < 39 && num1 >= 0 && num2 < 39 && num2 >= 0 && num3 < 39 && num3 >= 0)
				choice = true;
			myLock.setnum1(num1);
			myLock.setnum2(num2);
			myLock.setnum3(num3);
		} else if (user_selection == 'U' || user_selection == 'u') {
			myLock.setnum1(10);
			myLock.setnum2(5);
			myLock.setnum3(25);
			choice = true;
		} else if(user_selection != 'S' || user_selection != 's' || user_selection != 'U' || user_selection != 'u') {
			cout << "Invalid Selection";
			choice = false;
		}
		if (choice != 1)
			cout << "Invalid Selection\n";
		
		
	} while (choice == false);

	while (myLock.getstate() !=3) {				//while the lock is locked
		cout <<"\nNumber of Clicks:"<< myLock.getclick_count() <<  "		Current Number: " << myLock.getcurrent_number() << "		LockState: "<< myLock.getstate() << endl;
		_getch();								//pauses for user input
			
		myLock.keyboard_input();
		myLock.state_changer();
	}
		
	cout << "UNLOCKED\n";


	system("pause");
	return 0;
}
