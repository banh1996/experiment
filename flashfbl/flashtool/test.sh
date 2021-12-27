#!/bin/sh
FOTASTATEFILE=/samples/systems/fota_aurix/fotastate.txt
if test -f "$FOTASTATEFILE"; then
    cd /samples/systems/fota_aurix/
    touch newnew.txt
    echo "$FOTASTATEFILE exists."
    state_val="$(cat $FOTASTATEFILE)"
    string_compare="FOTA_IN_PROGRESS"
    if [ "$state_val" = "$string_compare" ]; then
        touch temp.txt
        pp="$(pwd)"; echo "$pp" >  temp.txt
        params="/samples/systems/fota_aurix/run_test"; $params &
    fi  
fi
