set confirm off
set pagination off
break find_reg
commands 1
  silent
  printf "allocno_order:"
  set $i=0
  while $i < 15
    printf " %d", ((int*)allocno_order)[$i]
    set $i = $i + 1
  end
  printf "\n"
  set $a = ((int*)allocno_order)[0]
  printf "first alloc reg=%d\n", ((int*)allocno_reg)[$a]
  delete 1
  continue
end
run
quit
