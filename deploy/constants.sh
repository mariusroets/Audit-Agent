#!/bin/bash

installdir="Lattitude Audit Agent"
if [ -e version ]; then
    version=`cat version`
else
    version="head"
fi;
tarball="audit_agent-"$version".tar.gz"
prefix="/opt"
service="lattitude-audit-agent"
logdir="/var/log/lattitude"
settingsdir="/etc/lattitude"
servicelog="service.log"
echo $tarball
