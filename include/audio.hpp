#ifndef __AUDIO_HPP
#define __AUDIO_HPP

#include <random>
#include <vector>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <stdexcept>


#include "complex.hpp"
#include "wavheader.hpp"


AudioBuffer loadWAV(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file)
        throw std::runtime_error("Cannot open WAV");

    char id[4];
    uint32_t size;

    file.read(id, 4);                 
    if (std::strncmp(id, "RIFF", 4))
        throw std::runtime_error("Not RIFF");

    file.read(reinterpret_cast<char*>(&size), 4); 

    file.read(id, 4);                 
    if (std::strncmp(id, "WAVE", 4))
        throw std::runtime_error("Not WAVE");

    uint16_t audioFormat = 0;
    uint16_t channels = 0;
    uint32_t sampleRate = 0;
    uint16_t bitsPerSample = 0;
    uint32_t dataSize = 0;

    
    while (file.read(id, 4)) {
        file.read(reinterpret_cast<char*>(&size), 4);

        if (!std::strncmp(id, "fmt ", 4)) {
            file.read(reinterpret_cast<char*>(&audioFormat), 2);
            file.read(reinterpret_cast<char*>(&channels), 2);
            file.read(reinterpret_cast<char*>(&sampleRate), 4);
            file.seekg(6, std::ios::cur); 
            file.read(reinterpret_cast<char*>(&bitsPerSample), 2);
            file.seekg(size - 16, std::ios::cur);
        }
        else if (!std::strncmp(id, "data", 4)) {
            dataSize = size;
            break;
        }
        else {
            file.seekg(size, std::ios::cur); 
        }
    }

    if (audioFormat != 1 || bitsPerSample != 16)
        throw std::runtime_error("Unsupported WAV");

    std::vector<int16_t> raw(dataSize / 2);
    file.read(reinterpret_cast<char*>(raw.data()), dataSize);

    AudioBuffer audio;
    audio.sampleRate = sampleRate;
    audio.channels = channels;
    audio.samples.resize(raw.size());

    for (size_t i = 0; i < raw.size(); i++)
        audio.samples[i] = raw[i] / 32768.0f;

    return audio;
}

std::vector<float> toMono(const AudioBuffer& buffer){
    if(buffer.channels == 1)
        return buffer.samples;
    std::vector<float> mono;
    mono.reserve(buffer.samples.size()/buffer.channels);
    for (size_t i = 0; i < buffer.samples.size(); i+=buffer.channels)
    {
        float sum = 0.0f;
        for (int ch = 0; ch < buffer.channels; ch++)
        {
            sum += buffer.samples[i+ch];
        }
        mono.push_back(sum/buffer.channels);
    }
    return mono;
}

void writeWAV(const std::string& filename, const std::vector<float>& samples, int sampleRate, int channels=1){
    std::ofstream file(filename,std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("Cannot open output WAV file");
    }
    
    std::vector<int16_t> pcm(samples.size());
    for (size_t i = 0; i < samples.size(); i++) {
        double x = std::clamp(static_cast<double>(samples[i]), -1.0, 1.0);
        pcm[i] = static_cast<int16_t>(x * 32767.0);
    }

    WAVHeader header;

    std::memcpy(header.riff,"RIFF",4);
    std::memcpy(header.wave,"WAVE",4);
    std::memcpy(header.fmt,"fmt ",4);
    std::memcpy(header.data,"data",4);

    header.subchunk1Size = 16;
    header.audioFormat = 1;

    header.bitsPerSample = 16;

    header.numChannels = channels;
    header.sampleRate = sampleRate;
    header.blockAlign = channels * sizeof(int16_t);
    header.byteRate = sampleRate * header.blockAlign;
    header.dataSize = pcm.size() * sizeof(int16_t);
    header.chunkSize = 36 + header.dataSize;

    file.write(reinterpret_cast<char*>(&header), sizeof(WAVHeader));
    file.write(reinterpret_cast<char*>(pcm.data()), header.dataSize);
}

std::vector<float> addNoise(const std::vector<float>& samples,const float stddev){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> noiseDist(0.0f, stddev);  // small stddev

    std::vector<float> noisy;
    noisy.reserve(samples.size());
    for (auto s : samples) {
        float n = s + noiseDist(gen);
        if (n > 1.0f) n = 1.0f;
        if (n < -1.0f) n = -1.0f;
        noisy.push_back(n);
    }
    return noisy;
}

