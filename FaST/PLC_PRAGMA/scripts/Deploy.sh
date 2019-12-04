#!/usr/bin/env bash
#
#Be sure in correct parameters before script running
#
#More information and additional files looks in FaST repository
#

targetAddress=192.168.137.2
targetLogin=pi
targetPassword=raspberry
inputDir=/PLC_PRAGMA

if sshpass -p $targetPassword scp -r pi@192.168.137.2:/home/${targetLogin}/${inputDir} ~${inputDir} ; then
  echo -e "Files from ${inputDir} \e[32mtransferred\e[39m"
else
  echo -e "Files from ${inputDir} \e[31mnot transferred\e[39m"
fi

sshpass -p $targetPassword scp -r pi@192.168.137.2:/home/${targetLogin}/Beremiz/beremiz/ ~${inputDir}/tools/STbuilder.py

if sshpass -p $targetPassword ssh ${targetLogin}@${targetAddress} '/home/pi/MakeFull.sh' ; then
  echo -e "Deploy \e[32msuccess\e[39m"
else
  echo -e "\nSSH connection \e[31mfailed\e[39m.\nCheck SSH service on ${targetAddress} for ${targetLogin}\n"
fi
