# Gemini ESP32 Web AI Chat

Proyek ini memungkinkan ESP32 untuk menjadi web server yang menghosting antarmuka chat berbasis Gemini API langsung dari perangkat IoT. Dibuat menggunakan **Arduino IDE**, proyek ini memungkinkan pengguna untuk berinteraksi dengan Gemini AI melalui jaringan lokal.

## Fitur

* Menjadikan ESP32 sebagai web server (port 80)
* Antarmuka web interaktif dengan UI modern
* Menggunakan Gemini 2.0 Flash API dari Google untuk pemrosesan pertanyaan
* Mendukung respons markdown (ditampilkan dengan `marked.js`)
* Optimal untuk perangkat low-power seperti ESP32

## Prasyarat

* **ESP32 Board**
* **Arduino IDE** dengan:

  * Board ESP32 sudah diinstal [arduino-esp32](https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json)
  * Library `WiFi.h` dan `WebServer.h` (biasanya sudah bawaan ESP32 core)
* API Key dari [Google AI Studio](https://aistudio.google.com)
* Koneksi Wi-Fi aktif

## Instalasi

### Cara 1: Clone dan buka langsung

1. **Clone repositori ini**

   ```bash
   git clone https://github.com/Katryoshkh/Gemini-ESP32-Web-AI-Chat.git
   ```

2. **Buka file `.ino`**

   Buka file `Gemini-ESP32-Web-AI-Chat/Gemini-ESP32-Web-AI-Chat.ino` di Arduino IDE.

3. **Masukkan kredensial Wi-Fi & API Key**

   ```cpp
   const char* ssid = "YOUR_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";
   ...
   const API_KEY = "YOUR_API_KEY";
   ```

4. **Unggah ke ESP32**

   Pastikan board dan port sudah benar di Arduino IDE.

5. **Buka Serial Monitor**

   Setelah ESP32 terhubung Wi-Fi, akses IP yang muncul lewat browser.

---

### Cara 2: Salin kode manual

1. Buat folder proyek di komputer, misalnya:

   ```
   /Gemini-ESP32-Web-AI-Chat/
   ```

2. Buat file baru bernama `Gemini-ESP32-Web-AI-Chat.ino` di dalam folder tersebut.

3. Salin seluruh kode dari repo [Gemini-ESP32-Web-AI-Chat](https://github.com/Katryoshkh/Gemini-ESP32-Web-AI-Chat/blob/main/Gemini-ESP32-Web-AI-Chat/Gemini-ESP32-Web-AI-Chat.ino)

4. Buka file ini dengan Arduino IDE.

5. Masukkan kredensial Wi-Fi & API Key seperti biasa.

6. Unggah ke ESP32 dan cek Serial Monitor seperti cara 1.

## Cara Pakai

* Ketikkan prompt di kolom input.
* Klik tombol **"Kirim"** atau tekan `Enter`.
* Respons akan ditampilkan dengan format markdown.

## Screenshot

*Tampilan antarmuka web akan terlihat seperti ini:*
![preview](docs/screenshot.png)

## Catatan Penting

* Gunakan API Key pribadi dan jangan share secara publik.
* Proyek ini **tidak melakukan hosting model AI di perangkat**, dan hanya menjadi antarmuka ke cloud Gemini API.
* Pastikan koneksi internet stabil saat digunakan.

## Lisensi

MIT License - bebas digunakan dan dimodifikasi.
