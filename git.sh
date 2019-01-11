#!/bin/bash

rm -rf .git &&
git init &&
git remote add origin git@github.com:ljx791863565/working.git &&
git fetch &&
git reset --hard origin/master

