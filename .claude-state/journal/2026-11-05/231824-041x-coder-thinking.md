---
ts: 2026-11-06T06:18:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hIFn7b5WJdSb7u8EbPxR
---
Now r72 has no conflict with 16. Order: 72 (a0) then 166, 73 (loopptr), 80 (ent), 74, 75, 76.

Priorities: r72 19266, r166 12500, r73 7714 (loopptr), r80 2500 (ent).

We need r73 to fall below r80 (2500) or r80 to rise above 7714.

r73 = 9 refs, live 35 → 3*9/35*1e4 = 7714.
r80 = 3 refs, live 12 → 1*3/12*1e4 = 2500.

Idea: extend r73's live length. Live length is the count of insns over which the pseudo is live. What if `s5 = s2 + 0x3240` is computed *before* the if? It already is. Hmm.

Alternatively, what if the loop's end pointer `s5` is derived from s2 differently... 

Another approach: change WHICH pseudo is the loop pointer. What if the loop uses `s5` as the counter and s2 as the limit? No.

Better idea: what if the loop body references the loop pointer via a *different* variable so that the loop pointer pseudo is used only in the test and increment, while the address computations use a separate pointer? E.g.:

```c
s2 = (u16 *)D_801202A0;
s5 = s2 + 0x3240;
...
do {
    ent = (s16 *)(s2 + 2);
    if (*s2 == 0xF2) { ... unkCC = (s32)s2; ... }
    s2 += 0x86;
} while (s2 != s5);
```

The target has the loop pointer in $18 and ent in $17.

Hmm, what if I split s2 into two variables: a "cursor" used for the address computations and the test? No, they must stay in sync.

Alternative approach: raise ent's priority by lengthening... no, by increasing refs. Actually easier: reduce ent's live length? Its live is 12; with 4 refs and live 10, pri = 2*4/10*1e4 = 8000 > 7714. Hmm.

What if ent is declared as a `s16 *` and used in the first call as `(void *)ent` and second as `ent` — same.

Hmm, what about using ent for the `*s2 == 0xF2` test as `ent[-1]`? Let me think about what gcc does. ent = (s16*)(s2+2), so ent[-1] = *(s16*)(s2). But the target uses `lhu v1,0(s2)` — a *u16* load compared to 0xF2. `*s2` is u16 (s2 is u16*). ent is s16*, so ent[-1] is s16 → lh, sign-extended. Different insn (lh vs lhu). The target has lhu. So no.

What about making the loop pointer a `u8 *`? No.

Let me think differently: maybe the natural way the original author wrote it produced $18 for the loop pointer... The pin exists precisely because the natural code gives $17. So this is a genuine wall candidate: "the pin reserves $18 for the loop pointer; lever-free the loop pointer's priority (loop-weighted... well, unweighted now) beats ent".

But wait — we're allowed PARTIAL: "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". So if the pin can't go, we could keep the pin and drop the launder → PARTIAL:pin if score 0. Let me test that: keep the pin, only remove the launder (with the dead-reset). If score 0, that's PARTIAL:pin.

Let me test that quickly: orig.c with launder replaced by dead-reset pattern, pin kept.

Actually the pin is `register u16 *s2 __asm__("$18")`. With the pin, s2 is in $18 and ent gets $17 naturally. The dead-reset for the address then fixes the param conflict... but wait, with the pin at $18, does the address pseudo take $16? The address pseudo r147 conflicts... it took $16 in the first candidate, and then a0 got $17. With the pin, a0 would get $16 or the address would.

Let me just test: win_p.c = orig with launder→dead-reset, pin kept.

But first, let me spend a few more tries on the full MATCH since PARTIAL is a fallback.

Think: what determines ent's priority 2500 vs loopptr 7714? 

Idea: make the loop pointer's live range *longer* by having the loop body use it later... it already spans to the loop end.

Idea: make the *increment* not a "set+use" (2 refs). E.g., `s2 = s2 + 0x86` is the same. What about using a `for` loop: `for (s2 = (u16*)D_801202A0; s2 != s5; s2 += 0x86)` — same refs.

Idea: use the end pointer differently: `if (s2 != s5) { ... } while (s2 != s5)` — the entry test could be avoided by a do-while with a pre-test... 

Hmm, what if we restructure: since `s5 = s2 + 0x3240` and the loop compares s2 to s5, we could count: no, target's insns are fixed.

