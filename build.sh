if [ $1 ]; then
    git checkout $1
    echo $1 > deploy/version
else
    echo "head" > deploy/version
fi;
    
cd libgeneral/
make clean
make
cd ../
cd ftplib/
make clean
make
cd ..
cd dmidecode/
make clean
make
cd ..
make clean
make
git checkout master
cd deploy
./create_tarball.sh
cd ..
