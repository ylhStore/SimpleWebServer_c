#!/bin/bash
source ./prefix.sh
ip=127.0.0.1
port=80
maxClient=8
background=8
AimSvrd=${Svrd}${Version}
BIN=${AimSvrd}
./$BIN --ip=$ip --port=$port --maxClient=$maxClient --background=$background


