/*
to compile: make

usage:  pd [comma-delimited partition 1, enclosed in quotes] [comma-delimited partition 2, enclosed in quotes]

examples: ./pd "2,2,2,2" "5,5,5,5"
          ./pd "1,1,0,0" "2,2,2,2"
          ./pd "1,1,0,0" "3,3,4,4"
          ./pd "1,1,2,2,2,6,6,5,6,7,8,8" "4,4,6,6,6,0,0,0,2,2,2,2"
          
notes: Partitions must be encoded using positive integers. pd returns a normalized partition
       distance, calculated as the partition distance of Gusfield 2002, Information Processing 
       Letters, 82:159, divided by the maximum possible partition distance, as described 
       by Charon et al. 2006, Journal of Classification 23:103. The normalized partition 
       distance is returned as stdout.
*/
