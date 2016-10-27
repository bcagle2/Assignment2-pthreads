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
./a3-22.exe 50000000 1 16
./a3-22.exe 50000000 5 16
./a3-22.exe 50000000 10 16
./a3-22.exe 50000000 15 16
exit 0
