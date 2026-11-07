---
ts: 2026-11-06T10:34:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rkw2LNahB2oOcDpk78bz
---
Good, the dir names match. Now let me append the moves.md lines (one per item):
`kind | func | MATCH: move / WALL tag — mechanism (G27x)`

Since all are WALLs:
```
keepalive,pin | func_8017E8D8 | WALL lreg-copy-pref-dying-base — void def: target move v0,s0 is the return of a0; extern void decls kill the value lever-free (51/52) (G27x)
keepalive,pin | func_8012BA10 | WALL lreg-qty-priority — block-local s1ang takes $s0 in local-alloc before the global divisor d; globalising s1ang lifts its pri past d (G27x)
keepalive,pin | func_8012BB3C | WALL sched1-birth-order — do-while(0) ref boost cracks the $16 pin (div=$s0, 5); keepalive ang anchor left: andi hoist + (s16)div temp $v1 vs in-place $s0 (G27x)
keepalive,pin | func_801535F4 | WALL global-hardreg-reserve — pin fcopy=$3 reserves $v1; lever-free flags takes $v0 and ret $v1; the keepalive's live-extend (5->15) is what gives flags $a0 (G27x)
```

Let me append to moves.md. I'll use bash printf append (allowed, under my shard's allowed writes? moves.md is .run/P40/T11/moves.md — the brief says "appends to .run/P40/T11/moves.md"). Let me use a python append or printf. The instruction "one action per command" — this is one action.

Let me use a heredoc append with cat >> (a shell write). Hmm, the guidance says use the Write tool for scratch. moves.md is a shared append target. Let me use printf.

Actually, let me use the Write tool? No — it would overwrite the whole moves.md (which is huge). I must append. Let me use bash `cat >> ... <<'EOF'`. That's fine.

Wait — the earlier grep of moves.md worked. Let me append.
