set pagination off
set confirm off
set height 0
set width 0
set debuginfod enabled off
break abort
run -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker /home/musashi/bfm-decomp/.run/giants/pincrash/mini_call.c -o /dev/null
echo \n=== reload_completed (0=sched1, 1=sched2):\n
print (int)reload_completed
echo \n=== BACKTRACE ===\n
bt 8
echo \n=== create_reg_dead_note args (frame 1): reg rtx ===\n
frame 1
info frame
echo \n=== the reg being killed (debug_rtx of arg0) ===\n
# cdecl: args at ebp+8 (reg), ebp+12 (insn)
set $cr_ebp = $ebp
frame 0
# walk to frame 1's saved ebp: at abort entry, esp points at return addr; caller ebp unknown -> use frame cmd
frame 1
x/2wx $ebp+8
call (void)debug_rtx(*(void**)($ebp+8))
echo \n=== the insn being processed ===\n
call (void)debug_rtx(*(void**)($ebp+12))
quit
