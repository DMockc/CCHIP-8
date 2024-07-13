This is a virtual machine of [CHIP-8](https://en.wikipedia.org/wiki/CHIP-8) written in C++.

# Getting started
> [!IMPORTANT]
> **Only compatible with Windows 10 or higher.**

This virtual machine features CHIP-8 graphics and sounds.
It also contains several keys with special uses which are explained in [INSTRUCTIONS](INSTRUCTIONS.md) file.

### Example of Pong
![image](https://github.com/DMockc/CCHIP8/assets/118026464/684ab5ab-9e9c-45c4-8b6c-88d6c43279cb)

# How to compile
Go to the source directory and execute in the terminal the following commands:
```bat
:: Create the build directory
mkdir build
:: Enter the build directory
cd build
:: Configure cmake
cmake -S .. -B release
:: Build the project
cmake --build release --config Release
```
The compiled project should be in `build/release/Release`. 
All files in the folder are required for proper operation.

<hr>
The opcode documentation was obtained from this website: https://tonisagrista.com/blog/2021/chip8-spec/
