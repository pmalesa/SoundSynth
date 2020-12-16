#include "Oscillator.h"
#include <iostream>
#include <cmath>

unsigned int Oscillator::nProcessedSamples_ = 0;

Oscillator::Oscillator()
{

}

Oscillator::Oscillator(unsigned int sampleRate) : sampleRate_(sampleRate)
{
}

Oscillator::~Oscillator()
{

}

int Oscillator::sine(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
    double streamTime, RtAudioStreamStatus status, void* userData)
{
    // Sine wave generation still has some problem (some artifact noise) !!!
    double* buffer = static_cast<double*>(outputBuffer);
    double* lastValues = static_cast<double*>(userData);
    float time = 0.0;
    if (status)
        std::cout << "Stream underflow detected!\n";
    for (unsigned int i = 0; i < nBufferFrames; ++i)
    {
        float value = 0.05 * sin(2 * M_PI * 440 * time);
        for (unsigned int j = 0; j < 2; ++j)
        {
            lastValues[j] = value;
            *buffer++ = lastValues[j];
        }
        time = (nProcessedSamples_ + i) / 44100.0;
    }
    nProcessedSamples_ += nBufferFrames;
    return 0;
}

int Oscillator::square(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
    double streamTime, RtAudioStreamStatus status, void* userData)
{
    double* buffer = (double*) outputBuffer;
    double* lastValues = (double*) userData;
    float amplitude = 0.05;
    if (status)
        std::cout << "Stream underflow detected!\n";
    for (unsigned int i = 0; i < nBufferFrames; ++i)
        for (unsigned int j = 0; j < 2; ++j)
        {
            *buffer++ = lastValues[j];
            lastValues[j] = (i < nBufferFrames / 2) ? amplitude : -amplitude;
        }
    return 0;
}

int Oscillator::saw(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
    double streamTime, RtAudioStreamStatus status, void* userData)
{
    double* buffer = (double*) outputBuffer;
    double* lastValues = (double*) userData;
    float baseRate = 0.005;

    if (status)
        std::cout << "Stream underflow detected!\n";
    
    double increment;
    for (unsigned int i = 0; i < nBufferFrames; ++i)
        for (unsigned int j = 0; j < 2; ++j)
        {
            *buffer++ = lastValues[j];
            lastValues[j] += baseRate;
            if (lastValues[j] >= 1.0)
                lastValues[j] -= 2.0;
        }
    return 0;
}