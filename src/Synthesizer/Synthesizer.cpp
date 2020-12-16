#include "Synthesizer.h"
#include "Oscillator/Oscillator.h"

Synthesizer::Synthesizer() : audio_(nullptr), sampleRate_(44100), nBufferFrames_(256)
{
    try
    {
        audio_= std::make_unique<RtAudio>();
    }
    catch(RtAudioError& error)
    {
        error.printMessage();
        exit(EXIT_FAILURE);
    }
    parameters_.deviceId = audio_->getDefaultOutputDevice();
    parameters_.nChannels = 2;
    parameters_.firstChannel = 0;
    Oscillator Oscillator(44100);
}

Synthesizer::~Synthesizer()
{
    
}

void Synthesizer::showDeviceCapabilities()
{
    std::cout << "----------Device-capabilities:----------\n";
    // Determine the number of devices available
    int devices = 0;
    if (audio_)
        devices = audio_->getDeviceCount();
    std::cout << "Number of devices: " << devices << '\n';
    std::cout << "Default device ID: " << parameters_.deviceId << '\n';
    
    // Scan through devices for various capabilities
    for (int i = 1; i <= devices; ++i)
    {
        try 
        {
            auto info = audio_->getDeviceInfo(i);
            std::cout << "device = " << i;
            std::cout << ": maximum output channels = " << info.outputChannels << '\n';        
        }
        catch (RtAudioError& error)
        {
            error.printMessage();
            break;
        }
    }
    std::cout << "----------------------------------------\n";
}
void Synthesizer::playBackExample()
{
    if (!audio_) 
        return;
    double data[2];

    std::cout << "Opening stream.\n";
    try
    {
        if (audio_->isStreamOpen())
            audio_->closeStream();
        audio_->openStream(&parameters_, nullptr, RTAUDIO_FLOAT64, sampleRate_, &nBufferFrames_, &Oscillator::square, (void*)&data);
        audio_->startStream();
    }
    catch (RtAudioError& error)
    {
       error.printMessage(); 
    }
    std::cin.get();
    stopAndCloseStream();
}

void Synthesizer::stopAndCloseStream()
{
    try
    {
        audio_->stopStream();
    }
    catch(RtAudioError& e)
    {
        e.printMessage();
    }
    if (audio_->isStreamOpen())
        audio_->closeStream();
}


































// void Synthesizer::playSound()
// {
    // RtAudio dac;
    // if (dac.getDeviceCount() < 1) 
    // {
    //     std::cout << "\nNo audio devices found!\n";
    //     exit(0);
    // }
    // RtAudio::StreamParameters parameters;
    // parameters.deviceId = dac.getDefaultOutputDevice();
    // parameters.nChannels = 1;
    // parameters.firstChannel = 0;
    // unsigned int sampleRate = 44100;
    // unsigned int bufferFrames = 256; // 256 sample frames
    // double data[2];
    // try 
    // {
    //     dac.openStream( &parameters, NULL, RTAUDIO_FLOAT64, sampleRate, &bufferFrames, &saw, (void *)&data );
    //     dac.startStream();
    // }
    // catch ( RtAudioError& e ) 
    // {
    //     e.printMessage();
    //     exit(0);
    // }
    // char input;
    // std::cout << "\nPlaying ... press <enter> to quit.\n";
    // std::cin.get(input);
    
    // try 
    // {
    //     // Stop the stream
    //     dac.stopStream();
    // }
    // catch (RtAudioError& e) 
    // {
    //     std::cout << "ERROR MESSAGES\n";
    //     e.printMessage();
    // }
    // if (dac.isStreamOpen())
    //     dac.closeStream();

//}

