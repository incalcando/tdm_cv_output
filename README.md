On MacOS in terminal (first time rp2350 project): 

brew uninstall arm-none-eabi-gcc ## this compiler doesn't work 
brew autoremove
brew install --cask gcc-arm-embedded ##this compiler works

When opening project for first time :

git clone https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init
cd .. 


In root CMakeLists.txt edit project name 
