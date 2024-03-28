FILE=cmd_line.sh
TMP=script_tmp
EXE=../minishell
VALGRIND=$(echo valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes)
make test_debug -sC ../

_COLOR_END=$(tput sgr0)
_COLOR_BOLD=$(tput bold)
_COLOR_RED=$(tput setaf 1)
_COLOR_GREEN=$(tput setaf 2)
_COLOR_YELLOW=$(tput setaf 3)

bad_v=0
bad_1=0
bad_2=0
passed=0
total=0
skiped=0
empty=0
trap 'exit' SIGINT
if [ "" = "$VALGRIND" ]; then
	echo "${_COLOR_RED}warning: valgrind disabled!!${_COLOR_END}"
fi
while IFS= read -r line; do
	if [ ! "#" = "${line:0:1}" ]; then
		rm -f $TMP"m" $TMP"b" $TMP"m2" $TMP"m1" $TMP"b2" $TMP"b1" $TMP"v"
		touch $TMP"m" $TMP"b" $TMP"m2" $TMP"m1" $TMP"b2" $TMP"b1" $TMP"v"
		echo "$line" > $TMP"b"
		echo -e "$line\nexit\n" > $TMP"m"
		<$TMP"b" bash 1>$TMP"b1" 2>$TMP"b2"
		<$TMP"m" $EXE 1>$TMP"m1" 2>$TMP"m2"
		if [ ! "" = "$VALGRIND" ]; then
			<$TMP"m" $VALGRIND $EXE 1>/dev/null 2>$TMP"v"
		fi
		#echo $VALGRIND $EXE | awk '{v=0} /==[0-9]+==/{v=1} ("ERROR" == $2){print $4}'
		sed -rzi 's/minishell> [^\n]*\n//g' $TMP"m1"
		B1=$(cat $TMP"b1" | sed -rz "s/\n/${_COLOR_BOLD}(newline)${_COLOR_END}/g")
		M1=$(cat $TMP"m1" | sed -rz "s/\n/${_COLOR_BOLD}(newline)${_COLOR_END}/g")
		B2=$(cat $TMP"b2" | sed -rz "s/\n/${_COLOR_BOLD}(newline)${_COLOR_END}/g")
		M2=$(cat $TMP"m2" | sed -rz "s/\n/${_COLOR_BOLD}(newline)${_COLOR_END}/g")
		B2L=$(echo -n $B2 | awk 'END{print NR==0}')
		M2L=$(echo -n $M2 | awk 'END{print NR==0}')
		if [[ "$line" == *"grep"* ]] || [[ "$line" == *"sort"* ]]; then
			V="";
			VSKIP=1
		else
			V=$(cat $TMP"v" | awk 'BEGIN{e=0} {v=0} /==[0-9]+==/{v=1} (v && "lost:" == $3 && "0" != $4){e++} (v && "ERROR" == $2){e += int($4)} END{print e}')
			VSKIP=0
		fi
		if [ "$B1" = "$M1" ]; then IS1EQ=1; else IS1EQ="${_COLOR_YELLOW}0${_COLOR_END}"; bad_1=$((bad_1+1)); fi
		if [ "$B2L" = "$M2L" ]; then IS2EQ=1; else IS2EQ="${_COLOR_YELLOW}0${_COLOR_END}"; bad_2=$((bad_2+1)); fi
		if [ "0" = "$V" ] || [ "" = "$V" ]; then ISVOK=1; else ISVOK="${_COLOR_YELLOW}0${_COLOR_END}"; bad_v=$((bad_v+1)); fi
		if [ ! $IS1EQ = 1 ] || [ ! $IS2EQ = 1 ] || [ ! $ISVOK = 1 ]; then
			printf '%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' _
			echo -e "${_COLOR_RED}KO:\t${_COLOR_BOLD}$line${_COLOR_END}"
			echo -e "IS1EQ=$IS1EQ IS2EQ=$IS2EQ ISVOK=$ISVOK"
			if [ $VSKIP = 1 ]; then
				echo -e "${_COLOR_YELLOW}valgrind disabled${_COLOR_END}"
			fi
			if [ ! $ISVOK = 1 ]; then
				echo -e "valgrind=$V errors"
			fi
			if [ ! $IS1EQ = 1 ] || [ ! $IS2EQ = 1 ]; then
				echo -e "bash 1:'$B1' 2:'$B2'"
				echo -e "mini 1:'$M1' 2:'$M2'"
			fi
			printf '%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' _
		else
			if [ ! "" = "$line" ]; then
				if [ ! "" = "$VALGRIND" ] && [ $VSKIP = 1 ]; then
					echo -e "${_COLOR_GREEN}OK:\t${_COLOR_BOLD}$line${_COLOR_END} (no valgrind)"
				else
					echo -e "${_COLOR_GREEN}OK:\t${_COLOR_BOLD}$line${_COLOR_END}"
				fi
				# echo "**** STDOUT:"$B1
				# if [ ! "" = "$M2" ] && [ ! "$B2" = "$M2" ]; then
				# 	echo "Bash STDERR:"$B2
				# 	echo "Mini STDERR:"$M2
				# fi
				passed=$((passed+1))
			fi
		fi
		if [ ! "" = "$line" ]; then
			total=$((total+1))
		else
			empty=$((empty+1))
		fi
		#exit
		rm -f $TMP"m" $TMP"b" $TMP"m2" $TMP"m1" $TMP"b2" $TMP"b1" $TMP"v"
	else
		skiped=$((skiped+1))
		echo -e "${_COLOR_YELLOW}SKIP:\t${_COLOR_BOLD}$line${_COLOR_END}"
	fi
done < $FILE

printf '%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' _
echo -e "passed\t$passed/$total Rate:$(echo "100 * "$passed/$total | bc)% (skiped:$skiped empty:$empty)"
echo -e "Errors:\nleak\t$bad_v/$total\nstdout\t$bad_1/$total\nstderr\t$bad_2/$total"
printf '%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' _