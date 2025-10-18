#!/bin/bash

if [ $# -eq 0 ]; then
    echo "$0 'message'"
    exit 1
fi

message="$1"
echo "$message" | nc localhost 12345
