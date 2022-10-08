// #include <esp_now.h>
// #include <WiFi.h>


// // Callback when data is received
// void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
//   int dataReceived;
//   memcpy(&dataReceived, incomingData, sizeof(dataReceived));

//   Serial.print("Data Received: ");
//   Serial.println(dataReceived);

//   Serial.println();    
// }

// void setup() {

//   Serial.begin(115200);
//   delay(100);

//   Serial.println("Starting...\n");

//   // Set device as a Wi-Fi Station
//   WiFi.mode(WIFI_STA);

//   // print our mac address
//   Serial.println(WiFi.macAddress());

//   // Init ESP-NOW
//   if (esp_now_init() != ESP_OK) {
//     Serial.println("Error initializing ESP-NOW");
//     for(;;) {      delay(1);  } // do not initialize wait forever
//   }
  
//   Serial.println("initialized ESP-NOW");



//   // Register for a callback function that will be called when data is received
//   esp_now_register_recv_cb(OnDataRecv);

// }

// void loop() {}