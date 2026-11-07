---
ts: 2026-11-06T16:28:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DQG15bHvAmKA5a0b0TyC
---
Score 8. The main mismatch: target has `move v1,v0` (ret in v1, m in v0) while mine has ret in v0 and m computed into v0 directly (no copy). So I need to force ret into v1 and m into v0 with plain C.

Ideas:
1. Make `ret` live across something so v0 is needed for m. If ret is used after the m computation... it isn't in the source. But we can restructure: compute `m = ret & 0x8000` first, then test `ret`. E.g.:

```c
m = ret & 0x8000;
if (ret == 0) {
} else if (m != 0) { ... }
```
But that computes andi before beqz. Target: beqz v1 first, andi in delay slot. Hmm target order: move v1,v0; beqz v1; andi v0,v1,0x8000 (delay slot). So andi is after the branch (in delay slot). That's the source order: test ret==0, then m = ret & 0x8000. So source order stays.

2. Why would gcc copy v0→v1? Because the call-result pseudo and ret pseudo are different. If we write `s32 ret = func(...)` and ret is used, the call result is directly assigned to ret's pseudo (single set). Unless we add a temp: `s32 r = func(...); ret = r;` — that could be coalesced by copy propagation or local-alloc tie. Hmm, but if r is also used elsewhere, no.

3. Alternative: m needs v0. The andi's result is a pseudo. Local-alloc gives m... In the pinned version, ret pinned $3 (v1) and m pinned $2 (v0), so the move v1,v0 arises because ret's pseudo is pinned v1 and the call returns v0, needing a copy. So in plain C we need local-alloc to give ret a hard reg ≠ v0 while the call result is v0.

In gcc 2.7.2 local-alloc: the call result comes into v0 (a hard reg) and then there's a move to the pseudo. Actually no — expand emits the call with `(set (reg:SI 2) (call ...))` then `(set (pseudo) (reg 2))`? Hmm. In gcc 2.7.2 MIPS, `function_value` returns a pseudo? Let's check: in calls.c/expr.c, `expand_call` sets the target as a pseudo (`struct_value`). The call insn is `(set (reg 2) (call ...))` via `emit_call_insn`? Actually the standard is the call insn itself has the return in a hard reg, and then `emit_move_insn (target, hard_return_reg)`. In mips.md, the `call_value` pattern sets the return register from the call. Then expr.c copies.

So there's always a move from v0 to the pseudo. Local-alloc's copy preference will try to tie the pseudo to v0 (preference from the move). If it succeeds, the move is deleted and pseudo = v0. If it fails (v0 conflicts, e.g. v0 is used by something else in the block that conflicts), the pseudo gets another reg.

To make it fail, we need v0 to be busy at the point of the pseudo's live range. The `m = ret & 0x8000` result in v0: if the m pseudo's live range starts at the andi and the ret pseudo's live range extends... no, they're in the same block; local-alloc allocates per-block; two pseudos with overlapping live ranges conflict. ret is live from the move (34c) through the andi; m is live from andi to bnez. They overlap at the andi. So ret and m cannot both be v0.

