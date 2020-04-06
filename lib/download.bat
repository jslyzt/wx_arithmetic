@echo off
set PATH=%PATH%;tool

if not exist wxWidgets-3.0.4-headers.7z (
   wget https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.4/wxWidgets-3.0.4-headers.7z
)

if not exist wxMSW-3.0.4_vc120_x64_Dev.7z (
   wget https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.4/wxMSW-3.0.4_vc120_x64_Dev.7z
)

mkdir wxwidgets
7z x wxWidgets-3.0.4-headers.7z -owxwidgets
7z x wxMSW-3.0.4_vc120_x64_Dev.7z -owxwidgets