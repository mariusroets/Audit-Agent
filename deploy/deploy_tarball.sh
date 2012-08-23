#!/bin/bash

. constants.sh

scp $tarball root@"$1":$prefix/
ssh root@"$1" "cd $prefix; tar -xzvf $tarball; cd '$installdir'; ./deploy_init.sh" 
