#pragma once

#include "../include/rtaudio/RtAudio.h"

enum class WaveType : int { SINE, SQUARE, SAW };

class Oscillator
{
public:
    Oscillator();
    Oscillator(unsigned int sampleRate);
    ~Oscillator();

    static int sine(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData);
    static int square(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData);
    static int saw(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData);

    void setAmplitude(float newAmplitude) { amplitude_ = (newAmplitude > 0.8 || newAmplitude < -0.8) ? 0.8 : newAmplitude; }
    void setFrequency(float newFrequency) { frequency_ = (newFrequency > 20000) ? 20000 : newFrequency; }
    void setPhase(float newPhase) { phase_ = newPhase; }

    static unsigned int nProcessedSamples_;    
private:
    float amplitude_;
    unsigned int frequency_;
    float phase_;

    unsigned int sampleRate_;
};