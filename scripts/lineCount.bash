#!/bin/bash

count=0

walk_dir () {
    shopt -s nullglob dotglob

    for pathname in "$1"/*; do
        if [ -d "$pathname" ]; then
            walk_dir "$pathname"
        else
#            printf '%s\n' "$pathname"
          num=$(wc -l < "$pathname")
          printf '%d\t\t%s\n' "$num" "$pathname"
          count=$((num+count))
        fi
    done
}
printf "Line count\tDirectory\n"
printf '%.0s-' {1..100}
printf "\n"

walk_dir include
walk_dir src
walk_dir examples

printf '%.0s-' {1..100}
printf "\nTotal:\t\t%d\n" "$count"
