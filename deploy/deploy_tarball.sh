#!/bin/bash

. constants.sh
if [ -z "$2" ]; then
    echo Doing local deploy...
    cp $tarball $prefix/
    cd $prefix
    tar -xzvf $tarball
    cd "$installdir"
    ./deploy_init.sh
else
    echo Doing remote deploy deploy to $2...
    scp $tarball root@"$1":$prefix/
    ssh root@"$1" "cd $prefix; tar -xzvf $tarball; cd \"$installdir\"; ./deploy_init.sh" 
fi
