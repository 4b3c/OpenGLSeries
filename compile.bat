set /p FILENAME= "Filename: "
echo Compiling and running %FILENAME%
cd "C:\Users\Abram P\Desktop\Programming\C++\IsometricRevisit"
g++ "%FILENAME%.cpp" -o %FILENAME%
start cmd.exe /k "%CD%\%FILENAME%"
