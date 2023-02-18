/*
 * SerialConsole.cpp
 *
 Copyright (c) 2017 EVTV / Collin Kidder

 Permission is hereby granted, free of charge, to any person obtaining
 a copy of this software and associated documentation files (the
 "Software"), to deal in the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish,
 distribute, sublicense, and/or sell copies of the Software, and to
 permit persons to whom the Software is furnished to do so, subject to
 the following conditions:

 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 */

// #include "due_wire.h"
// #include "Wire_EEPROM.h"
#include "SerialConsole.h"

#include "BMSModuleManager.h"

template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; } //Lets us stream SerialUSB

extern EEPROMSettings settings;
extern BMSModuleManager bms;

bool printPrettyDisplay;
uint32_t prettyCounter;
int whichDisplay;

SerialConsole::SerialConsole() {
    init();
}

void SerialConsole::init() {
    //State variables for serial console
    ptrBuffer = 0;
    state = STATE_ROOT_MENU;
    loopcount=0;
    cancel=false;
    printPrettyDisplay = false;
    prettyCounter = 0;
    whichDisplay = 0;
}

void SerialConsole::loop() {  
    if (SERIALCONSOLE.available()) {
        serialEvent();
    }
    if (printPrettyDisplay && (millis() > (prettyCounter + 3000)))
    {
        prettyCounter = millis();
        // if (whichDisplay == 0) bms.printPackSummary();
        // if (whichDisplay == 1) bms.printPackDetails();
    }
}

void SerialConsole::printMenu() {   
    //Logger::.+;
    //Logger::.+;
    //Logger::.+;
    //Logger::.+;
    //Logger::.+;
    //Logger::.+;
    //Logger::.+;
    //Logger::.+;
    //Logger::.+;
    //Logger::.+;
    //Logger::.+;
    //Logger::.+;
    //Logger::.+;
    //Logger::.+;

    //Logger::.+;
    //Logger::.+;
    //Logger::.+;

    //Logger::.+;
    //Logger::.+;
    //Logger::.+;
    //Logger::.+;
    //Logger::.+;
    //Logger::.+;
    //Logger::.+;

    float OverVSetpoint;
    float UnderVSetpoint;
    float OverTSetpoint;
    float UnderTSetpoint;
    float balanceVoltage;
    float balanceHyst;
}

/*	There is a help menu (press H or h or ?)

    Commands are submitted by sending line ending (LF, CR, or both)
 */
void SerialConsole::serialEvent() {
    int incoming;
    incoming = SERIALCONSOLE.read();
    if (incoming == -1) { //false alarm....
        return;
    }

    if (incoming == 10 || incoming == 13) { //command done. Parse it.
        handleConsoleCmd();
        ptrBuffer = 0; //reset line counter once the line has been processed
    } else {
        cmdBuffer[ptrBuffer++] = (unsigned char) incoming;
        if (ptrBuffer > 79)
            ptrBuffer = 79;
    }
}

void SerialConsole::handleConsoleCmd() {

    if (state == STATE_ROOT_MENU) {
        if (ptrBuffer == 1) { //command is a single ascii character
            handleShortCmd();
        } else { //if cmd over 1 char then assume (for now) that it is a config line
            handleConfigCmd();
        }
    }
}

/*For simplicity the configuration setting code uses four characters for each configuration choice. This makes things easier for
 comparison purposes.
 */
