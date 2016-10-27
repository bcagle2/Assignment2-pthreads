#delete output files
set -x
file="output.txt"

#if output files exist delete them
if [ -f $file ]  
then rm $file
fi 

file="output.csv"
if [ -f $file ]  
then rm $file
fi 

#now run the program - exit ends early
#  args    a b #points intensity
./a3-11.exe 5 10 10 1
./a3-11.exe 5 10 10 10
./a3-11.exe 5 10 10 100
./a3-11.exe 5 10 10 1000

./a3-11.exe 5 10 100 1
./a3-11.exe 5 10 100 10
./a3-11.exe 5 10 100 100
./a3-11.exe 5 10 100 1000

./a3-11.exe 5 10 1000 1
./a3-11.exe 5 10 1000 10
./a3-11.exe 5 10 1000 100
./a3-11.exe 5 10 1000 1000

#exit 0

./a3-11.exe 5 10 10000 1
./a3-11.exe 5 10 10000 10
./a3-11.exe 5 10 10000 100
./a3-11.exe 5 10 10000 1000

./a3-11.exe 5 10 100000 1
./a3-11.exe 5 10 100000 10
./a3-11.exe 5 10 100000 100
./a3-11.exe 5 10 100000 1000

./a3-11.exe 5 10 1000000 1
./a3-11.exe 5 10 1000000 10
./a3-11.exe 5 10 1000000 100
./a3-11.exe 5 10 1000000 1000

./a3-11.exe 5 10 10000000 1
./a3-11.exe 5 10 10000000 10
./a3-11.exe 5 10 10000000 100
./a3-11.exe 5 10 10000000 1000

./a3-11.exe 5 10 100000000 1
./a3-11.exe 5 10 100000000 10
./a3-11.exe 5 10 100000000 100
./a3-11.exe 5 10 100000000 1000
exit 0