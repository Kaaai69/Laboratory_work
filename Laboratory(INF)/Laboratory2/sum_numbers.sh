read number1 number2 
if [ -z "$number1" ] && [ -z "$number2" ]; then 
    echo "Не дурите и введите числа"
else
    result=$(( $number1 + $number2 ))
    echo "$result"
fi


