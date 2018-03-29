//Uno transmitter

#include <SoftwareSerial.h>

#define S_RX 4
#define S_TX 5
#define SLP_N 3
#define ALPINE_RX 10
#define ALPINE_TX 11
#define WAKE_N 6
#define ALPINE_PIN 7

const int REQUEST_DELAY = 10; //ms
const int SLAVE_ID = 0x8E;
const int MASTER_ID = 0x0D;
const int SYNC_SIGNAL = 0x55;
const int DATA = 0x7E;

byte BTN_HORN[7] = { 0x00,0xFF,0xF0,0x60,0x0,0x30,0x01 };
byte BTN_OK[7] = { 0x28,0xFF,0xF0,0x60,0x0,0x30,0x0 };
byte BTN_BACK[7] = { 0x29,0xFF,0xF0,0x60,0x0,0x30,0x0 };
byte BTN_LEFT_R[7] = { 0x09,0xFF,0xF0,0x60,0x0,0x30,0x0 };
byte BTN_RIGHT_R[7] = { 0x0A,0xFF,0xF0,0x60,0x0,0x30,0x0 };
byte BTN_UP[7] = { 0x22,0xFF,0xF0,0x60,0x0,0x30,0x0 };
byte BTN_DOWN[7] = { 0x23,0xFF,0xF0,0x60,0x0,0x30,0x0 };
byte BTN_MIC[7] = { 0x2B,0xFF,0xF0,0x60,0x0,0x30,0x0 };
byte BTN_TEL[7] = { 0x1A,0xFF,0xF0,0x60,0x0,0x30,0x0 };
byte BTN_VOL_P[7] = { 0x06,0xFF,0xF0,0x60,0x0,0x30,0x0 };
byte BTN_VOL_M[7] = { 0x07,0xFF,0xF0,0x60,0x0,0x30,0x0 };
byte BTN_LEFT_L[7] = { 0x03,0xFF,0xF0,0x60,0x0,0x30,0x0 };
byte BTN_RIGHT_L[7] = { 0x02,0xFF,0xF0,0x60,0x0,0x30,0x0 };


String CMD_NAMES[14]{ "BTN_VOL_P", "BTN_VOL_M", "BTN_LEFT_R", "BTN_RIGHT_R", "BTN_UP",
					  "BTN_DOWN", "BTN_OK", "BTN_MIC", "BTN_BACK", "BTN_TEL", "BTN_LEFT_L",
					  "BTN_RIGHT_L", "BTN_HORN" };


byte CMD_LIGHT[5]{ 0xFF, 0xFB, 0xFF, 0xFF, 0xF6 };


// ALPINE CMD
//byte ALPINE_CMD_PREFIX[3] = { 0xD7, 0xDB, 0xAB };
//
//byte ALPINE_CMD_VOL_UP[3] = { 0xDB, 0xD6, 0xD5 };
//byte ALPINE_CMD_VOL_DOWN[3] = { 0x6D, 0xF6, 0xD5 };
//byte ALPINE_CMD_MUTE[3] = { 0xAD, 0xEE, 0xD5 };
//byte ALPINE_CMD_PST_UP[3] = { 0xAB, 0xEF, 0x55 };
//byte ALPINE_CMD_PST_DN[3] = { 0x55, 0xFF, 0x55 };
//byte ALPINE_CMD_SOURCE[3] = { 0xB7, 0xDB, 0x55 };
//byte ALPINE_CMD_TRK_UP[3] = { 0xBB, 0xDA,0xD5 };
//byte ALPINE_CMD_TRK_DN[3] = { 0x5D, 0xFA, 0xD5 };
//byte ALPINE_CMD_POWER[3] = { 0x77, 0xEB, 0x55 };
//byte ALPINE_CMD_END_PLAY[3] = { 0x57, 0xFD, 0x55 };
//byte ALPINE_CMD_BAND_PROG[3] = { 0x6B, 0xF7, 0x55 };

