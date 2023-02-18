
// // Load Wi-Fi library
// #include <WiFi.h>
// #include <WiFiClient.h>
// #include <DNSServer.h>
// #include <WiFiAP.h>

// const char *server_name = "www.tester.com";  // Can be "*" to all DNS requests
// IPAddress apIP(192, 168, 4, 1);
// DNSServer dnsServer;

// #include "BMSModuleManager.h"
// #define Slave_ID1 2
// #define Slave_ID2 1

// uint8_t fault_1 = 5;
// uint8_t fault_2 = 24;

// #define RXD1 15 //RX1 pin
// #define TXD1 4 //TX1 pin

// #define RXD2 16 //RXX2 pin
// #define TXD2 17 //TX2 pin

// //#define BMS_BAUD  612500
// #define BMS_BAUD  617647
// //#define BMS_BAUD  608695

// const uint8_t countBmb = 16;
// const float DeltaInBMB = 0.010;
// const float DeltaInACB = 0.10;

// uint8_t dispalyPage = 1;//1--домашня сторінка
// uint8_t helpData = 0;

// float voltAVG  [countBmb][6];//збереження значень для виводу
// float volt     [6];//таблиця для тимчасового зберігання вольт
// float sumD[countBmb] = {0};
// float FullVolt = 0;
// uint8_t indexMinVoltBatery[2];
// uint8_t indexMaxVoltBatery[2];
// const float critDisbalanse = 0.01;
// bool isCritDisbalanse;


// float maxFVolt = 0;
// float minFVolt = 0;
// uint8_t indexMax =0;
// bool isCrit = 0;
// uint8_t indexMin =0;

// float tempAVG  [countBmb][2];//збереження значень для виводу
// float temp     [2];//таблиця для тимчасового зберігання температури
// char balanse[countBmb] = {0};
// bool isBalanse = false;
// BMSModuleManager bms;
// uint8_t countBord = 0; //кількість плат
// unsigned long time1;
// unsigned long time2;


// #include "BMSModuleManager.h"
// // Replace with your network credentials
// //const char* ssid = "ESP32";
// //const char* password = "01234567";

// const char* ssid = "NKService";
// const char* password = "NKService123";

// // Set web server port number to 80
// IPAddress local_ip(192,168,2,1);
// IPAddress gateway(192,168,2,1);
// IPAddress subnet(255,255,255,0);
// WiFiServer server(80);

// // Variable to store the HTTP request
// String header;

// void prsingDataVoltTemp(){
//   int i =0;
//   FullVolt = 0;
//   float maxVoltBat = 0;
//   float minVoltBat = 5;
//   indexMinVoltBatery[0] = 0;
//   indexMaxVoltBatery[0] = 0;
//   indexMinVoltBatery[1] = 0;
//   indexMaxVoltBatery[1] = 0;
//   while(bms.getStatusModule(i+1)){

//       bms.getTempCell(i+1,temp);
//       bms.getVoltCell(i+1,volt);
//       sumD[i] = 0;

//       for(int j = 0 ; j <6;j++){
//           voltAVG[i][j] = round(volt[j]*500)/500;
//           if(maxVoltBat<voltAVG[i][j]){
//             maxVoltBat = voltAVG[i][j];
//             indexMaxVoltBatery[0] = i;
//             indexMaxVoltBatery[1] = j;
//           }
//           if(minVoltBat>voltAVG[i][j]){

//             minVoltBat=voltAVG[i][j];
//             indexMinVoltBatery[0] = i;
//             indexMinVoltBatery[1] = j;
//           }
//           sumD[i] += volt[j];
//           FullVolt+= volt[j];
//       }
//       for(int j = 0 ; j <2;j++){
//           tempAVG[i][j] = temp[j];
//       }
//       i++;
//     }
//     maxFVolt = sumD[0];
//     minFVolt = sumD[0];
//     indexMax =0;
//     indexMin =0;

//     if(abs(maxVoltBat-minVoltBat)>critDisbalanse){isCritDisbalanse =true;}
//     else{isCritDisbalanse =false;}


