---
ts: 2026-11-06T21:21:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_osiKxkkMw5zruc5kqN8Y
---
- p_only (pin removed, launders kept): score 23, 206 ins (same count!), REG-callee. So removing the pin only causes a callee-saved reg difference.
- l_only (launders removed, pin kept): score 83, 215 ins. So the launders are load-bearing for instruction count (rematerialization).

So:
1. The launders must be replaced by real-C 2nd sets to keep 206 insns.
2. The pin must be replaced by real-C that gives the right callee-saved assignment.

Both are hard. Let me tackle the launders first (bigger effect).

The three launders: two on `ap` and one on `tp`.
- ap launder: `ap = buf; __asm__("" : "=r"(ap) : "0"(ap));` — forces ap to be a real 2nd set so ap (buf address) is materialized in a reg rather than using buf directly. Target: `addiu a0,sp,16` (buf address in a0) — wait, with launder, ap = buf materialized. Without launder, `func_8017D418((s16*)ap, ...)` might use buf directly (sp-relative). Let me check: the target first call passes `addiu a0,sp,16`? Actually target line 50 `addiu a0,sp,16` — that's the buf address. Hmm, both would use sp+16.

Wait, the launder on ap might be to force ap into a specific register (a0) vs recomputing. Let me see the l_only diff more.

- tp launder: keeps tp = D_801274F0 in a register (s0) instead of rematerializing.

Let me look at the l_only diff to see what changes.

Actually, let me think about the "real 2nd set" for tp. tp = D_801274F0_8017CF48 (a symbol). Then `*(Blk8*)tp = *(Blk8*)buf;`. Then uses of tp.

Real 2nd set: what if we write `tp = (s32)D_801274F0_8017CF48;` and then, after the first store, reassign `tp = (s32)D_801274F0_8017CF48;`? The second assignment is identical and would be cse'd/merged. But if there's a call in between? There's no call between the store and the uses.

Hmm. What about making tp a pointer and incrementing it? `tp += 0`? folded.

What about the C0414 dead-reset: `tp = 0;` after all uses? dead.

Actually, maybe the launder on tp is replaceable by using tp in a way that forces it into a register naturally. For example, if tp is used as the destination of the store AND then arithmetic (tp-8, tp-6, tp-4), the compiler could still rematerialize. But if we compute `tp` from a non-constant expression that the compiler can't rematerialize... e.g., load it from a global pointer: `tp = *(s32*)&D_801274F0_8017CF48;`? That changes semantics (loads the pointer value).

Hmm.

Let me look at the actual target vs mine for tp. Target:
```
lh a0,-8(s0)
...
sh v0,-8(s0)
lh a0,-6(s0)
...
sh v0,-6(s0)
lh a0,-4(s0)
...
sh v0,-4(s0)
```
So s0 = tp (D_801274F0). Mine (l_only):
```
lui a0,0x0; lh a0,-8(a0)    // rematerialize D_801274F0 each time
...
lui at,0x0; sh v0,-8(at)
```
So mine rematerializes the address (lui+lo) each use → extra insns.

The launder forces tp into a register. Real C way: make tp a value that can't be rematerialized. Since D_801274F0 is a constant address (REG_EQUIV), the compiler rematerializes. To prevent, make tp not equivalent to a constant: e.g., pass it through a computation.

Idea: `tp = (s32)D_801274F0_8017CF48;` then `tp = tp | 0;`? folded.
Idea: `tp = (s32)((u8 *)D_801274F0_8017CF48);` same.
Idea: `tp = (s32)D_801274F0_8017CF48 + (t & 0);` folded.
Idea: use a variable that holds the address loaded once: `u8 *g = D_801274F0...; tp = (s32)g;` — g is still constant.

What if the address is loaded from a table/pointer? E.g., `tp = *(s32 *)(&D_801274F0_ptr);` — changes the code (extra load).

Hmm.

Actually — maybe there's a simpler crack: use `tp` in the store to a *different* type that forces materialization? No.

Let me look at how other items cracked a "keep symbol in reg" launder. Search moves.md for "rematerial" or "symbol" or "const-ptr". The walls mention "cse-const-addr" and "greg-const-ptr-priority". Let me grep moves for "remateriali".

Actually line 24: "barrier,launder | func_8017ED5C | WALL greg-const-ptr-priority — e (const symbol ptr, 2 refs) loses greg priority to off". So a const symbol ptr kept in a reg is a known wall.

But the moves also show MATCHes with "real 2nd set". For a const symbol, a real 2nd set: e.g., `vol = D_801274F0; ... vol = vol;` no.

Wait — maybe the trick is different. The launder `__asm__("" : "=r"(tp) : "0"(tp))` creates a 2nd set of tp. The real-C equivalent could be: assign tp, then use it in a way that creates a genuine second set from an arithmetic op. But tp is a symbol address; arithmetic on it is legitimate: `tp = (s32)D_801274F0_8017CF48;` and the code does `*(s16*)(tp-8)` etc. What if we rewrite using a base pointer and offsets such that the base is computed once and incremented?

