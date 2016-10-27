#delete output files
#set -x
file='output22q3.txt'
#if output files exist delete them
if [ -f $file ]  
then rm $file
fi 
file='output22q3.csv'
if [ -f $file ]  
then rm $file
fi 
#now run the program - exit ends early
#           intensity	intensity factor	max# threads	
./a3-22.exe 50000000 5 1
./a3-22.exe 50000000 5 2
./a3-22.exe 50000000 5 4
./a3-22.exe 50000000 5 8
./a3-22.exe 50000000 5 16

exit 0
