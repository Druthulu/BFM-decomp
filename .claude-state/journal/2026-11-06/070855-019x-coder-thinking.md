---
ts: 2026-11-06T14:08:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_T8LsfIQyTKAgHfltmNmI
---
The only difference is a swap between t2 ($10) and t3 ($11): i and dst. Currently (asm removed) i gets t2 ($10)? Let me see:

Target:
- `move $10,$0` -> i = 0 (t2)
- `addu $11,$9,$2` -> dst = src + n (t3)
- `sh $5,0($11)` -> *dst (t3)
- `addu $11,$11,2` -> dst++ (t3)
- `addu $10,$10,1` -> i++ (t2)
- `slt $2,$10,$12` -> i < n (t2)

Mine (asm removed):
- `move t3,zero` -> i = 0 (t3)
- `addu t2,t1,v0` -> dst = src + n (t2)
- `sh a1,0(t2)` -> *dst (t2)
- `addiu t2,t2,2` -> dst++ (t2)
- `addiu t3,t3,1` -> i++ (t3)
- `slt v0,t3,t4` -> i < n (t3)

So mine has i in t3, dst in t2; target has i in t2, dst in t3. Just a swap.

Interesting: t3->t2 x4 and t2->t3 x4 — exactly 4 uses each.

So I need i to get $10 (t2) and dst to get $11 (t3). The keepalive on i added refs, giving i higher priority to get a lower-numbered reg? In gcc 2.7.2, local-alloc allocates in order of reg number availability... Actually the register allocator assigns hard regs by "local-alloc" with qsort by REG_N_REFS? Let me recall: local-alloc sorts regs by... Actually local_alloc() in local-alloc.c allocates each pseudo in order of REGNO (or by priority via `qty`?). Hmm.

Actually in gcc 2.7.2, `local_alloc` iterates over all pseudos in REGNO order? No — it uses `reg_qty` and `qty_phys_reg`... Let me think. local-alloc.c: `local_alloc()`:
```
  /* Allocate each register, in order of decreasing "quantity" priority */
```
It sorts `qty` structs by `qty_n_refs` descending? Let me check the source. tools/reference/gcc-2.7.2/local-alloc.c exists. Let me grep.

Actually the comment says the keepalives affect sched1, not local-alloc. But the final result is register assignment. Hmm, "keeps src above i, below the mfhi temp" — that sounds like local-alloc priority (register order). Let me look at local-alloc.c to see how it orders quantities.

Let me grep local-alloc.c for n_refs / sort.