Idea: reduce loopptr refs from 9 to 4-5 by having the body use a *copy* of the pointer for the loads. E.g.:
```c
u16 *p2 = s2;  // inside loop
ent = (s16*)(p2+2);
if (*p2 == 0xF2) { ... unkCC = (s32)p2; ... }
```
Then p2 would be its own pseudo with refs inside the loop... but that would add a `move` instruction unless the copy is coalesced away. Hmm, if coalesced, refs are attributed to... the pseudo that survives.

OK here's another thought. What if the increment uses a *different* register class or the loop is structured so the pointer is live longer? Live length counts insns where the reg is live: from first use to last use. Currently 35. If I make the *entry test* happen before the `s5 = s2 + 0x3240`... no.

Actually, what about the reverse: what if s5 (the end pointer, 3 refs live 66) is what gets $17? No, ent is $17 in the target.

Let me reconsider: maybe ent's priority can rise by making its live range shorter. ent = (s16*)(s2+2) is computed at the top of the loop body, then used in the two calls with a conditional between. If ent were computed right before the first call (i.e., `if (func_8012BC60((void*)s3, (void*)(s16*)(s2+2)) < 0x4000)`), then ent wouldn't exist as a variable... but the target has `addiu s1,s2,4` before the `lhu v1,0(s2)`:

Target asm at 212-216:
```
addiu s3,s0,4
lhu v1,0(s2)
...
addiu s1,s2,4
```
So ent (s1) is computed *after* the lhu — i.e., after the `*s2 == 0xF2` test! In my source, `ent = (s16*)(s2+2)` is before the `if (*s2 == 0xF2)`. Since ent is dead until the calls, sched1 moves it. Fine — mine also has addiu s2,s0,4 at 216.

Hmm OK.

Let me try a completely different angle: what if the *param* a0 and the loop pointer could be made to swap by... no, a0 is right now.

Let me look at it from the "what did the original author write" angle: the pin was added by us (a fake). The real ROM code has the loop pointer in $18 and ent in $17. The natural C would give loopptr priority 7714 > ent 2500 → loopptr $17. So the ROM's codegen must have had something making ent win. In the ROM, maybe ent's live range is shorter, or its refs more.

Wait — maybe in the ROM the loop pointer variable is NOT the same pseudo as I think. What if the source used the *end* pointer as the loop variable and the current pointer derived? Or what if the loop is `while (s2 != s5)` with the increment at the top?

Let me look at the target asm for the loop region to see the actual register roles. From the diff (target side):
```
206 move a0,s0
207 lui s2,0x0
208 addiu s2,s2,0
209 addiu s5,s2,25728
210 beq s2,s5,...
212 addiu s3,s0,4
213 lhu v1,0(s2)
216 addiu s1,s2,4
219 move a1,s1
222 move a1,s1
227 sh v0,2(s0)
228 move a0,s0
229 lw v1,32(s0)
234 sw s2,204(s0)
236 move a0,s0
240 move a0,s0
242 sh v0,22(s0)
243 addiu s2,s2,268
244 bne s2,s5,...
```
So target: s2 = loop pointer, s5 = end, s1 = ent, s3 = s0+4.

Now the refs: in the target, the loop pointer s2 has the same 9 refs. So the target's ent must have higher priority than the loop pointer... but with the pin it doesn't matter! The pin forces s2 into $18 regardless of priority, so ent naturally gets $17.

So in the real ROM, this was probably compiled from source with a hard-reg... no wait, the ROM is the original compiled code. Hmm, but the pin is *our* reconstruction: we discovered that to reproduce the ROM's code we need to pin. The ROM's compiler (gcc 2.7.2 with the same flags) produced $18 for the loop pointer *from the original C source*. So the original source had something that made it happen. That's what we're trying to find.

Since the original source might have had a different variable structure (e.g., the loop pointer might have been used more, or ent fewer).

Hmm! What if in the original, `ent` is NOT a variable but the two calls take `(void *)(s2 + 2)` and `(s16 *)(s2 + 2)` — but then the target's `addiu s1,s2,4` (a separate register) wouldn't exist; the arg would be computed into a1 directly at each call. The target has ONE addiu s1,s2,4 and then `move a1,s1` twice. So ent is one pseudo used twice. Confirmed.

What if ent is used *three* times in the original (a third use that got optimized out)? Can't be.

What about the *order* of declarations affecting allocno numbers? The tie-break is by allocno number, but priorities differ here.

OK, what about making the loop pointer live *longer*? What if `s5` is computed as `s2 + 0x3240` but the comparison is against a different variable? no.

Hmm, what about the fact that live_length is the number of insns in the range... What if the loop pointer were live from earlier (e.g., assigned at the top of the case)? That changes insn order.

Let me try: what if I give ent an extra ref by writing `(void *)ent` in the first call and `ent` in the second, plus... no, casts are free.

