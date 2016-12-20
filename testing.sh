#!/bin/sh

# for size in {4..7}
# do
# 	for THRESHOLD in {3..6}
# 		do
# 			for proc in {1..10}
# 				do
# 					./charmrun ./strassen $((2**$size)) $((2**$THRESHOLD)) 0 +p$proc
# 					./OpenMP $((2**$size)) $((2**$THRESHOLD)) $proc
# 				done

# 		done
# 	./charmrun ./strassen $((2**$size)) $((2**$size)) 0 +p1
# done


for size in {6..10}
do
	for THRESHOLD in {6..7}
		do
			for proc in {1..10}
				do
					./charmrun ./strassen $((2**$size)) $((2**$THRESHOLD)) 0 +p$proc
					./OpenMP $((2**$size)) $((2**$THRESHOLD)) $proc
				done

		done
	./charmrun ./strassen $((2**$size)) $((2**$size)) 0 +p1
done

