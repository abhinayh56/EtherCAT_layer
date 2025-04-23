#!/bin/bash

echo "Select from below options..."
echo "1. Build"
echo "2. Execute"
echo "3. Build and execute"
echo "4. Start EtherCAT master"
echo "5. Stop EtherCAT master"
echo "6. Restart EtherCAT master"
echo "---"
read -p "Enter your option: " usr_input
echo "---"

cd ~/Abhinay/Ethercat_IGH/EtherCAT_layer/build

if [[ $usr_input -eq 1 ]]
then
    make clean
    cmake ..
    make
elif [[ $usr_input -eq 2 ]]
then
    ./ethercat_layer
elif [[ $usr_input -eq 3 ]]
then
    make clean
    cmake ..
    make
    ./ethercat_layer
elif [[ $usr_input -eq 4 ]]
then
    sudo /etc/init.d/ethercat start
elif [[ $usr_input -eq 5 ]]
then
    sudo /etc/init.d/ethercat stop
elif [[ $usr_input -eq 6 ]]
then
    sudo /etc/init.d/ethercat restart
else
  echo "Invalid option selected"
fi