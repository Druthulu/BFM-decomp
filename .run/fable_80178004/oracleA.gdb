set confirm off
set pagination off
break local_alloc
commands 1
  silent
  set ((short*)reg_n_deaths)[72] = 2
  continue
end
run
quit
