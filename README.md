# Minishell

watch this video https://www.youtube.com/watch?v=8Hx5Ye_mf8A&list=PLKUb7MEve0Tizh0gqRm8s8IJiPg5VC4mO
allokey




### Don't forget to protect against losing the env vars with <env -i ./minishell> cmd   ###



#### treat this case for exec  cat a & echo "bomm bom"   ######


### treat this case  cat <<EOF
This is a test
EOF  ####


| task | M4ntr4    | Jaime    |
| :---:   | :---: | :---: |
| Display a prompt when waiting for a new command. | done  | done   |
| Have a working history | done   | done  |
| Search and launch the right executable (based on the PATH variable or using arelative or an absolute path). | done   | TO DO   |
| Not use more than one global variable. Think about it. You will have to explainits purpose. | TO DO  | -   |
| Handle (single & doublle quote) | done   | done   |
| Implement redirections: | done    | done    |
|  Implement pipes | done | done   |
| Handle environment variables ($) | done    | TO DO    |
| Handle $? which should expand to the exit status of the most recently executedforeground pipeline. | DONE    | TODO    |
| Handle ctrl-C, ctrl-D and ctrl-\ | TO DO    | TO DO    |
| implement the  builtins | TO DO    | TO DO    |
| task | M4ntr4    | Jaime    |
