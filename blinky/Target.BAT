SET PATH=C:\ARM\ARMCLANG\Bin;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files\dotnet\;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Program Files (x86)\Flash Magic;C:\Program Files\Git\cmd;C:\Program Files\MATLAB\R2025a\runtime\win64;C:\Program Files\MATLAB\R2025a\bin;C:\Users\Reetesh\AppData\Local\Microsoft\WindowsApps;C:\mingw64\bin;C:\Users\Reetesh\AppData\Local\Programs\Microsoft VS Code\bin;C:\Users\Reetesh\.dotnet\tools;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files\dotnet\;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Program Files (x86)\Flash Magic;C:\Program Files\Git\cmd;C:\Program Files\MATLAB\R2025a\runtime\win64;C:\Program Files\MATLAB\R2025a\bin;C:\PROGRA~2\FLASHM~1
SET ARMCC6_ASMOPT=--diag_suppress=9931
SET ARMCC6_CCOPT=--diag_suppress=9931
SET ARMCC6_LINKOPT=--diag_suppress=9931
SET CPU_TYPE=STM32F407VGTx
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Target
SET CPU_CLOCK=0x00B71B00
"C:\ARM\ARMCLANG\Bin\ArmClang.exe" @".\main.__i"
"C:\ARM\ARMCLANG\Bin\ArmClang.exe" @".\startup_stm32f407xx._ac"
"C:\ARM\ARMCLANG\Bin\ArmClang.exe" @".\system_stm32f4xx.__i"
"C:\ARM\ARMCLANG\Bin\ArmLink" --Via ".\blinky.lnp"
"C:\ARM\ARMCLANG\Bin\fromelf.exe" ".\blinky.axf" --i32combined --output ".\blinky.hex"