// 11 commands
boolean ALPINE_CMD_VOL_UP[48] = { 1,1,0,1,0,1,1,1, 1,1,0,1,1,0,1,1, 1,0,1,0,1,0,1,1, 1,1,0,1,1,0,1,1, 1,1,0,1,0,1,1,0, 1,1,0,1,0,1,0,1 };
boolean ALPINE_CMD_VOL_DOWN[48] = { 1,1,0,1,0,1,1,1, 1,1,0,1,1,0,1,1, 1,0,1,0,1,0,1,1, 0,1,1,0,1,1,0,1, 1,1,1,1,0,1,1,0, 1,1,0,1,0,1,0,1 };
boolean ALPINE_CMD_MUTE[48] = { 1,1,0,1,0,1,1,1, 1,1,0,1,1,0,1,1, 1,0,1,0,1,0,1,1, 1,0,1,0,1,1,0,1, 1,1,1,0,1,1,1,0, 1,1,0,1,0,1,0,1 };
boolean ALPINE_CMD_PST_UP[48] = { 1,1,0,1,0,1,1,1, 1,1,0,1,1,0,1,1, 1,0,1,0,1,0,1,1, 1,0,1,0,1,0,1,1, 1,1,1,0,1,1,1,1, 0,1,0,1,0,1,0,1 };
boolean ALPINE_CMD_PST_DOWN[48] = { 1,1,0,1,0,1,1,1, 1,1,0,1,1,0,1,1, 1,0,1,0,1,0,1,1, 0,1,0,1,0,1,0,1, 1,1,1,1,1,1,1,1, 0,1,0,1,0,1,0,1 };
boolean ALPINE_CMD_SOURCE[48] = { 1,1,0,1,0,1,1,1, 1,1,0,1,1,0,1,1, 1,0,1,0,1,0,1,1, 1,0,1,1,0,1,1,1, 1,1,0,1,1,0,1,1, 0,1,0,1,0,1,0,1 };
boolean ALPINE_CMD_TRK_UP[48] = { 1,1,0,1,0,1,1,1, 1,1,0,1,1,0,1,1, 1,0,1,0,1,0,1,1, 1,0,1,1,1,0,1,1, 1,1,0,1,1,0,1,0, 1,1,0,1,0,1,0,1 };
boolean ALPINE_CMD_TRK_DOWN[48] = { 1,1,0,1,0,1,1,1, 1,1,0,1,1,0,1,1, 1,0,1,0,1,0,1,1, 0,1,0,1,1,1,0,1, 1,1,1,1,1,0,1,0, 1,1,0,1,0,1,0,1 };
boolean ALPINE_CMD_POWER[48] = { 1,1,0,1,0,1,1,1, 1,1,0,1,1,0,1,1, 1,0,1,0,1,0,1,1, 0,1,1,1,0,1,1,1, 1,1,1,0,1,0,1,1, 0,1,0,1,0,1,0,1 };
boolean ALPINE_CMD_END_PLAY[48] = { 1,1,0,1,0,1,1,1, 1,1,0,1,1,0,1,1, 1,0,1,0,1,0,1,1, 0,1,0,1,0,1,1,1, 1,1,1,1,1,1,0,1, 0,1,0,1,0,1,0,1 };
boolean ALPINE_CMD_BAND_PROG[48] = { 1,1,0,1,0,1,1,1, 1,1,0,1,1,0,1,1, 1,0,1,0,1,0,1,1, 0,1,1,0,1,0,1,1, 1,1,1,1,0,1,1,1, 0,1,0,1,0,1,0,1 };
//---------------------------------------------------

int BTN_NOT_PRESSED_INDEX = -1;

int BTN_VOL_P_INDEX = 0;
int BTN_VOL_M_INDEX = 1;
int BTN_LEFT_R_INDEX = 2;
int BTN_RIGHT_R_INDEX = 3;
int BTN_UP_INDEX = 4;
int BTN_DOWN_INDEX = 5;
int BTN_OK_INDEX = 6;
int BTN_MIC_INDEX = 7;
int BTN_BACK_INDEX = 8;
int BTN_TEL_INDEX = 9;
int BTN_LEFT_L_INDEX = 10;
int BTN_RIGHT_L_INDEX = 11;
int BTN_HORN_INDEX = 12;

byte* _states[13]
{
	BTN_VOL_P,   // ALPINE_CMD_VOL_UP
	BTN_VOL_M,   // ALPINE_CMD_VOL_DOWN
	BTN_LEFT_R,  // ALPINE_CMD_TRK_UP
	BTN_RIGHT_R, // ALPINE_CMD_TRK_DOWN
	BTN_UP,      // ALPINE_CMD_PST_UP
	BTN_DOWN,    // ALPINE_CMD_PST_DOWN
	BTN_OK,      // ALPINE_CMD_SOURCE
	BTN_MIC,     // ALPINE_CMD_MUTE
	BTN_BACK,    // ALPINE_CMD_POWER
	BTN_TEL,     // ALPINE_CMD_END_PLAY
	BTN_LEFT_L,  // ALPINE_CMD_BAND_PROG
	BTN_RIGHT_L, //
	BTN_HORN     // 
};


