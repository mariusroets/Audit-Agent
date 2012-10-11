#!/bin/bash

# Just run this script from the directory where it is located to create a tarball

. constants.sh

mkdir "$installdir"
cp version "$installdir"
cp ../agent "$installdir"
mkdir "$installdir"/dmidecode
cp ../dmidecode/dmidecode "$installdir"/dmidecode
cp ../configfile.cfg "$installdir"
cp agent_service.sh "$installdir"
cp deploy_init.sh "$installdir"
cp constants.sh "$installdir"
tar -czvf $tarball "$installdir"
rm -rf "$installdir"
