#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// LogGirdisi yapısı, syslog kaydını tutacak.
typedef struct LogGirdisi {
    char oncelik[10];
    char zamanDamgasi[30];
    char anaMakine[50];
    char islem[50];
    char mesaj[200];
    struct LogGirdisi* sonraki;
} LogGirdisi;

// Bağlı listeye yeni bir günlük kaydını ekler
void log_girdisi_ekle(LogGirdisi** baslangic, char* oncelik, char* zamanDamgasi, char* anaMakine, char* islem, char* mesaj) {
    LogGirdisi* yeni_girdi = (LogGirdisi*)malloc(sizeof(LogGirdisi));
    if (yeni_girdi == NULL) {
        perror("Bellek tahsisi başarısız");
        exit(1);
    }

    // Verileri bağlı liste elemanına kopyala
    strcpy(yeni_girdi->oncelik, oncelik);
    strcpy(yeni_girdi->zamanDamgasi, zamanDamgasi);
    strcpy(yeni_girdi->anaMakine, anaMakine);
    strcpy(yeni_girdi->islem, islem);
    strcpy(yeni_girdi->mesaj, mesaj);

    // Yeni girişi bağlı listeye ekle
    yeni_girdi->sonraki = *baslangic;
    *baslangic = yeni_girdi;
}

// Bağlı listedeki tüm günlükleri yazdırır
void log_girdilerini_yazdir(LogGirdisi* baslangic) {
    LogGirdisi* suanki = baslangic;
    while (suanki != NULL) {
        printf("Öncelik: %s, Zaman Damgası: %s, Ana Makine: %s, İşlem: %s, Mesaj: %s\n", 
                suanki->oncelik, suanki->zamanDamgasi, suanki->anaMakine, suanki->islem, suanki->mesaj);
        suanki = suanki->sonraki;
    }
}

// Bağlı listedeki tüm günlükleri serbest bırakır
void log_girdilerini_serbest_birak(LogGirdisi* baslangic) {
    LogGirdisi* suanki = baslangic;
    while (suanki != NULL) {
        LogGirdisi* temp = suanki;
        suanki = suanki->sonraki;
        free(temp);
    }
}

int main() {
    // Syslog dosyasını aç
    FILE* dosya = fopen("/var/log/syslog", "r");
    if (dosya == NULL) {
        perror("Syslog dosyası açılırken hata oluştu");
        return 1;
    }

    LogGirdisi* log_listesi = NULL;  // Başlangıçta boş bir liste
    char satir[256];

    // Syslog dosyasındaki her satırı oku
    while (fgets(satir, sizeof(satir), dosya)) {
        char oncelik[10], zamanDamgasi[30], anaMakine[50], islem[50], mesaj[200];

        // Syslog satırını ayırarak verileri al
        int parseEdilen = sscanf(satir, "<%9[^>]> %29s %49s %49s %199[^\n]", oncelik, zamanDamgasi, anaMakine, islem, mesaj);
        
        if (parseEdilen == 5) {
            // Eğer veriler doğru şekilde parse edilmişse, bağlı listeye ekle
            log_girdisi_ekle(&log_listesi, oncelik, zamanDamgasi, anaMakine, islem, mesaj);
        }
    }

    fclose(dosya);  // Dosyayı kapat

    // Bağlı listedeki tüm logları yazdır
    printf("Syslog Girdileri:\n");
    log_girdilerini_yazdir(log_listesi);

    // Belleği temizle (bağlı listeyi serbest bırak)
    log_girdilerini_serbest_birak(log_listesi);

    return 0;
}
