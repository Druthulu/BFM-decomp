---
ts: 2026-11-06T10:51:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YAK1zHPEbN7QWw6mjfmY
---
This is the .lreg (local-alloc) dump. "4 basic blocks". Block 2: first insn 32, last 140 — the big else block. So the barrier does NOT split the block for local-alloc (block 2 spans the whole else).

The register list for block 2 gives qty info. Now, the local-alloc dump prints ";; Register N in block" and the allocation results. But I need the qty birth/death and the register chosen. The .lreg output includes the insn list with reg numbers? Let me look at the section after the blocks.

Actually the key question: in the orig, t (pinned $2) is a hard reg, so local-alloc doesn't allocate it. The address pseudo gets v1 — because v0 is used by t? No, t is hard reg 2 (fixed), so v0 is occupied for the whole block? Actually local-alloc sees hard reg 2 as used by t's insns, so other pseudos avoid it.

So in the orig, the address can't use v0 because t (hard $2) is in the same block! That's the whole point: the pin reserves v0 for the block.

Lever-free, t is a pseudo and competes with the address; the address wins v0 (born later, shorter range).

So to get t in v0 lever-free, t must have priority over the address. The qty priority = floor_log2(refs)*refs*size/(death-birth). Both refs=2 → 2*4/(death-birth). So whoever has the SHORTER range wins. 

t's range: birth at the load, death at the ori. a's: birth at the address, death at the store. If the store comes BEFORE the ori (target order!), a's range is shorter → a wins v0. Contradiction with the target — unless the target's order has the store after the ori? No, the target has sw 88 before ori.

Wait, but in the target, t is a hard reg (pin), so this competition doesn't happen. Lever-free, we need a different mechanism.

So: make t's range shorter than a's. If the RMW (ori) comes right after the load in the C, t's range is short. But then the address/store would be scheduled after → wrong order.

Unless... we use a *different* C shape where t's live range is genuinely short and the target order still emerges. What if we compute `t | 0x2` early? No.

What if t is loaded and used immediately (t = t|2) and then stored later? The target code is lw, (address), sw 88, ori, sw 196 — the ori is after the store. So t's live range includes the store. In the C, `t = unkC4; unk58=...; unkC4 = t|2;` — t's range spans the store statement.

If instead we write:
```
t = unkC4 | 2;    // ori right after load? then store 196 later
unk58 = &D_801907C4;
unkC4 = t;
```
Then the load+ori are adjacent, t = value|2, and the store to unkC4 comes after unk58. The target's schedule has the ori AFTER the sw 88, so this would give ori before sw 88 → wrong.

Hmm.

What if t's range is short because we use it immediately but the *store* of t to unkC4 is separated... The target order: lw, lui, addiu, sw88, ori, sw196. The ori is right before its store. So t is loaded early (28) and used at 32 — a range of 4 insns. a is computed at 29-30 and used at 31 — a range of 2 insns. a is shorter.

So in any C shape with this schedule, a wins v0 by the qty rule... unless t has MORE refs. floor_log2(refs): refs=2 → 1; refs=3 → 1; refs=4 → 2. So if t had 4 refs, its priority doubles.

How to give t 4 refs without a keepalive? Hmm. t is used once in `t | 0x2`. Could we write the RMW using t twice? `t = t | 0x2` — that's still 2 refs (one read, one write). `unkC4 = t | 0x2` reads t once.

What if we use t in a comparison? No.

OK, so the local-alloc route won't give t v0 with this shape.

Alternative: make the address pseudo NOT use v0 for another reason: e.g., if the address is a *global* allocno with lower priority than t. If the address's definition is in a different block (global), then global-alloc assigns it after t (if t has higher priority). Global-alloc priority uses live length too.

In v_addr4: t global (live block1→block2), a local → t got v0. That worked! Only the store sank.

So v_addr4's structure is the right one for registers. The remaining problem is purely sched1 sinking the store in block2.

In v_addr4's block2: [a=addr, unk58=a, unkC4=t|2]. sched1: lui, addiu, ori, sw196, (later) sw88.

