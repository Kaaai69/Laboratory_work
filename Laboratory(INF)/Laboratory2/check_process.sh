#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Не указано имя процесса"
    exit 1
fi

process="$1"
а
if pgrep -x "$process" > /dev/null; then
    echo "Процесс запущен"
else
    echo "Процесс не найден"
fi
