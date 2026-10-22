---
ts: 2026-10-22T00:22:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_MFhxMc2G6DO1ds7A8Nxg
---
func_8003DF8C: the diff is a big register-allocation difference (a0/a1/a2 vs a3/t0/s3 etc.) — the target keeps arg0/arg1 in a3/t0 (callee-saved) while mine keeps them in a0/a1. That's because the `i = arg0 + zr; j = arg1 + zr;` copies (opaque) forced the parameters into callee-saved regs (i and j are live across calls → i,j in s-regs, and arg0/arg1 copies in a3/t0).

So it's the same mechanism (the $0 copies) plus the allocation. The best score is 34.

Now let me score the 800D2650 candidate.

Then finalize. Let me also try 801415C0 with the "local/global" idea: hmm.

Actually, for 801415C0, let me try ONE thing: make `c` and `d` multi-set so they become globals... impossible.

Hmm, alternatively for 801415C0: what if I make a,b NOT globals by... hmm.

Let me try a different idea for 801415C0: what if `e` is split so that fewer globals exist? Hmm.

Actually, let me revisit: the target's allocation is base(s0), b(s1), c(s2), d(s3), e(s4). In my candidate: c(s0), d(s1), a(s2), b(s3), e(s4).

What if I could make c and d globals (multi-set) — then the globals would be a,b,c,d,e and the assignment by priority: a(5000)→s0, b(4615)→s1, c(4285)→s2, e(3636)→s3, d(3000)→s4. The target wants d=s3, e=s4. So I need d > e in priority.

Hmm, if c,d are globals, their live lengths change. Hmm.

Alternatively: what if I make c,d LOCALS but ensure the locals don't take s0/s1? Hmm.

Hmm, what if the function had only ONE local (c,d merged)? no.

Hmm, let me think about the local-alloc's reg choice for locals: gcc 2.7's local.c `find_reg` chooses among the available local regs. The order might be influenced by `reg_last_freq` (the frequency of the last use of each register).

Hmm! Here's an idea: if a and b were LOCALS (not globals), then local-alloc would assign them first (by priority) and c,d later. The target order (a,b,c,d,e) suggests exactly that.

To make a and b locals: they must not cross a call... they do.

Hmm, hold on! What about the criterion "multi-set AND crosses a call ⇒ global"? What if I could make a,b single-set?

a: `a = param_2; ... a = (s16)a; ... a = a*2+0x14;` — 3 sets.
Hmm! What if a and b were not variables but the PARAMETERS themselves?
```c
void func_801415C0(s32 param_1, s32 param_2) {
    s32 c, d, e;
    param_2 = (s16)param_2;      /* set on the param pseudo */
    ...
    c = param_2 + 0x2F;
    ...
    param_2 = param_2 * 2 + 0x14;
    func_800291C8(param_2, ...);
}
```
The param pseudo: the copy-in (1 set), the sext (2), the *2 (3) — still 3 sets. Hmm.

Hmm, what if the parameter is used WITHOUT modification:
```c
    c = (s16)param_2 + 0x2F;   /* the sext is a temp */
    ...
    func_800291C8(param_2 * 2 + 0x14, ...);
```
Then param_2's pseudo: copy-in (1 set) + 2 reads. Single-set! But then the target's structure (one register holding param_2 raw → sext → *2) is lost: the sext would be computed into a temp and the *2+0x14 into another ✗ (the target has `sll s0,s0,0x10; sra s0,s0,0x10; addiu s2,s0,47` — hmm, the sext is in-place on s0 and c = s0+47 in s2).

Hmm! Actually: the target's `sll s0,s0,0x10; sra s0,s0,0x10` is the sext in place on s0 (= param_2's register). If param_2 weren't modified, the sext would be computed into a temp (a new reg) ✗.

So a must be modified in place → multi-set → global.

⇒ 801415C0 is likely a WALL too. Hmm. But wait — the earlier G07 coder cracked func_8012EF34 and func_8012EF70 (similar functions) by using the s32 return type. So similar items CAN be cracked.

Hmm, for 801415C0: the target has a=s0, b=s1, c=s2, d=s3, e=s4.

Hmm, what if the trick is the RETURN TYPE? The function returns void. The moves.md entry for func_8012EF34: "the game's real prototype is s32, not void: the s32 return keeps $v0 live across the gte_stsz asm, so local-alloc gives the &sp10/load temp $v1 instead of $v0".

