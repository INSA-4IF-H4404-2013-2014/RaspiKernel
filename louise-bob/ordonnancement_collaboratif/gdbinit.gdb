layout split
fs cmd
wh cmd 12
target remote:1234
b notmain
b ctx_switch
b funcA
b funcB
source include.gdb
