#!/bin/sh
# put this file in /usr/local

local RETRIES=0
local MAX_RETRIES=10

# Wait for eq0 interface to be up
while [ $RETRIES -lt $MAX_RETRIES ]; do
	if_up -p eq0
	if [[ $? -eq 0 ]]; then
		break;
	fi
	RETRIES=$(( RETRIES + 1 ))
done

sysctl -w net.inet.tcp.delack_ticks=3  #reduce delay ticks
params="/samples/systems/fota_aurix/run_fota_manager path=/samples/systems/fota_aurix/"; $params &  # run FOTA binary
