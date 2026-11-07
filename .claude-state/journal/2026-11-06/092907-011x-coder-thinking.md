---
ts: 2026-11-06T16:29:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bsWTE5v1zOejC2jRz1hx
---
So quantities with copy preferences (the move v0→pseudo) get first priority. That's ret: it has a copy preference to v0, so it wins and gets v0. m has no preference. So ret=v0 naturally, then m=v1? But mine shows m in v0 too (shared). Because m's live range doesn't overlap ret's (ret dies at the andi, m born there) → m can reuse v0. Hmm, in the target m is v0 and ret is v1.

Wait, maybe in the target the move is NOT the call result copy. Let me reconsider: maybe the target source is:

```c
s32 ret = func(...);   // ret in v0
...
if (ret == 0) ...
else if ((m = ret & 0x8000) != 0)
```

and the `move v1,v0` is the copy of ret to v1 because ret is used in the *andi* whose output must be v0 (for some other reason) and ... no, the move is before the beqz.

Hmm, alternatively, maybe the pinned version has ret in $3 and the move v1,v0 is inserted because the call returns in v0 and ret's hard reg is v1. Yes, that's what the pinned build does. And the target bytes equal the pinned build. So target's `move v1,v0` is the artifact of the pin. So a lever-free body must reproduce a copy from v0 to v1 by natural means.

So the question: how to get gcc to allocate ret to v1 and m to v0 naturally? 

Idea: make ret have a normal preference (not copy preference) to v1? No, preferences come from moves.

Idea: make the call result pseudo (v0) live beyond the andi — e.g., use the raw call result later, so v0 is occupied when ret is allocated... but ret is the call result.

Idea: prevent the copy-preference tie by making the move from v0 to ret not the only copy — i.e., two copies from v0 so the preference conflicts? In local-alloc, if two pseudos both have a copy pref to v0 and their live ranges overlap, only one gets v0.

Idea: make m have a copy preference to v0 too, with higher priority than ret. E.g. `m = ret & 0x8000` isn't a copy. But what if m is assigned from a variable that's in v0? 

Idea: the source might be:

```c
s32 t = func_801638A0(...);
s32 ret = t;   // copy
m = ret & 0x8000;
```
copy prop would kill.

Alternative idea: use a 2-register value? No.

Let me think about what makes ret NOT get v0: if v0 is live across the whole block from the block start (e.g., a value in v0 live across the call? not possible, calls clobber).

What if the andi's operand and result are different pseudos such that m's live range overlaps ret's? For instance, if the source is:

```c
m = ret & 0x8000;
if (ret == 0) {}
else if (m != 0) ...
```
Then the andi comes before the beqz (m computed first), and ret is live after the andi (for the test). So ret's live range overlaps m's at the andi. Then ret and m can't share. ret has copy pref → v0. m → v1. Target would be `andi v1,v0,0x8000; beqz v0; bnez v1` — but target is `move v1,v0; beqz v1; andi v0,v1`. So not that.

OK here's another thought: what if the call's result is assigned to `m` directly and `ret` is a separate variable? No, ret = call.

Let me look at this from the "what C gives move v1,v0" angle. A copy v1←v0 is emitted when the call result pseudo is allocated v1, i.e. the pseudo has copy preference to v0 but v0 is unavailable. v0 unavailable because... another pseudo live at the move point occupies v0. At the move point (right after the call), the live pseudos are: a0 (s0), sp20 addr (a1 maybe), sp28, ret. Also possibly `m` if born earlier. If m were born BEFORE the move... m = ret & 0x8000 can't be before the call.

Unless the source computes something into v0 right after the call in a different order. Hmm.

What about `ret` being live across a call? No.

What about the andi target being a hard reg via a struct/field? No pins allowed.

Hmm, wait: maybe I've got it backwards. Let me look at mine's insns 12-18 more carefully.

mine:
```
12  bnez v0,368
...
16  beqz v0,380
17  andi v0,v0,0x8000
18  --
```
target:
```
16  move v1,v0
17  beqz v1,384
18  andi v0,v1,0x8000
```

Mine has an extra insn at 18? No: mine[16:18] is 2 insns, target[16:19] is 3. And "mine 102 ins, target 103" → one missing (the move).

So mine: call; beqz v0; andi v0,v0. Where's the ret copy? Absent (tied). Right.

So to match, need `move v1,v0`. Since it's a hard-reg copy emitted at expand time? Actually in gcc 2.7.2 the call_value pattern for MIPS: let me check mips.md call_value. The return value is moved from the hard reg to the pseudo by expr.c. The move insn is `(set (pseudo) (reg 2))`. Local-alloc then either ties (deletes move) or assigns pseudo a reg, keeping the move. The move's destination is ret's pseudo. So `move v1,v0` means ret got v1.

For ret to get v1, v0 must be unavailable at the move. v0 is live at that point if some other pseudo lives in v0 across the call... impossible. OR v0 is *preferred* by a higher-priority qty that lives there.

