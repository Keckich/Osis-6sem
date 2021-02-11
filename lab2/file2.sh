# !/bin/bash

window_x=$(tput lines)
window_y=$(tput cols)
M=32323
a=7
c=77
xi=$(($(date +%N)%M))

next_xi() {
	xi=$(((a*xi+c)%M))
}

while true
	do
	printf "\033c"
	next_xi
	x=$((xi%window_x))
	next_xi
	y=$((xi%window_y))
	tput cup $x $y
	date +"%H:%M"
	sleep 10
done


