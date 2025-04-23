#!/bin/bash

echo "Select from below options..."
echo "1. Build"
echo "2. Build and execute"
echo "3. Execute"
read usr_input

cd ~/Abhinay/Ethercat_IGH/EtherCAT_layer/build


if [[ $usr_input -eq 1 ]]
then
    make clean
    cmake ..
    make
elif [[ $usr_input -eq 2 ]]
then
    make clean
    cmake ..
    make
    ./ethercat_layer
elif [[ $usr_input -eq 3 ]]
then
    ./ethercat_layer
else
  echo "Invalid option selected"
fi