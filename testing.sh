#!/bin/sh

for size in {7..11}
do
	for THRESHOLD in {6..11}
		do
			if [$THRESHOLD > $size]
			then
				break
			fi
			for proc in {1..6}
				do
					./charmrun ./strassen $((2**$size)) $((2**$THRESHOLD)) 0 +p$proc
					echo "----------------------------------------------------------"
				done

		done
done