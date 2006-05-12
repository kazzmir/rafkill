#!/bin/sh

mkdir install
mkdir bin
scons prefix=install bin=bin
scons install