Consider: if `m` had a copy preference to v0 with higher priority. How could m have a copy pref to v0? If m were assigned from a value in v0 — e.g. if the andi's input is in v0. But at allocation time preferences come from moves, not andi.

Alternative: maybe the copy from v0 to ret is not the only insn; maybe there's a second copy `ret2 = v0` — no.

Hmm, maybe the target's source uses the call result twice via a temporary that is a *function argument copy*... 

Let me try a completely different tack: empirically generate many variants and score. This is a search task; 30 tries budget. Let me write ~15 variants at once and score with sc.sh.

Variants to try (all lever-free):

1. decl m first, then ret.
2. ret u16.
3. ret s16.
4. m u16.
5. m s16.
6. no m var: `else if (ret & 0x8000)`.
7. `s32 ret = func(...);` at decl (init at decl).
8. `s32 m; ... m = ret & 0x8000;` hoisted before the if (with the test on m).
9. `if (ret) { if ((m=ret&0x8000)) ... else ... }`.
10. use `& 0x8000` twice.
11. temp t = func; ret = t.
12. `register`-free but `volatile`? no.
13. m declared as `s32 m;` but used in stores too.
14. Different: make ret a `s32` but assign via `ret = func(...) & 0xFFFFFFFF`? That creates an extra andi... no.

Also: what if the call result is assigned to a variable declared as `u32` and ret is compared `if ((u32)ret == 0)`? no change.

Wait — maybe the actual mechanism in the target is different: maybe `move v1,v0` is a copy that exists because ret is used in the ANDI as an operand that must be in v0? Like `andi v0, v1, 0x8000` — the output v0. If the andi output pseudo `m` has a copy preference to... hmm.

Alternatively, consider this C:

```c
if (func_801638A0(...) != 0) { ... }
```
with the result stored in `ret` only inside? no.

Let me think about gcc 2.7.2's behavior for `ret = f(); if (ret == 0) {} else if ((m = ret & 0x8000))`. Hmm, mine already shows the natural result.

Could the target's `move v1,v0` be from `ret = func(...)` where `ret` is a `register` variable? Not allowed.

Maybe from assigning to a struct field or array element? e.g. `sp20[1] = func(...)`? Then it would store.

OK here's another thought: maybe the *function's return value type* matters. If the call is cast, e.g. `(s32)func_801638A0(...)`, no.

What if the source does:
```c
ret = func_801638A0((u8 *) a0, (s32) sp20);
if (ret == 0) {
} else if ((m = ret & 0x8000) != 0) {
```
and `ret` is declared as `s32 ret;` but ALSO `m` is declared `s32 m;` — mine. 

Hmm, what if `ret` is used in the second arm in a way that makes it live longer... target shows it isn't.

Let me look at the original game's likely C. The function: calls func_801638A0, checks return. This might be from a pattern where ret is `s32 ret = func(...)` and then `if (ret == 0) goto ...; if ((m = ret & 0x8000) == 0) ...`.

Actually — what if the branch structure is inverted: `if (ret != 0) { if (m) A else B }` and the empty `if (ret == 0) {}` is an artifact of `if (!ret) goto tail;`. The target has `beqz v1, 384` where 384 is the common tail. That means ret==0 → tail. So source order: test ret, if zero skip the m handling.

What if the code is:

```c
ret = func(...);
if (ret != 0) {
    m = ret & 0x8000;
    if (m != 0) {...}
    else {...}
}
```
Same.

Hmm, what about the possibility that `ret` and `m` are the SAME variable? `ret = func(); if (ret == 0) {} else if ((ret = ret & 0x8000) != 0)`. Then m is ret reassigned! The andi output would be a new value in the same pseudo. Target: `move v1,v0; beqz v1; andi v0,v1,0x8000` — the andi output v0 is a different pseudo than ret (v1) because the pseudo's live range... if it's the same pseudo, andi would write v1. So no.

Unless the reuse forces a split? No.

OK, let me consider that local-alloc's copy preference may be defeated by the `ret` pseudo being *live across a call*? It isn't.

Actually — wait. What about `qty_n_refs` and the priority? If `m` has a *suggestion* (copy pref) to v0 from somewhere and ret also has a copy pref, `qty_sugg_compare` gives priority to the one with fewer suggestions... Both have 1. Then priority by refs/life. Hmm.

Where could m get a copy pref to v0? If the andi's source `ret` is in v0... no, preferences come from `(set (reg) (reg))` insns.

Idea: introduce a plain copy from v0 to m! E.g., what if the call result is assigned to BOTH ret and m? `ret = func(); m = ret;` then m has copy pref to ret's reg. If ret=v0, m also prefers v0. With m live overlapping ret... 

Hmm, let's think about a construction that forces the target:
- We want pseudo A (=ret) allocated v1, with a move v1←v0 from the call.
- We want pseudo B (=m) allocated v0.

