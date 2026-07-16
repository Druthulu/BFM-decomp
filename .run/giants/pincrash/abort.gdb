set pagination off
set confirm off
set height 0
set width 0
set debuginfod enabled off
break abort
break fancy_abort
break fatal_insn
run -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker /home/musashi/bfm-decomp/.run/giants/pincrash/era_d9b0.i -o /home/musashi/bfm-decomp/.run/giants/pincrash/era_d9b0.s
echo \n=== BACKTRACE ===\n
bt 25
quit
