output=$(ls -l ./error | grep "rw" | awk '{print $9}')

for file in $output; do
    # Execute ./miniRT with the current file as an argument
    	echo "\e[1;31m	Testing ./miniRT error/$file\e[0m"
	valgrind ./miniRT "error/$file" 2> grep "LEAK SUMMARY"
done
