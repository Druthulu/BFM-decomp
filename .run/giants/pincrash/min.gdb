set pagination off
set confirm off
set debuginfod enabled off
break abort
run -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker /home/musashi/bfm-decomp/.run/giants/pincrash/minimal_repro.c -o /dev/null
bt 8
print (int)reload_completed
frame 1
x/2wx $ebp+8
call (void)debug_rtx(*(void**)($ebp+8))
call (void)debug_rtx(*(void**)($ebp+12))
quit
