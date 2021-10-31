# Problem 1:

1. `execl*` vs `execv*`
    1. `execl`
        1. Known all the arguments passed in
    2. `execv`
        1. Known there will be arguments passed in, but don't know how many are there.
    3. Conclusion
        1. Since `ls`  take one argument, while `grep cat word.txt` takes three arguments, we cannot sure how many arguments will be passed in. Therefore, `execv` should be the pick
2. Should use `execvp`
    1. Since there is no full path of the program provided in the test case, we should use suffix `p` which will search the directories in the PATH environment variable.

# Problem2:

1. `open`
    1. `rcmd->mode|O_CREAT` : create the file if not present
    2. `S_IRWXU`: 700 - give user read, write, execute to this file
2. `dup2`
    1. replace standard input or output with the open file