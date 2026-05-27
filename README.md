# ESP32 Wi-Fi CSI Human Movement Detector (RF-Pose)

<img width="1247" height="701" alt="image" src="https://github.com/user-attachments/assets/b700ef7b-4613-4754-9419-0dfa798e0b0a" />


A DIY "See-Through-Wall" radar system built with an ESP32-S3 microcontroller and Machine Learning. This project utilizes Wi-Fi Channel State Information (CSI) to detect physical movements (like human walking) in a room without the need for cameras or traditional motion sensors.

## 🚀 Features
* **Real-time CSI Extraction:** Captures raw CSI sub-carrier data from a standard home Wi-Fi router.
* **Live Signal Visualization:** Plots real-time RSSI/CSI variations using Python and Matplotlib.
* **Automated Data Collection:** Records waveform data into CSV files and labels them for specific activities (e.g., Empty Room, Human Walking).
* **Machine Learning Integration:** Uses `scikit-learn` (Random Forest Classifier) to train a custom AI model based on the collected dataset.
* **Live Detection System:** Real-time inference script that continuously monitors the room and alerts when specific movements are detected.

## 🛠️ Hardware Requirements
* 1x **ESP32-S3** Development Board (Works with standard ESP32 as well).
* 1x Standard Home Wi-Fi Router.
* A PC/Laptop (for serial data processing and running the ML models).
* Micro-USB or USB-C cable for data transfer.

## 💻 Software & Libraries
* **IDE:** VS Code / Cursor with the **PlatformIO** extension.
* **C++ Framework:** Arduino framework for ESP32 (`esp_wifi.h`, `WiFi.h`).
* **Python 3.x**
* **Python Packages:** ```bash
  pip install pyserial matplotlib pandas scikit-learn


## 📂 Project Structure
```text
WiFi_CSI_Transmitter/
│
├── src/
│   └── main.cpp             # ESP32 C++ code for CSI extraction and dummy UDP traffic
├── monitor.py               # Python script for real-time waveform graphing
├── data_collector.py        # Python script to record labeled data into a CSV
├── train_model.py           # Python script to train the Random Forest ML model
├── live_detector.py         # Python script for real-time activity prediction
└── platformio.ini           # PlatformIO configuration file
