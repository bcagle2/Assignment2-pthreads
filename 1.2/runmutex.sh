#delete output files
set -x
file='output12.txt'
#if output files exist delete them
if [ -f $file ]  
then rm $file
fi 
file='output12.csv'
if [ -f $file ]  
then rm $file
fi 
#now run the program - exit ends early
#  args  a  b #points intensity	#thread granularity mutexType
./a3-12.exe   5 10 10 	10	  16	  1000	      inner
./a3-12.exe   5 10 10 	10	  16	  1000	      local
./a3-12.exe   5 10 10 	10	  16	  1000	      thread

./a3-12.exe   5 10 100 	10	  16	  1000	      inner
./a3-12.exe   5 10 100 	10	  16	  1000	      local
./a3-12.exe   5 10 100 	10	  16	  1000	      thread

./a3-12.exe   5 10 1000 	10	  16	  1000	      inner
./a3-12.exe   5 10 1000 	10	  16	  1000	      local
./a3-12.exe   5 10 1000 	10	  16	  1000	      thread

./a3-12.exe   5 10 10000 	10	  16	  1000	      inner
./a3-12.exe   5 10 10000 	10	  16	  1000	      local
./a3-12.exe   5 10 10000 	10	  16	  1000	      thread

./a3-12.exe   5 10 100000 	10	  16	  1000	      inner
./a3-12.exe   5 10 100000 	10	  16	  1000	      local
./a3-12.exe   5 10 100000 	10	  16	  1000	      thread

./a3-12.exe   5 10 1000000 	10	  16	  1000	      inner
./a3-12.exe   5 10 1000000 	10	  16	  1000	      local
./a3-12.exe   5 10 1000000 	10	  16	  1000	      thread

./a3-12.exe   5 10 10000000 	10	  16	  1000	      inner
./a3-12.exe   5 10 10000000 	10	  16	  1000	      local
./a3-12.exe   5 10 10000000 	10	  16	  1000	      thread

./a3-12.exe   5 10 100000000 	10	  16	  1000	      inner
./a3-12.exe   5 10 100000000 	10	  16	  1000	      local
./a3-12.exe   5 10 100000000 	10	  16	  1000	      thread
exit 0