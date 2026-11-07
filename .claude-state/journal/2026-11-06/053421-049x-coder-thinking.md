---
ts: 2026-11-06T12:34:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_V58JZ3jhN44Ka8QlDqmN
---
Now the picture is clear: mine emits `li a0,7; j 1e24` while target has `j 1e38; li v0,7`. So ret is in a0 in mine (not v0!). The register pairs said a0->v0. So ret got a0, not v0.

Why a0? Because global-alloc chose a0 for ret. And the store at the STORE label: `sh v0,2(s1)` requires the value in v0 → mine must move a0→v0 at the STORE.

Hmm wait, mine has `j 1e24` — a different STORE label (1e24 vs 1e38) because mine's STORE block starts earlier (with a move v0,a0?).

So: ret in a0 in c2, and the target wants v0.

The register allocator picks a call-clobbered reg; among them, the priority order: global.c assigns by priority; when several regs are free, it picks the lowest-numbered available (or by `reg_alloc_order`). The candidate pool order in gcc 2.7.2 for MIPS: a0-a3, v0, v1, t0-t9... Actually `reg_alloc_order` in mips.h? In global.c the order comes from `reg_alloc_order` or REG_ALLOC_ORDER. Hmm, in gcc 2.7.2 global.c sorts by `allocno_compare` (priority/density), then assigns the first free register in `reg_alloc_order`? Let's check: in global.c `find_reg`, it iterates `i = 0; i < FIRST_PSEUDO_REGISTER; i++` with `reg = reg_alloc_order[i]`? Let me check.

Since a0 was chosen for a short-lived pseudo, and the target wants v0, we need ret's priority/density or the pool order to differ.

How did the pin give v0? The pin forces $2.

Lever-free ideas to get v0 for ret:
1. Make ret's live range such that a0 is taken at the def/use points by another value. E.g., at the STORE point, a0 is used? In target at 1e38: `sh v0,2(s1)` — s1 = param_1.
2. Use a different variable that's naturally in v0: e.g. make the arms assign to a variable that's the return expression directly... 

Hmm, what about making the arms' ret assignment go through a `s16` cast or something that forces the value into v0? The store `unk2 = ret` is a s16 store; gcc needs the value in a register.

What if we write the STORE as: `((...)->unk2 = ret;` and return `ret` — the return wants v0. There are two uses of ret at the STORE: the store and the return. If ret were allocated v0, both are free. If allocated a0, then v0 = a0 needed for the return.

In global.c, when a pseudo is used by a `return` (i.e., there's a `use v0` and a `set v0 = pseudo`), does the allocator prefer v0? Not automatically.

But hold on — gcc's global-alloc has `reg_preferred_class`/`reg_alternate_class` from REG_ALLOC_ORDER? There's also `PREFERRED_RELOAD_CLASS`. Hmm.

Practical approach: try a few C shapes and see which gives ret v0:
(a) `return ret;` at STORE only (as now) with early `return 0`.
(b) declare ret as `s16 ret;` — the store is s16; but the return needs the value... may add extension.
(c) make the return expression `((Unkstruct *)param_1)->unk2` (reload) — extra insn.
(d) reorder the STORE: `return ret;` after the store.

Actually — what about the classic move: make the value *born* in v0 by computing it as an expression involving a function call? No.

Alternative: give ret's allocno a higher priority so it's allocated FIRST, before other pseudos take v0/a0. Priority = floor_log2(refs) * refs * 10000 / live_length. ret has ~7 refs and a short live length. Hmm.

But which register does global-alloc pick first for the highest-priority allocno? It picks from `reg_alloc_order`. In mips, `REG_ALLOC_ORDER`? Let me check gcc 2.7.2's global.c `find_reg`: it iterates over `regs` sorted by `allocno_order`... For each allocno (in priority order), it tries registers in a specific order: `for (i = 0; i < FIRST_PSEUDO_REGISTER; i++) { reg = reg_alloc_order[i]; ...}` — actually I recall `find_reg` uses `reg_alloc_order`. Let me grep.

If the order is a0 first, then a pseudo with high priority takes a0. To get v0, v0 must come before a0 in reg_alloc_order (MIPS: in gcc 2.7.2 mips.h REG_ALLOC_ORDER is probably defined as {..., 4,5,6,7,8,...} where 4=v0? MIPS regs: 0=zero,1=at,2=v0,3=v1,4-7=a0-a3, 8-15=t0-t7, 16-23=s0-s7, 24-25=t8-t9, 28=gp,29=sp,30=s8,31=ra.

If REG_ALLOC_ORDER starts with 2 (v0)... but then why did ret get a0?

Let me look at global.c find_reg to understand.
