
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
#include <EEPROM.h>

// Replace with your network credentials
const char* ssid = "NKService";
const char* password = "NKService123";
IPAddress apIP(192, 168, 4, 1);
const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncEventSource events("/events");
/**/


 #include "BMSModuleManager.h"
 #define Slave_ID1 2
 #define Slave_ID2 1
//
 uint8_t fault_1 = 5;
 uint8_t fault_2 = 24;

 #define RXD1 15 //RX1 pin
 #define TXD1 4 //TX1 pin

 #define RXD2 16 //RXX2 pin
 #define TXD2 17 //TX2 pin

 //#define BMS_BAUD  612500
 #define BMS_BAUD  617647
 //#define BMS_BAUD  608695

 const uint8_t countBmb = 16;
 const float DeltaInBMB = 0.010;
 const float DeltaInACB = 0.10;

 uint8_t dispalyPage = 1;//1--домашня сторінка
 uint8_t helpData = 0;

 float voltAVG  [countBmb][6];//збереження значень для виводу
 float volt     [6];//таблиця для тимчасового зберігання вольт
 float sumD[countBmb] = {0};
 float FullVolt = 0;
 uint8_t indexMinVoltBatery[2];
 uint8_t indexMaxVoltBatery[2];
 const float critDisbalanse = 0.01;
 bool isCritDisbalanse;

 float maxFVolt = 0;
 float minFVolt = 0;
 float maxFTemp = 0;
 float minFTemp = 0;
 uint8_t indexMax =0;
 bool isCrit = 0;
 uint8_t indexMin =0;

uint8_t countBalansing = 0;//кільксть циклів балансування  

 float tempAVG  [countBmb][2];//збереження значень для виводу
 float temp     [2];//таблиця для тимчасового зберігання температури
 bool balanse[countBmb] = {false};
 bool isBalanse = false;
 BMSModuleManager bms;
 uint8_t countBord = 0; //кількість плат
 unsigned long time1;
 unsigned long time2;


