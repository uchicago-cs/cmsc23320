#!/bin/bash

# Script to grade a single repository.
#
# Usage:
# 
#     grade-chirc.sh <team> <assignment> [<commit>]
# 
# First parameter is your team identifier
#
# Second parameter is the chirc assignment number
#
# Optional third parameter is the commit you want to build.
# (if none is specified, the head of the master branch will be built)

set -o pipefail

if [ "X$1" == "X" ];
then
	echo "ERROR: Please specify a team."
	exit 1
fi

if [ "X$2" == "X" ];
then
	echo "ERROR: Please specify an assignment number."
	exit 1
fi

TEAM=$1
AID=$2

if ! chisubmit student team show $TEAM 2>&1 > /dev/null;
then
    echo "No such team: $TEAM"
    exit 1
fi

echo -n "Cloning your repository... "
 
REPO_DIR=$(chisubmit student team repo-pristine-clone $TEAM 2>&1 | grep -o "/tmp/.*")

if [ "$?" -ne "0" ]; 
then
    echo "ERROR: Could not clone the repository for $TEAM"
    exit 1
fi
echo "done."

if [ ! -e $REPO_DIR/chirc ];
then
    echo "ERROR: Your repository doesn't seem to contain a valid chirc directory"
    exit 1
fi

cd $REPO_DIR/chirc

if [ $# -eq 3 ];
then
	CHECKOUT=$3
else
	CHECKOUT=master
fi

if [ $CHECKOUT != "master" ];
then
	git rev-list --all | grep $CHECKOUT > /dev/null

	if [ "$?" -ne "0" ]; 
	then
		echo "ERROR: Repository $TEAM does not have a $CHECKOUT commit."
		exit 1
	else
		git checkout $CHECKOUT > /dev/null 2>&1
	fi
else
	git checkout master > /dev/null 2>&1
fi

echo -n "Checking for chirc files... "
for CHIRC_FILE in $REPO_DIR/chirc/ $REPO_DIR/chirc/tests/ $REPO_DIR/chirc/src/;
do
    if [ ! -e $CHIRC_FILE ];
    then
        echo "ERROR: Your repository doesn't seem to contain a valid chirc directory"
        exit 1
    fi
done
echo "done."

echo -n "Building $TEAM chirc..."

BUILD_LOG="/tmp/chirc-build-$USER-$$.log"
touch $BUILD_LOG
chmod 600 $BUILD_LOG

mkdir build
cd build
cmake .. > $BUILD_LOG 2>&1
make clean >> $BUILD_LOG 2>&1
make >> $BUILD_LOG 2>&1
if [ "$?" -ne "0" ]; 
then
	echo "ERROR: Your project did not build."
    echo "       Build log is in $BUILD_LOG"
    exit 1
else
    rm $BUILD_LOG
fi	

echo "done."


echo "Running tests..."

CHIRC_DIR=$(mktemp -d)

git clone https://github.com/uchicago-cs/chirc.git $CHIRC_DIR > /dev/null 2>&1

if [ "$?" -ne "0" ]; 
then
    echo "ERROR: Could not clone chirc upstream repository"
    exit 1
fi

python3 -m pytest $CHIRC_DIR/tests/ --chirc-rubric $CHIRC_DIR/tests/rubrics/assignment-${AID}.json
python3 $CHIRC_DIR/tests/grade.py $CHIRC_DIR/tests/rubrics/assignment-${AID}.json

rm -rf $CHIRC_DIR
rm -rf $REPO_DIR

echo "DONE"


