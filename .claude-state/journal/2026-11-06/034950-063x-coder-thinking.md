---
ts: 2026-11-06T10:49:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZHQWz7Llzd5t4VyosFJb
---
The TU includes "../shared/engine_prelude.h". If I copy the TU to src/ov_SC03_028/ ... no, I can't write to src/. The rule: write only under .run/P40/T11/G28x/. So the scratch TU must be under .run — then "../shared/..." resolves to .run/P40/.../shared which doesn't exist. But cc1_dumps_tu adds -Isrc/shared which doesn't help for "../shared/".

Hmm, but the include is `"../shared/engine_prelude.h"` — a quoted include resolves relative to the including file's directory first. If I put the scratch TU in .run/P40/T11/G28x/<item>/t.c, then "../shared/" = .run/P40/T11/G28x/shared. Missing.

I could create a symlink .run/P40/T11/G28x/shared → ../../../../src/shared? The dirs: .run/P40/T11/G28x/shared → ../../../../src/shared = .run/P40/T11/G28x/../../../../src = repo/src. Yes! That works. But wait, cc1_dumps_tu runs cpp with -Iinclude -I$(dirname $tc) -Isrc/shared. For a scratch TU at .run/P40/T11/G28x/<item>/t.c, dirname = .run/P40/T11/G28x/<item>, so "../shared" = .run/P40/T11/G28x/shared → symlink to src/shared. And "common.h" resolves via -Iinclude. Good.

But also the TU may include other relative headers? Only these two at the top. Let me check for other #include lines.

Actually, this dump approach could take a while. Let me weigh: I've spent maybe 35-40 minutes on item 1 already. The budget says 20-30 min wall per item; past 30 min stop and record a wall, but a WALL needs ≥20 min and ≥30 scored tries. I have ~20+ tries now. But I'm close (score 2 twice).

Let me spend a bit more with a targeted experiment: the reg swap in v_addr5 vs v_addr4. Let me try a few quick permutations around the block structure, aiming for t=v0.

Idea: in v_addr5, t is global and got v1. What if I make `a` also global by moving its definition into block1 (with the load) but keep the store in block2? That's v_addr4 (a local). Hmm.

Idea: declare `a` with a longer live range to lower its priority: e.g., declare a at the top of the function and assign in block2. Then a is global (declared early, but live range starts at the assignment). 

Idea: swap the roles: what if the load result `t` is used in the *same block* as the address (block2), so both are local in block2, and put the load itself in block1? Then t is global (defined in block1, used in block2).

Hmm, that's v_addr4 exactly (t global, a local) → t got v0, correct! And only the store sank.

So v_addr4 has correct registers. I need the store to not sink. In v_addr4's block2: a=addr; unk58=a; unkC4=t|2. sched1 sank the store.

What if I reorder block2: a=addr; unkC4=t|2; unk58=a; → then the store is last in source; sched1 might hoist it above the ori? Probably not.

What if the RMW is in block3 (its own do-while) while a+store stay in block2? That's v_addr5 (regs swapped).

Argh, the regs swap between these two.

Let me try: v_addr4 but with the store moved *before* the address? No.