const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
   <head>
   <meta http-equiv="Content-Type" content="text/html; charset=windows-1252"><meta name="viewport" content="width=device-width, initial-scale=1">
       <style>html { font-family: Helvetica;  display: inline-block; margin: 0px auto;background-color:black;color:white; padding:0;}</style>
       <style>.borderButtonBMB {margin-top:0.5vh; color:white; font-size:3.5vw;background-color:black; padding:1%%;width:48%%}</style>
       <style>.dot {height: 3.5vw;width: 3.5vw;background-color: white;border-radius: 50%%; margin:0.2vw; }</style>
       <style>.divButton{display: flex;  flex-direction: row; align-items:stretch;justify-content: center; font-size:3.5vw;}</style>
       <style>.divBattrySelect{display: flex;  flex-direction: row; align-items:stretch;justify-content: center; font-size:3.5vw;}</style>
       <style>#divCollDataTemp{width:20vw; margin-left:1.5vw; color:Aquamarine; align-items:center;}</style>
       <style>#divCollDataState{flex-direction: colomn; align-items:stretch;justify-content:stretch;}</style>
       <style>#fault{font-size:9.5vw;color:red;text-align:center;}</style>
       <style>.sticky{position: sticky; top: 0; background-color:black; padding-bottom:2px; border-bottom:2px solid #fff;}</style>

       <script>
          var dataBattery; 
          var blockSelected;
          var idBlockSelected;

          function balancing(element){
              var xhr = new XMLHttpRequest();
              xhr.open("GET", "/balanse?value="+element, true);
              xhr.send();
          }

          function BMBReconect(){
              var xhr = new XMLHttpRequest();
              xhr.open("GET", "/reconnection", true);
              xhr.send();
          }
          
          function closeBlock(e){
            var bodyDiv = document.getElementById('SelectBlock');
            bodyDiv.innerHTML = "";
            blockSelected = flase;
            idBlockSelected =-1;
          }
       
          function clickBlock(element){
            blockSelected = true;
            idBlockSelected = element.id.split('_')[1]-1;
            
            var bodyDiv = document.getElementById('SelectBlock');
            bodyDiv.innerHTML = "";
                          
            var divBattrySelect = document.createElement("div");
            divBattrySelect.className = "divBattrySelect";

            var numberModuleSelect = document.createElement("h3");  
            numberModuleSelect.style.width = "11vw"; 
            numberModuleSelect.innerHTML = "M"+element.id.split('_')[1];

           
             var divCollData = document.createElement('div');
             divCollData.style.border = "1px solid white";
             divCollData.style.display = "block"; 
             divCollData.style.width = "38vw";
             divCollData.id = "divCollDataVolt"
  
             for(var r = 0; r <2;r++){
                 var divRowColl = document.createElement('div');
                 divRowColl.style.display = "flex";
                 for(var t = 0; t < 3;t ++){
                     var span = document.createElement('span');                               
                     span.style.margin = "1vw";
                     span.style.flexGrow  = "1";
                     span.style.textAlign = "center";
                     if(element.id.split('_')[1] < 9){
                        span.className = "bat_"+(5-(3*r + t));
                     }
                     else{
                         span.className = "bat_"+((3*r + t));;
                     }
                     span.innerHTML ="-.---v";
                     divRowColl.appendChild(span);
                     
                 }
                 divCollData.appendChild(divRowColl);
             }

             var divCollDataTemp = document.createElement('div');
             divCollDataTemp.id = "divCollDataTemp";

                var divTemp1 = document.createElement('div');
                divTemp1.innerHTML  = "T1 ="+12.3+"*C";
                divCollDataTemp.appendChild(divTemp1);
                var brTemp = document.createElement('br');
                divCollDataTemp.appendChild(brTemp);
                var divTemp2 = document.createElement('div');
                divTemp2.innerHTML  = "T2 ="+12.3+"*C";
                divCollDataTemp.appendChild(divTemp2);

             var divCollDataState = document.createElement('div');
             divCollDataState.id = "divCollDataState";
             
             var divFullVolt = document.createElement('div');
             divFullVolt.innerHTML  = "Full V "+ "--.--";

             divCollDataState.appendChild(divFullVolt);

             var brTemp = document.createElement('br');
             divCollDataState.appendChild(brTemp);

             var divBalanseState = document.createElement('div');
             divBalanseState.innerHTML  = "Balanse off";
             divCollDataState.appendChild(divBalanseState); 
              
             var divButton = document.createElement("div");
             divButton.style.display = "flex"
             divButton.style.justifyContent = "space-between";
             divButton.className = "divButton"
             var buttonBalansing = document.createElement('button');
             buttonBalansing.className = "borderButtonBMB";
             buttonBalansing.style.border = "2px solid SteelBlue";
             buttonBalansing.style.padding = "2%%"; 
             buttonBalansing.innerHTML ="Enable balancing";
             buttonBalansing.setAttribute("onclick","balancing("+element.id.split('_')[1]+")",false);
             
             var buttonHome = document.createElement("button");
             buttonHome.className = "borderButtonBMB";
             buttonHome.style.border = "2px solid SteelBlue";
             buttonHome.style.padding = "2%%";
             buttonHome.innerHTML ="Close";
             buttonHome.setAttribute("onclick","closeBlock(this)",false);
             
             divBattrySelect.appendChild(numberModuleSelect);
             divBattrySelect.appendChild(divCollData);
             divBattrySelect.appendChild(divCollDataTemp);
             divBattrySelect.appendChild(divCollDataState);            
             divButton.appendChild(buttonHome);
             divButton.appendChild(buttonBalansing);
             bodyDiv.appendChild(divBattrySelect);
             bodyDiv.appendChild(divButton);
             writeDataSelect();
          }
       
           function loadPage(){      
              var bodyDiv = document.getElementById('bodyDiv');

              bodyDiv.innerHTML ="";// element.id.split('_');       
               for(var i = 8,j =9;i>0;i--,j++ ){
                   var divRow = document.createElement('div');
                   divRow.style.display = "flex"
                   divRow.style.justifyContent = "space-between";
                   for(var  z =0 ; z<2;z++){                       
                       var button = document.createElement('button');
                       button.className = "borderButtonBMB";
                       

                       var divColl = document.createElement('div');
                       divColl.style.display =  "flex";
                       divColl.style.alignItems = "stretch";
                       
                       var divCollData = document.createElement('div');
                       divCollData.style.border = "1px solid #fff";
                       divCollData.style.display = "block"; 
                       divCollData.style.width = "38vw";
                       
                       var divCollNumber = document.createElement('div');
                       divCollNumber.style.width = "5vw";
                       divCollNumber.style.alignItems = "center";
                       var pNuber =  document.createElement('p');
                       for(var r = 0; r <2;r++){
                           var divRowColl = document.createElement('div');
                           divRowColl.style.display = "flex";
                           for(var t = 0; t < 3;t ++){
                               var span = document.createElement('span');                               
                               span.style.margin = "1vw";
                               span.style.flexGrow  = "1";
                               span.style.textAlign = "center";
                               if(z == 0){
                                  span.className = "bat_"+(5-(3*r + t));
                               }
                               else{
                                   span.className = "bat_"+((3*r + t));;
                               }
                               span.innerHTML ="-.---v";
                               divRowColl.appendChild(span);         
                           }
                           divCollData.appendChild(divRowColl);
                       }                  
                      if(z == 0){
                          pNuber.innerHTML = i;
                          divCollNumber.appendChild(pNuber);
                          button.id = "Block_"+i; 
                          divColl.appendChild(divCollNumber);
                          divColl.appendChild(divCollData);
                       }
                       else{
                        pNuber.innerHTML = j;
                        divCollNumber.appendChild(pNuber); 
                        button.id = "Block_"+j;
                        divColl.appendChild(divCollData);
                        divColl.appendChild(divCollNumber);    
                       }
                       button.appendChild(divColl);
                       divRow.appendChild(button);
                   }
                   bodyDiv.appendChild(divRow);
               }
           }

function writeDataSelect(){
  if(dataBattery.battery[idBlockSelected].isD == 1){
    debugger
    var voltSelected = document.getElementById("divCollDataVolt");
    voltSelected.getElementsByClassName("bat_5")[0].innerHTML = dataBattery.battery[idBlockSelected].v6;
    colorElementa(voltSelected.getElementsByClassName("bat_5")[0],dataBattery.battery[idBlockSelected].cb6);
    voltSelected.getElementsByClassName("bat_4")[0].innerHTML = dataBattery.battery[idBlockSelected].v5;
    colorElementa(voltSelected.getElementsByClassName("bat_4")[0],dataBattery.battery[idBlockSelected].cb5);
    voltSelected.getElementsByClassName("bat_3")[0].innerHTML = dataBattery.battery[idBlockSelected].v4;
    colorElementa(voltSelected.getElementsByClassName("bat_3")[0],dataBattery.battery[idBlockSelected].cb4);
    voltSelected.getElementsByClassName("bat_2")[0].innerHTML = dataBattery.battery[idBlockSelected].v3;
    colorElementa(voltSelected.getElementsByClassName("bat_2")[0],dataBattery.battery[idBlockSelected].cb3);
    voltSelected.getElementsByClassName("bat_1")[0].innerHTML = dataBattery.battery[idBlockSelected].v2;
    colorElementa(voltSelected.getElementsByClassName("bat_1")[0],dataBattery.battery[idBlockSelected].cb2);
    voltSelected.getElementsByClassName("bat_0")[0].innerHTML = dataBattery.battery[idBlockSelected].v1;
    colorElementa(voltSelected.getElementsByClassName("bat_0")[0],dataBattery.battery[idBlockSelected].cb1);
    
    var tempSelected = document.getElementById("divCollDataTemp");
    tempSelected.getElementsByTagName("div")[0].innerHTML = "T1 ="+dataBattery.battery[idBlockSelected].t1+"*C";
    tempSelected.getElementsByTagName("div")[1].innerHTML = "T2 ="+dataBattery.battery[idBlockSelected].t2+"*C";  
  
    var stateSelected = document.getElementById("divCollDataState");
    stateSelected.getElementsByTagName("div")[0].innerHTML = "Full V "+dataBattery.battery[idBlockSelected].fv;
    if(dataBattery.battery[idBlockSelected].bal == 1){
      stateSelected.getElementsByTagName("div")[1].innerHTML = "Balanse ON";
      stateSelected.getElementsByTagName("div")[1].style.color = "green";
    }  
    else{
      stateSelected.getElementsByTagName("div")[1].innerHTML = "Balanse OFF";
      stateSelected.getElementsByTagName("div")[1].style.color = "red";
    }

  }
  else{
    var voltSelected = document.getElementById("divCollDataVolt");
    voltSelected.getElementsByClassName("bat_5")[0].innerHTML = "-.---v";
    voltSelected.getElementsByClassName("bat_4")[0].innerHTML = "-.---v";
    voltSelected.getElementsByClassName("bat_3")[0].innerHTML = "-.---v";
    
    voltSelected.getElementsByClassName("bat_2")[0].innerHTML = "-.---v";
    voltSelected.getElementsByClassName("bat_1")[0].innerHTML = "-.---v";
    voltSelected.getElementsByClassName("bat_0")[0].innerHTML = "-.---v";
    
    var tempSelected = document.getElementById("divCollDataTemp");
    tempSelected.getElementsByTagName("div")[0].innerHTML = "T1 =--.-*C";
    tempSelected.getElementsByTagName("div")[1].innerHTML = "T2 =--.-*C"; 
  
    var stateSelected = document.getElementById("divCollDataState");
    stateSelected.getElementsByTagName("div")[0].innerHTML = "Full V --.-";
    if(dataBattery.battery[idBlockSelected].bal == 1){
      stateSelected.getElementsByTagName("div")[1].innerHTML = "Balanse ON";
      stateSelected.getElementsByTagName("div")[1].style.color = "green";
    }  
    else{
      stateSelected.getElementsByTagName("div")[1].innerHTML = "Balanse OFF";
      stateSelected.getElementsByTagName("div")[1].style.color = "red";
    }
  }
}

function colorElementa(element,idColor){
  switch(idColor){
    case "0": element.style.background = "#000";break;
    case "1": element.style.background = "#608b37";break;
    case "2": element.style.background = "DarkOrange";break;
    case "3": element.style.background = "DarkRed";break;
  }
}

if (!!window.EventSource) {
  var source = new EventSource('/events');

  source.addEventListener('open', function(e) {
    console.log("Events Connected");
  }, false);

  source.addEventListener('error', function(e) {
    if (e.target.readyState != EventSource.OPEN) {
      console.log("Events Disconnected");
    }
  }, false);

  source.addEventListener('message', function(e) {
    console.log("message", e.data);
  }, false);

  source.addEventListener('myevent', function(e) {
    console.log("myevent", e.data);
  }, false);
  source.addEventListener('battery', function(e) {
    //debugger
    var msg = JSON.parse(e.data);
    dataBattery = msg; 
    document.getElementById("FullVolt").innerHTML = msg.fullVolt;
    
    for(var i =0 ; i <msg.battery.length-1;i++){
      if(dataBattery.battery[i].isD == 1){
        var block = document.getElementById("Block_"+msg.battery[i].b1);
        block.getElementsByClassName("bat_5")[0].innerHTML = msg.battery[i].v6+"v";
        colorElementa(block.getElementsByClassName("bat_5")[0],msg.battery[i].c6);
        block.getElementsByClassName("bat_4")[0].innerHTML = msg.battery[i].v5+"v";
        colorElementa(block.getElementsByClassName("bat_4")[0],msg.battery[i].c5);
        block.getElementsByClassName("bat_3")[0].innerHTML = msg.battery[i].v4+"v";
        colorElementa(block.getElementsByClassName("bat_3")[0],msg.battery[i].c4);
        block.getElementsByClassName("bat_2")[0].innerHTML = msg.battery[i].v3+"v";
        colorElementa(block.getElementsByClassName("bat_2")[0],msg.battery[i].c3);
        block.getElementsByClassName("bat_1")[0].innerHTML = msg.battery[i].v2+"v";
        colorElementa(block.getElementsByClassName("bat_1")[0],msg.battery[i].c2);
        block.getElementsByClassName("bat_0")[0].innerHTML = msg.battery[i].v1+"v";
        colorElementa(block.getElementsByClassName("bat_0")[0],msg.battery[i].c1);
        if(msg.battery[i].bal == 1){ 
          block.style.border = "2px solid Aquamarine";
        }  
        else{
          block.style.border = "2px solid SteelBlue";
        }
        if(msg.fault == 1){
        }
        else{
          block.setAttribute("onclick","clickBlock(this)",false);
        }

      }
      else{
        var block = document.getElementById("Block_"+msg.battery[i].b1);
        block.getElementsByClassName("bat_5")[0].innerHTML = "-.---v";
        colorElementa(block.getElementsByClassName("bat_5")[0],"0");
        block.getElementsByClassName("bat_4")[0].innerHTML = "-.---v";
        colorElementa(block.getElementsByClassName("bat_4")[0],"0");
        block.getElementsByClassName("bat_3")[0].innerHTML = "-.---v";
        colorElementa(block.getElementsByClassName("bat_3")[0],"0");
        block.getElementsByClassName("bat_2")[0].innerHTML = "-.---v";
        colorElementa(block.getElementsByClassName("bat_2")[0],"0");
        block.getElementsByClassName("bat_1")[0].innerHTML = "-.---v";
        colorElementa(block.getElementsByClassName("bat_1")[0],"0");
        block.getElementsByClassName("bat_0")[0].innerHTML = "-.---v";
        colorElementa(block.getElementsByClassName("bat_0")[0],"0");
        block.style.border = "2px solid grey";
      }
    }
      if(blockSelected){
          writeDataSelect();
      }
      if(msg.fault == 1){
        document.getElementById("fault").innerHTML = "Fault";
        document.getElementById("faultPoint").style.backgroundColor = "red"; 
      }
      else{
        document.getElementById("fault").innerHTML = "";
        document.getElementById("faultPoint").style.backgroundColor = "green";
      }
    //console.log(msg.v1);
  }, false);
}


       </script>
   </head>
   <body onload="loadPage()">
    <section class="sticky">
   <div style="display: flex; vertical-align: middle; justify-content: space-around;"><div style="display: flex; vertical-align: middle;">
    <span class="dot" id="faultPoint"></span>
    </div><span style="color:White; font-size:3.5vw;">Full Volt: <span id="FullVolt">---.--</span> V</span>
    <button class="button" style="font-size:3.5vw;  border-radius:20px;  background:Silver;" onclick="BMBReconect()">&#8634; BMB</button>
    </div>
    <div id="fault"></div>
    <div id='SelectBlock'>
    </div>
    </section>
    <section>
       <div id='bodyDiv'>


       </div>
</section>
       
   </body>
</html>
)rawliteral";



