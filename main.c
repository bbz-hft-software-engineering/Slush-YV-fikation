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

// status Events
#define WAIT 0
#define EMPTY 1
#define TRANSONE 2
#define FILLING 3
#define TRANSTWO 4
#define FULL 5

// Directions
#define RIGHT 0
#define LEFT 1

// Settings
#define SENSORSET 10
#define SPEED 40
#define CALFLOW 50

// Drinks
#define WATER 0
#define STRAWBERRY 1
#define HOLUNDER 2

// Sizes
#define SMALL 1
#define MEDIUM 2
#define LARGE 3

// Menu points
#define DRINKSELECT 0
#define SIZESELECT 1
#define WORKINPROGRESS 2

// Drink 1 Receipe in % Water
#define D1L1 0
#define D1L2 100
#define D1L3 0

// Drink 2 Receipe in % STRAWBERRY
#define D2L1 50
#define D2L2 50
#define D2L3 0

// Drink 3 Receipe in % HOLUNDER
#define D3L1 0
#define D3L2 50
#define D3L3 50

//////////////////////////////////////////////////////////////////////////////////////////////
//
//	Global Variables
//
//
//////////////////////////////////////////////////////////////////////////////////////////////

int status = WAIT;
float sensStart = 500;
float sensFill = 500;
int drink = 0;
int size = 0;
int menu = DRINKSELECT;

int l1ready = 0;
int l2ready = 0;
int l3ready = 0;

// Flankenerkennung
int backLeft = 0;
int backMiddle = 0;
int backRight = 0;
int backUp = 0;
int backDown = 0;
int nowLeft = 0;
int nowMiddle = 0;
int nowRight = 0;
int nowUp = 0;
int nowDown = 0;
int triggerLeft = 0;
int triggerMiddle = 0;
int triggerRight = 0;
int triggerUp = 0;
int triggerDown = 0;

//////////////////////////////////////////////////////////////////////////////////////////////
//
//	Function prototypes
//
//
//////////////////////////////////////////////////////////////////////////////////////////////

int DispenseDrink(int chosenDrink, int drinkSize);
void HandleMenu(void);
void FlankHandler(void);

//////////////////////////////////////////////////////////////////////////////////////////////
//
//	Function MAIN
//	Basic sequence
//
//////////////////////////////////////////////////////////////////////////////////////////////