The copy preference ties ret (or rather the call result move target) to v0. Then m gets v1 (or another). Mine got exactly that: ret=v0, m=v0?? No, mine shows `beqz v0`, `andi v0,v0,0x8000`. So mine: ret=v0, m also v0 (non-overlapping? the andi writes v0 after reading v0 — allowed, same reg because m's live range starts after ret's last use... at the andi, ret is read and m is written; gcc's local-alloc allows the output to share the reg with a dying input? Actually no: local-alloc computes live ranges where a def kills; m's live range begins at the andi and ret's ends at the andi (last use). With `death` notes, they can share.)

Target: ret=v1, m=v0. So local-alloc chose to give the andi's result m the hard reg v0 and ret v1. Why? Because m's pseudo has copy preference? No... Perhaps because of the `switch` later? No, different blocks.

Hmm, maybe in the target the source differs: maybe the source had the call result assigned to a variable that's live longer, e.g. `ret` used in a later block too. But target doesn't show that.

Wait, maybe the mechanism is different: the move v1,v0 could come from `m = ret & 0x8000` where... no, move v1,v0 is before beqz, so it's the ret copy.

What if the source is:

```c
s32 ret = func(...);
if (ret != 0) {
    m = ret & 0x8000;
    ...
}
```
Same.

What if ret is declared as `register`? No register vars allowed.

What about a u16 ret? Hmm: if ret were `u16`, then... the copy would still be in v0.

What if we make the call result go to a temp and ret a separate copy that's used more? E.g.:

```c
s32 t = func_801638A0(...);
ret = t;
```
Then t = call result, ret = copy. cse/combine would probably fold ret = t. With `ret` used and `t` used in the andi? If we use t in the andi and ret in the test:

```c
s32 t = func(...);
ret = t;
if (ret == 0) {}
else if ((m = t & 0x8000) != 0) ...
```
Then ret = t gets folded (copy prop) and ret is gone... combine would merge.

Alternative approach: get the andi result into v0 by making it a longer-lived variable, and ret into v1. What determines which pseudo gets v0? local-alloc gives hard regs by priority: pseudos with more refs / longer life get first pick. `ret` is used twice (test, andi). `m` is used once (test). The call result copy has the return-reg preference. Hmm.

Actually maybe the trick: the andi's result and ret could both be in v0 if gcc is fine sharing (as mine did). To prevent sharing, make m live across something: e.g. use m again later (after the if/else chain) — but that changes the code. Or make the andi's output not able to share with ret's death: if m is used twice (test + something), then it can't share with ret? Actually sharing requires m's live range to not conflict with ret's. If m is live past the point where ret dies... ret dies at the andi (last use). m starts at the andi. A def after a use of the same reg is fine. So even 2 uses of m wouldn't conflict with ret.

Hmm. What if ret is live after the andi? In target, ret isn't used after. Unless... the `if (ret == 0) {}` structure means ret is live across the branch? No.

Wait. Maybe the target's `move v1,v0` is not a copy of the call result but the result of `m`? No, m = andi v0,v1.

Let me reconsider: maybe the source is `ret = func(...); if (ret == 0) { ... }` where ret is `s32` but the comparison is `if (ret != 0)`. Hmm.

Alternative: maybe the target came from a different C shape where `ret` is assigned from the call and the call's return type/cast creates a copy. E.g., `ret = (s32) func_801638A0(...)` — a cast that's a no-op.

Let's look at how gcc 2.7.2 handles `x = f(...)` with x in v0 vs v1. In local-alloc, the block-alloc assigns regs. The move from v0 to pseudo has qty `ret` with a copy pref to v0. If ret also gets a `reg_dead` at ... hmm.

Let me try a different route: use `s32 ret;` but add a second use of the call result in a way that prevents tying, or declare m before ret in decl order? Decl order affects local-alloc order (qty order). In local-alloc, pseudos are processed in order of qty number; earlier-declared = lower qty. The first allocated gets its preference. Hmm, but the copy preference is a tie-breaker on the move.

Actually, maybe swap: declare `m` first, then `ret`. Then m has lower qty... but the allocation order in local-alloc's `block_alloc` sorts by `qty_cmp` (refs, live length, then qty number?). Let me look at gcc 2.7.2 local-alloc.c to understand.

Actually simpler: just try variations empirically. I have budget 20-30 min per item. Let me write a script to generate candidates and score them with sc.sh.

Candidates:
A: current (ret,m) → 8.
B: decl order m then ret.
C: no m variable: `} else if (ret & 0x8000) {` (target then would andi v0,v0 - no copy).
D: two-step: `s32 t = func(...); ret = t;` etc.
E: make ret a `u32`?
F: `ret = func_801638A0(...); if (ret) { if (ret & 0x8000) ... }`.
G: use m for the test but keep ret... 

Hmm wait. Let me reconsider the problem. In the target, `move v1,v0` then `beqz v1` and `andi v0,v1`. Consider source:

```c
if ((ret = func_801638A0(...)) != 0) {
    if ((m = ret & 0x8000) != 0) {...}
    else {...}
}
```

Same insns.

What about the target having `move v1,v0` because v0 is needed for the *second* call `func_80146E90`? No, that's in another block.

Let me look at what the pinned body compiles to vs target. The pinned body scores 0 presumably (it's the current src, which is banked). Let me check the build's dump for func_800CB118 to see the pinned version's insns — it should be identical to target (score 0). The pins force ret=v1, m=v0.

So the question is purely: can local-alloc assign ret to v1 and m to v0 without pins? Note that in the pinned version, ret is `register __asm__("$3")` — a hard reg v1, and m hard v0. The copy from v0 to v1 appears. Without pins, the natural assignment is ret=v0, m=v0.

To get ret=v1, we need the ret pseudo to be unable to take v0. v0 is taken by... In the block, which other pseudos are live? a0 (s0, callee-saved), sp20 address, sp28, and m. If m's live range overlaps ret's at the point where ret must be assigned, then ret can't be v0 (since m is v0). But m = v0 would then be forced by the copy preference? m has no copy preference. So why would m get v0?

Unless the andi's result m gets v0 because local-alloc processes m before ret and v0 is free? The andi is after the move, so m's live range starts later. The allocator processes pseudos in qty order: ret (declared first) then m. ret would grab v0 by preference. Unless m is declared first and its qty is lower, so m gets allocated first and takes v0 (as its "first free" — but local-alloc prefers call-crossing regs? no).

Hmm: local-alloc block_alloc: for each qty in order of `qty_cmp` (higher refs first, then longer live, then lower qty number). ret: refs 2 (test + andi), m: refs 2 (def + test)? Then live lengths: ret from move to andi, m from andi to bnez — similar. Then qty number: ret (declared first) lower. So ret allocated first → v0 by copy pref.

But in the target, ret=v1. So maybe ret has *fewer* refs? Or m has more.

Wait, actually maybe in the original source the variable order was different, or the code is `m = ret & 0x8000` where m is used in the test and ALSO the stores use m? No.

Let me step back and look at other pins cracked in the moves file for guidance. E.g. "pin | func_800CD57C | MATCH — store subtract direct to unkA (no v0 var hop): fld load wins v0 in local-alloc (W03)". And "pin | func_80180C04 | MATCH — $0 zr pin dropped, flag declared s16: HImode flag=1 test not folded by cse (W07)".

Hmm, what about using `s16`/`u16` for m? If m is `s16`, then `m = ret & 0x8000` — the andi produces HImode... then the test `m != 0` is `sll/sra`? Hmm no.

What if `ret` is declared `u16`? Then `ret = func(...)` truncates to HImode: move v1? Hmm.

Let me think about the `move v1,v0`: it's a full 32-bit move. The call result goes to v0, then moved to v1. If ret were `u16`, the move would be from v0 to... the HImode pseudo would be assigned to v1 with a `move v1,v0`? Actually a HImode copy still uses a full reg. And `ret == 0` test on HImode: beqz. And `ret & 0x8000`: andi v0,v1,0x8000 then maybe sll/sra? Hmm, `(m = ret & 0x8000) != 0` with ret u16: andi, then test. That might not change.

Hmm. Let's consider `m` being the first declared:

```c
s32 m;
s32 ret;
```

Try it.

Also consider: maybe the target's shape comes from ret being used in BOTH arms of the switch later? No, ret isn't used later.

Wait, actually, let me re-read the target flow. `beqz v1, 384` — the ret==0 case jumps to 384, which is the common code after the if/else chain. In the C, `if (ret == 0) {}` empty. So gcc emits the branch to the else-if. Fine.

Let me look at the pinned build's insns to confirm they match target (score 0). Actually the current src is banked and presumably matches. Let me check by compiling orig.c? The orig.c has the pins and should score 0. Let me score orig.c to confirm baseline.

Let me also check the "COUNT; mine 102 ins, target 103" — mine has 102, target 103. The missing insn is the move v1,v0, but also the branch offsets shift.

Plan: generate a batch of variants and score with sc.sh. Let me write them.

Variants:
v1: decl order m, ret
v2: m declared before ret, and `s32 m = ret & 0x8000;` right after the call? That changes order (andi before beqz).
v3: ret as u16
v4: ret as s16
v5: m as u16
v6: separate call temp: `s32 t = func(...); ret = t;` with t used in andi.
v7: use `if (ret != 0) { if ((m = ret & 0x8000)) ... }`.
v8: keep the `if (ret == 0) {}` but write `else if ((m = (s16)ret & 0x8000) != 0)`.

Actually, wait. Let me think about why `m` would take v0 *and* ret v1 in the target: perhaps because in the target's source, `ret` is used in the andi as a *different* pseudo — e.g., the call result is stored in a variable `r`, and `ret` is `r` copied. Hmm.

Alternatively, maybe the pins were needed for a completely different reason and the natural allocation is close. Let me check the pinned body's dump and the natural body's dump more carefully, and look at local-alloc.c in tools/reference/gcc-2.7.2/local-alloc.c.

Let me look at the block alloc ordering.
