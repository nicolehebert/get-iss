// called once on startup
void setup() {
    // For simplicity, we'll format our weather data as text, and pipe it to serial.
    // but you could just as easily display it in a webpage or pass the data to another system.

    // Learn more about the serial commands at https://docs.particle.io/reference/firmware/photon/#serial
    //  for the Photon, or https://docs.particle.io/reference/firmware/core/#serial for the Core
    // You can also watch what's sent over serial with the particle cli with
    //  particle serial monitor
    Serial.begin(115200);
    
    pinMode(D7, OUTPUT);

    // Lets listen for the hook response
    Spark.subscribe("hook-response/get_iss", gotWeatherData, MY_DEVICES);

    // Lets give ourselves 10 seconds before we actually start the program.
    // That will just give us a chance to open the serial monitor before the program sends the request
    for(int i=0;i<10;i++) {
        Serial.println("waiting " + String(10-i) + " seconds before we publish");
        delay(1000);
    }
}


// called forever really fast
void loop() {

    // Let's request the weather, but no more than once every 60 seconds.
    Serial.println("Requesting Weather!");

    // publish the event that will trigger our Webhook
    Particle.publish("get_iss");

    // and wait at least 60 seconds before doing it again
    delay(60000);
}

// This function will get called when weather data comes in
void gotWeatherData(const char *name, const char *data) {
    // Important note!  -- Right now the response comes in 512 byte chunks.  
    //  This code assumes we're getting the response in large chunks, and this
    //  assumption breaks down if a line happens to be split across response chunks.
    //
    // Sample data:
    //  <location>Minneapolis, Minneapolis-St. Paul International Airport, MN</location>
    //  <weather>Overcast</weather>
    //  <temperature_string>26.0 F (-3.3 C)</temperature_string>
    //  <temp_f>26.0</temp_f>


    String str = String(data);
    Serial.print(str);
   // String locationStr = tryExtractString(str, "<location>", "</location>");
    //String weatherStr = tryExtractString(str, "<weather>", "</weather>");
    //String tempStr = tryExtractString(str, "<temp_f>", "</temp_f>");
    //String windStr = tryExtractString(str, "<wind_string>", "</wind_string>");
    //String humidityStr = tryExtractString(str, "<relative_humidity>", "</relative_humidity>");   //humidity check added here

  //  if (locationStr != NULL) {
    //     Serial.println("At location: " + locationStr);
    // }

    // if (weatherStr != NULL) {
    //     Serial.println("The weather is: " + weatherStr);
    // }

    // if (tempStr != NULL) {
    //     Serial.println("The temp is: " + tempStr + String(" *F"));
    // }

    // if (windStr != NULL) {
    //     Serial.println("The wind is: " + windStr);
    // }
    
    //  if (humidityStr != NULL) {
    //     Serial.println("The humidity is: " + humidityStr);
    // }
    
    //  if (humidityStr.toInt() > 95){   //if humidity is above 95 the LED will blink 10 times every minute to indicate possible rainfall
    //      for(int i=0;i<10;i++){
    //         digitalWrite(D7,HIGH);
    //         delay(500);
    //         digitalWrite(D7,LOW);
    //         delay(500);
    //      }
    // }
}

// Returns any text found between a start and end string inside 'str'
// example: startfooend  -> returns foo
String tryExtractString(String str, const char* start, const char* end) {
    if (str == NULL) {
        return NULL;
    }

    int idx = str.indexOf(start);
    if (idx < 0) {
        return NULL;
    }

    int endIdx = str.indexOf(end);
    if (endIdx < 0) {
        return NULL;
    }

    return str.substring(idx + strlen(start), endIdx);
}
