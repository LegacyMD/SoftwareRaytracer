mkdir build -p
cd build
cmake ..

if [ $? -ne 0 ]; then
    read _
fi
