
|
echo ok | echo ok 
echo ok |
echo ok | | echo ok 
| echo ok
echo ok | >lol
(false | true) && echo $? 
(true | false) || echo $? 

||
echo ok || echo ok 
echo ok || || echo ok 
|| echo ok
false || echo $?


&&
echo ok && echo ok 
echo ok && && echo ok 
&& echo ok
true || echo $?


echo lol | exit 2 && echo $?
echo lol | exit && echo $?
echo lol | exit 2 3 && echo $?
echo lol | exit patate && echo $?
echo lol | exit patate 2 && echo $?
echo lol | exit "" && echo $?
echo patate | cat | cat | cat | cat
echo patate | cat | echo lol

echo
echo a
echo hello world
echo -n
echo -n a
echo -n hello world
echo -nnnnnnnn ok
echo hello -n
echo "-n" hello
echo '-n' hello
echo "-n" "hello"
echo '-n' 'hello'
echo $PATH
echo "$PATH"
echo '$PATH'
echo a "" b "" c
#echo a "$NO_SUCH_ENV" b $NO_SUCH_ENV c, unset NO_SUCH_ENV
echo "$ $ $ $ $ $ "
echo $

&
# echo ok & echo ok 
echo ok & & echo ok 
& echo ok

;
# echo ok ; echo ok 
# echo ok ; ; echo ok 
; echo ok

(>lol )
( )
()
(true)
((true)
(true))
(
)
(true || false) && echo patate
(true && false) && echo patate
(true && true) && echo patate
(true && false) || echo patate

>
>ok1 >ok2 >ok3 echo patate && cat ok1 && echo "ok" && cat ok2 && echo "ok" && cat ok3 && rm ok1 && rm ok2 && rm ok3
<
>>
<cmd_line.sh cat >>tmp1 && rm tmp1
<cmd_line.sh cat >>tmp1 && echo 1 >>tmp1 && cat tmp1 && rm tmp1
<<

cd

env | grep -v -E '^_=' | sort
env | grep -v -E '^_=' | sort, export A=hello
cd ../ && env | grep -v -E '^_=' | sort

export A=5 "" && echo $? 
export A=5 "" || echo $? 
export A=5 "" && (env | grep -e "^A=")
export PATH=
export A=1 && echo $A
# export B && echo $B
export C= && echo $C
export d=5 && echo $d
export 8=5
export _ANKHN1654adasd=5
# export
export =5
export ==5
export A==5
export L=l S=s && $L$S
# export LS="ls -la" && $LS
export "" || echo $?
export "=" || echo $?
export "A=3" && echo "echo $A$A$A$A$"

#export 1 _+ _OK _2? _OK2=VAR =NG OK3= && env | grep -v -E '^declare -x _='
# export APPEND=1 && export APPEND+=2 && env | grep APPEND
export APPEND_EMPTY="" && export APPEND_EMPTY="" && export APPEND_EMPTY="" && env | grep APPEND_EMPTY
export OVERWRITE=42 &&  export OVERWRITE=a && env | grep OVERWRITE
export A=B=C=D && env | grep -e "^A"
# export PATH && env | grep PATH
# export PWD && env | grep PWD
# export OLDPWD && env | grep OLDPWD
unset PWD && cd .. && env | grep PWD
unset OLDPWD && cd .. && env | echo $OLDPWD
unset PWD && cd .. && export PWD=new_value && env | grep PWD
unset OLDPWD && cd .. && export OLDPWD=new_value && env | grep OLDPWD
# unset PWD && cd .. && export PWD && env | grep PWD
# unset OLDPWD && cd .. && export OLDPWD && env | grep OLDPWD
export =

export PATH=":"  && ls
export PATH="::"  && ls
export PATH=":/"  && ls
cp ../minishell ./minishell && chmod 000 minishell && ./minishell || chmod 777 ./minishell && rm -rf ./minishell
export PATH=":$PATH"  && ls
export PATH="::$PATH"  && ls
export PATH="::$PATH:"  && ls
export PATH="::$PATH::"  && ls

cd .. && pwd && cd $OLDPWD && pwd
cd .. && unset OLDPWD && cd && echo $OLDPWD
cd .. && unset PWD && cd && echo $OLDPWD
cd XXx_PATATE_xXX
cd XXx_PATATE_xXX || echo $?
cd XXx_PATATE_xXX && echo $?
cd >tmp && cat tmp && rm tmp

unset 5
unset A
unset A=3
unset ""
unset XXx_PATATE_xXX

unset && env | grep -v -E '^_=' | sort
unset A && echo $A
unset _A1 && echo $_A1
unset A B C && echo $A$B$C$D
unset A B =invalid C && echo $A$B$C$D
unset PWD && echo $PWD
unset OLDPWD && echo $OLDPWD
unset NO_SUCH_ENV && echo $?$NO_SUCH_ENV
unset 1
unset A=a && echo $A
unset ' $&`'

#env

echo !!!space bellow!!!
    
echo !!!space above!!!

echo ok | echo ok
echo ok | | echo ok

echo
echo ""
echo "ok"
echo "ok" "lol" ""
echo -n ""
echo -n "ok"
echo -n "ok" "lol" ""
echo "ok" >tmp && cat tmp && rm tmp

pwd
pwd ""
pwd ok
pwd ok banane
pwd >tmp && cat tmp && rm tmp

patate
patate ""
patate grosse
patate grosse et fraiche et ""
patate >tmp || cat tmp && rm tmp

/usr/bin/ls
/usr/bin/ls main.c
/usr/bin/ls virus_win64.exe
./virus_win64.exe
/usr/bin/ls uh-oh

echo "OK"'lol'*"$HOME"'$HOME'
echo $HOME$HOME$HOME
echo $HOME'$HOME'"$HOME"

export A="*" && echo $A
echo *
echo *.c
echo *".c"
echo *'.c'
echo **.c
echo *.c*
echo .c*
echo .*
echo \*
echo "*"
echo *

echo $?
patate fraiche
echo $?
true && echo $? 
false || echo $?
true && echo $? || patate || echo $? && echo $?
((true && echo $?) || (patate && patate grosse et delicieuse)) && echo $?
(> tmp) && echo $? && rm tmp && echo $?
true
echo $? | echo $?
echo $? | false | echo $?
false
echo $? | echo $?
