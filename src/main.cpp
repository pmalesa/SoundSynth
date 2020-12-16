#include <iostream>
#include "Synthesizer/Synthesizer.h"

using std::cout;

int main()
{
    std::cout << "Welcome to SoundSynth!\n";
    Synthesizer::get().showDeviceCapabilities();
    Synthesizer::get().playBackExample();
	return 0;
}