//     for(int i =0 ; i <countBmb;i++){
//       if(bms.getStatusModule(i+1)){
//         if(maxFVolt<sumD[i]){
//           maxFVolt=sumD[i];
//           indexMax = i;

//         }
//         if(minFVolt>sumD[i]){
//           maxFVolt=sumD[i];
//           indexMin = i;
//         }
//       }

//       if(abs(maxFVolt-minFVolt)>DeltaInACB){isCrit =true;}
//       else{isCrit =false;}
//     }
// }


// void setup() {
//   Serial.begin(115200);
//   Serial2.begin(617647, SERIAL_8N1, RXD2, TXD2);
//   // Initialize the output variables as outputs
//   pinMode(fault_1, INPUT);//fault
//   pinMode(fault_2, INPUT);//fault
//   // Connect to Wi-Fi network with SSID and password
//   Serial.print("Setting AP (Access Point)…");
// //  WiFi.mode(WIFI_AP);
// //  // Remove the password parameter, if you want the AP (Access Point) to be open
// //  WiFi.softAP(ssid, password);
// //  delay(100);
// //  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Connecting to WiFi..");
//   }
//   const byte DNS_PORT = 53;
//   dnsServer.start(DNS_PORT, server_name, apIP);
//   //IPAddress myIP = WiFi.softAPIP();

//   bms.renumberBoardIDs();
//   bms.clearFaults();
//   countBord = bms.getNumFoundModules();//визначення кількості плат
//   bms.getAllVoltTemp();//отримання даних з про вологість та температуру

//   bms.getAllVoltTemp();//отримання даних з про вологість та температуру

//   prsingDataVoltTemp();

//   time1 = millis();

//   server.begin();
// }

// void balanseAndUpdateData(){
//   if(time1+1000<millis()){
//     bms.getAllVoltTemp();//отримання даних з про вологість та температуру
//     prsingDataVoltTemp();
//     if(isBalanse){
//       bms.balanceCells((uint8_t *)balanse);
//       isBalanse = false;
//     }
//     else{
//       bms.balanceCellsOff();
//       isBalanse = true;
//     }
//   time1 = millis();
//   }
// }

// void dravBlock(int i,WiFiClient& client){
//   if(bms.getStatusModule(i+1)){//якщо є звязок з платою
//     if (balanse[i]==0) {
//       client.println("<a href=\"/"+ String(i) +"/open\"><button class=\"borderButtonBMB\" style=\"border:2px solid SteelBlue;\">");
//     } else {
//       client.println("<a href=\"/"+ String(i) +"/open\"><button class=\"borderButtonBMB\" style=\"border:2px solid Aqua;\">");
//     }
//     client.println("<div style=\"display: flex; align-items: stretch;\">");
//        if(i<8)client.println("<div style=\"width:5vw;  align-items: center;\"><p>"+String(i+1)+"</p></div>");
//        client.println("<div style=\"border: 1px solid white; display: block; width:38vw;\">");
//         if(i<8){

