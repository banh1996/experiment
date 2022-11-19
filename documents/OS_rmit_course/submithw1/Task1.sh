#!/bin/bash
awk '$1 ~ /^[a-z]+$/' $1 | awk '{ if (length($0) < 16 && length($0) > 2) { print } }' | uniq -u
