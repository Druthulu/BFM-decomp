set confirm off
set pagination off
break local_alloc
commands 1
  silent
  set ((short*)reg_n_deaths)[72] = 2
  continue
end
break global_alloc
commands 2
  silent
  set ((int*)reg_n_refs)[72] = 4
  set ((int*)reg_n_refs)[74] = 15
  printf "ORACLE2 applied\n"
  continue
end
run
quit
