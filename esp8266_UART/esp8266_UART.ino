#include <SoftwareSerial.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    if (gps.encode(Serial.read())) {
      if (gps.location.isValid()) {
        latitude = gps.location.lat();
        lat_str = String(latitude, 6);
        longitude = gps.location.lng();
        lng_str = String(longitude, 6);
      }
    }
    //    Serial.println(lat_str);

    String str2 = "s1";
    String str3 = "s2";
    
    if (str2 != NULL && str3 != NULL) {
      discord.send("http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=" + str2 + "," + str3);
    }
  }
}
