set confirm off
set pagination off
break find_reg
commands 1
  silent
  set $num = *(int*)($esp+4)
  printf "find_reg allocno=%d reg=%d refs=%d len=%d calls=%d size=%d\n", $num, ((int*)allocno_reg)[$num], ((int*)allocno_n_refs)[$num], ((int*)allocno_live_length)[$num], ((int*)allocno_calls_crossed)[$num], ((int*)allocno_size)[$num]
  continue
end
run
quit
