#pragma config(Sensor, S1,     StartSens,      sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     FillSens,       sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          BeltMot,       tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          L1Mot,         tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          L2Mot,         tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          L3Mot,         tmotorEV3_Large, PIDControl, encoder)

//////////////////////////////////////////////////////////////////////////////////////////////
//
//	Defines and parameter settings
//
//
//////////////////////////////////////////////////////////////////////////////////////////////

#define WAIT 0
#define EMPTY 1
#define FILLING 2
#define FULL 3
#define RIGHT 0
#define LEFT 1
#define SENSORSET 10
#define SPEED 40

#define WATER 0
#define STRAWBERRY 1
#define HOLUNDER 2

#define SMALL 0
#define MEDIUM 1
#define LARGE 3

#define DRINKSELECT 0
#define SIZESELECT 1
#define WORKINPROGRESS 2


//////////////////////////////////////////////////////////////////////////////////////////////
//
//	Global Variables
//
//
//////////////////////////////////////////////////////////////////////////////////////////////

int status = WAIT;
int sensStart = 500;
int sensFill = 500;
int drink = 0;
int size = 0;
int menu = 0;
int cancel = 0;

//////////////////////////////////////////////////////////////////////////////////////////////
//
//	Function prototypes
//
//
//////////////////////////////////////////////////////////////////////////////////////////////

int MoveBelt(int setDirection, int setSpeed);
int DispenseDrink(int chosenDrink, int drinkSize);
void HandleMenu(void);

//////////////////////////////////////////////////////////////////////////////////////////////
//
//	Function MAIN
//	Basic sequence
//
//////////////////////////////////////////////////////////////////////////////////////////////

task main(){

	drawBmpfile(0, 127, "startScreen"); // Show splash screen
	delay(2000);	// Wait 2 seconds

	while(1){	// repeating loop
		HandleMenu();
		if (status != WAIT){	// Task active?

			sensStart = getUSDistance(StartSens);
			sensFill = getUSDistance(FillSens);

			if((status == EMPTY) && (SENSORSET >= sensFill)){

				status = MoveBelt(LEFT,SPEED);

			}
			if((status == EMPTY) && (SENSORSET <= sensFill)){

				status = FILLING;

			}
			if(status == FILLING){

				status = DispenseDrink(drink, size);

			}
			if((status == FULL) && (SENSORSET <= sensStart)){

				status = MoveBelt(RIGHT,SPEED);

			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//	The MoveBelt function controlls the motor for the belt system. It must be possible to set
//	the direction and the speed of the belt.
//	The movement must be stoped automaticly when the glass reches an endpoint.
//
//////////////////////////////////////////////////////////////////////////////////////////////

int MoveBelt(int setDirection, int setSpeed){

	if( setDirection == 1){

		if(sensStart >= SENSORSET){

			setMotorSpeed(BeltMot,SPEED);

		}
		else{

			setMotorSpeed(BeltMot,0);

		}
	}

	else{

		if(sensFill >= SENSORSET){

			setMotorSpeed(BeltMot,(SPEED * -1));

		}
		else{

			setMotorSpeed(BeltMot,0);

		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//	The DispenseDrink function is responisble to output the right amount of the liquids
//	required to make the drink which was chosen from the user.
//
//////////////////////////////////////////////////////////////////////////////////////////////

int DispenseDrink(int chosenDrink, int drinkSize){




}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//	The HandleMenu function is responisble to display the actual state of the menu and handle
//	the user imputs with the five menu buttons.
//
//////////////////////////////////////////////////////////////////////////////////////////////

void HandleMenu(void){

	while (!getButtonPress(buttonAny)) { }// Wait for a button press before exiting


	switch (menu){

		case DRINKSELECT:

			drawBmpfile(0, 127, "chooseDrink");
			if(getButtonPress(buttonLeft)){

				menu = SIZESELECT;
				drink = STRAWBERRY;

			}
			else if(getButtonPress(buttonEnter)){

				menu = SIZESELECT;
				drink = WATER;

			}
			else if(getButtonPress(buttonRight)){

				menu = SIZESELECT;
				drink = HOLUNDER;

			}

		break;

		case SIZESELECT:

			drawBmpfile(0, 127, "chooseSize");
			if(getButtonPress(buttonLeft)){

				menu = WORKINPROGRESS;
				size = SMALL;

			}
			else if(getButtonPress(buttonEnter)){

				menu = WORKINPROGRESS;
				size = MEDIUM;

			}
			else if(getButtonPress(buttonRight)){

				menu = WORKINPROGRESS;
				size = LARGE;

			}
			else if(getButtonPress(buttonUp)|| getButtonPress(buttonDown)){

				menu = DRINKSELECT;

			}
		break;

		case WORKINPROGRESS:

			drawBmpfile(0, 127, "workInProgress");

		 if(getButtonPress(buttonEnter)){

				menu = DRINKSELECT;
				cancel = 1;

			}
		break;
	}
}
