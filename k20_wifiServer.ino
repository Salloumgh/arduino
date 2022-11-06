#include <ESP8266Web.h>
#include <ESP8266WiFi.h>

IPAddress    apIP(55, 55, 55, 55);
const char* ssid = "Dht_data_WiFi"; // שם הרשת שיוצג
ESP8266Web (80);


void wifi_setup() {
	WiFi.mode(WIFI_AP_STA);
	WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00   
	WiFi.softAP(ssid);
	//WiFi.softAP(ssid,password); // עם סיסמא
	.on("/", handleRoot);
	.onNotFound(handleNotFound);
	.begin();
}

void handleRoot() {
	char html[2000] = "";
	strcat(html, "<!DOCTYPE html>");
	strcat(html, "<html>");
	strcat(html, "<head>");
	strcat(html, "<meta charset=\"utf-8\" />");
	//https://www.w3schools.com/tags/att_meta_http_equiv.asp
	strcat(html, "<meta http-equiv=\"refresh\" content = \"5\">");
	strcat(html, "<title>Last Minute Tempratures</title>");
	strcat(html, "<style>");
	strcat(html, "td{border:1px solid black;}");
	strcat(html, "</style>");
	strcat(html, "</head>");
	strcat(html, "<body>");
	strcat(html, "<table>");
	strcat(html, "<tr>");
	strcat(html, "<th>#</th>");
	strcat(html, "<th>value</th>");
	strcat(html, "</tr>");
	char tmp[3]="";
	char dataTmp[7] = "";
	for (int k = SAMPLES_PER_MINUTE-1; k >= 0; k--) {
		strcat(html, "<tr>");
		strcat(html, "<td>");
		itoa(k, tmp, 10);
		strcat(html, tmp);
		strcat(html, "</td>");
		strcat(html, "<td>");
		dtostrf(LastMinSamples[k], 6, 2, dataTmp);//https://www.programmingelectronics.com/dtostrf/
		strcat(html, dataTmp);
		strcat(html, "</td>");
		strcat(html, "</tr>");
	}
	strcat(html, "</table>");
	strcat(html, "</body>");
	strcat(html, "</html>");

	.send(200, "text/html", html);
}

void wifi_loop() {
	.handleClient();//  is defined at this tab
	delay(10);
}
void handleNotFound() {
	String message = "File Not Foundnn";
	message += "URI: ";
	message += .uri();
	message += "\nMethod: ";
	message += (.method() == HTTP_GET) ? "GET" : "POST";
	message += "\nArguments: ";
	message += .args();
	message += "\n";

	for (uint8_t i = 0; i < .args(); i++) {
		message += " " + .argName(i) + ": " + .arg(i) + "\n";
	}
}