What if I make the store's value `a` also used by the ori chain? No.

What if I swap the order in block2: [unkC4=t|2, a=addr, unk58=a]? Then sched1 might schedule: ori, sw196, lui, addiu, sw88 → wrong.

What if the RMW is in block1 with the load (dw2)? Then block2 = [store] and block3 = ... no.

Hmm, what if block2 = [a=addr, unk58=a] and block3 = [unkC4=t|2] — v_addr5, which gave t v1 (because t's live range is longer, losing to the call-result pseudo).

What if in v_addr5 we make t's global priority higher by shortening its live range: put the RMW immediately after the load in block1? Then t is local to block1 and the store block is after... 

Let me enumerate the block structures and their reg outcomes:
- t in block1 alone (load), store+RMW in block2: v_addr4 → t v0 ✓, store sinks ✗
- t in block1 alone, address+store in block2, RMW in block3: v_addr5 → order ✓, t v1 ✗
- t+address in block1, store+RMW in block2: v_addr → order ✓, t v1 ✗
- t in block1, address in block2, store+RMW in block2 (v_addr4 variant): t v0 ✓ but store sinks.

Wait, v_addr4 = t in block1 (do-while), then a=addr, store, RMW all in block2. The store sank.

What if the RMW goes in block2 but the store in block1? Can't (store after address which is after the block).

What if the address is in block1 with the load (v_addr) AND the store+RMW in block2, and we fix the regs by making `a` global? If `a` is global, global-alloc assigns t and a by priority. t's range (block1→block2) vs a's (block1→block2). Hmm.

In v_addr, both t and a are local to block1 (both born and live-at-end). local-alloc picks by birth: a born later → shorter → v0.

If I make a's birth EARLIER than t's, t wins v0 but sched1 keeps the address first (v_addr3).

What if a is born in block0 (before the else)? E.g., compute the address at the top of the function! Then a is global. In block2, a's live range is long (from the function top), so its priority is low, and t (born in block1, live to block2) is shorter → t wins v0.

But the address computation would be scheduled in block0/1 — the target has lui/addiu at 29-30 (after the load). If a is computed at the function top, the lui/addiu would appear in the prologue. Wrong.

Hmm, but what if `a` is computed in block1 *before* the load in source but sched1 moves the load first? v_addr3 showed sched1 keeps the source order (lui/addiu then lw).

Unless the load is in a *different* block placed before... 

OK here's another thought: what if the address variable is initialized at its declaration in the *else block* (which is the block start)? The declaration is at the top of the else block; `s32 a = (s32)&D_801907C4;` would emit the lui/addiu at the block start, i.e., before the stores. Wrong.

Let me try yet another idea: make the load's result t used by TWO statements so it has more refs. For instance, write the RMW as `t = t | 0x2;` and store `unkC4 = t;` — t read once, written once → the qty has refs counting insns where it appears: load (1 def), ori (1 use + 1 def?), store (1 use) = 3 refs. floor_log2(3)=1 → 3*4/range. If a has 2 refs → 2*4/range. t's priority would be 1.5x higher! That might flip it.

Let me test: 
```
do { t = unkC4; } while(0);      // block1
a = (s32)&D_801907C4;            // block2
unk58 = a;
t = t | 0x2;                     // block2
unkC4 = t;                       // block2
```
t is global (block1→block2). Hmm, global-alloc, not local. But it might work.

Actually simpler: in v_addr4 (the structure with correct regs), the store sinks. Let me attack that with t having more refs:
```
do { t = unkC4; } while(0);
a = (s32)&D_801907C4;
unk58 = a;
t = t | 0x2;
unkC4 = t;
```
In block2, the schedule might now favor... hmm, the store sw88 doesn't involve t.

Wait, the sinking of sw88: sched1 chose ori/sw196 before sw88. If the ori chain is longer (ori + copy + store), maybe the scheduler prefers the shorter ready store first? Let's just test.

Also test the variant with `t = t | 2; unkC4 = t;` in v_addr (both in block1) to see if the regs flip.

Let me generate both.
