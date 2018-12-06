
#!/bin/bash


# The line above makes your script executable.
# You should write your tutorial in here.

# I agree to share my tutorial on piazza.

# In daliy life, when we handle mess data such as stock price online, or the 
# company has the financial record, the data contains price, qulity and other 
# staff. When we need the some specific, looking at the oriangal file takes time,
# some this script can take into a csv file which contains the oriangal data, and 
# allow users the select the specific column of data as they want. 

# Since stock data contains price and usually people care about the price,
# This shell script allow user the enter the amount of data as they want. 
# For example, if the user want the second column's data, and want top 10 of
# it. It will select the specific data and sort it from high to low. User can 
# choose top10 or top 1 or more to handle the data easier and faster. 


# This script follow the first instrodution from the example provided by
# professor. When user run this shell, they can see the first row of the 
# csv file come with the index number of each data. 
# They will also get how may column the csv file
# Then the shell will ask user to provide which column of data they want
# And how many data they want to see. Such as enter 10 means check the
# top 10 data. All data are sorted from high to low.
# Also it will give the user the average of all rows of the column data they
# chose.



# Usage: 1. Get into the directory of the shell file. called myscript.sh
#        2. enter the command "sh myscript.sh"
#        3. Then the echo will ask you to enter the location of your csv file
#           I provided a csv file in the same directory as myscript.sh, and I 
#           made this location printed on the terminal interface when you run
#           the shell. You can just copy and paste it from the terminal 
#           interface.
#        4. After you enter the csv file location, the shell will list you the 
#           first row of data of the csv file provided. With the column number 
#           corresponding with each data. Such as Column 1 is Date...
#        5. It also provide the Max number of column
#        6. Then it will ask user to enter the number of column they want,
#           if user provides wrong input such as strings or numbers beyond the
#           maxium number of column, it will print the warning message and allow
#           users to enter again, it WON'T exit if user provides wrong input.
#        7. Then the shell wil ask users to enter how many rows of that column 
#           they want, for example, enter 10 means they want the top 10 data.
#           The order of data are sorted from high to low.
#        8. In the end the average of the whole column data which the user chose
#           will followed. 


#Ask the user to input the csv file location.
echo "Please enter the CSV file's location."
# Provide the user with the location of an example csv file.
echo "Here is the file location of my example csv file"
echo "/home/wangzongru/monorepo-Zongru-Wang/Assignment1_ShellScript/CSV.csv"
# Read the location that the user input.
read dir 

# Provide users with the first row of data from the csv file, corresponding
# with the index(start with 1) for each data
echo "Here is the first row of this file:"

awk 'BEGIN{ FS=","} 
      {for (n=1;n<=NF;n++){ print "Column" n" = " $n;}; exit;}' $dir


# Provide user with the Max number of column, so that avoid them ask the index
# of column which beyond the max number they can input.
echo "Here is the total number of columns:"
awk 'BEGIN{ FS=","} {{ print  NF;}; exit;}' $dir

# Ask user which column of data they want.
echo "Which column of data do you want?"
# Define a local variable which is the max column number of input csv file.
# It will be used to make the while loop after.
declare maxcoaldeclare maxcol=$( awk 'BEGIN{ FS=","}
  {{ print  NF;}; exit;}' $dir )

ifdone=false


# While user enter wrong input for column number, such as strings or beyond the 
# max column, this while loop ensures the terminal won't exit becasue of the 
# wrong input. So users will get chances to enter the data again without 
# rerun the shell file. 
while [ $ifdone = "false" ]
do 

# Read the user's input for which column they want.
read column


standrad='^[0-9]+$'

# Define a standard for users so if they enter not a integer, it will warn them
# but won't exit the script.
if ! [[ $column =~ $standrad ]]
then echo error: Not a number, please enter a number

# If the user input beyond the max column number, it will warn user and allow
# user to make a correct input.
elif [ $column -gt $maxcol ]
then echo "Your input is beyond the limit of column!"

# If the user input all data correctly, it will finished the while loop.
# By setting the boolean variable to be true.
else 

# Ask user to input How many result they want to see. 10 means top 10.
echo "Please enter how many result you want, ex: top10 enter 10"
read numberOfresult

# If the user enter a numberofruslt not a number, this script will quit.
if ! [[ $numberOfresult =~ $standrad ]]
 then echo "Please enter a number for tops!"
 exit 1
fi

#Set the variable to be ture, so the script ends.
ifdone=true

# Give the column that user chose and give the top ones that user chose.
awk -F "\"*,\"*" '{print $a}' a="$column"  $dir| sort -rk$column | tail -n $numberOfresult

# Cauculate the average of the whole column data which chose by the user.
echo "And the average of the column of data is:"
awk -F',' '{sum += $b} END {print sum / NR}' b="$column" $dir

# Finish the program
fi
done














