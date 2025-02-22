# Syslog Bağlı Liste Uygulaması

Bu proje, Linux işletim sistemindeki syslog dosyasındaki günlük (log) kayıtlarını okur ve bağlı liste veri yapısını kullanarak saklar. Syslog dosyasındaki her bir kaydın bilgilerini ayrıştırarak, bu verileri bir bağlı listeye ekler ve sonrasında bu verileri ekrana yazdırır.

## Özellikler

- Syslog dosyasındaki verileri okur.
- Syslog kayıtlarını ayrıştırarak ilgili bilgileri çıkarır (Öncelik, Zaman Damgası, Ana Makine, İşlem, Mesaj).
- Verileri bir **bağlı liste** yapısında saklar.
- Bağlı listedeki tüm günlükleri ekrana yazdırır.
- Dinamik bellek yönetimi sağlar.

## Gereksinimler

- **Linux İşletim Sistemi**: Syslog dosyasına erişim gereklidir (`/var/log/syslog`).
- **C Derleyicisi**: GCC veya benzeri bir C derleyicisi.
- **Root Erişimi**: Syslog dosyasına erişim için root erişimi gereklidir.

## Derleme

"gcc -o syslog_reader syslog_reader.c" 

## Çalıştırma

-"sudo ./syslog_reader"
