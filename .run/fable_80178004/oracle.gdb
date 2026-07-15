set confirm off
set pagination off
break local_alloc
commands 1
  silent
  set ((short*)reg_n_deaths)[72] = 2
  printf "ORACLE: reg_n_deaths[72]=2 at local_alloc\n"
  continue
end
break global_alloc
commands 2
  silent
  set ((int*)reg_n_refs)[72] = 4
  printf "ORACLE: reg_n_refs[72]=4 at global_alloc\n"
  continue
end
run
quit
