# TSM_PicoW_Blinky
Project using the Pico-W RP2040 board with VS Code, implementing a simple blinky program.

## Build
Project has `Debug`, `Release` and `Test` targets, using CMake Presets. 

Configure:
```
cmake --list-presets
cmake --preset Debug
cmake --preset Release
cmake --preset Test
```

Build:
```
cmake --build --list-presets
cmake --build --preset app-debug
cmake --build --preset app-release
cmake --build --preset app-test
```

Test:
```
ctest --list-presets
ctest --test-dir build/Test -R Led_1
```

Worflow:
```
cmake --workflow --list-presets
```

## Debug
Use `J-Link cortex-debug' launch config for a direct USB J-Link connection.

If using a DevContainer, use the 'inside DevContainer' launch config. You have to launch the debug server on the host first with
```
JLinkGDBServerCL -select USB -device RP2040_M0_0 -endian little -if SWD -rtos GDBServer/RTOSPlugin_FreeRTOS
```
Note: if using semihosting (e.g. with gcov), the current directory *has to be the project folder*.

The program implements the ShellSort to sort a list of numbers.

## Scientific Debugging
The application includes the 'sample' program of the 'scientific debugging' part, enabled with the `PL_CONFIG_USE_SAMPLE` setting in `platform.h.

Open a serial terminal (Termite/PuTTy or the 'Serial Monitor' in VS Code). Connect to the VCOM (115200, CRLF at the end). Type in 'help' to get some guidance.
Example in using Serial Monitor in VS Code:
```
---- Opened the serial port COM181 ----
---- Sent utf8 encoded message: "help\r\n" ----
Sample program. Type in numbers, separated by spaces. Press <ENTER> at the end.
---- Sent utf8 encoded message: "20 5 3\r\n" ----
Output: 3 5 20 
```

## Doxygen
Run task: Menu Terminal -> Run Task... -> doxygen

## Coverage
Enable `PL_CONFIG_USE_GCOV` in `platform.h` and use the `Debug` build.
Run the application with the debugger.

If using DevContainer, you have to install `gcovr` with `pip`.
First we need to create a new local python environment in a folder (`venv`):
```
cd /workspace
python3 -m venv venv
./penv/bin/pip install gcovr
```
After that, one can use 'gcovr' with the python `venv` environment:
```
/apps/venv/bin/gcovr .
```

To generate a text report:
```
gcovr .
```
To generate a HTML report:
```
gcovr --html-details -o ./gcovr/main.html
```
or use Terminal -> Run Task... -> gcovr

You can use the `gcov` utility on a file like this:
```
gcov build/debug/srcLib/CMakeFiles/srcLib.dir/main.c.gcda
```

## Test
Build  with `Test` build configuration.

Manual Test Runner run:
```
JRun --device RP2040_M0_0 --pc off --sp off --if SWD --args "Led_1" build/Test/TSM_PicoW_Blinky.elf
```
Manual CTest run:
```
ctest --extra-verbose --test-dir build/Test --timeout 15 --output-on-failure -R Led_1
```

If using DevContainer, you have to use an IP connection to the debug probe on the host.
For this, start a GDB server for debugging, for example:
```
JLinkGDBServerCL -select USB -device RP2040_M0_0 -endian little -if SWD -rtos GDBServer/RTOSPlugin_FreeRTOS
```
Or for using JRun, you can run the following and then use the IP address (host.docker.internal):
```
JLinkRemoteServerCL
```
Otherwise, you have to use a tunnel service:
```
JLinkRemoteServerCL -UseTunnel -TunnelBySN -select="801048148"
```

