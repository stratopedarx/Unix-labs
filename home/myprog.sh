#!/bin/bash

file_name=$1  # the text file
script_name=$0
echo "$file_name"
echo "Вы запустили скрипт с именем $script_name и параметром $parametr1"
if [ ! -f $file_name ] ;then   # if file is not exist
    echo "The file $file_name is not exist! Create him!"
    exit 1
fi
flag=yes
while [ "eternal cycle" ] 
do
	echo "What do you want to do? Choose one of the following commands"
	echo "1 - Find the word and print all strings with this word"
	echo "2 - Replace the word in the text file"
	echo "3 - Count the number of strings with your word"
	echo "4 - Save the current file"
	echo "5 - Exit from the program"
	echo "Enter please the command: "
	read doing
	echo "Your choice is $doing"
	case $doing in
		1)
			echo "Enter the word please: "
			read word
			grep "$word" "$file_name"
			echo "Push the button 'enter'"
		;;
		2)
			echo "Enter the old word: "
			read old_word
			echo "Enter the new word: "
			read new_word
			cat "$file_name" | sed "s/$old_word/$new_word/g" | grep "$new_word"  # print string with new word
			cat "$file_name" | sed "s/$old_word/$new_word/g" > ./temporary_file.txt  # cat new text in temp file
			mv -f ./temporary_file.txt "$file_name"  # resave 
			echo "Push the button 'enter'"
		;;
		3)
			echo "Enter the word please: "
			read word
			echo "Your word $word and number of the strings with this word: "
			grep "$word" "$file_name" | wc -l
			echo "Push the button 'enter'"
			
		;;
		4)
			cp "$file_name" ./temporary_file.txt
			cp ./temporary_file.txt "$file_name"
			rm ./temporary_file.txt
			echo "Successful save"
			echo "Push the button 'enter'"
		;;
		5)
			echo "Have a nice day brother!"
			exit 0
		;;
		*)
			echo "Input Error"
			echo "Push the button 'enter'"
	esac
	read flag
done
	echo "Have a nice day brother!"
exit 0