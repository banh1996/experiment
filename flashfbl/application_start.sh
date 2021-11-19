#!/bin/sh
FOTASTATEFILE=/samples/systems/fota_aurix/fotastate.txt
if test -f "$FOTASTATEFILE"; then
    cd /samples/systems/fota_aurix/
    #touch newnew.txt
    echo "$FOTASTATEFILE exists."
    state_val="$(cat $FOTASTATEFILE)"
    string_compare="FOTA_IN_PROGRESS"
    if [ "$state_val" = "$string_compare" ]; then
        #waitfor /dev/socket
        #touch temp.txt
        #pp="$(pwd)"; echo "$pp" >  temp.txt
        params="/samples/systems/fota_aurix/run_fota_qnx continue /samples/systems/fota_aurix/"; $params &
    fi  
fi
