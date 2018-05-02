#!/bin/sh
# Created by David Haylock on 2/05/2018.

repobase="https://github.com";
repos="jefftimesten/ofxJSON  \
paulvollmer/ofxCsv \
DHaylock/ofxHttpUtils";

# I've included a version of ofxFft into the Repo that I've altered slightly 
# This is easier than me faffing with uploading the repo etc
# So lets copy this straight across
cp -r ofxFft/ /home/pi/openFrameworks/addons

cd /home/pi/openFrameworks/addons/

echo "------------------------------";
echo "----> Looking for Addons <----";

# Cycle through the Repo's Clone if they don't exist
# If they do then Make sure they are upto date
for repo in ${repos};
do
if [ ! -d "${repo}" ]; then
    echo "----> Cloning ${repo} <----";
    git clone "${repobase}/${repo}.git";
    echo "----> Cloned ${repo} <----";
else
    echo "----> Pulling ${repo} <----";

    # Put us into the addon directory
    cd "${repo}";
    pwd;

    # Pull the latest verison from GitHub
    git pull;

    # Put us one level up
    cd ..;
    echo "----> Pulled ${repo} <----";
fi
done
exit;
