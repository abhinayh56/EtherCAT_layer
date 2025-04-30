#!/bin/bash

echo "==== IGH EtherCAT Master Diagnostic ===="

# 1. Check master status
echo -e "\n-- [1] Master Status --"
ethercat master || { echo "❌ ethercat master failed"; exit 1; }

# 2. Check slave status
echo -e "\n-- [2] Slave Status --"
ethercat slaves || echo "⚠️  No slaves detected!"

# 3. Check if all slaves are in OP state
echo -e "\n-- [3] Verifying Operational (OP) state --"
ethercat slaves | grep -q "OPERATIONAL"
if [ $? -eq 0 ]; then
    echo "✅ All slaves are in OP"
else
    echo "❌ One or more slaves are NOT in OP!"
fi

# 4. Check for lost frames
echo -e "\n-- [4] Lost Frames --"
ethercat master | grep "Lost frames"

# 5. Check PDOs
echo -e "\n-- [5] PDO Mapping --"
ethercat pdos || echo "⚠️  Could not read PDOs"

# 6. Check configured PDOs
echo -e "\n-- [6] PDO Registration Summary (C Struct) --"
ethercat cstruct || echo "⚠️  cstruct output failed"

# 7. Print NIC info
echo -e "\n-- [7] NIC Info (Check for Real-Time Driver) --"
ethtool -i $(ethercat master | grep -oP 'Main device:\s+\K.*') 2>/dev/null

# 8. Reminder about VirtualBox limitations
echo -e "\n-- [8] Virtual Machine Warning --"
if hostnamectl | grep -iq virtual; then
    echo "⚠️  You're running in a Virtual Machine. PDO exchange is unreliable in VirtualBox!"
else
    echo "✅ Running on bare-metal (or not a known VM)"
fi

echo -e "\n=== Done ==="
