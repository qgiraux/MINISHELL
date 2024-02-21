valgrind -s --trace-children=yes --leak-check=full --show-leak-kinds=all ./pipex text_files/test.txt "sort -r" "grep 7" "cat -e" "text_files/out"; echo $?; cat text_files/out;
valgrind -s --trace-children=yes --leak-check=full --show-leak-kinds=all ./pipex here_doc end "sort -r" "grep test" "cat -e" "text_files/out"; echo $?; cat text_files/out;

