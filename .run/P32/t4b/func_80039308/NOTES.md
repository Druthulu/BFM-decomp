# func_80039308 (main/800_c, 518 ins) — S83 hand probes (residual 17: rows 49/50 sched swap, 390/391 structure, 412/415 $t0 vs $s7,
484–497 = the `*mp` second load must move ABOVE the D_800C7D20 store)
A `D_80073140[j][0]` direct (the TU's [][1] type — the sibling func_800391D4's lever) → 517 ins / 83; B row-pointer form → 517 / 81:
the 2-D spelling changes the address computation (an instruction is lost) — the report's "the /s unlock costs the address
allocation" reproduced with the array type too. The TU now spells `extern s32 D_80073140[][1]` (T4b plumbing) — the draft's
`extern s32 D_80073140[]` + `mm = D_80073140` must become `(s32 *)D_80073140` to compile in the real TU (rtu). Fable: the
alias fact is one MEM_IN_STRUCT_P/varying-address decision (§30/§364); find the spelling that grants /s to the SECOND `*mp`
load only (a struct-typed view of the row: `((struct { s32 v; } *)mp)->v`) without touching the first load's address form.