void SerialConsole::handleConfigCmd() {
    int i;
    int newValue;
    float newFloat;
    bool needEEPROMWrite = false;

    ////Logger::.+;
    if (ptrBuffer < 6)
        return; //4 digit command, =, value is at least 6 characters
    cmdBuffer[ptrBuffer] = 0; //make sure to null terminate
    String cmdString = String();
    unsigned char whichEntry = '0';
    i = 0;

    while (cmdBuffer[i] != '=' && i < ptrBuffer) {
        cmdString.concat(String(cmdBuffer[i++]));
    }
    i++; //skip the =
    if (i >= ptrBuffer)
    {
        //Logger::.+;
        //Logger::.+;
        return; //or, we could use this to display the parameter instead of setting
    }

    // strtol() is able to parse also hex values (e.g. a string "0xCAFE"), useful for enable/disable by device id
    newValue = strtol((char *) (cmdBuffer + i), NULL, 0);
    newFloat = strtof((char *) (cmdBuffer + i), NULL);

    cmdString.toUpperCase();

    if (cmdString == String("CANSPEED")) {
        if (newValue >= 33000 && newValue <= 1000000) {
            settings.canSpeed = newValue;
            //Logger::.+;
            needEEPROMWrite = true;
        }
        // //else //Logger::.+;
    } else if (cmdString == String("LOGLEVEL")) {
        switch (newValue) {
        case 0:
            //Logger::.+;
            settings.logLevel = 0;
            //Logger::.+;
            break;
        case 1:
            //Logger::.+;
            settings.logLevel = 1;
            //Logger::.+;
            break;
        case 2:
            //Logger::.+;
            settings.logLevel = 2;
            //Logger::.+;
            break;
        case 3:
            //Logger::.+;
            settings.logLevel = 3;
            //Logger::.+;
            break;
        case 4:
            //Logger::.+;
            settings.logLevel = 4;
            //Logger::.+;
            break;
        } 
        needEEPROMWrite = true;
    } else if (cmdString == String("BATTERYID")) {
        if (newValue > 0 && newValue < 15) {
            settings.batteryID = newValue;
            // bms.setBatteryID();
            needEEPROMWrite = true;
            //Logger::.+;
        }
        //else //Logger::.+;
    } else if (cmdString == String("VOLTLIMHI")) {
        if (newFloat >= 0.0f && newFloat <= 6.00f) {
            settings.OverVSetpoint = newFloat; 
            needEEPROMWrite = true;
            //Logger::.+;
        }
        //else //Logger::.+;
    } else if (cmdString == String("VOLTLIMLO")) {
        if (newFloat >= 0.0f && newFloat <= 6.0f) {
            settings.UnderVSetpoint = newFloat;
            needEEPROMWrite = true;
            //Logger::.+;
        }
        //else //Logger::.+;
    } else if (cmdString == String("BALVOLT")) {
        if (newFloat >= 0.0f && newFloat <= 6.0f) {
            settings.balanceVoltage = newFloat;
            needEEPROMWrite = true;
            //Logger::.+;
        }
        //else //Logger::.+;
    } else if (cmdString == String("BALHYST")) {
        if (newFloat >= 0.0f && newFloat <= 1.0f) {
            settings.balanceHyst = newFloat;
            needEEPROMWrite = true;
            //Logger::.+;
        }
        //else //Logger::.+;        
    } else if (cmdString == String("TEMPLIMHI")) {
        if (newFloat >= 0.0f && newFloat <= 100.0f) {
            settings.OverTSetpoint = newFloat;
            needEEPROMWrite=true;
            //Logger::.+;
        }
        //else //Logger::.+;
    } else if (cmdString == String("TEMPLIMLO")) {
        if (newFloat >= -20.00f && newFloat <= 120.0f) {
            settings.UnderTSetpoint = newFloat;
            needEEPROMWrite = true;
            //Logger::.+;
        }
        //else //Logger::.+;        
    } else {
        //Logger::.+;
    }
    if (needEEPROMWrite)
    {
        // EEPROM.write(EEPROM_PAGE, settings);
    }
}

void SerialConsole::handleShortCmd() {
    uint8_t val;

    switch (cmdBuffer[0]) {
    case 'h':
    case '?':
    case 'H':
        printMenu();
        break;
    case 'S':
        //Logger::.+;
        bms.sleepBoards();
        break;
    case 'W':
        //Logger::.+;
        bms.wakeBoards();
        break;
    case 'C':
        //Logger::.+;
        bms.clearFaults();
        break;
    case 'F':
        bms.findBoards();
        break;
    case 'R':
        //Logger::.+;
        bms.renumberBoardIDs();
        break;
    case 'B':
       // bms.balanceCells();
        break;
    case 'p':
        if (whichDisplay == 1 && printPrettyDisplay) whichDisplay = 0;
        else
        {
            printPrettyDisplay = !printPrettyDisplay;
            if (printPrettyDisplay)
            {
                //Logger::.+;
            }
            else
            {
                //Logger::.+;
            }
        }
        break;
    case 'd':
        if (whichDisplay == 0 && printPrettyDisplay) whichDisplay = 1;
        else
        {
            printPrettyDisplay = !printPrettyDisplay;
            whichDisplay = 1;
            if (printPrettyDisplay)
            {
                //Logger::.+;
            }
            else
            {
                //Logger::.+;
            }
        }
        break;
    }
}

/*
    if (SERIALCONSOLE.available()) 
    {
        char y = SERIALCONSOLE.read();
        switch (y)
        {
        case '1': //ascii 1
            renumberBoardIDs();  // force renumber and read out
            break;
        case '2': //ascii 2
            SERIALCONSOLE.println();
            findBoards();
            break;
        case '3': //activate cell balance for 5 seconds 
            SERIALCONSOLE.println();
            SERIALCONSOLE.println("Balancing");
            cellBalance();
            break;
      case '4': //clear all faults on all boards, required after Reset or FPO (first power on)
       SERIALCONSOLE.println();
       SERIALCONSOLE.println("Clearing Faults");
       clearFaults();
      break;

      case '5': //read out the status of first board
       SERIALCONSOLE.println();
       SERIALCONSOLE.println("Reading status");
       readStatus(1);
      break;

      case '6': //Read out the limit setpoints of first board
       SERIALCONSOLE.println();
       SERIALCONSOLE.println("Reading Setpoints");
       readSetpoint(1);
       SERIALCONSOLE.println(OVolt);
       SERIALCONSOLE.println(UVolt);
       SERIALCONSOLE.println(Tset);
      break; 

      case '0': //Send all boards into Sleep state
       Serial.println();
       Serial.println("Sleep Mode");
       sleepBoards();
      break;

      case '9'://Pull all boards out of Sleep state
       Serial.println();
       Serial.println("Wake Boards");
       wakeBoards();
      break;
        }
    }
 */