What if in v_addr4 I use `|=` for the RMW (no t at the ori, t's last use is the load)? Then t's live range is short (load only?) — `unkC4 |= 2` doesn't use t. Then t is dead after the load → the load would be a dead store? No, t is used... hmm, if I write `unkC4 |= 2` the load is part of the RMW, not a separate t.

Hmm what about: `t = unkC4;` in block1, then `unk58 = a;` and `unkC4 = t|2;` in block2. Same as v_addr4.

Let me look at sched1's behavior: maybe if the store's address (a) is computed in block1 (with the load) but the store in block2, the store is ready immediately in block2 and gets scheduled first! Try:
```
do { t = unkC4; a = (s32)&D_801907C4; } while(0);   // block1: lw, lui, addiu
unk58 = a;     // block2 first
unkC4 = t | 2; // block2
```
This is v_addr (score 8): order lw, lui, addiu, sw, ori, sw — correct order! but regs swapped (t v1, a v0).

And v_addr3 (a first, t second in the do-while) gave correct regs but the load late.

Hmm! So in v_addr the regs are swapped because a got v0 (both local in block1, a's live range shorter).

What if I make a's live range LONGER than t's in block1 so t wins v0? a is used in block2; t is used in block2. Both. The birth/death: t born at the load, a born at the address; t dies at the ori, a at the store. If the store comes before the ori in the block, a's range is shorter. But that's in block2's schedule, not block1's. local-alloc computes birth/death per block: for block1, both are born; deaths are at the end of the block (last use in block1?) — in local-alloc, a pseudo that's live at the block end has death = block end. Both live at block end → same death. So priority differs by birth: a born later → shorter range → higher priority → v0. That explains a getting v0.

So in block1, whichever is born LAST gets v0. Target has t (born first) getting v0 → the target's t was NOT in the same block as a, or t's birth index is later.

If t and a are in different blocks: t global, a local. Global t gets a hard reg first; if global-alloc picks v0 for t, a gets v1. That's v_addr4 (correct regs). So v_addr4 is the right structure; only the store sinks in block2.

In v_addr4's block2, why does the store sink? Block2: lui, addiu, sw(a), ori, sw(t). Hmm wait, in v_addr4 the address `a = ...` is a separate statement in block2 (not in a do-while), and the store follows. The scheduler emitted lui, addiu, ori, sw, ..., sw. So it sank the store below the ori. The store depends on addiu; the ori depends on t (from block1). Both ready; it chose ori first.

Priority: the ori's result is used by the sw 196 (a store). The store sw(a) has no dependents. sched1's priority for the ori might be higher because it's part of a chain feeding a store? Both feed stores.

Hmm, what if the store's value a is computed *later* in the block so it's not ready? No.

What if I make the store's address a "live" value with more refs (higher priority)? E.g., use a twice? Not semantic.

Let me try the alternative: make the RMW use `|=` so there's no ori chain... then block2: lui, addiu, sw a, lw t, ori, sw. Hmm, the lw would be in block2 then.

New idea: what if we don't split at all, and instead make the load un-hoistable by giving it a *varying address*. E.g., compute the address of unkC4 via a pointer variable that gcc can't fold to base+const? Like `s32 *p = (s32 *)a0; t = p[49];` — the address is (plus (reg) 196), same.

What about `t = *(s32 *)((u8 *)a0 + 0xC4);` — same.

Hmm, what if the load is from a *different* alias set AND a varying address: e.g., `t = ((u32 *)a0)[49];` no.

OK, let me try the memrefs_conflict_p angle: make the load's address vary (a register without constant): 
```
s32 *p = (s32 *)((s32)a0 + 0xC4);
t = *p;
```
The address becomes a register (p), which is `rtx_addr_varies_p` true. And the store to 92 is MEM_IN_STRUCT (struct field) at a fixed address. Per true_dependence: conflict = memrefs_conflict_p(...) && !(MEM_IN_STRUCT_P(mem) && addr_varies(mem) && mode!=QI && !MEM_IN_STRUCT_P(x) && !addr_varies(x)). Here mem = the store (MEM_IN_STRUCT, addr fixed), x = the load (not in struct, addr varies) → the exclusion doesn't apply (it requires mem in struct AND mem addr varies). So it falls to memrefs_conflict_p: two addresses, one a register, one base+const → can't prove distinct → conflict → dependence! So the load can't be hoisted above the stores.

But would `p = (s32*)((s32)a0 + 0xC4); t = *p;` produce the same code? p is a pseudo = a0+196. cse might fold it back to base+const. But if cse folds, we're back.

Worth a try: it's a real-C move ("pointer reuse"/address in a variable). Let me test v_ptr:
```
s32 *p;
...
p = (s32 *)((s32)a0 + 0xC4);
t = *p;
... unk58 = &D_801907C4;
*p = t | 2;
```
No do-while. Let me score.

Actually, also: `*(s32 *)((s32)a0 + 0x20)` loads are already of this form (int cast). Fine.

Let me try.
