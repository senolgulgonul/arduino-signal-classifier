# Arduino Sinyal Siniflandirici — ML on Arduino Uno

Bir sinir agini Python'da egitip agirliklarini Arduino Uno uzerinde calistiran bir proje.

## Ne Yapiyor?

A0 pininden alinan analog sinyali 4 kategoriden birine siniflandirir:
- **rising** — artan sinyal
- **falling** — azalan sinyal  
- **U** — once azalip sonra artan
- **inverted_U** — once artip sonra azalan

Sonuclar Serial Plotter'da gercek zamanli goruntulenir.

## Mimari
```
Python (PC)                    Arduino Uno
-----------                    -----------
Sentetik veri uret             Forward pass
Sinir agi egit      ----->     W1 (16x8) + b1
Agirliklari export             W2 (8x4)  + b2
model_weights.h                Sonuc: Serial Plotter
```

## Sinir Agi
```
Giris:  16 olcum noktasi (A0, 0-1023)
Gizli:  8 noron (ReLU)
Cikis:  4 sinif
Bellek: ~688 byte (Arduino Uno 2KB RAM'e sigdi!)
```

## Dosyalar

- `train.ipynb` — Python egitim kodu (PyTorch)
- `sinyal_siniflandirici/sinyal_siniflandirici.ino` — Arduino sketch
- `sinyal_siniflandirici/model_weights.h` — Egitilmis agirliklar (C array)

## Gereksinimler

### Python
```
pip install numpy pandas scikit-learn matplotlib torch
```

### Arduino
- Arduino Uno
- Arduino IDE

## Nasil Kullanilir?

1. `train.ipynb` notebook'unu calistirin — model egitilir, `model_weights.h` olusur
2. `sinyal_siniflandirici.ino` dosyasini Arduino IDE ile acin
3. Upload edin
4. Serial Plotter'i 115200 baud ile acin
5. A0 pinine potansiyometre baglayip cevirip deneyin!

## Nasil Calisir?

Python'da egitilen sinir aginin agirliklari C float array olarak export edilir.
Arduino sadece **forward pass** yapar — toplama ve carpma islemi.
Backpropagation veya egitim yok — cok az bellek yeterli!

## Tetikleme Mantigi

Surekli olcum degil — A0 degeri 10'dan fazla degisince olcum baslar.
16 x 100ms = 1.6 saniyede sinyal okunur, siniflandirilir, Serial Plotter'a yazilir.

## Sonuclar

- Egitim dogrulugu: %100
- Test dogrulugu: %100
- Arduino bellek kullanimi: ~688 byte
