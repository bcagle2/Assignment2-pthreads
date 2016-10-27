#delete output files
#set -x
file='output21.txt'
#if output files exist delete them
if [ -f $file ]  
then rm $file
fi 
file='output21.csv'
if [ -f $file ]  
then rm $file
fi 
#now run the program - exit ends early

./a3-21.exe 50000000
./a3-21.exe 100000000
./a3-21.exe 150000000
./a3-21.exe 500000000
./a3-21.exe 1000000000

exit 0