//           client.println("<div style=\"display: flex;\">");
//           for(int z = 3; z<6;z++  ){
//               client.println("<span style=\"margin:1vw;");
//               if(voltAVG[i][z] == voltAVG[indexMaxVoltBatery[0]][indexMaxVoltBatery[1]] && !isCritDisbalanse){client.println("background:DarkOrange;");}
//               else if(voltAVG[i][z] == voltAVG[indexMinVoltBatery[0]][indexMinVoltBatery[1]]){      client.println("background:#83FF08;");}
//               else if(voltAVG[i][z] == voltAVG[indexMaxVoltBatery[0]][indexMaxVoltBatery[1]] && isCritDisbalanse){client.println("background:DarkRed;");}
//               client.println("\">"+String(voltAVG[i][z],3)+"v </span>");
//               //client.println("<div style=\"margin:0.5vw;\">"+String(voltAVG[i][z],3)+"v </div>");
//           }
//           client.println("</div>");
//           client.println("<div style=\"display: flex;\">");
//           for(int z = 2; z>=0;z--){
//               client.println("<span style=\"margin:1vw;");
//               if(voltAVG[i][z] == voltAVG[indexMaxVoltBatery[0]][indexMaxVoltBatery[1]] && !isCritDisbalanse){client.println("background:DarkOrange;");}
//               else if(voltAVG[i][z] == voltAVG[indexMinVoltBatery[0]][indexMinVoltBatery[1]]){      client.println("background:#83FF08;");}
//               else if(voltAVG[i][z] == voltAVG[indexMaxVoltBatery[0]][indexMaxVoltBatery[1]] && isCritDisbalanse){client.println("background:DarkRed;");}
//               client.println("\">"+String(voltAVG[i][z],3)+"v </span>");
//           }
//           client.println("</div>");
//         }
//         else{
//           for(int z = 0; z<6;z++  ){
//             if(z == 3 || z == 0){
//               client.println("<div style=\"display: flex;\">");
//             }
//               client.println("<span style=\"margin:1vw;");
//               if(voltAVG[i][z] == voltAVG[indexMaxVoltBatery[0]][indexMaxVoltBatery[1]] && !isCritDisbalanse){client.println("background:DarkOrange;");}
//               else if(voltAVG[i][z] == voltAVG[indexMinVoltBatery[0]][indexMinVoltBatery[1]]){      client.println("background:#83FF08;");}
//               else if(voltAVG[i][z] == voltAVG[indexMaxVoltBatery[0]][indexMaxVoltBatery[1]] && isCritDisbalanse){client.println("background:DarkRed;");}
//               client.println("\">"+String(voltAVG[i][z],3)+"v </span>");
//             if(z == 2 || z==5){
//               client.println("</div>");
//             }
//           }
//         }
//       client.println("</div>");
//     if(i>7)client.println("<div style=\"width:5vw; align-items: center;\"><p>"+String(i+1)+"</p></div>");

//     client.println("</div></button></a>");

//   }
//   else{
//     if (balanse[i]==0) {
//       client.println("<a href=\"/"+ String(i) +"/open\"><button class=\"borderButtonBMB\" style=\"border:2px solid SteelBlue;\">");
//     } else {
//       client.println("<a href=\"/"+ String(i) +"/open\"><button class=\"borderButtonBMB\" style=\"border:2px solid Aqua;\">");
//     }

//     client.println("<div style=\"display: flex; align-items: stretch;\">");
//        if(i<8)client.println("<div style=\"width:5vw;  align-items: center;\"><p>"+String(i+1)+"</p></div>");
//        client.println("<div style=\"border: 1px solid white; display: block; width:38vw;\">");
//             client.println("<div style=\"display: flex;\">");
//               client.println("<div style=\"margin:0.5vw;\">No connection </div>");
//             client.println("</div>");
//             client.println("<div style=\"display: flex;\">");
//               client.println("<div style=\"margin:0.5vw;\">detected </div>");
//             client.println("</div>");
//         client.println("</div>");
//     if(i>7)client.println("<div style=\"width:5vw; align-items: center;\"><p>"+String(i+1)+"</p></div>");

//     client.println("</div></button></a>");
//   }
// }

// void displayInfoBattery(uint8_t i,WiFiClient& client){
//   float maxD = voltAVG[i][0];
//   float minD = voltAVG[i][0];
//   if(bms.getStatusModule(i+1)){//якщо є звязок з платою


//       bool indexMaxCrit;
//       int indexMaxBMB;
//       int indexMinBMB;
//       for(int j = 0 ; j < 6;j++){
//         if(maxD<voltAVG[i][j]){
//           maxD = voltAVG[i][j];
//           indexMaxBMB = j;
//         }
//         if(minD>voltAVG[i][j]){
//           minD = voltAVG[i][j];
//           indexMinBMB  = j;
//         }
//       }
//       if(abs(minD-maxD)>DeltaInBMB){indexMaxCrit =true;}
//       else{indexMaxCrit =false;}



