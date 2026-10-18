#!/bin/bash

temps=(11 22 101 -44 -99 33)

func_f()
{
    local cel=$(($1 * 9 / 5 + 32))
    echo $cel
}

func_c()
{
    local fahr=$((($1 - 32) * 5 / 9))
    echo $farh
}

add()
{
    read -p "введите тмпературу (С): " new_t
    temps+=("$new_t")
}

show()
{
    read -p "1 - cel, 2 - fahr, 3 - exit: " choice
    case $choice in
    1)
    for temp in "${temps[@]}"
    do 
        echo -n "$temp " 
    done 
    echo ;;
    2)
    for temp in "${temps[@]}"
    do 
        echo -n "$(func_f "$temp")  " 
    done 
    echo ;;
    3) return 
    esac
}

while true; do
    read -p "1 - add, 2 - show, 3 - exit: " choice

    case $choice in
        1) add ;;
        2) show ;;
        3) exit 0 ;;
    esac
done