What about making `s3` and `ent` the same variable? no.

Alternative: reduce the loop pointer's refs by 2 and increase ent's by 2 through a restructuring where the loop pointer's address arithmetic uses ent: e.g.
```c
ent = (s16 *)(s2 + 2);
if (ent[-1] == 0xF2) ...
```
No (lh vs lhu).

Hmm, what about `if (s2[0] == 0xF2)`, `ent = (s16*)(s2+2)`, `unkCC = (s32)s2`...

New idea: what if the loop pointer variable is `u16 *s2` but the *increment* is folded into the loop test as a separate expression? e.g. `while ((s2 += 0x86) != s5)`? That's a comma/complex condition. `do { ... } while ((s2 += 0x86) != s5);` — that removes the separate increment statement. Refs stay the same.

OK, let me consider: can I increase ent's refs to 5 without adding instructions? Refs are counted per RTL mention. If the same variable appears in an expression that's folded, no ref.

What about `func_8012BC60((void *)s3, (void *)(ent + 0))`? combine folds +0.

Hmm. What if ent is declared `u16 *ent` and used as `(void*)ent` and `(s16*)ent` — same refs.

What about this: `ent` is used in the calls; if I ALSO use ent in the `unkCC = (s32)s2` line... no.

OK, alternative: reduce loopptr priority by increasing its live length. The live length counts insns where live. Currently 35 (the loop body is ~30 insns). If the loop pointer were initialized earlier in the block — e.g., move `s2 = (u16 *)D_801202A0; s5 = s2 + 0x3240;` before `func_80131C78(a0); func_8012A828(a0, &D_801C0200);` — the live length would grow by ~10 insns but the *insn order* would change: the target has lui/addiu s2 AFTER those calls (at 207). Hmm, would sched1 move it back? sched1 reorders within a basic block. The block: func_80131C78(a0); func_8012A828(...); s2=...; s5=...; beq; ... Actually if I move the assignment earlier in source, sched1 might sink it, but calls are barriers for scheduling? sched1 doesn't move insns across calls (they're not movable? Actually it can move a lui/addiu across a call if no dependency... it typically doesn't move across calls in the same block? It does treat calls as having high cost).

This is getting long. Let me time-box: try the PARTIAL fallback first to bank a guaranteed result, then try a couple more MATCH ideas.

Actually, wait. Better idea! What about the *entry test*: `if (s2 != s5)`. What if the loop is written so the first test is a `beq` at the bottom only (do-while)? That's what orig has, and it gave the same allocation... but that changes loop notes.

Hmm, here's a cleaner idea: **make ent's live range shorter and its refs higher by computing it inside the if**. But the target computes ent unconditionally (`addiu s1,s2,4` before the branch)? Let me check the target asm order: 
```
212 addiu s3,s0,4
213 lhu v1,0(s2)
...
216 addiu s1,s2,4
```
Is 216 inside the if or before the branch? Let me look at the full target asm around there. The diff shows mine 216 = `addiu s2,s0,4` and target `addiu s1,s2,4` — both at index 216, so same position. The branch structure: after lhu there's a compare and branch (bne) — where is it? The diff didn't show those lines because they matched. Let me get the target asm from the build to see the block structure. Let me look at the full diff file (it only shows differences). Let me instead disassemble/objdump? 

Simpler: look at the .s produced by the candidate and the target? The target asm is available via the build object. Hmm, dt.sh compares.

Alternative: use --explain? It prints the residual with context. Let me get a wider diff with context by using the tool's --show? Hmm.

Actually, the simplest: the two calls take ent. In the target, `addiu s1,s2,4` appears before `move a1,s1` at 219. Both calls are inside the `if (func_8012BC60(...) < 0x4000)` block: the first call is the test itself, the second is func_8012B6D4. So ent is born (addiu) before the branch — outside the if, as in the source.

OK. Let me try yet another angle: what if `ent` is used as a *void pointer* in both calls and the `(s16 *)s3` cast stays: `func_8012BC60((void *)s3, (void *)ent)` and `func_8012B6D4((s16 *)s3, (s16 *)ent)`. Same.

Honest assessment: I've spent ~20 min. Let me bank PARTIAL:pin (remove the launder only) and then continue trying.

Let me build win_p.c: orig.c with the launder → dead-reset, keeping the pin.

Actually careful: with the pin kept, the launder line is the asm at case 2. Replace with `p = &D_801C00D0; func_8012A828(a0, p); p = 0;`. And the second call stays `func_8012A828(a0, &D_801C00D0);`.

Let me test whether that scores 0.
