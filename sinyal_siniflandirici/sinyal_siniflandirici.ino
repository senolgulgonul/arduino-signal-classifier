
#include "model_weights.h"

float relu(float x) { return x > 0 ? x : 0; }

int tahmin_et(float* giris) {
    float gizli[N_HIDDEN];
    float cikis[N_OUTPUT];

    float norm[N_INPUT];
    for (int i = 0; i < N_INPUT; i++) {
        norm[i] = (giris[i] - mean[i]) / scale[i];
    }

    for (int j = 0; j < N_HIDDEN; j++) {
        float toplam = b1[j];
        for (int i = 0; i < N_INPUT; i++) {
            toplam += W1[j * N_INPUT + i] * norm[i];
        }
        gizli[j] = relu(toplam);
    }

    for (int j = 0; j < N_OUTPUT; j++) {
        float toplam = b2[j];
        for (int i = 0; i < N_HIDDEN; i++) {
            toplam += W2[j * N_HIDDEN + i] * gizli[i];
        }
        cikis[j] = toplam;
    }

    int en_iyi = 0;
    for (int j = 1; j < N_OUTPUT; j++) {
        if (cikis[j] > cikis[en_iyi]) en_iyi = j;
    }
    return en_iyi;
}

float olcumler[N_INPUT];
int ref_deger;
int sonuc = -1;

void plotter_yaz(int a0_deger) {
    Serial.print("A0:");
    Serial.print(a0_deger);
    Serial.print(",");
    Serial.print("rising:");
    Serial.print(sonuc == 0 ? 1000 : 0);
    Serial.print(",");
    Serial.print("falling:");
    Serial.print(sonuc == 1 ? 1000 : 0);
    Serial.print(",");
    Serial.print("U:");
    Serial.print(sonuc == 2 ? 1000 : 0);
    Serial.print(",");
    Serial.print("inverted_U:");
    Serial.println(sonuc == 3 ? 1000 : 0);
}

void setup() {
    Serial.begin(115200);
    ref_deger = analogRead(A0);
}

void loop() {
    int simdiki = analogRead(A0);

    if (abs(simdiki - ref_deger) >= 10) {
        sonuc = -1;

        for (int i = 0; i < N_INPUT; i++) {
            olcumler[i] = analogRead(A0);
            plotter_yaz((int)olcumler[i]);
            delay(100);
        }

        sonuc = tahmin_et(olcumler);

        for (int i = 0; i < 5; i++) {
            plotter_yaz((int)olcumler[N_INPUT-1]);
            delay(100);
        }

        ref_deger = analogRead(A0);
        sonuc = -1;
    } else {
        plotter_yaz(simdiki);
    }

    delay(20);
}
