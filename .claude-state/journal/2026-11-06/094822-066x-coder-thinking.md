---
ts: 2026-11-06T16:48:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RSFGHQIyRiuBFqVVQkx1
---
localalloc_sim takes a cc1 dump (.s from -dS?) and a uid. That's for the TU dumps. Building a candidate cc1 dump would need the candidate TU compiled with -dS. There's tools/cc1_dumps_tu.sh (TU dumps) — maybe it can dump a candidate TU. But this is a lot of work.

Time check: item 3 started ~09:44. Let me check the clock. Also item 1's 20-min mark passed (09:47). Let me append item 1's row soon.

Let me take a step back on item 3. The pin is the only lever. The function is 67 insns. Lever-free best so far: 34 (n08). A WALL needs 20 min + 30 tries. I've done ~10 tries. I should try harder — maybe there's a MATCH.

Key insight from m02: the shift merged into v0 but the v0/v1 allocation still swapped. The target's order has source v0 in $2 (first free). The allocator gave $2 to source v1 in m02. So source v1 has higher priority in the first block.

Source v1's first-block live range: from `lhu v1,48(a1)` (set) through `addu` to `sh v1,48(a1)` (death). That's ~3-4 insns. Source v0's: `lhu v0,0(at)` (set) → addu → shift → branch (~4-5 insns). refs: v0 has 3-4, v1 has 3.

Hmm. What if I reduce v1's refs in the first block: `CAST_WIDTH(u16,a1,0x30) += v0;`? That's n11 (68 ins, worse).

What if I make v0 the accumulator: `v0 = v0 + CAST_WIDTH(...)`? That changes v0's value (v0 must stay the loaded u16 for the test).

Hmm, what if the source loads the field into v1 and the u16 into v0 but computes `v1 += v0` (compound)? Same.

Let me look at the *target's* first block order again:
```
3354 lh v0,112(s0)      ; v0 = unk70
3358 lw a1,32(s0)       ; a1 = unk20
335c sll v0,v0,1
3360 lui at
3364 addu at,at,v0
3368 lhu v0,0(at)       ; v0 = loaded
336c lhu v1,48(a1)      ; v1 = field
3370 nop
3374 addu v1,v1,v0
3378 sll v0,v0,0x10     ; test
337c bgez v0,33bc
3380 sh v1,48(a1)       ; delay slot store
```
Mine (m02):
```
3354 lh v1,112(s0)      ; v0=unk70 -> $v1
3358 lw a1,32(s0)
335c sll v1,v1,1
3360 lui at
3364 addu at,at,v1
3368 lhu v1,0(at)
336c lhu v0,48(a1)      ; field -> $v0
3370 nop
3374 addu v0,v0,v1
3378 sll v1,v1,0x10
337c bgez v1
3380 sh v0,48(a1)
```
The instruction order is identical! Only the register *names* are swapped ($v0↔$v1) plus at the store. So if I could just swap the two source variables' allocation... 

The priority: in the target, v0 got $2 (allocated first), v1 got $3. In mine, v1 got $2, v0 got $3.

What distinguishes them? Let me compute refs and live lengths for the first block:
- v0: refs in block 1: set by lh (1), use in sll (2), set by lhu (3), use in addu (4), use in sll test (5) = 5 refs. birth = lh, death = the test.
- v1: set by lhu (1), use in addu (2), use in sh (3) = 3 refs. birth = lhu, death = sh.

Hmm, in m02 v0 also has the shift merged (sll v1,v1). 

pri(v0) = log2(5)*5*4/(death-birth). log2(5)=2. 2*5*4=40 / len.
pri(v1) = log2(3)*3*4 = 1*12=12 / len.

v0 should win! Unless the live lengths differ a lot. v0's live length: from the first lh (insn ~4) to the test (~20) = 16. v1's: from ~10 to ~14 = 4. So pri(v0)=40/16=2.5; pri(v1)=12/4=3. v1 wins! Yes.

So v1's short live range gives it higher priority. In the target, v0 wins — maybe because v0's live range is shorter or refs higher.

To make v0 win: reduce v0's live length or increase its refs. The live length of v0 spans from the first `lh v0,112(s0)` to the test, crossing the `lhu v0,0(at)` redefinition... wait, a qty in local-alloc is per block with possibly multiple live ranges? No, a qty's birth/death are the first/last refs in the block, even if redefined in between. So v0's live range spans the whole first block.

In the target's compiled code, v0's live range is the same. So why does v0 win there? Because the *pin* forces v0=$2 (hard reg), so it's not a qty competition. Right — the target has the pin. So the original source ALSO had a pin (the decomp's pin is genuine). Lever-free, local-alloc gives $2 to v1 (shorter life).

So to get v0 into $2 lever-free, we need v0 to out-prioritize v1. Options:
- Split v0 into two variables so the first part has a short life? E.g., `v0a = unk70; at = base + v0a*2;` then `v0 = *(u16*)at;` — v0's birth moves later, shortening its life to from the lhu to the test. Then v0's pri = 40/8 = 5 > v1's 3. That might give v0 $2!

Wait, but v0 is also used as the index (unk70*2). If we use a separate variable for the index, v0's live range starts at the lhu. Let me try:
```
s32 v0i;  // or reuse `at`? 
v0i = unk70; v0i *= 2; at = D_8019C7D4 + v0i; v0 = *(u16*)at;
```
But that adds a variable (register pressure). Alternatively, use `v0` for the index then... no, that's the long life.

