# Redukovanje šuma koristeći algoritam Brze Furijeove transformacije (FFT)

## Pregled

Ovaj seminarski ima za cilj da prikaže primjenu algoritma brze furijeove transformacije u polju obrade zvuka, 
tačnije redukovanja šuma iz samog zvuka. Implementacija čitave protočne obrade je odrađena u C++ i sadrži:

- Potpunu implementaciju artimetike kompleksnih brojeva
- Algoritam brze Furijeove transformacije
- Kratkoročna Furijeova transformacija:
    - Hann prozor
    - Hamming prozor
    - Welch prozor
    - Parzen prozor
- Spektralno odstranjenje šuma 
- Čitač i pisač WAV (16-bit) fajlova 
- Konverzija u mono audio
- Dodavanje šuma (korišteno za testiranje)

## Struktura projekta

```
├── data
│   ├── cleaned         # Očišćenji fajlovi 
│   ├── sample          # Fajlovi sa šumom
│   └── src             # Originalni fajlovi, bez šuma
├── include
│   ├── audio.hpp       # implementacija čitača i pisača, kao i sam algoritam STFT
│   ├── complex.hpp     # implementacija komplkesnih brojeva
│   ├── utils.hpp       # implementacija FFT
│   └── wavheader.hpp   # strukture u kojima se upisuju podaci iz WAV fajlova
├── main.cpp
├── Makefile
├── README.md
├── src
│   └── complex.cpp
└── DAA__seminarski.pdf # opis

```

## Osobine audio fajlova za obradu

Da bi protočna obrada audio fajlova radila, potrebno je da sam audio fajl zadovolji par karakteristika.
Te karakteristike su:
- WAV format
- PCM kodiranje
- 16-bitno uzorkovanje

Ako je audio u nekom drugom formatu, moguće je izvršiti konverziju u terminalu na idući način:

```bash
ffmpeg -i input.mp3 -ac 1 -ar 44100 -c:a pcm_s16le output.wav
```
