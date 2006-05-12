#!/bin/sh

if [ "x$1" = "x" ]; then
	echo "version.sh x.y.z"
	exit 0
fi

version=$1

scons package
dir="rafkill-$version"
rm -rf $dir
mkdir $dir
cd $dir
untar ../src/source.tar
cp -a ../data .
cp -a ../music .
cp ../SConstruct .
cp ../build-rafkill.sh .
cp ../README .
cp ../Makefile .
cp ../INSTALL .
find . -name CVS | xargs rm -rf
cd ..
tar="rafkill-${version}.tar"
tar -cf $tar $dir
gzip $tar

rm -rf versions/$dir versions/$tar.gz
mv $tar.gz $dir versions