//       client.println("<div style=\"display: flex;  flex-direction: row; align-items:stretch;justify-content: center; font-size:3.5vw;\">");
//       client.println("<h3 style=\"width:11vw;\">M"+String(i+1)+"</h3>");
//         client.println("<div style=\"border: 1px solid white; display: block; width:38vw\">");
//         if(i<8){
//           client.println("<div style=\"display: flex;\">");
//           for(int z = 3; z<6;z++  ){
//               client.println("<span style=\"margin:1vw;");
//                 if(voltAVG[i][z] == voltAVG[i][indexMaxBMB] && !indexMaxCrit){client.println("background:DarkOrange;");}
//                 else if(voltAVG[i][z] == voltAVG[i][indexMinBMB]){      client.println("background:#83FF08;");}
//                 else if(voltAVG[i][z] == voltAVG[i][indexMaxBMB]&& indexMaxCrit){client.println("background:DarkRed;");}
//               client.println("\">"+String(voltAVG[i][z],3)+"v </span>");
//           }
//           client.println("</div>");
//           client.println("<div style=\"display: flex;\">");
//           for(int z = 2; z>=0;z--){
//               client.println("<span style=\"margin:1vw;");
//                 if(voltAVG[i][z] == voltAVG[i][indexMaxBMB] && !indexMaxCrit){client.println("background:DarkOrange;");}
//                 else if(voltAVG[i][z] == voltAVG[i][indexMinBMB]){      client.println("background:#83FF08;");}
//                 else if(voltAVG[i][z] == voltAVG[i][indexMaxBMB] && indexMaxCrit){client.println("background:DarkRed;");}
//               client.println("\">"+String(voltAVG[i][z],3)+"v </span>");
//           }
//           client.println("</div>");
//         }
//         else{
//           for(int z = 0; z<6;z++  ){
//             if(z == 3 || z == 0){
//               client.println("<div style=\"display: flex;align-items: center;text-align:center; text-align:center;\">");
//             }
//               client.println("<span style=\"margin:1vw;");
//                 if(voltAVG[i][z] == voltAVG[i][indexMaxBMB] && !indexMaxCrit){client.println("background:DarkOrange;");}
//                 else if(voltAVG[i][z] == voltAVG[i][indexMinBMB]){      client.println("background:#83FF08;");}
//                 else if(voltAVG[i][z] == voltAVG[i][indexMaxBMB] && indexMaxCrit){client.println("background:DarkRed;");}
//               client.println("\">"+String(voltAVG[i][z],3)+"v </span>");
//             if(z == 2 || z==5){
//               client.println("</div>");
//             }
//           }
//         }
//         client.println("</div>");

//       client.println("<div style=\" width:20vw; margin-left:1.5vw; color:Aquamarine; align-items:center\">");
//         client.println("<div>T1= "+String(tempAVG[i][0],1)+ "*c</div><br>");
//         client.println("<div>T2= "+String(tempAVG[i][1],1)+ "*c</div>");
//       client.println("</div>");

//       client.println("<div style=\"flex-direction: colomn; align-items:stretch;justify-content:stretch \">");
//       client.println("<div style=\"text-align:center;");
//         if(i == indexMax && !isCrit){client.println("background:DarkOrange;");}
//         else if(i == indexMin){      client.println("background:DodgerBlue;");}
//         else if(i == indexMax && isCrit){client.println("background:DarkRed;");}
//       client.println("\">Full V "+String(sumD[i])+"</div><br>");
//        if (balanse[i]==0) {
//         client.println("<div style=\" color:SteelBlue; \">Balanse off</div>");
//       } else {
//         client.println("<div style=\" color:Aqua;\">Balanse on</div>");
//       }
//       client.println("</div>");



//       client.println("</div>");



//     }
//     else{
//              client.println("<div style=\"display: flex;  flex-direction: row; align-items:stretch;justify-content: center; font-size:3.5vw;\">");
//               client.println("<div style=\"margin:0.5vw;\">No connection detected </div>");
//             client.println("</div>");
//     }


//       client.println("<div style=\"display: flex;  flex-direction: row; align-items:stretch;justify-content: center; font-size:3.5vw;\">");
//       client.println("<a href=\"/returnHomePage\"><button class=\"borderButtonBMB\" style=\"border:2px solid SteelBlue;\">Home page</button></a>");

