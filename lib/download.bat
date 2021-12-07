@echo off
set PATH=%PATH%;tool

if not exist wxWidgets-3.1.5-headers.7z (
   wget https://github.com/wxWidgets/wxWidgets/releases/download/v3.1.5/wxWidgets-3.1.5-headers.7z
)

if not exist wxMSW-3.1.5_vc14x_x64_Dev.7z (
   wget https://github.com/wxWidgets/wxWidgets/releases/download/v3.1.5/wxMSW-3.1.5_vc14x_x64_Dev.7z
)

mkdir wxwidgets
7z x wxWidgets-3.1.5-headers.7z -owxwidgets
7z x wxMSW-3.1.5_vc14x_x64_Dev.7z -owxwidgets