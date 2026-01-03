#include <iostream>

#include "utils.hpp"
#include "audio.hpp"
#include "complex.hpp"

int main() {
    auto a = loadWAV("data/src/rusija.wav");
    std::vector<float> monoAudio = toMono(a);
    std::cout << "Adding noise..." << std::endl;
    std::vector<float> noise = addNoise(monoAudio,0.2f);
    writeWAV("data/sample/rusija.wav", noise, a.sampleRate, 1);
    std::cout << "Denoising... (factor 1.0f)" << std::endl;
    std::vector<float> denoised1 = removeNoiseSTFT(noise,1.0f);
    writeWAV("data/cleaned/rusija_1.wav", denoised1, a.sampleRate, 1);
    std::cout << "Denoising... (factor 1.5f)" << std::endl;
    std::vector<float> denoised2 = removeNoiseSTFT(noise,1.5f);
    writeWAV("data/cleaned/rusija_15.wav", denoised2, a.sampleRate, 1);
    std::cout << "Denoising... (factor 0.5f)" << std::endl;
    std::vector<float> denoised3 = removeNoiseSTFT(noise,0.5f);
    writeWAV("data/cleaned/rusija_05.wav", denoised3, a.sampleRate, 1);
    std::cout << "Denoising... (factor 2.0f)" << std::endl;
    std::vector<float> denoised4 = removeNoiseSTFT(noise,2.0f);
    writeWAV("data/cleaned/rusija_2.wav", denoised4, a.sampleRate, 1);


    return 0;
}