//       if(minD>3.1){
//         if (balanse[i]==0) {
//           client.println("<a href=\"/"+ String(i) +"/on\"><button class=\"borderButtonBMB\" style=\"border:2px solid SteelBlue;\"> Enable balancing");
//         } else {
//           client.println("<a href=\"/"+ String(i) +"/off\"><button class=\"borderButtonBMB\" style=\"border:2px solid Aqua;\"> Disable balancing");
//         }
//       }
//       else{
//         if (balanse[i]==0) {
//           client.println("<a><button class=\"borderButtonBMB\" style=\"border:2px solid SteelBlue;\"> Balancing is not possible");
//         }
//       }
//       client.println("</button></a></div>");


// }
// inline bool respToClient(WiFiClient& client, String& currentLine)
// {
//     // Читаем байт и выводим его в последовательный порт
//     char c = client.read();
//     Serial.write(c);

//     // Если байт - символ новой строки
//     if (c == '\n') {

//         // Если текущая строка пуста, значит был получен
//         // символ новой строки два раза подряд
//         // Это означает конец клиентского HTTP-запроса.
//         if (currentLine.length() == 0) {

//             // Посылаем HTTP заголовок
//             client.println("HTTP/1.1 200 OK");
//             client.println("Content-type:text/html");
//             client.println();

//             client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
//             client.println("<link rel=\"icon\" href=\"data:,\">");
//             client.println("<meta http-equiv=\"Refresh\" content=\"5\" />");
//             client.println("<style>html { font-family: Helvetica;  display: inline-block; margin: 0px auto;background-color:black;color:white; padding:0;}");
//             client.println(".borderButtonBMB {margin-top:0.5vh; font-size:20px;  color:white; padding:1%;background:black;font-size:3.5vw;}");
//             client.println(".dot {height: 3.5vw;width: 3.5vw;background-color: white;border-radius: 50%; margin:0.2vw;}");
//             client.println("</style>");
// //            client.println("<script>function a(){fetch('http://192.168.4.1/movies').then(response => response.json()).then(data => alert(data));}</script>");
// //            client.println("<script>function a(){let xhr = new XMLHttpRequest();   xhr.open('GET', 'http://192.168.4.1:80/movies');    xhr.send();   }</script>");
// //            client.println("<script>setInterval(a,1000);</script>");
//             // Посылаем текст страницы
//             client.println("<div style=\"display: flex; vertical-align: middle; justify-content: space-around;\"><div style=\"display: flex; vertical-align: middle;\">");
//               if (digitalRead(fault_1) == LOW) {
//                   client.println("<span class=\"dot\" style=\"background-color: red;\"></span>");
//               }
//               else
//               {
//                 client.println("<span class=\"dot\" style=\"background-color: green;\"></span>");
//                  //isFault = false;
//               }

// //              if (digitalRead(fault_2) == LOW) {
// //                  //isFault = true;
// //                  client.println("<span class=\"dot\" style=\"background-color: red;\"></span>");
// //              }
// //              else
// //              {
// //                client.println("<span class=\"dot\" style=\"background-color: green;\"></span>");
// //              }
// //
//               client.println("</div><span style=\"color:White; font-size:3.5vw;\">Full Volt:");
//               client.println(FullVolt);
//               client.println(" V</span>");
//               client.println("<a href=\"/reconnection\"><button class=\"button\" style=\"height:4vh; font-size:3.5vw;  border-radius:20px;  background:Silver;\">&#8634; BMB</button></a>");

//             client.println("</div>");
//             if(dispalyPage == 1){
//               for(int i = 7,j = 8 ; i>=0; i--,j++){

//                 client.println("<div style=\"display: flex; justify-content: space-between\">");
//                 dravBlock(i,client);
//                 dravBlock(j,client);
//                 client.println("</div  \">");

//               }
//             }
//             if(dispalyPage == 2){
//               displayInfoBattery(helpData,client);
//             }


//             client.println("</body></html>");

//             // посылаем пустую строку
//             client.println();

//             // необходимые данные клиенту переданы -
//             // выходим из функции с флагом true
//             return true;
//         }