Hmm! For func_801415C0 (void), a void return means no $v0. Hmm.

Hmm, what if the real prototype was `s32` and the function returns something? That would change the signature ✗ ("no signature or decl change outside the body"). Hmm, the brief says "no signature or decl change outside the body (callers stay as they are)". Changing the return type would change the callers' expectations... The 8012EF34 case changed the header's prototype (which is the body's signature) — hmm, that was allowed there.

Hmm, for 801415C0, the callers call `func_801415C0(a, b)` and ignore the result. If the prototype were s32, the callers would still work. Hmm! But the constraint says "no signature or decl change outside the body" — the body includes the signature? The brief for the other coder (G07 without 'r') said the same, and the 8012EF34 match changed the return type... that was a different coder (T11.cG07, the earlier one). Hmm, and it's recorded in results.tsv as a MATCH.

Hmm, so changing the return type in the body is acceptable (it's inside the body).

Let me try: make func_801415C0 return s32 with a return value at the end? Hmm, that changes the code (a `move v0,...` + the return). The target's function ends with:
```
move a0,s2
move a0,s3
lw ra,36(sp) ...
```
No v0 set → void ✓. So the return type is void ✓ (no change possible).

OK.

So for 801415C0, the allocation a=s0,b=s1,c=s2,d=s3,e=s4 vs mine c=s0,d=s1,a=s2,b=s3,e=s4.

Hmm, hold on! What if I make c and d NOT locals by giving them a second set...

Hmm, hmm. What if c and d are assigned in a way that creates 2 sets: e.g.
```c
d = b + 0x2F;
...
d = d;   /* identity */
```
✗ forbidden.

Hmm, what if:
```c
c = a + 0x2F;
func_800291A0(d, func_800291B4(c) & 0xFF);
func_800291A0(c, e);
```
Hmm.

OK. Let me try ONE experiment for 801415C0 that might work: **make the ORDER of the source such that a and b are assigned FIRST and c,d later** — they already are.

Hmm, what about the priority of a vs c: a(5000) > c(4285) ✓ — so if all were globals, a would get s0 ✓ and b s1 ✓, c s2 ✓, then e(3636) s3 ✗ (target: d s3, e s4).

So I need d > e. d: refs 3, live 10 → 3000. e: refs 4, live 22 → 3636.

Hmm! What if e's live were longer? e = 291B4(d)&0xFF is set early and used at `291A0(c,e)`. Then e is reassigned at `e = 291DC(b)` and used at the end.

Hmm, e's live length 22 — the second e's live (from `e = 291DC(b)` to the last use) is long.

Hmm, what if e's SECOND assignment were later in the source? The source order is fixed by the semantics (e = 291DC(b) must come after b = b*2+0x14).

Hmm, what if `e` were split into two variables (e1, e2)? Then e1 (2 refs) and e2 (2 refs). Hmm, and the target has both in s4 (the same register) — with two separate variables, they'd get different regs ✗ (unless the register allocator assigns the same reg to non-overlapping pseudos — gcc 2.7's local-alloc CAN do that for locals! But e1/e2 cross calls → globals → global-alloc gives each a distinct reg ✗).

Hmm.

What if d had more refs? d is used 3 times. Hmm.

Hmm, what if the second `e = func_800291DC(b)` were written as `e = func_800291DC(b)` (unchanged) but the FIRST e's use were different...

OK, let me try the "make c,d globals" experiment for 801415C0 in a code-neutral way...

Hmm, actually! Here's an idea: what if `d` is assigned TWICE with the same value but the second assignment is a REAL re-computation that gcc can't CSE because it's in a different block? E.g.:

```c
d = b + 0x2F;
e = func_800291B4(d) & 0xFF;
...
```
Hmm.

Hmm, what about giving `c` a second set via a different expression that's equal:
```c
c = a + 0x2F;
...
c = a + 0x2F;   /* recompute */
```
→ CSE merges (same expression) → 1 set.

Hmm, what if the second is `c = c + 0`? → folded.

Hmm.

OK, let me accept the WALLs and finalize. Actually, let me do ONE quick test for 801415C0: the "make c and d globals" idea via a legitimate multi-set: what if `d` is computed as `d = b + 0x2F;` and later `d = d + 0`? no.

Hmm, alternatively: what if `d` were used to compute `e` and then `d` were REASSIGNED the same value in a branch? no.

Let me just try: 801415C0 with `c` and `d` given an extra (dead) assignment to make them multi-set, to TEST the hypothesis. If the hypothesis holds (score improves dramatically), then I'd think about how to do it legitimately.

Test variant:
```c
    d = b + 0x2F;
    d = d;      /* TEST only */
```
Hmm, gcc would fold `d = d` → hmm, it might create a second set! `(set d (reg d))` — combine would fold it to a no-op. Hmm.

Let me instead test with `c = c + 0;` — hmm.

OK, honestly: let me test the hypothesis with a REAL semantic change first (to see if multi-set → global helps): e.g. `d = b + 0x2F; d = b + 0x2F;` (a duplicate assignment, CSE-merged → hmm).

Time is very tight. Let me finalize now:

Results:
1. func_8012EF34 — MATCH (existing row)
2. func_8012EF70 — MATCH (existing row)
3. func_800D02D0 — WALL (existing row)
4. func_80181E64 — WALL, best 3, tag cse-opaque-copy
5. func_80180480 — WALL, best 19, tag lreg-v0-local-first
6. func_800D0D7C — WALL, best 17, tag cse-opaque-copy
7. func_800D2650 — ? (need to score)
8. func_8003DF8C — WALL, best 34, tag cse-opaque-copy (probably)
9. func_8012944C — MATCH ✓ (141/141)
10. func_801415C0 — WALL, best 40, tag lreg-qty-order?

Let me score 800D2650 and try 801415C0 once more with a quick idea. Then finalize.

For 801415C0, let me try ONE more variant class: swap the roles of c and d in the source (i.e., name them so that the variable that must be s2 is created first). Hmm, the assignment ORDER matters: d = b + 0x2F comes before c = a + 0x2F in the source. If I could make c's pseudo created first (so c gets s0... no wait, I want c to get s2 and d s3).

In my candidate: c=s0, d=s1, a=s2, b=s3. The target: a=s0, b=s1, c=s2, d=s3.

Hmm, if c,d were globals with priorities a(5000) > b(4615) > c(4285) > e(3636) > d(3000) → a=s0,b=s1,c=s2,e=s3,d=s4.

So I'd need d > e. Hmm.

Alternatively if c,d were globals and the ORDER were by priority, to get d=s3 I need d > e.

d: refs 3 (set + 2 uses), live 10 → 3000.
e: refs 4, live 22 → 3636.

To raise d: refs 4 → 2*4/10 = 8000 ✓ (but then d > c: c=4285 < 8000 ✗ → d would get s2 and c s3 ✗).

Hmm, need c > d > e: c(4285) > d > e(3636). So d's priority between 3636 and 4285: e.g. refs 3 with live 7 → 4285 (=c, tie) hmm; refs 3, live 8 → 3750 ✓ (between 3636 and 4285 ✓).

So d's live would need to be 8 (currently 10) and c's live 7.

Hmm! c's live is 7 and d's is 10. If d's live were ≤ 8...

d's live: from `d = b + 0x2F` to its last use (`func_800291A0(d, ...)`).

In the source, d is used at `e = func_800291B4(d) & 0xFF;` and `func_800291A0(d, ...)`. Between them: the call 291B4. So d's live spans ~10 insns.

Hmm, if d's assignment were moved LATER (closer to its uses): d is needed by the first call (291B4(d)). Hmm, the first call is early.

Hmm, what if the first call `e = func_800291B4(d) & 0xFF;` were moved AFTER `func_800291A0(d, ...)`? ✗ semantics (e is needed).

OK. I'll record 801415C0 as a WALL.

Hmm, but hold on. Let me reconsider ONE more time for 801415C0: what if the whole allocation flips if the globals' set changes? Currently the globals are a,b,e (3) and the locals c,d (2). If c,d were globals (5 globals), the allocation would be a=s0,b=s1,c=s2,e=s3,d=s4 (by priority). The target wants d=s3,e=s4.

Hmm, what if e's live were longer than d's? e's live 22, d's 10 → e has a HIGHER priority (fewer... hmm: pri(e) = 2*4/22 = 3636 > pri(d) = 1*3/10 = 3000).

To flip d and e: d needs pri > 3636: refs 4 (→8000, too big vs c=4285 ✗) or refs 3 with live ≤ 8 (→3750 ✓).

Hmm, so d's live must be ≤ 8. Hmm, d's live is 10 in the current source. Hmm, what if d's live is measured differently...

OK, ENOUGH. Let me finalize. Score 800D2650 and write everything up.

Let me score800D2650 now.
