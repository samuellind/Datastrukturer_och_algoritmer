echo 'Compiling program'
gcc -Wall -o perf Dmenu.c menu.c BEPerf.c betree.c
echo 'Compile done, running program'
./perf < script1 > perf.out
echo 'Execution finished, running diff'
diff perf.old perf.out