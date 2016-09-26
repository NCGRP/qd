/*
To compile: make

Usage:  qd [-q qmatrix1 qmatrix2] [-p partition1 partition2 [-n]]

Options: 
-q Calculate the q-distance.
  qmatrix1 = path to file containing a q-matrix
  qmatrix2 = path to file containing a second q-matrix
 
-p Calculate the partition distance
  partition1 = a comma-delimited partition, enclosed in quotes
  partition2 = a comma-delimited partition, enclosed in quotes
  -n normalize the partition distance to the maximum possible value

  Examples: ./qd -p "1,1,1,1,1,1" "2,2,2,2,2,1"
            ./qd -p "1,1,1,1,1,1" "2,2,2,2,1,1"
            ./qd -p "1,1,1,1,1,1" "2,2,2,1,1,1"
            ./qd -p "1,1,1,1,1,1" "2,2,2,2,3,1"
            ./qd -p "1,1,1,1,1,1" "2,2,3,3,1,1"
            ./qd -p "1,1,1,1,1,1" "6,5,4,3,2,1"
            ./qd -p "1,1,0,0" "3,3,4,4"
            ./qd -p "1,1,2,2,2,6,6,5,6,7,8,8,946" "4,4,6,6,6,0,0,0,2,2,2,2,4"

  Notes: Encode partitions using positive integers. qd -p returns the partition distance of Gusfield 2002, Information Processing 
         Letters, 82:159, optionally normalized by dividing by the maximum possible partition distance, as described 
         by Charon et al. 2006, Journal of Classification 23:103.
*/