Actually, the code already computes `tp - 8`, `tp - 6`, `tp - 4` — these are (plus tp -8). If tp is in a reg, these are displacements. If tp is rematerialized, each is a lui/lh with the symbol.

What if we write `tp = (s32)D_801274F0_8017CF48 - 8;` (a computed value) and use `*(s16*)tp`, `*(s16*)(tp+2)`, etc.? Then tp = sym - 8, which is still a constant → rematerializable. Hmm.

What if we do pointer arithmetic through a non-constant: `tp = (s32)D_801274F0_8017CF48; tp = tp + (flag & 0);`? folded (flag&0 = 0).

Hmm. Real 2nd set that survives and is value-preserving seems to need an opaque operation. Without asm, hard.

Wait — but the item is in a "crack shard", so maybe some items are WALLs. This one has 2 kinds and a big residual. Let me try a couple of quick real-C ideas and then record a WALL if needed.

Idea 1: For tp, use a local pointer `u8 *tp` and write the store as `*(Blk8*)tp = *(Blk8*)buf;` then `tp += -8;`? no.

Idea 2: The two `ap` launders: `ap = buf; __asm__(ap);`. The purpose: force ap into a register (a0) for the call. Without it, the compiler might pass `buf` as sp+16 directly (which is what target does at line 50: addiu a0,sp,16). Hmm, wait, target HAS addiu a0,sp,16, so ap IS materialized as sp+16 in a0. The launder might be forcing it to not be folded into the call argument. Let me look at what l_only does differently for ap.

Given the complexity and that this is a multi-lever item, let me spend ~10 more minutes trying, then WALL.

Let me first try the most promising real-C move for tp: replace the launder with a genuine second set via a self-reassignment through an arithmetic that combine won't fold. For a symbol address, `tp = (s32)D_801274F0_8017CF48;` then `tp = tp & ~0;`? `& ~0` = `& 0xFFFFFFFF` folded. 

What about `tp = (s32)D_801274F0_8017CF48; ... tp = tp;` removed.

Hmm. What if tp is used BEFORE the 2nd set and after? E.g.:
```
tp = (s32)D_801274F0_8017CF48;
*(Blk8*)tp = *(Blk8*)buf;   // use 1
tp = (s32)D_801274F0_8017CF48;  // 2nd set (dead? no, used below)
t0 = func(*(s16*)(tp-8), ...);  // use 2
```
The 2nd set is live (used below). The first set is live (used in store). So tp has 2 sets, both live! That gives reg_n_sets=2, preventing REG_EQUIV rematerialization? Maybe. And the code should be identical: both sets are the same constant, so the compiler would materialize once and reuse (or the 2nd set is redundant and cse removes it). cse might merge the two identical sets → 1 set.

But if there's a call between? No call between the store and the uses. Hmm.

Actually there IS a difference: between the store `*(Blk8*)tp = ...` and the later uses, there's no call. So cse would see tp = sym twice with no clobber → merge.

What if we put the 2nd set AFTER `func_80012DBC` calls (in the L174/LAB region)? The tp code is after LEND, after the calls. Let me look: LEND is after the L174/LAB branch merge, which contains func_80012DBC/func_80012ABC calls. Then tp = D_801274F0; store; func_80012F74 calls. 

So between the tp assignment and the uses there are func_80012F74 calls (which clobber). If we place a 2nd set of tp after one of those calls... but then it's just a second identical set.

Hmm, actually the simplest: does the target maybe have tp materialized once because of the *store* `*(Blk8*)tp = ...` which uses tp as a base, plus later `tp-8` uses? The launder forces a reg. 

Let me try the "two live sets" idea empirically:
```
tp = (s32)D_801274F0_8017CF48;
*(Blk8_8017CF48 *)tp = *(Blk8_8017CF48 *)buf;
t0 = func_80012F74(*(s16 *)(tp - 8), buf[0], 4, 1);
u1 = buf[1];
*(s16 *)(tp - 8) = t0;
tp = (s32)D_801274F0_8017CF48;   // 2nd set
t1 = func_80012F74(*(s16 *)(tp - 6), u1, 4, 1);
...
```
Hmm, this might work if the first func_80012F74 call clobbers memory, preventing cse of the constant? No, a call doesn't invalidate a constant.

Actually cse invalidates REG_EQUIV for pseudo regs when... the constant is still a constant. cse would keep tp.

Let me just test: does a redundant `tp = (s32)D_801274F0_8017CF48;` in the middle help? Probably cse removes it.

Let me instead look at what the launder actually changes in RTL. Let me dump the orig (with levers) and l_only and compare the tp region. But time.

Let me take a practical approach: try 4-5 variants and score.

Variant A: tp 2nd set before the second func_80012F74.
Variant B: tp 2nd set right before the last use.
Variant C: make tp a pointer variable `u8 *tp` assigned from D_801274F0.
Variant D: use `tp = (s32)&D_801274F0_8017CF48;` (address-of).
Variant E: keep the two ap launders? no, must remove.

Actually, the biggest issue: l_only (launders removed) = 215 vs 206. The extra 9 insns. If I can't recover the count, WALL.

Let me first see the l_only diff head to understand which launders cost what. Let me capture l_only diff.
