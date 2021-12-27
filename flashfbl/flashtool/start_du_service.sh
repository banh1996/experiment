#!/bin/sh
#
# Copyright (c) 2019-2021, NVIDIA CORPORATION.  All rights reserved.
#
# NVIDIA CORPORATION and its licensors retain all intellectual property
# and proprietary rights in and to this software, related documentation
# and any modifications thereto.  Any use, reproduction, disclosure or
# distribution of this software and related documentation without an express
# license agreement from NVIDIA CORPORATION is strictly prohibited.
#

#define NVDU_ID
NVDU_ID=3360

#define DU_ROOT_PATH
DU_ROOT_PATH='/usr/local/driveupdate'

#Check if Comms & Security is enabled
NVSEC_STATUS=0
if [ -e "/dev/nvdt/tegra_hv_secmsg" ]; then
    read NVSEC_MSG_NODE < /dev/nvdt/tegra_hv_secmsg/status
    if [[ "$NVSEC_MSG_NODE" != *"disabled"* ]]; then
        NVSEC_STATUS=1
    fi
fi

if [[ -e "/dev/nvdt/chosen/driveupdate/gos-b" ]]; then
    # Wait for TA/TB connection on dual-tegra
    if [[ "$NVSEC_STATUS" -eq 1 ]]; then
        if_up -r 20 hv2
    else
        if_up -r 20 vlan200
    fi
fi

# Start router
iolauncher -U $NVDU_ID:$NVDU_ID,2000,3220 -T nvdriveupdate_router $DU_ROOT_PATH/bin/dulink_router

# Start Boot health check
iolauncher -U $NVDU_ID:$NVDU_ID,2000,3220 $DU_ROOT_PATH/bin/dubhc_plugin

# Start Boot Manager
iolauncher -U $NVDU_ID:$NVDU_ID,2000,3220 $DU_ROOT_PATH/bin/bootmgr

# Plugins only packaged in standard build
if [ -e "/dev/nvdt/" ]; then
    # Start Aurix firmware installer
    iolauncher -U $NVDU_ID:$NVDU_ID,2000,3220 $DU_ROOT_PATH/bin/aurix_installer

    # aquantia firmware installer needs to run as root for now
    $DU_ROOT_PATH/bin/aquantia_installer
fi