boolean* _alpineCommands[11]{
	ALPINE_CMD_VOL_UP,
	ALPINE_CMD_VOL_DOWN,
	ALPINE_CMD_TRK_UP,
	ALPINE_CMD_TRK_DOWN,
	ALPINE_CMD_PST_UP,
	ALPINE_CMD_PST_DOWN,
	ALPINE_CMD_SOURCE,
	ALPINE_CMD_MUTE,
	ALPINE_CMD_POWER,
	ALPINE_CMD_END_PLAY,
	ALPINE_CMD_BAND_PROG
};


byte buf[16] = { 0 };
int cmd_counter = 0;
int _prevKeyId = 0;
byte* _lastButtonState;

SoftwareSerial LIN(S_RX, S_TX); // RX, TX


void setup()
{
	// NWAKE
	pinMode(SLP_N, OUTPUT);
	digitalWrite(SLP_N, HIGH);
	pinMode(WAKE_N, OUTPUT);
	digitalWrite(WAKE_N, LOW);
	Serial.begin(19200);
	Serial.flush();
	LIN.begin(19200);
	LIN.flush();

	pinMode(ALPINE_PIN, OUTPUT);
}


void loop()
{
	//mySerial.print(speedL);            //send the two speeds
	//mySerial.print(",");
	//mySerial.print(speedR);
	//mySerial.print('\n');

	//Serial.print(speedL);            //just for debugging
	//Serial.print(",");
	//Serial.print(speedR);
	//Serial.print('\n');
	/*LIN.write(SYNC_SIGNAL);
	LIN.write(ID);
	LIN.write(DATA);*/

	SendLinHeader(MASTER_ID);
	SendLinCommand(CMD_LIGHT);
	delayMicroseconds(100);

	SendLinHeader(SLAVE_ID);
	LIN.flush();
	ReadLinResponse(SLAVE_ID);

	delay(REQUEST_DELAY);
}


void SendLinHeader(int pid)
{
	digitalWrite(S_TX, LOW);
	delayMicroseconds(700);
	digitalWrite(S_TX, HIGH);
	delayMicroseconds(60);
	LIN.flush();
	LIN.write(SYNC_SIGNAL);
	LIN.write(pid);
}


void SendLinCommand(byte* cmd)
{
	for (int i = 0; i < 5; ++i)
	{
		LIN.write(cmd[i]);
	}
}


void ReadLinResponse(int id)
{
	int b_counter = 0;
	while (LIN.available()) {   //read the two speeds

		buf[b_counter] = LIN.read();
		b_counter++;
	}
	//PrintState(buf, b_counter);
	switch (id)
	{
	case SLAVE_ID: ParseSteeringWheelState(buf, b_counter); break;
	default:
		break;
	}

	//if (b_counter > 2)
	//{
	//	//ClearInput();
	//	for (int i = 0; i < b_counter; i++)
	//	{
	//		Serial.print(buf[i], HEX);
	//		Serial.print(" ");
	//	}
	//	Serial.println();
	//	//Serial.println();

	//	//delay(100);
	//}
}


void ParseSteeringWheelState(byte bytes[], int length)
{
	if (_prevKeyId > BTN_NOT_PRESSED_INDEX && memcmp(bytes, _lastButtonState, 7) == 0)
	{
		if (++cmd_counter == 3)
		{
			SendAlpineCmd(_prevKeyId);
		}
	}
	else
	{
		for (int i = 0; i < 13; ++i)
		{
			if (memcmp(bytes, _states[i], 7) == 0)
			{
				_lastButtonState = _states[i];
				_prevKeyId = i;
				return;
			}
		}
		_prevKeyId == BTN_NOT_PRESSED_INDEX;
	}
}


void SendAlpineCmd(int commandIndex)
{
	boolean *cmd = _alpineCommands[commandIndex];

	//first send 8ms high
	digitalWrite(ALPINE_PIN, HIGH);
	delay(8);
	// send 4.5ms low
	digitalWrite(ALPINE_PIN, LOW);
	delayMicroseconds(4500);

	for (int i = 0; i <= 47; i++) {
		//send bit for 0.5ms
		if (cmd[i] == 1) {
			digitalWrite(ALPINE_PIN, HIGH);
		}
		else {
			digitalWrite(ALPINE_PIN, LOW);
		}
		delayMicroseconds(500);
		// wait 0.5ms
		digitalWrite(ALPINE_PIN, LOW);
		delayMicroseconds(500);
	}
	// send 41ms low
	digitalWrite(ALPINE_PIN, LOW);
}


void PrintCommandNameByIndex(int index)
{
	if (index != 0)
	{
		Serial.println(CMD_NAMES[index]);
	}
}


void PrintState(byte bytes[], int length)
{
	for (int i = 0; i < length; i++)
	{
		Serial.print(buf[i], HEX);
		Serial.print(" ");
	}
	Serial.println();
}
