#delete output files
#set -x
file='output22.txt'
#if output files exist delete them
if [ -f $file ]  
then rm $file
fi 
file='output22.csv'
if [ -f $file ]  
then rm $file
fi 
#now run the program - exit ends early
#           intensity	intensity factor	max# threads	
./a3-22.exe 50000000 5 16
./a3-22.exe 100000000 5 16
./a3-22.exe 150000000 5 16
./a3-22.exe 500000000 5 16
./a3-22.exe 1000000000 5 16
exit 0
