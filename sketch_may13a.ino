#include <WiFi.h>
#include <WiFiClient.h>

WiFiServer server(8080); // Proxy listens on port 8080

void setup() {
  Serial.begin(115200);

  WiFi.begin("JioFiber4G", "12345678");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected");

    // Read HTTP request from client
    String req = "";
    unsigned long timeout = millis() + 2000; // Timeout after 2s
    while (client.connected() && millis() < timeout) {
      while (client.available()) {
        char c = client.read();
        req += c;
        if (req.endsWith("\r\n\r\n")) break;
      }
    }

    if (req.length() == 0) {
      client.stop();
      Serial.println("Empty request, disconnected");
      return;
    }

    Serial.println("Request from client:");
    Serial.println(req);

    // Parse host from request
    int hostIndex = req.indexOf("Host: ");
    if (hostIndex == -1) {
      client.println("HTTP/1.1 400 Bad Request\r\n\r\nMissing Host header");
      client.stop();
      return;
    }

    hostIndex += 6; // Move past "Host: "
    int endHostIndex = req.indexOf("\r\n", hostIndex);
    if (endHostIndex == -1) {
      client.println("HTTP/1.1 400 Bad Request\r\n\r\nMalformed Host header");
      client.stop();
      return;
    }

    String host = req.substring(hostIndex, endHostIndex);
    host.trim();

    Serial.print("Forwarding to host: ");
    Serial.println(host);

    // Forward request to real server
    WiFiClient forwardClient;
    if (forwardClient.connect(host.c_str(), 80)) {
      forwardClient.print(req); // send original request

      // Read response from remote and send back to original client
      while (forwardClient.connected()) {
        while (forwardClient.available()) {
          char c = forwardClient.read();
          client.write(c);
        }
      }
      forwardClient.stop();
    } else {
      client.println("HTTP/1.1 502 Bad Gateway\r\n\r\nFailed to connect to host");
    }

    client.stop();
    Serial.println("Client disconnected\n");
  }
}
