pushd "%~dp0"
rmdir /S /Q "%PUBLIC%\Documents\LeCroy\USB Protocol Suite\Scripts"
xcopy Scripts "%PUBLIC%\Documents\LeCroy\USB Protocol Suite\Scripts\" /O /X /E /H /K
pause