//         // иначе (строка не пуста)
//         else {
//             // стираем текущую строку
//             currentLine = "";
//         }
//     }

//     // иначе (байт не символ новой строки),
//     // если байт - не символ возврата каретки
//     else if (c != '\r') {

//         // добавляем его в текущую строку
//         currentLine += c;
//     }

//     // Проверяем какой запрос сделал клиент.
//     // Если GET /H
//   if (currentLine.endsWith("GET /movies")) {
//   Serial.println("  1  ");
//   client.println("Success!");
//   }

//     if (currentLine.endsWith("GET /returnHomePage")) {
//       dispalyPage = 1;
//       helpData = 0;
//       bms.getAllVoltTemp();//отримання даних з про вологість та температуру
//       prsingDataVoltTemp();

//   }

//  if (currentLine.endsWith("GET /reconnection")) {
//     bms.renumberBoardIDs();
//     bms.clearFaults();
//     countBord = bms.getNumFoundModules();//визначення кількості плат
//     bms.getAllVoltTemp();//отримання даних з про вологість та температуру

//     bms.getAllVoltTemp();//отримання даних з про вологість та температуру
//     prsingDataVoltTemp();
//   }

//   uint8_t i = 0;
//   while(i < countBmb){
//     if (currentLine.endsWith("GET /"+ String(i)+"/open")) {
//       dispalyPage = 2;
//       helpData = i;
//       //balanse[i] = 1;

//     } else if (currentLine.endsWith("GET /"+ String(i)+"/offL")) {
//       balanse[i] = 0;
//     }

//     if (currentLine.endsWith("GET /"+ String(i)+"/on")) {
//       balanse[i] = 1;

//     } else if (currentLine.endsWith("GET /"+ String(i)+"/off")) {
//       balanse[i] = 0;
//     }
//     i++;
//   }

//     return false;
// }

// // Функция обработки клиента
// inline void handleClient(WiFiClient& client)
// {
//   time2 = millis();
//     // выводим сообщение в последовательный порт
//     Serial.println("Новый клиент.");

//     //Создаём строковый объект для хранения входных данных
//     String currentLine = "";

//     // Входим в цикл пока клиент подсоединён
//     while (client.connected()) {

//         // Если есть данные для чтения
//         if (client.available()) {

//             // Вызываем функцию ответа клиенту
//             bool resp = respToClient(client, currentLine);

//             // Если функция передала все данные клиенту
//             if (resp == true)

//                 // прерываем цикл
//                 break;
//         }
//         balanseAndUpdateData();
//         if(time2+3000<millis()){
//           break;
//         }
//     }

//     // Закрываем соединение
//     client.stop();
//     Serial.println("Клиент отключён.");
// }

// void loop() {
//      dnsServer.processNextRequest();
//     // Создаём объект клиента и проверяем, есть ли подключённые клиенты
//     WiFiClient client = server.available();
//     //Serial.println("Нет Клиента");
//     // Если клиенты есть
//     if (client) {

//         // Вызываем функцию обработки клиента
//         handleClient(client);
//     }
//     balanseAndUpdateData();

// }



// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "NKS";
const char* password = "NKS1234";
IPAddress apIP(192, 168, 4, 1);
const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
/**/
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
   <head>
   <meta http-equiv="Content-Type" content="text/html; charset=windows-1252"><meta name="viewport" content="width=device-width, initial-scale=1">
       <style>html { font-family: Helvetica;  display: inline-block; margin: 0px auto;background-color:black;color:white; padding:0;}</style>
       <style>.borderButtonBMB {margin-top:0.5vh; color:white; font-size:3.5vw;background-color:black; padding:1%%;}</style>
       <style>.dot {height: 3.5vw;width: 3.5vw;background-color: white;border-radius: 50%%; margin:0.2vw; }</style>
       

       <script>
           function loadPage(){
              var sssss  = document.getElementById("htmLP");
              sssss.innerHTML = "Start";
               debugger
               for(var i = 8,j =9;i>0;i--,j++ ){
                sssss.innerHTML = "Start1";
                   var bodyDiv = document.getElementById('bodyDiv');
                   var divRow = document.createElement('div');
                   sssss.innerHTML = "Start2";
                   divRow.style.display = "flex"
                   divRow.style.justifyContent = "space-between";
                   sssss.innerHTML = "Start3";
                   for(var  z =0 ; z<2;z++){
                    sssss.innerHTML = "Start4";
                       var a = document.createElement('a');
                       a.href = '#';//'http://192.168.4.1/7/open';
                       
                       var button = document.createElement('button');
                       button.className = 'borderButtonBMB';
                       button.style.border = "2px solid SteelBlue";
                       //button.setAttribute("onclick","clickBlock");
                       var divColl = document.createElement('div');
                       divColl.style.display =  "flex";
                       divColl.style.alignItems = "stretch";

                       var divCollData = document.createElement('div');
                       divCollData.style.border = "1px solid #fff";
                       divCollData.style.display = "block" 
                       divCollData.style.width = "38vw";

                       var divCollNumber = document.createElement('div');
                       divCollNumber.style.width = "5vw";
                       divCollNumber.style.alignItems = "center";

                       var pNuber =  document.createElement('p');
                       sssss.innerHTML = "Start5";
                       if(z == 0){
                              
                       }
                       else{
                           pNuber.innerHTML = j;    
                       }
                       sssss.innerHTML = "Start6";
                       for(var r = 0; r <2;r++){
                        sssss.innerHTML = "Starty6.1";
                           var divRowColl = document.createElement('div');
                           sssss.innerHTML = "Starty6.2";
                           divRowColl.style.display = "flex";
                           sssss.innerHTML = "Starty6.3";
                           for(var t = 0; t < 3;t ++){
                            sssss.innerHTML = "Starty6.4";
                               var span = document.createElement('span');
                               sssss.innerHTML = "Starty6.5";
                               
                               span.style.margin = "1vw";
                               span.style.flexGrow  = "1";
                               span.style.textAlign = "center";
                               
                               sssss.innerHTML = "Starty6.6";
                               span.className = "bat_"+(z+1)*+t;
                               sssss.innerHTML = "Starty6.7";
                               span.innerHTML ="-.---v"
                               sssss.innerHTML = "Starty6.8";
                               divRowColl.appendChild(span);
                               sssss.innerHTML = "Starty6.9";
                           }
                           divCollData.appendChild(divRowColl);
                       }
                        sssss.innerHTML = "Start7";
                       
                      
                       if(z == 0){
                          pNuber.innerHTML = i;
                          divCollNumber.appendChild(pNuber);
                          divRow.id = "Block"+i; 
                          divColl.appendChild(divCollNumber);
                          divColl.appendChild(divCollData);
         
                       }
                       else{
                        pNuber.innerHTML = j;
                        divCollNumber.appendChild(pNuber); 
                        divRow.id = "Block"+j;
                        divColl.appendChild(divCollData);
                        divColl.appendChild(divCollNumber);    
                       }
sssss.innerHTML = "Start8";
                       button.appendChild(divColl);
                       sssss.innerHTML = "Start9";
                       //a.appendChild(button);
                       sssss.innerHTML = "Start10";
                       divRow.appendChild(button);
                       sssss.innerHTML = "Start11";
                   }
                   sssss.innerHTML = "Start12";
                   bodyDiv.appendChild(divRow);
                   sssss.innerHTML = "Start13";
               }
           }


          setInterval(function ( ) {
          var xhttp = new XMLHttpRequest();
          xhttp.onreadystatechange = function() {
            debugger;
            if (this.readyState == 4 && this.status == 200) {
              var msg = JSON.parse(this.responseText);
              console.log(msg.v1);
              //document.getElementById("humidity").innerHTML = this.responseText;
            }
          };
          xhttp.open("GET", "/humidity", true);
          xhttp.send();
        }, 10000 ) ;

          


          
       </script>
   </head>
   <body >
   <button onclick="loadPage()"> dsd sad sad sad sad sa</button>
   <p id="htmLP">PIZDA</p>
     <h2>ESP Web Server</h2>

       <div id='bodyDiv'>


       </div>

       
   </body>
