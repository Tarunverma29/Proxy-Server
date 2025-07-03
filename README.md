<h1 align="center">🚀 ESP32 Proxy Server</h1>

<p align="center">
A lightweight proxy server built on the ESP32-WROOM-32 to filter, log, and control network traffic in real-time — ideal for IoT security and small network management.
</p>

---

## 📌 Project Overview

The **ESP32 Proxy Server** is an embedded networking project that intercepts and manages HTTP/TCP traffic using the ESP32 microcontroller. It offers logging, filtering, and real-time monitoring via a web-based dashboard.

> 🛡️ A compact, low-power alternative to traditional proxy servers.

---

## 🛠️ Features

- 🌐 **Wi-Fi Station & Access Point** mode
- 🔀 **Request Forwarding** (Client ↔ Proxy ↔ Server)
- 🧪 **Traffic Logging**: IPs, URLs, methods
- 🛡️ **Filtering**: Domain, keywords, IP/MAC whitelist
- 📊 **Web Dashboard** for control and logs
- 🔐 Optional **Authentication & TLS**
---

## 🧪 Technologies Used

- ESP32-WROOM-32
- Arduino IDE / ESP-IDF
- C/C++
- HTML/CSS/JS (for Web UI)
- SPIFFS or LittleFS (for local storage)

---

## 📚 How to Use

1. Clone the repo
2. Open in Arduino IDE or PlatformIO
3. Set your Wi-Fi credentials
4. Upload code to ESP32
5. Connect to ESP32’s hotspot or network
6. Visit the dashboard at `192.168.x.x` to monitor and configure

---

## 🌟 Star this repo

If you found this project helpful, consider giving it a ⭐️ to show support!

