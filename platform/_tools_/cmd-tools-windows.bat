@echo off
setlocal

REM Define the destination directory
set "destination=%USERPROFILE%\android"

REM Fetch the download URL for the command-line tools using PowerShell
for /f "tokens=*" %%i in ('powershell -command "Invoke-WebRequest -Uri https://developer.android.com/studio -UseBasicParsing ^| Select-String -Pattern 'https:\/\/dl.google.com\/android\/repository\/commandlinetools-win-[0-9]*_latest.zip' ^| ForEach-Object {$_.Matches.Value}"') do (
    set "toolsDownloadUrl=%%i"
)

REM Download the tools using curl or PowerShell
echo Downloading Android command-line tools...
curl --location -o android.zip %toolsDownloadUrl%

REM Extract the contents using tar (available on modern Windows systems) or unzip
echo Extracting files...
mkdir android-temp
tar -xf android.zip -C android-temp

REM Move the extracted files to the destination directory
mkdir "%destination%\cmdline-tools\latest"
move android-temp\cmdline-tools\bin "%destination%\cmdline-tools\latest\bin"

REM Clean up
rmdir /s /q android-temp
del android.zip

echo Android SDK command-line tools have been installed to %destination%\cmdline-tools\latest.
pause