// Replaces placeholder with button section in your web page
String processor(const String& var){
 //Serial.println(var);
 if(var == "BUTTONPLACEHOLDER"){
   return "";//buttons;
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

uint8_t returnColorVolt(uint8_t i,uint8_t j){
    if(voltAVG[i][j] == voltAVG[indexMaxVoltBatery[0]][indexMaxVoltBatery[1]] && !isCritDisbalanse){return 2;}//оранжевий 
    else if(voltAVG[i][j] == voltAVG[indexMinVoltBatery[0]][indexMinVoltBatery[1]]){     return 1;}//зелений
    else if(voltAVG[i][j] == voltAVG[indexMaxVoltBatery[0]][indexMaxVoltBatery[1]] && isCritDisbalanse){return 3;}//червоний 
    else{return 0;}//чорний 
}

uint8_t returnColorBlock(uint8_t i,uint8_t j){

  float maxD = voltAVG[i][0];
  float minD = voltAVG[i][0];
  bool indexMaxCrit;
  int indexMaxBMB = 0;
  int indexMinBMB = 0;
  for(int j = 0 ; j < 6;j++){
    if(maxD<voltAVG[i][j]){
      maxD = voltAVG[i][j];
      indexMaxBMB = j;
    }
    if(minD>voltAVG[i][j]){
      minD = voltAVG[i][j];
      indexMinBMB  = j;
    }
  }
  if(abs(minD-maxD)>DeltaInBMB){indexMaxCrit =true;}
  else{indexMaxCrit =false;}

  if(voltAVG[i][j] == voltAVG[i][indexMaxBMB] && !indexMaxCrit){return 2;}//оранжевий 
  else if(voltAVG[i][j] == voltAVG[i][indexMinBMB]){return 1;}//зелений
  else if(voltAVG[i][j] == voltAVG[i][indexMaxBMB] && indexMaxCrit){return 3;}//червоний 
  else{return 0;}//чорний 
}


void sendDataToClient(){
    String  dataS;
    dataS = "{\"fullVolt\":\""+String(FullVolt)+"\",\"fault\":\""+String(!digitalRead(fault_1))+"\",\"battery\":[";
    for(int n = 0 ; n <16; n++){
      dataS += "{\"b1\":\""+String(n+1)+"\",\"bal\":\""+String(balanse[n])+"\","+
                    +"\"v1\":\""+String(voltAVG[n][0],3)+"\",\"c1\":\""+String(returnColorVolt(n,0))+"\",\"cb1\":\""+String(returnColorBlock(n,0))+"\","+
                    +"\"v2\":\""+String(voltAVG[n][1],3)+"\",\"c2\":\""+String(returnColorVolt(n,1))+"\",\"cb2\":\""+String(returnColorBlock(n,1))+"\","+
                    +"\"v3\":\""+String(voltAVG[n][2],3)+"\",\"c3\":\""+String(returnColorVolt(n,2))+"\",\"cb3\":\""+String(returnColorBlock(n,2))+"\","+
                    +"\"v4\":\""+String(voltAVG[n][3],3)+"\",\"c4\":\""+String(returnColorVolt(n,3))+"\",\"cb4\":\""+String(returnColorBlock(n,3))+"\","+
                    +"\"v5\":\""+String(voltAVG[n][4],3)+"\",\"c5\":\""+String(returnColorVolt(n,4))+"\",\"cb5\":\""+String(returnColorBlock(n,4))+"\","+
                    +"\"v6\":\""+String(voltAVG[n][5],3)+"\",\"c6\":\""+String(returnColorVolt(n,5))+"\",\"cb6\":\""+String(returnColorBlock(n,5))+"\","+
                    +"\"t1\":\""+String(tempAVG[n][0],1)+"\",\"t2\":\""+String(tempAVG[n][1],1)+"\","+
                    +"\"fv\":\""+String(sumD[n],1)+"\",\"isD\":\""+String(bms.getIsExisting(n+1))+"\""+
                    +"},";
                    
    }
    dataS +="{}]}";
    //sprintf(dataS, "{\"v1\":\"%.3fv\",\"v2\":\"%.3fv\",\"v3\":\"%.3fv\",\"v4\":\"%.3fv\",\"v5\":\"%.3fv\",\"v6\":\"%.3fv\"}",3.331,3.332,3.333,3.334,3.335,3.336);
    events.send(String(dataS).c_str(),"battery",millis());
}


 void prsingDataVoltTemp(){
   int i =0;
   FullVolt = 0;
   float maxVoltBat = 0;
   float minVoltBat = 5;
   indexMinVoltBatery[0] = 0;
   indexMaxVoltBatery[0] = 0;
   indexMinVoltBatery[1] = 0;
   indexMaxVoltBatery[1] = 0;
   while(bms.getStatusModule(i+1)){
       bms.getTempCell(i+1,temp);
       bms.getVoltCell(i+1,volt);
       sumD[i] = 0;
       for(int j = 0 ; j <6;j++){
           voltAVG[i][j] = round(volt[j]*500)/500;
           if(maxVoltBat<voltAVG[i][j]){
             maxVoltBat = voltAVG[i][j];
             indexMaxVoltBatery[0] = i;
             indexMaxVoltBatery[1] = j;
           }
           if(minVoltBat>voltAVG[i][j]){
             minVoltBat=voltAVG[i][j];
             indexMinVoltBatery[0] = i;
             indexMinVoltBatery[1] = j;
           }
           sumD[i] += volt[j];
           FullVolt+= volt[j];
       }
       for(int j = 0 ; j <2;j++){
           tempAVG[i][j] = temp[j];
       }
       i++;
     }
     maxFVolt = sumD[0];
     minFVolt = sumD[0];
     indexMax =0;
     indexMin =0;
     if(abs(maxVoltBat-minVoltBat)>critDisbalanse){isCritDisbalanse =true;}
     else{isCritDisbalanse =false;}
     for(int i =0 ; i <countBmb;i++){
       if(bms.getStatusModule(i+1)){
         if(maxFVolt<sumD[i]){
           maxFVolt=sumD[i];
           indexMax = i;
         }
         if(minFVolt>sumD[i]){
           maxFVolt=sumD[i];
           indexMin = i;
         }
       }
       if(abs(maxFVolt-minFVolt)>DeltaInACB){isCrit =true;}
       else{isCrit =false;}
     }

//    maxFTemp = tempAVG[0][0];
//    minFTemp = tempAVG[0][0];
//   for(int i =0 ; i <countBmb;i++){
//     if(bms.getStatusModule(i+1)){
//       if(maxFTemp<sumD[i]){
//         maxFTemp=sumD[i];
//       }
//       if(minFVolt>sumD[i]){
//         maxFVolt=sumD[i];
//       }
//     }
//   }
 }


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
//    WiFi.mode(WIFI_AP);
  // Remove the password parameter, if you want the AP (Access Point) to be open
//  WiFi.softAP(ssid, password);
//  delay(100);
//  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
   delay(1000);
   Serial.println("Connecting to WiFi..");
 }
 // Print ESP Local IP Address
 Serial.println(WiFi.localIP());
 // Route for root / web page
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
   request->send_P(200, "text/html", index_html, processor);
 });
  server.on("/reconnection", HTTP_GET, [](AsyncWebServerRequest *request){
     bms.renumberBoardIDs();
     bms.clearFaults();
     countBord = bms.getNumFoundModules();//визначення кількості плат
     bms.getAllVoltTemp();//отримання даних з про вологість та температуру

     bms.getAllVoltTemp();//отримання даних з про вологість та температуру
     prsingDataVoltTemp();
    request->send(200, "text/plain", "OK");
    sendDataToClient();
  });
  
  server.on("/balanse", HTTP_GET, [](AsyncWebServerRequest *request){
    String inputMessage;
    if (request->hasParam("value")) {
      inputMessage = request->getParam("value")->value();
      balanse[inputMessage.toInt()-1] = !balanse[inputMessage.toInt()-1];
    }
    else {
      inputMessage = "No message sent";
    }
    request->send(200, "text/plain", "OK");
    sendDataToClient();
  });
 
  events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it gat is: %u\n", client->lastId());
    }
    //send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!",NULL,millis(),1000);
  });
  //HTTP Basic authentication
  server.addHandler(&events);
 // Start server
 server.begin();

   Serial2.begin(617647, SERIAL_8N1, RXD2, TXD2);
   pinMode(fault_1, INPUT);//fault
   pinMode(fault_2, INPUT);//fault


   bms.renumberBoardIDs();
   bms.clearFaults();
   countBord = bms.getNumFoundModules();//визначення кількості плат
   bms.getAllVoltTemp();//отримання даних з про вологість та температуру
   bms.getAllVoltTemp();//отримання даних з про вологість та температуру
   prsingDataVoltTemp();





 time1 = millis();
}



void loop() {
  if(time1+100<millis()){
    
     bms.getAllVoltTemp();//отримання даних з про вологість та температуру
     prsingDataVoltTemp();
     if(isBalanse){
       sendDataToClient();
       bms.balanceCells((uint8_t *)balanse);
       isBalanse = false;
     }
     else if(countBalansing > 9){
       bms.balanceCellsOff();
       isBalanse = true;
       countBalansing = 0;
     }
    countBalansing++;

    time1 = millis();
  }


}
