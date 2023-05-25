# Sistem Keamanan Penyebrangan Pejalan Kaki Pada Zebra Cross
Simulasi sistem keamanan penyebrangan pejalan kaki menggunakan tombol penyebrangan, ketika tombol penyebrangan ditekan, warna lampu penyebrangan pejalan kaki akan berubah menjadi warna hijau. Tetapi ketika tombol penyebrangan tidak ditekan, warna lampu penyebrangan akan tetap berwarna merah. Dalam kondisi lampu penyebrangan berwarna merah, sensor ultrasonik akan bekerja untuk mendeteksi jarak pejalan kaki dari jalan. Jika pejalan kaki terlalu dekat dengan jalan, maka sensor akan mendeteksi hal tersebut dan menyalakan buzzer sebagai alarm.

## Metode IoT
Pengiriman dan penerimaan data dilakukan menggunakan MQTT, dimana lampu penyebrangan pejalan kaki dan tombol penyebrangan bertindak sebagai publisher, serta sensor ultrasonik dan alarm akan bertindak sebagai subscriber. Tombol penyebrangan juga berguna untuk mengontrol lampu penyebrangan pejalan kaki. Monitoring dilakukan melalui aplikasi IoT MQTT Panel pada ponsel android.

## Komponen yang digunakan
1.	ESP8266 (2)
2.	Breadboard (2)
3.	Kabel jumper (14)
4.	Sensor Ultrasonik HC-SR04 (1)
5.	Lampu LED warna merah (1), kuning (1), hijau (1)
6.	Push button (1)
7.	Resistor (4)
8.	Piezo buzzer (1)

## Board Schematic
![Schematic Board PA B2](https://github.com/AlyaniNS/pa-praktikum-iot-unmul-B2/assets/74224380/85e0b703-07d9-4927-bedd-b643bdd2e206)

## Manual Book
[ManualBook_IOT_B2.pdf](https://github.com/AlyaniNS/pa-praktikum-iot-unmul-B2/files/11567784/ManualBook_IOT_B2.pdf)

## Pembagian Tugas
No|Nim       |Nama                            |Tugas                           |
--|----------|--------------------------------|--------------------------------|
1 |1915026021|Muhammad Dicky Rizqia Nur Achmar|Konfigurasi Rangkaian Publisher |
2 |2009106034|Sael Samuel Rude’               |Membuat Guidebook               |
3 |2009106100|Alyani Noor Septalia            |Konfigurasi Rangkaian Subscriber|
4 |2009106112|Adrian Tasmin                   |Membuat Rangkaian               |