For A to not take v0: v0 must be unavailable when A is allocated. In local-alloc, allocation processes qtys; a qty is assigned the first free hard reg (or its preference). If B is allocated first and takes v0, then A can't. So B must have higher priority AND take v0. B taking v0: the allocator picks the first available hard reg in some order — for pseudos without preference, it picks by `reg_alloc`... it uses `find_free_reg` with a preference order: `reg_preferred`... Actually for no-preference, `find_free_reg` tries `alloc_reg` order (0..31) or based on `regs_live_at`. In MIPS, a pseudo would typically get v1 if v0 is... hmm mine gave m v0 by *sharing* with ret (tying). Not by separate allocation.

Actually, in mine, m is in v0 because local-alloc ties m's output with the dying input ret (the tying loop: "We can tie operand 0 with some operand that dies in this insn"). So m gets v0 by tying with ret's v0. To prevent that, ret must not be in v0.

So the crux: force ret to v1. What makes ret not get v0? The copy preference is on the move from v0. If we can make the move's destination a different pseudo that then copies to ret... Let's think:

```c
s32 t; s32 ret;
t = func(...);      // t tied to v0 (move deleted)
ret = t;            // ret has copy pref to t's reg v0
```
cse/copy-prop would fold ret=t unless t is used elsewhere. If t is used elsewhere AFTER ret's last use? E.g.:

```c
t = func(...);
ret = t;
if (ret == 0) {}
else if ((m = t & 0x8000) != 0) ...
```
Then t is used twice, ret once. ret=t copy might remain (cse can't fold because t is live). Then ret gets a copy pref to v0 and t is v0. Both can't be v0 (overlapping lives). So ret gets v1 → move v1,v0! And m = t & 0x8000 → andi v0,v1? Wait, the andi input would be t (v0) and output m → v0? Then `andi v0,v0,0x8000` — target is `andi v0,v1,0x8000`. Hmm, target's andi reads v1 (ret). So the andi reads ret, not t.

Unless m = ret & 0x8000 and ret=v1 → andi v0,v1. Yes! So source: t = func(); ret = t; test ret; m = ret & 0x8000; t used elsewhere so the copy stays.

Where would t be used elsewhere? Hmm, in the target nothing else uses the call result. But maybe the source had `t` used in a later block (dead) and flow deleted it? Flow deletes dead code, so if t were used later, we'd see it. 

Alternatively, ret is used later and t is the call result... 

Hmm, what if `ret` is used in the m arm and `t` in the test? Target andi reads v1 which is ret (from the test). Both the test and andi read v1.

OK, what if there's a copy chain: call → v0, ret = v0 (copy kept because...). For the copy to be kept, ret must have a conflicting preference or v0 unavailable.

What if `ret` has TWO copies from v0? No.

What if v0 is occupied at the move by the *address of sp20*? The call is `func_801638A0((u8*)a0, (s32)sp20)`. The addiu a1,sp,32 is in the delay slot. a1 is not v0.

What if v0 is occupied by a live value from before the call? Calls clobber v0, so no.

Hmm, so within a block, after a call, v0 is free. ret must get v0 unless it can't be tied due to a conflict with another qty that *also* has a copy preference to v0 and higher priority, or ret's live range conflicts with a v0-holding qty.

A qty holding v0 across the move point: the only candidate is a pseudo allocated v0 whose live range covers the move. Before the call, v0 is call-clobbered, so basic_block_live_at_start includes v0 only if live at block start — no.

Unless the function is inlined? no.

Hmm, so maybe the move v1,v0 isn't from the call result at all! Maybe it's a copy from another value. Let's re-read the target around 34c:

```
344: jal func_801638A0
348: addiu a1,sp,32      (delay slot)
34c: move v1,v0
350: beqz v1, 384
354: andi v0,v1,0x8000   (delay slot)
358: bnez v0, 37c
35c: nop
```

Yes move v1,v0 is right after the call; it's the call result copy.

So the target genuinely has the call result copied to v1 and then andi v0,v1. With pins, that's forced. Lever-free... The item is a "pin" kind item; the whole point of these shards is to find a plain-C spelling that makes the allocator do it.

Maybe the mechanism: make `ret` an `s16`/`u16`! Then the call result copy is a HImode move: v0 → pseudo (HImode). HImode pseudos in local-alloc: the copy pref is to v0. Hmm, still ties.

What if `ret` is `s32` but compared with `!= 0` where the comparison result feeds... no.

Hmm, let me look at similar cracked pins in the moves file to learn the trick. Search moves.md for pins that cracked where the target had a call-result copy to v1. E.g. "pin | func_80157BC8 | MATCH: both $2 result pins -> call-site return-type casts". Let me grep moves.md for "v1,v0" or "call result".

Actually, maybe I should search for W47x-like prior shards. Let me grep moves.md for func_800CB118 or md_MAIN_041.
