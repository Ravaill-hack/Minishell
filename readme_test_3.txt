https://github.com/thallard/minishell_tester

uncomment second main and the ft_launch_minishell function

cd minishell_tester_2

bash test.sh compatibility

bash test.sh help

bash test.sh

bash test.sh [--diff] [--fast] [--short] [--valgrind] <name_file> ...

bash test.sh --diff all
bash test.sh --diff echo 
bash test.sh --fast echo cd
bash test.sh --diff --fast echo export unset
bash test.sh --diff --valgrind all
bash test.sh -f -s -d all
