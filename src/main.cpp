#include <WiFi.h>
#include <esp_wifi.h>
#include <WiFiUdp.h> // 🟢 Newly added (To maintain continuous traffic)

const char *ssid = ".....";
const char *password = "........";

WiFiUDP udp;
IPAddress gatewayIP;

// Function that triggers when Wi-Fi CSI data is received
void csi_callback(void *ctx, wifi_csi_info_t *data) {
  wifi_csi_info_t d = data[0];
  
  if (d.len > 0) { 
    Serial.print("Router Signal Received! | RSSI: ");
    Serial.print(d.rx_ctrl.rssi);
    Serial.print(" | CSI Data Bytes: ");
    Serial.println(d.len);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n--- ESP32-S3 Wi-Fi CSI Scanner ---");
  Serial.print("Connecting to Home Router...");
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nSuccessfully connected to the Router!");

  // Get the Router's IP Address
  gatewayIP = WiFi.gatewayIP();

  // Turn OFF Wi-Fi Power Saving Mode (to capture raw signals continuously)
  esp_wifi_set_ps(WIFI_PS_NONE);

  wifi_csi_config_t csi_config = {
      .lltf_en           = true,
      .htltf_en          = true,
      .stbc_htltf2_en    = true,
      .ltf_merge_en      = true,
      .channel_filter_en = true,
      .manu_scale        = false,
      .shift             = false
  };
  
  esp_wifi_set_csi_config(&csi_config);
  esp_wifi_set_csi_rx_cb(&csi_callback, NULL);
  esp_wifi_set_csi(true);
  
  Serial.println("CSI Tracking Active! Collecting data...");
}

void loop() {
  // 🟢 To maintain a continuous connection with the router and receive CSI Data,
  // we send a small "dummy" packet to the router.
  udp.beginPacket(gatewayIP, 8080);
  udp.write('X'); // Send a random character
  udp.endPacket();

  // Wait 100 milliseconds (Sends 10 times per second)
  delay(100); 
}