Hmm, but the target's source (per the shipped decomp) uses v0 for both, and the pin forces $2. Lever-free we need a different source shape that yields the same bytes. If we split v0 into v0i and v0, the register count changes: v0i needs a register too. The target uses v0 for both (same register). Splitting would use two registers → different bytes.

Unless v0i is allocated to a register that's free... the first block has $2,$3,$4,$5 free (plus $6). Target uses $2(v0),$3(v1),$4(a0r),$5(a1),$1(at). If we add v0i, it needs a 5th register → $6, changing the frame (an extra saved reg). Bad.

Alternative: shorten v0's live range by reordering the source so the `lh v0,112(s0)` happens later? The scheduler decides.

Alternative: increase v0's refs. C0505: "Call-result temps of one type across cases → one function-scope variable (many refs, short live length outrank the self pointer)". v0 already has many refs across the function (global). Hmm, but local-alloc is per-block.

Wait — maybe v0 and v1 are both *global* allocnos (used in multiple blocks). local-alloc only allocates qtys that are local to one block. If v0 and v1 are used in several blocks, they're global, and local-alloc doesn't allocate them; global-alloc does. The $2 rotation would then be global-alloc's priority. Hmm.

v1 is used in the first block only? Let me check: v1 appears in the if-branch (`v1 = (s16)v1;`), the else branch, and the JOIN. So v1 is used in multiple blocks → global. v0 used in many blocks → global. So global-alloc decides.

global-alloc priority (`allocno_compare` in global.c): floor_log2(refs)*refs*size/live_length, with the *function-wide* live length. v1 is born in the first block and dies... in the JOIN? It's used in both branches. v0 is live almost the whole function. So v1 has a shorter global live range → higher priority → gets $2.

In the target, the pin forces v0=$2 and global-alloc then gives v1=$3.

So lever-free, to get v0=$2 we need v0 to outrank v1 globally. v0's live range is long (whole function) but refs are many. Hmm.

What if we reduce v1's refs or increase its live length? That would change the code.

Alternatively: could we make the *other* variables (a1, a0r) take registers such that the rotation works out? The target wants v0=$2, v1=$3, a0r=$4, a1=$5. Global-alloc priority order in mine: shift temp? (local), v1, v0, a0r, a1? Actually mine gave v1=$2? No wait: in m02, source v1→$v0, source v0→$v1, a0r→$a0, a1→$a1. So the order was v1, v0, a0r, a1. Target: v0, v1, a0r, a1.

So we need to flip v1 and v0 in the priority order. v1's priority > v0's currently.

How to lower v1's priority? Increase its live length or reduce refs. v1 is a temp holding the u16 field. If we make v1 live longer (e.g., declare it earlier or use it later)... 

Hmm, actually: what if we merge v1 into v0? Not semantically possible.

What if we split v0 into two variables so that the *global* v0 has fewer refs and a shorter life? E.g., use a separate variable for the index computation (but that adds a register).

Wait — maybe the real source didn't use v0 for the index; maybe it used `at` or another temp. Let me look at the target: `lh v0,112(s0); sll v0,v0,1; addu at,at,v0; lhu v0,0(at)`. v0 is reused. That's natural C: `v0 = unk70; v0 = v0*2; at = base+v0; v0 = *(u16*)at;`.

Hmm OK. Let me try changing the *declaration scope* of v1: if v1 is declared in an inner block (block-scoped), it becomes a local allocno and local-alloc handles it, possibly differently. C0087: "The allocno CLASS (local vs global) is the dominant regalloc lever, and C reaches it ONLY through declaration scope and variable reuse".

So: declare v1 inside the first block / inside each if branch? But v1 is used across branches. Hmm.

Alternatively, declare v0 in a narrower scope? v0 is used everywhere.

What about splitting v0 into two: `v0` used in the first block and `v0b` used later? The target uses the same register $2 throughout, so splitting might still allocate both to $2 if their live ranges don't overlap. Actually that's a classic move: "two locals the tree pins to one register are one variable (R28)" — inverse: one variable used in disjoint regions can be split into two, each with a shorter life, which changes priorities!

So: split v0 into `v0` (first region) and `v0b` (later regions). If the regions' live ranges are disjoint, both could get $2. And v0's priority in the first block might then beat v1.

Let me try splitting v0 at various points:
- v0 is used in: block1 (index+load+test), then branch bodies, then JOIN, then K.
- Split into v0 (first block only) and v0b (the rest).

But the first block's v0 live range: `lh v0,112(s0)` ... `sll v0,v0,0x10`. If we use a separate variable for the index part (v0i), that's the split. But that adds a register... unless v0i dies before v0 is born, so they can share $2! If v0i's live range is [lh, addu] and v0's is [lhu, test], they're disjoint (v0 is born after v0i dies at the addu). Then both can get $2!

And v0's priority (shorter life) might beat v1's.

So:
```
s32 v0i = unk70 * 2;   // or v0i = unk70; v0i *= 2;
at = D_8019C7D4 + v0i;
v0 = *(u16*)at;
```
The target bytes: `lh v0,112; sll v0,v0,1; addu at,at,v0; lhu v0,0(at)`. With v0i in $2 and v0 in $2, the bytes match! And the extra variable v0i doesn't need a new register if its live range is disjoint from all others.

Let me try this! Variants:
- o01: introduce `s32 v0i;` declared with the others; `v0i = unk70; v0i = v0i*2; at = D_8019C7D4 + v0i; v0 = *(u16*)at;`
- o02: same but only in the first block.
- o03: split in all the index computations (the function has several `v0 = unk70; v0 = v0*2; at = ...` patterns). Split the first one only.

Also the other regions use the same pattern; splitting them too may help.

Let me test o01 first.
