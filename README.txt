/*
to compile:
make

usage:  pd [comma-delimited partition 1, enclosed in quotes] [comma-delimited partition 1, enclosed in quotes]

examples: ./pd "2,2,2,2" "5,5,5,5"
          ./pd "1,1,0,0" "1,1,1,1"
          ./pd "1,1,2,2,2,6,6,5,6,7,8,8" "4,4,6,6,6,0,0,0,2,2,2,2"
          
notes: Partitions must be encoded using positive integers. pd returns a normalized partition
       distance, calculated as the partition distance of Gusfield (2002), divided by the 
       maximum possible partition distance (for the two partitions), as described by 
       Charon and Denoeud (2006).
*/
