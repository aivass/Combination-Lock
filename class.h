#pragma once

#include <iostream>
#include <conio.h>

#define KB_LEFT 75			//input values for left
#define KB_RIGHT 77			//input values for right
class lock
{
	int num1;
	int num2;
	int num3;
	int current_number = 0;
	int state = 0;			//lock state, 0 waiting for 1st correct, 1 waiting for 2nd correct...., 3 UNLOCKED
	int KB_code = 0;
	int last_direction = 0;	// 1 left, 2 right
	int click_count = 0;


	


public:

	void setnum1(int x) { num1 = x; }
	void setnum2(int x) { num2 = x; }
	void setnum3(int x) { num3 = x; }
	int getstate() { return state; }
	int getclick_count() { return click_count; }
	int getcurrent_number() { return current_number; }
	void keyboard_input();
	void state_changer();
};

class keyboardinput
{

};
void lock::keyboard_input()
{
	if (_kbhit())							//if a key has been pressed
	{
		KB_code = _getch();					//gets the keycode for left or right

		switch (KB_code)
		{
		case KB_LEFT:					//if spin left
			if (lock::last_direction == 2)	//if the spin direction has changed
			{
				lock::click_count = 0;		//reset the click count
			}
			lock::current_number += 1;		//incriment the current number
			if (lock::current_number == 40)	//rollover 39 -> 0
				lock::current_number = 0;
			lock::last_direction = 1;			//remember the rotation direction
			lock::click_count += 1;			//incriment the click count
			break;

		case KB_RIGHT:					//if spin right
			if (lock::last_direction == 1)	//if the spin direction has changed
			{
				lock::click_count = 0;		//reset the click count
			}
			lock::current_number -= 1;		//decriment the current number
			if (lock::current_number == -1)	//rollover 0 -> 39
				lock::current_number = 39;
			lock::last_direction = 2;			//remember the rotation direction
			lock::click_count += 1;			//incriment the click count
			break;
		}
	}
}

void lock::state_changer()
{
	if (lock::state == 0 && lock::click_count > 40 && lock::last_direction == 1 && lock::current_number == lock::num1)	//condition for first correct number, if true set state to start on second number
		state = 1;
	if (lock::state == 1 && lock::click_count > 40 && lock::last_direction == 2 && lock::current_number == lock::num2)	//condition for second correct number, if true set state to start on third number
		state = 2;
	if (lock::state == 2 && lock::last_direction == 1 && lock::current_number == lock::num3)						//condition for third correct number, if true the lock is unlocked
		state = 3;
	if (lock::state == 2 && lock::click_count > 40 && lock::current_number < lock::num2)							//stops user from spin to win unlock
		state = 0;
}