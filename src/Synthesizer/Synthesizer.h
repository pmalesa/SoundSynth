#pragma once
#include <memory>

#include "../include/rtaudio/RtAudio.h"

/*  Synthesizer is a singleton class. There will be only 
    one instance of Synthesizer class per application.  */

class Synthesizer
{
public:
    Synthesizer(const Synthesizer&) = delete;
    Synthesizer& operator=(const Synthesizer&) = delete;
    static Synthesizer& get()
    { 
        static Synthesizer instance;
        return instance; 
    }
    ~Synthesizer();

    void showDeviceCapabilities();
    void playBackExample();
    void stopAndCloseStream();

private:
    Synthesizer();

    std::unique_ptr<RtAudio> audio_;
    RtAudio::StreamParameters parameters_;
    unsigned int sampleRate_;
    unsigned int nBufferFrames_;
};