std::vector<float> removeNoise(const std::vector<float>& samples,const float thresh_procentage){
    // first we turn this into a complex vector
    ComplexVector samples_vec;
    int nearestPowerTwo = getNearestPower(samples.size(),2);
    samples_vec.reserve(nearestPowerTwo);
    std::cout << "Size for FFT: " << samples.size() << std::endl;
    std::cout << "Nearest power of 2: " << nearestPowerTwo << std::endl;
    for (int i = 0; i < nearestPowerTwo; i++)
    {
        if (i < samples.size())
        {
            samples_vec.push_back(Complex(samples[i],0.0f));
        }else{
            samples_vec.push_back(Complex(0.0f,0.0f));
        }
        
    }
    std::cout << "Performing FFT" << std::endl;
    ComplexVector spectrum = fft(samples_vec);

    float mean = 0.0f;
    for (auto &c : spectrum) 
        mean += c.module();
    mean /= spectrum.size();
    float threshold = thresh_procentage*mean;
    std::cout << "Thresholding..." << std::endl; 
    std::cout << "Size for thresholding: " << spectrum.size() << std::endl;
    for (int i = 0; i < spectrum.size(); i++)
    {
        if(spectrum[i].module() < threshold){
            spectrum[i] = Complex(0.0f,0.0f);
        }
    }
    
    std::cout << "Performing IFFT" << std::endl;
    ComplexVector cleaned = ifft(spectrum);
    std::vector<float> cleaned_samples;
    for (int i = 0; i < spectrum.size(); i++)
    {
        cleaned_samples.push_back(cleaned[i].real());
    }
    return cleaned_samples;
}

std::vector<float> hahnWindow(int N) {
    std::vector<float> w(N);
    for (int i = 0; i < N; i++)
    {
        w[i] = 0.5f * (1.0f - std::cos(2.0f * M_PI * i / (N - 1)));
    }
    return w;
}

std::vector<float> removeNoiseSTFT(const std::vector<float>& samples,const float procentage_removal){
    int N = 1024;
    int hop = N/2;
    std::vector<float> window = hahnWindow(N);

    int numFrames = (samples.size() + hop - 1) / hop;
    std::vector<float> output(samples.size() + N, 0.0f); 
    std::vector<float> windowSums(output.size(), 0.0f);  

    ComplexVector noiseSpectrum(N);
    {
        ComplexVector firstFrame(N);
        for (int i = 0; i < N; i++) {
            float x = (i < samples.size()) ? samples[i] * window[i] : 0.0f;
            firstFrame[i] = Complex(x, 0.0f);
        }
        noiseSpectrum = fft(firstFrame);
        for (auto& c : noiseSpectrum) c = Complex(c.module(), 0.0f);
    }

     for (int f = 0; f < numFrames; f++) {
        ComplexVector frame(N);
        for (int i = 0; i < N; i++) {
            int idx = f * hop + i;
            float x = (idx < samples.size()) ? samples[idx] * window[i] : 0.0f;
            frame[i] = Complex(x, 0.0f);
        }

        // FFT
        ComplexVector spectrum = fft(frame);

        // Spectral subtraction (simple)
        for (int k = 0; k < N; k++) {
            float mag = spectrum[k].module() - procentage_removal*noiseSpectrum[k].real();
            if (mag < 0.0f) mag = 0.0f;
            float phase = std::atan2(spectrum[k].imag(), spectrum[k].real());
            spectrum[k] = Complex(mag * std::cos(phase), mag * std::sin(phase));
        }

        // IFFT
        ComplexVector cleanedFrame = ifft(spectrum);

        // Overlap-add
        for (int i = 0; i < N; i++) {
            int idx = f * hop + i;
            if (idx < output.size()) {
                output[idx] += cleanedFrame[i].real() * window[i];
                windowSums[idx] += window[i] * window[i];
            }
        }
    }

    for (size_t i = 0; i < samples.size(); i++) {
        if (windowSums[i] > 0.0f)
            output[i] /= windowSums[i];
    }

    output.resize(samples.size());
    return output;

}

#endif