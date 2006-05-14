#!/bin/sh

if [ "x$1" = "x" ]; then
	echo "version.sh x.y.z"
	exit 0
fi

version=$1

important_files="SConstruct build-rafkill.sh README COPYING Makefile INSTALL"

scons package
dir="rafkill-$version"
rm -rf $dir
mkdir $dir
cd $dir
untar ../src/source.tar
cp -a ../data .
cp -a ../music .
for i in $important_files
do
	cp ../$i .
done
find . -name .svn | xargs rm -rf
cd ..
tar="rafkill-${version}.tar"
tar -cf $tar $dir
gzip $tar

md versions &>/dev/null
rm -rf versions/$dir versions/$tar.gz
echo "Moving $tar.gz to versions/$tar.gz"
mv $tar.gz $dir versions