task main(){

	drawBmpfile(0, 127, "startScreen"); // Show splash screen
	resetMotorEncoder(L1Mot);
	resetMotorEncoder(L2Mot);
	resetMotorEncoder(L3Mot);

	delay(2000);	// Wait 2 seconds

	while(1){	// repeating loop

		FlankHandler();
		HandleMenu();
		sensStart = getUSDistance(StartSens);
		sensFill = getUSDistance(FillSens);

		if (status != WAIT){	// Task active?

			if((status == EMPTY) && (SENSORSET < sensFill) && (SENSORSET > sensStart )){

				status = TRANSONE;
				setMotorSpeed(BeltMot,SPEED);

			}
			if((status == TRANSONE) && (SENSORSET > sensFill)){

				setMotorSpeed(BeltMot,0);
				status = FILLING;

			}

			if(status == FILLING){

				status = DispenseDrink(drink, size);

			}

			if((status == FULL) && (SENSORSET > sensFill) && (SENSORSET < sensStart )){

				setMotorSpeed(BeltMot,(SPEED * -1));
				status = TRANSTWO;

			}
		}
		else{

			setMotorSpeed(BeltMot,0);
			l1ready = 0;
			l2ready = 0;
			l3ready = 0;
			resetMotorEncoder(L1Mot);
			resetMotorEncoder(L2Mot);
			resetMotorEncoder(L3Mot);

		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////
//
//	The DispenseDrink function is responisble to output the right amount of the liquids
//	required to make the drink which was chosen from the user.
//
//////////////////////////////////////////////////////////////////////////////////////////////

int DispenseDrink(int chosenDrink, int drinkSize){

	int l1motget = getMotorEncoder(L1Mot);
 	int l2motget = getMotorEncoder(L2Mot);
	int l3motget = getMotorEncoder(L3Mot);

	switch(drink){

		case WATER:
			if((size * D1L1 * CALFLOW) > l1motget){

				setMotorSpeed(L1Mot, 100);

			}
			else{

				setMotorSpeed(L1Mot, 0);
				l1ready = 1;

			}
			if((size * D1L2 * CALFLOW) > l2motget){

				setMotorSpeed(L2Mot, 100);

			}
			else{

				setMotorSpeed(L2Mot, 0);
				l2ready = 1;

			}
			if((size * D1L3 * CALFLOW) > l3motget){

				setMotorSpeed(L3Mot, 100);

			}
			else{

				setMotorSpeed(L3Mot, 0);
				l3ready = 1;

			}
		break;


		case STRAWBERRY:
			if((size * D2L1 * CALFLOW) > l1motget){

				setMotorSpeed(L1Mot, 100);

			}
			else{

				setMotorSpeed(L1Mot, 0);
				l1ready = 1;

			}
			if((size * D2L2 * CALFLOW) > l2motget){

				setMotorSpeed(L2Mot, 100);

			}
			else{

				setMotorSpeed(L2Mot, 0);
				l2ready = 1;

			}
			if((size * D2L3 * CALFLOW) > l3motget){

				setMotorSpeed(L3Mot, 100);

			}
			else{

				setMotorSpeed(L3Mot, 0);
				l3ready = 1;

			}
		break;


		case HOLUNDER:
			if((size * D3L1 * CALFLOW) > l1motget){

				setMotorSpeed(L1Mot, 100);

			}
			else{

				setMotorSpeed(L1Mot, 0);
				l1ready = 1;

			}
			if((size * D3L2 * CALFLOW) > l2motget){

				setMotorSpeed(L2Mot, 100);

			}
			else{

				setMotorSpeed(L2Mot, 0);
				l2ready = 1;

			}
			if((size * D3L3 * CALFLOW) > l3motget){

				setMotorSpeed(L3Mot, 100);

			}
			else{

				setMotorSpeed(L3Mot, 0);
				l3ready = 1;

			}
		break;

	}

	if(l1ready && l2ready && l3ready){

		resetMotorEncoder(L1Mot);
		resetMotorEncoder(L2Mot);
		resetMotorEncoder(L3Mot);

		l1ready = 0;
		l2ready = 0;
		l3ready = 0;

		return FULL;
	}
	else{
		return FILLING;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//	The HandleMenu function is responisble to display the actual state of the menu and handle
//	the user imputs with the five menu buttons.
//
//////////////////////////////////////////////////////////////////////////////////////////////

void HandleMenu(void){

	switch (menu){

		case DRINKSELECT:

			drawBmpfile(0, 127, "chooseDrink");
			if(triggerLeft){

				menu = SIZESELECT;
				drink = STRAWBERRY;

			}
			else if(triggerMiddle){

				menu = SIZESELECT;
				drink = WATER;

			}
			else if(triggerRight){

				menu = SIZESELECT;
				drink = HOLUNDER;

			}

		break;

		case SIZESELECT:

			drawBmpfile(0, 127, "chooseSize");
			if(triggerLeft){

				menu = WORKINPROGRESS;
				size = SMALL;

			}
			else if(triggerMiddle){

				menu = WORKINPROGRESS;
				size = MEDIUM;

			}
			else if(triggerRight){

				menu = WORKINPROGRESS;
				size = LARGE;

			}
			else if(triggerDown || triggerUp){

				menu = DRINKSELECT;

			}
		break;

		case WORKINPROGRESS:

		 drawBmpfile(0, 127, "workInProgress");
			if (status == WAIT){
		 		status = EMPTY;
			}
		 if(triggerMiddle){

				menu = DRINKSELECT;
				status = WAIT;

			}
		break;
	}
		if ((status == TRANSTWO) && (SENSORSET > sensStart)  ){

			status = WAIT;
			menu = DRINKSELECT;

	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//	The FlankHandler is watching the button states and detects a change of the state of the
//	five buttons. It is needed to prevent multiple detections.
//
//////////////////////////////////////////////////////////////////////////////////////////////


void FlankHandler(void){

	nowLeft = getButtonPress(buttonLeft);
	nowMiddle = getButtonPress(buttonEnter);
	nowRight = getButtonPress(buttonRight);
	nowUp = getButtonPress(buttonUp);
	nowDown = getButtonPress(buttonDown);

	if (nowLeft == 1 && backLeft == 0){

		triggerLeft = 1;

	}
	else{ triggerLeft = 0; }

	if (nowMiddle == 1 && backMiddle == 0){

		triggerMiddle = 1;

	}
	else{ triggerMiddle = 0; }

	if (nowRight == 1 && backRight == 0){


		triggerRight = 1;

	}
	else{ triggerRight= 0; }

	if (nowUp == 1 && backUp == 0){

		triggerUp = 1;

	}
	else{ triggerUp= 0; }

	if (nowDown == 1 && backDown == 0){

		triggerDown = 1;

	}
	else{ triggerDown= 0; }

	backLeft= nowLeft;
	backMiddle=nowMiddle;
	backRight =nowRight;
	backUp = nowUp;
	backDown = nowDown;

}