</html>
)rawliteral";
/* %BUTTONPLACEHOLDER%*/
// Replaces placeholder with button section in your web page
String processor(const String& var){
 //Serial.println(var);
 if(var == "BUTTONPLACEHOLDER"){
   String buttons = "";
  // buttons += "<div style='display:flex;justify-content:space-between'><a href='http://192.168.4.1/7/open'><button class='borderButtonBMB' style='border:2px solid #4682b4'><div style='display:flex;align-items:stretch'><div style='width:5vw;align-items:center'><p>8</p></div><div style='border:1px solid #fff;display:block;width:38vw'><div style='display:flex'><div style='margin:.5vw'>No connection</div></div><div style='display:flex'><div style='margin:.5vw'>detected</div></div></div></div></button></a><a href='http://192.168.4.1/8/open'><button class='borderButtonBMB' style='border:2px solid #4682b4'><div style='display:flex;align-items:stretch'><div style='border:1px solid #fff;display:block;width:38vw'><div style='display:flex'><div style='margin:.5vw'>No connection</div></div><div style='display:flex'><div style='margin:.5vw'>detected</div></div></div><div style='width:5vw;align-items:center'><p>9</p></div></div></button></a></div>";
  // buttons += "<h4>Output - GPIO 4</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"4\" " + outputState(4) + "><span class=\"slider\"></span></label>";
  // buttons += "<h4>Output - GPIO 33</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"33\" " + outputState(33) + "><span class=\"slider\"></span></label>";
   return buttons;
 }
 return String();
}

String outputState(int output){
 if(digitalRead(output)){
   return "checked";
 }
 else {
   return "";
 }
}


//String voltBattery(){
//
//  String jresp;// = "{\"v1\":\""+String(3.333,3)+"\"}";
//  //sprintf(jresp, "{\"v1\":\"%f\",\"v2\":\"%f\",\"v3\":\"%f\", \"v4\":\"%f\",\"v5\":\"%f\",\"v6\":\"%f\" }", 3.333,3.332,3.331,3.334,3.335,3.336);
////  return str;
//}



void setup(){
 // Serial port for debugging purposes
 Serial.begin(115200);

 pinMode(2, OUTPUT);
 digitalWrite(2, LOW);
 pinMode(4, OUTPUT);
 digitalWrite(4, LOW);
 pinMode(33, OUTPUT);
 digitalWrite(33, LOW);

 // Connect to Wi-Fi
    WiFi.mode(WIFI_AP);
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);
  delay(100);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
//   WiFi.begin(ssid, password);
// while (WiFi.status() != WL_CONNECTED) {
//   delay(1000);
//   Serial.println("Connecting to WiFi..");
// }


 // Print ESP Local IP Address
 Serial.println(WiFi.localIP());

 // Route for root / web page
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
   request->send_P(200, "text/html", index_html, processor);
 });
   server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    char dataS[100] ;
    //sprintf(ss, "M%d", i+1);
//    sprintf(dataS, "{'v1':'%.3fv', 'v2':'%.3fv','v3':'%.3fv','v4':'%.3fv','v5':'%.3fv','v6':'%.3fv'}", 
//                                                                                3.333,3.333,3.333,3.333,3.333,3.333
//                                                   );

sprintf(dataS, "{\"v1\":\"%.3fv\",\"v2\":\"%.3fv\",\"v3\":\"%.3fv\", \"v4\":\"%.3fv\",\"v5\":\"%.3fv\",\"v6\":\"%.3fv\"}",3.331,3.332,3.333,3.334,3.335,3.336);
    request->send_P(200, "text/plain", dataS );
  });

 // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
   String inputMessage1;
   String inputMessage2;
   // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
   if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
     inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
     inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
     digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
   }
   else {
     inputMessage1 = "No message sent";
     inputMessage2 = "No message sent";
   }
   Serial.print("GPIO: ");
   Serial.print(inputMessage1);
   Serial.print(" - Set to: ");
   Serial.println(inputMessage2);
   request->send(200, "text/plain", "OK");
 });

 // Start server
 server.begin();
}

void loop() {

}
