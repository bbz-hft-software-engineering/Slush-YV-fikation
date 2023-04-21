#pragma config(Sensor, S1,     StartSens,      sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     FillSens,       sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          L3Mot,         tmotorEV3_Large, PIDControl, reversed, encoder)
#pragma config(Motor,  motorB,          L1Mot,         tmotorEV3_Large, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC,          L2Mot,         tmotorEV3_Large, PIDControl, reversed, encoder)
#pragma config(Motor,  motorD,          BeltMot,       tmotorEV3_Large, PIDControl, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

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
#define SENSORSET 4
#define SPEED 10
#define CALFLOW 200

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
#define D2L1 17
#define D2L2 83
#define D2L3 0

// Drink 3 Receipe in % HOLUNDER
#define D3L1 0
#define D3L2 83
#define D3L3 17

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

int l1motget = 0;
int l2motget = 0;
int l3motget = 0;

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
	resetMotorEncoder(L1Mot);						// Initialise Motor encoders
	resetMotorEncoder(L2Mot);
	resetMotorEncoder(L3Mot);

	delay(2000);	// Wait 2 seconds

	while(1){	// repeating loop

		FlankHandler();	// Flankenerkennung bei jedem programmdurchlauf
		HandleMenu();		// Handle user inputs and show menu on display
		sensStart = getUSDistance(StartSens); // read start sensor value
		sensFill = getUSDistance(FillSens); // read end sensor value

		if (status != WAIT){	// Task active?

			if((status == EMPTY) && (SENSORSET < sensFill) && (SENSORSET > sensStart )){ // Status is empty and start sensor active and end sensor not active

				status = TRANSONE; // set status in transport
				setMotorSpeed(BeltMot,SPEED); // turn on transport belt

			}
			if((status == TRANSONE) && (SENSORSET > sensFill)){ // if status is in transport and en sensor is active

				setMotorSpeed(BeltMot,0); // turn of transport belt
				status = FILLING; // set status filling

			}

			if(status == FILLING){ // when status filling

				status = DispenseDrink(drink, size);// fill drink like defined in recepies

			}

			if((status == FULL) && (SENSORSET > sensFill) && (SENSORSET < sensStart )){ // when status full and fill sensor active and start sensor not active

				setMotorSpeed(BeltMot,(SPEED * -1));// turn on transport belt in direction of start
				status = TRANSTWO; // set status to in transport

			}
		}
		else{ // when no job active

			setMotorSpeed(BeltMot,0); // reset all working parameters
			l1ready = 0;
			l2ready = 0;
			l3ready = 0;
			setMotorSpeed(L1Mot, 0);
			setMotorSpeed(L2Mot, 0);
			setMotorSpeed(L3Mot, 0);
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

	l1motget = getMotorEncoder(L1Mot); // get encoder values from motors
 	l2motget = getMotorEncoder(L2Mot);
	l3motget = getMotorEncoder(L3Mot);

	switch(drink){ // what drink was chosen

		case WATER: // case water
			if((size * D1L1 * CALFLOW * -1) < l1motget){ // calculate value and check status from encoders

				setMotorSpeed(L1Mot, 100); // turn on pump with max speed

			}
			else{

				setMotorSpeed(L1Mot, 0); // when right amount is dispensed stop pump
				l1ready = 1; // set status flag

			}
			if((size * D1L2 * CALFLOW* -1) < l2motget){ // same as in liquid 1

				setMotorSpeed(L2Mot, 100);

			}
			else{

				setMotorSpeed(L2Mot, 0);
				l2ready = 1;

			}
			if((size * D1L3 * CALFLOW* -1) < l3motget){ // same as in liquid 1

				setMotorSpeed(L3Mot, 100);

			}
			else{

				setMotorSpeed(L3Mot, 0);
				l3ready = 1;

			}
		break;


		case STRAWBERRY: // case strawberry
			if((size * D2L1 * CALFLOW* -1) < l1motget){ // same as in Drink1

				setMotorSpeed(L1Mot, 100);

			}
			else{

				setMotorSpeed(L1Mot, 0);
				l1ready = 1;

			}
			if((size * D2L2 * CALFLOW* -1) < l2motget){

				setMotorSpeed(L2Mot, 100);

			}
			else{

				setMotorSpeed(L2Mot, 0);
				l2ready = 1;

			}
			if((size * D2L3 * CALFLOW* -1) < l3motget){

				setMotorSpeed(L3Mot, 100);

			}
			else{

				setMotorSpeed(L3Mot, 0);
				l3ready = 1;

			}
		break;


		case HOLUNDER:
			if((size * D3L1 * CALFLOW* -1) < l1motget){// same as in Drink1

				setMotorSpeed(L1Mot, 100);

			}
			else{

				setMotorSpeed(L1Mot, 0);
				l1ready = 1;

			}
			if((size * D3L2 * CALFLOW* -1) < l2motget){

				setMotorSpeed(L2Mot, 100);

			}
			else{

				setMotorSpeed(L2Mot, 0);
				l2ready = 1;

			}
			if((size * D3L3 * CALFLOW* -1) < l3motget){

				setMotorSpeed(L3Mot, 100);

			}
			else{

				setMotorSpeed(L3Mot, 0);
				l3ready = 1;

			}
		break;

	}

	if(l1ready && l2ready && l3ready){ // when all liquids are ready

		resetMotorEncoder(L1Mot); // reset motor encoders
		resetMotorEncoder(L2Mot);
		resetMotorEncoder(L3Mot);

		l1ready = 0; // reset ready
		l2ready = 0;
		l3ready = 0;

		return FULL; // return status full
	}
	else{
		return FILLING; // when not ready return filling
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//	The HandleMenu function is responisble to display the actual state of the menu and handle
//	the user imputs with the five menu buttons.
//
//////////////////////////////////////////////////////////////////////////////////////////////

void HandleMenu(void){

	switch (menu){ // switch throgh menu points

		case DRINKSELECT: // when drink selection menu active

			drawBmpfile(0, 127, "chooseDrink"); // show menu point
			if(triggerLeft){ // when left button pressed

				menu = SIZESELECT; // menu status to select size
				drink = STRAWBERRY; // set drink to strawberry sirup

			}
			else if(triggerMiddle){ // when middle button pressed

				menu = SIZESELECT; // menu status to select size
				drink = WATER; // set drink to water

			}
			else if(triggerRight){

				menu = SIZESELECT;// menu status to select size
				drink = HOLUNDER;// set drink to holunder sirup

			}

		break;

		case SIZESELECT: // menu point size select

			drawBmpfile(0, 127, "chooseSize");// show menu point on display
			if(triggerLeft){ // same as in menupoint drinkselect

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

	nowLeft = getButtonPress(buttonLeft); // read all button states
	nowMiddle = getButtonPress(buttonEnter);
	nowRight = getButtonPress(buttonRight);
	nowUp = getButtonPress(buttonUp);
	nowDown = getButtonPress(buttonDown);

	if (nowLeft == 1 && backLeft == 0){ // compare if button is pressed and was not pressed before

		triggerLeft = 1; // set a button impuls

	}
	else{ triggerLeft = 0; } // when not pressed do not set button impulse

	if (nowMiddle == 1 && backMiddle == 0){ // same as in first button

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

	backLeft= nowLeft; // update status on switch status
	backMiddle=nowMiddle;
	backRight =nowRight;
	backUp = nowUp;
	backDown = nowDown;

}