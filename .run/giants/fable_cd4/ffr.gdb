set pagination off
set confirm off
set height 0
set debuginfod enabled off
break *0x8149ad0
commands 1
  silent
  set $cls = *(int*)($esp+4)
  set $qty = *(int*)($esp+12)
  set $acc = *(int*)($esp+16)
  set $sugg = *(int*)($esp+20)
  set $born = *(int*)($esp+24)
  set $dead = *(int*)($esp+28)
  set $qfr = *(int**)&qty_first_reg
  set $qnr = *(int**)&qty_n_refs
  set $qb = *(int**)&qty_birth
  set $qd = *(int**)&qty_death
  printf "FFR qty=%d reg1=%d refs=%d cls=%d acc=%d sugg=%d born=%d dead=%d (b=%d d=%d)\n", $qty, $qfr[$qty], $qnr[$qty], $cls, $acc, $sugg, $born, $dead, $qb[$qty], $qd[$qty]
  continue
end
break *0x814a164
commands 2
  silent
  set $regno = *(int*)($esp+4)
  set $life = *(int*)($esp+12)
  set $birth = *(int*)($esp+16)
  set $death = *(int*)($esp+20)
  if $life == 1
    printf "GRANT hard=%d birth=%d death=%d\n", $regno, $birth, $death
  end
  continue
end
run -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker t.i -o /dev/null
quit
