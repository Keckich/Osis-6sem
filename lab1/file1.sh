#!/bin/bash
echo "User: " $(whoami)  
echo "Date: " $(date)
echo "Directory: " $(pwd)
echo "All files in current directory: " $(ls)
echo "Number of processes: " $(ps aux | wc -l)
echo "Uptime: " $(uptime -p) " since " $(uptime -s)
