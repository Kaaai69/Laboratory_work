#!/bin/bash

echo "Start server"

while true; do
    echo "Waiting for messages"
    nc -l 12345 | while read message; do
	echo "Receive message: $message"
	echo "Had message" | nc localhost 12345
    done
done

