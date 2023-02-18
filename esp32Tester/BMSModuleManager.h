//#pragma once
#ifndef _BMS_MODULE_MANAGER_H_
#define _BMS_MODULE_MANAGER_H_
#include "config.h"
#include "BMSModule.h"


class BMSModuleManager
{
public:
    BMSModuleManager();
    void balanceCells(uint8_t *balanseOn);
    void balanceCellsOff();
    void setupBoards();
    void findBoards();
    int renumberBoardIDs();
    void clearFaults();
    void sleepBoards();
    void wakeBoards();
    bool  getAllVoltTemp();
    void readSetpoints();
    // void setBatteryID();
    float getPackVoltage();
    float getAvgTemperature();
    float getAvgCellVolt();
    // void processCANMsg(CAN_FRAME &frame);
    void printPackSummary();
    void printPackDetails();
    void lcdPrintf();
    float getVoltCell(int index,float* volt);
    bool getStatusModule(int index);
    float getTempCell(int index,float* temp);

    int getNumFoundModules(){return numFoundModules;}
    float getLowestPackVolt(){return lowestPackVolt;}
    float getHighestPackVolt(){return highestPackVolt;}

    uint8_t getModulBalanceState(uint8_t address, uint8_t number);
private:
    float packVolt;                         // All modules added together
    float lowestPackVolt;
    float highestPackVolt;
    float lowestPackTemp;
    float highestPackTemp;
    BMSModule modules[MAX_MODULE_ADDR + 1]; // store data for as many modules as we've configured for.
    int numFoundModules;                    // The number of modules that seem to exist
    bool isFaulted;
    
    // void showmsgXY(int x, int y, int sz, const GFXfont *f, const char *msg)
    // {
    //     // int16_t x1, y1;
    //     // uint16_t wid, ht;
    //     // tft.setFont(f);
    //     // tft.setCursor(x, y);
    //     // tft.setTextSize(sz);
    //     // tft.println(msg);
    // }
    // void sendBatterySummary();
    // void sendModuleSummary(int module);
    // void sendCellDetails(int module, int cell);
    
};
#endif
