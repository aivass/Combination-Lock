#pragma once

#define KB_LEFT 75			//input values for left
#define KB_RIGHT 77			//input values for right
class lock
{
	int num1;
	int num2;
	int num3;
	char user_selection;	//choice of user input or defaults
	int choice = 0;			//validity of choice, 0 invalid, 1 valid
	int current_number = 0;
	int state = 0;			//lock state, 0 waiting for 1st correct, 1 waiting for 2nd correct...., 3 UNLOCKED
	int KB_code = 0;
	int last_direction = 0;	// 1 left, 2 right
	int click_count = 0;



	void keyboard_input(int& click_count, int& current_number, int& last_direction);
	void state_changer(int& state, int& click_count, int& last_direction);
};

void lock::keyboard_input()
{
	if (_kbhit())							//if a key has been pressed
	{
		KB_code = _getch();					//gets the keycode for left or right

		switch (KB_code)
		{
		case KB_LEFT:					//if spin left
			if (last_direction == 2)	//if the spin direction has changed
			{
				click_count = 0;		//reset the click count
			}
			current_number += 1;		//incriment the current number
			if (current_number == 40)	//rollover 39 -> 0
				current_number = 0;
			last_direction = 1;			//remember the rotation direction
			click_count += 1;			//incriment the click count
			break;

		case KB_RIGHT:					//if spin right
			if (last_direction == 1)	//if the spin direction has changed
			{
				click_count = 0;		//reset the click count
			}
			current_number -= 1;		//decriment the current number
			if (current_number == -1)	//rollover 0 -> 39
				current_number = 39;
			last_direction = 2;			//remember the rotation direction
			click_count += 1;			//incriment the click count
			break;
		}
	}
}

void lock::state_changer()
{
	if (state == 0 && click_count > 40 && last_direction == 1 && current_number == num1)	//condition for first correct number, if true set state to start on second number
		state = 1;
	if (state == 1 && click_count > 40 && last_direction == 2 && current_number == num2)	//condition for second correct number, if true set state to start on third number
		state = 2;
	if (state == 2 && last_direction == 1 && current_number == num3)						//condition for third correct number, if true the lock is unlocked
		state = 3;
	if (state == 2 && click_count > 40 && current_number < num2)							//stops user from spin to win unlock
		state = 0;
}