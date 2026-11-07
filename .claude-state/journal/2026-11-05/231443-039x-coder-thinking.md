---
ts: 2026-11-06T06:14:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rJoNTuXzDG5knMSw17lI
---
Confirmed: r72 conflicts with hard reg 16. Note "147 in 16" — a local pseudo r147 is in $16! So local-alloc gave r147 $16, and r147 is live where r72 is. That's the conflict!

r147 in $16 — that's the local pseudo that got s0. But we found no s0 in .lreg... because the .lreg dump prints `(reg:SI 147)`? Let me check: line 424 of the section showed `(reg:SI 167)`. So .lreg prints pseudo numbers, and the "Register dispositions" in .greg shows the final assignment.

So a local pseudo r147 is assigned $16 by local-alloc. That must be the `lui/addiu` address pseudo or a constant. In the diff at line 169-172:

mine:
```
move a0,s1
lui s0,0x0
addiu s0,s0,0
move a1,s0
```
target:
```
move a0,s0
lui a1,0x0
addiu a1,a1,0
```
So in mine, a symbol address &D_801C00D0 (or similar) is materialized into s0 (a callee-saved!) because it's used twice around calls — hmm, it's held in s0. In the target, it's materialized into a1 and used immediately.

This is the launder site! `func_8012A828(a0, &D_801C00D0)` — in the target (with launder), the address is materialized into a1 (temp) at the call. In my lever-free version, the address `&D_801C00D0` is used twice (before and after the func_800291C8 call), so cse/global-alloc keeps it in a callee-saved register $16 for the whole function? That's the local-alloc choosing $16 for the address pseudo, which then conflicts with the param.

Wait: r147 in $16 — local-alloc assigns caller-saved regs usually first ($2-$15, then $24/$25, then $16..). Hmm, local-alloc assigns to regs in order of allocno priority; a block-local pseudo gets a caller-saved reg typically. But if it's live across a call, it must be callee-saved.

So in my candidate, the &D_801C00D0 address pseudo is live across the func_800291C8 call and gets $16, blocking the param from $16. That's exactly the thing the launder prevented! The launder forced the address into a temp (p) that is used only at the call, then the second call re-materializes.

Hmm, wait. Look at the target asm again:
```
169 move a0,s0        | 169 move a0,s0
170 lui s0,0x0        | 170 lui a1,0x0
171 addiu s0,s0,0     | 171 addiu a1,a1,0
172 move a1,s0        | 172 --
```
Hmm, mine materializes into s0 and moves to a1; target materializes into a1 directly. So in mine there's a pseudo (the address) that got $16, then copied to a1. In target, the address goes straight into a1 (the launder's tied-output operand forced it into a register at that point).

Then at 189-191:
```
189 move a0,s1     | 188 lui a1,0x0
190 --            | 189 addiu a1,a1,0
191 move a1,s0     | 190 move a0,s0
```
Hmm, mine: at the second call, `move a0,s1; move a1,s0` — reusing the s0-held address. Target: re-materializes lui/addiu a1 then move a0,s0.

So in the target, the address is re-materialized at each use (cse's REG_EQUAL const, reload rematerializes), while in mine it's held in a callee-saved reg across the whole function.

The known wall tag: "cse-const-addr" (cse folds/substitutes a constant/absolute address the target keeps base-relative) — not quite. Or "reload-rematerialise". Hmm.

Wait, actually — this is a *different* effect than the pin. Let's reconsider. In the target (with launder asm), the address is materialized into a1 at each of the two call sites. In my plain-C version, cse/global-alloc decides to keep &D_801C00D0 in a callee-saved reg ($16) because it's used twice (before and after a call) — this is the *classic* CSE of a constant address.

So how to get the target behavior in plain C? Options:
1. Make the address's two uses not CSE-able: e.g., use a different spelling the second time, or a dead reset between. The §373 dead-reset move! C0414: "dead-reset cse-breaker". If I put a dead assignment between the first and second use... but the address is a constant expression; cse's REG_EQUAL note would be broken by a store to memory (nonscalar store invalidates memory, but a constant address isn't memory-dependent... unless the symbol is a variable that could be aliased).

Hmm, actually cse keeps REG_EQUAL for the address in a pseudo; then global-alloc keeps it live across the call. To break it: make the address be re-derived. 

The known MATCH move for exactly this: line 198: "DEAD-RESET CSE-BREAKER (§373): pb=&buf; call(pb); pb=0; before every site; cse's &buf address class breaks, so all 6 sites rematerialise addiu aN,sp,56 and no callee-saved reg parks the address (63 ins = target)".

So here: use a variable for the address: `void *p; p = &D_801C00D0; func_8012A828(a0, p); func_8002D4C8(...); ... func_8012A828(a0, &D_801C00D0);` Hmm.

Actually wait. Let's look at the case-2 block more carefully:

```c
            if (D & 0x1000) {
                void *p;
                ...stores...
                __asm__("" : "=r"(p) : "0"(&D_801C00D0));  // launder
                func_8012A828(a0, p);
                func_8002D4C8(0x531, 0);
                func_8002D4C8(0x526, 0);
                func_800291C8(0xA, 0x3025);
                func_8012A828(a0, &D_801C00D0);
            } else {
```

So there are two uses of &D_801C00D0 in the same block, separated by calls. Target: both materialized inline (lui a1; addiu a1). Mine: kept in s0.

Plain C: 
```c
                void *p;
                ...
                p = &D_801C00D0;
                func_8012A828(a0, p);
                ...
                func_8012A828(a0, &D_801C00D0);
```
That would be the same. To break the CSE class, the §373 dead reset: `p = 0;` after the first call, then `p = &D_801C00D0;` again? Hmm, the pattern from moves: "pb=&buf; call(pb); pb=0; before every site".

So:
```c
void *p;
p = &D_801C00D0;
func_8012A828(a0, p);
p = 0;
func_8002D4C8(0x531, 0);
...
func_8012A828(a0, &D_801C00D0);
```
The dead `p = 0` kills the cse equivalence so the second use re-materializes. And the first use: the address is materialized into a1 directly at the call? In mine, it materialized into s0 then moved to a1 — because the pseudo was live across the call. With `p = 0` after the first call, p's live range ends at the call, so local-alloc can put it in a caller-saved reg... but will it be a1? The `move a1,s0` in mine suggests the pseudo went into $16 and then copied into a1 for the arg. Target: `lui a1; addiu a1` direct.

Hmm, so I want the address materialized directly into a1 (the arg reg). That happens when the pseudo's only use is the call arg — reload/caller-save.

Let me just try: replace the launder line + first call with:
```c
                p = &D_801C00D0;
                func_8012A828(a0, p);
                p = 0;
```
and keep the second call direct. Wait but then the second call's address is still CSE'd? cse processed the first use of the address into p; after `p=0` the class dies. The second `&D_801C00D0` is a new use → re-materialized. Good.

But hold on — is the target's first use `lui a1/addiu a1` then call? Yes:
```
188 lui a1,0x0
189 addiu a1,a1,0
190 move a0,s0
```
Wait, from the diff: target lines 188-190 are lui a1, addiu a1, move a0,s0. And mine 189-191: move a0,s1; --; move a1,s0. Hmm, mine has no lui/addiu at the second site because it reuses s0.

Let me check the first site: mine 169-172: move a0,s1; lui s0,0x0; addiu s0,s0,0; move a1,s0. Target 169-171: move a0,s0; lui a1,0x0; addiu a1,a1,0.

So in the target, the first site materializes the address into a1 (with a lui+addiu = symbol address) and the second site does too. In mine, it's materialized once into s0 and reused.

Great, so the dead-reset should fix both: the first materialization would go into a temp (maybe $3 or a1) and the second re-materialized.

But careful: does that also change the s0 assignment? The conflict with $16 disappears once r147 no longer gets $16 → the param takes $16, loop ptr $17... wait, but target wants ent $17 and loop ptr $18. Hmm! Target (with pin): a0 $16, ent $17, loopptr $18. Lever-free: a0 $16, then next by priority = loopptr (7714) → $17, then ent (2500) → $18. That gives a0 $16, loopptr $17, ent $18, but target has ent $17 and loopptr $18.

Hmm. But wait — the target has loopptr pinned at $18. Lever-free without the pin, we need loopptr to land at $18 too, i.e. *after* ent. Since ent's priority (2500) < loopptr's (7714), loopptr would take $17. So even with the address fixed, we'd get loopptr $17 / ent $18 — a swap vs target.

Unless the loop pointer's priority drops below ent's. ent = 3 refs live 12 insns → 2500. loopptr = 9 refs live 35 → 7714. To get loopptr below 2500, it needs live_length > 36 (9 refs: floor_log2(9)=3, 3*9/live*1e4 = 270000/live; for <2500 need live > 108). Or fewer refs: with 5 refs, floor_log2(5)=2 → 2*5/live*1e4=100000/live; live 35 → 2857, still > 2500. Hmm.

Wait, but the target's loopptr is in $18 because of the pin. If I can't move it naturally, then... the target ordering is: a0 $16, ent $17, loopptr $18. Is there a plain-C way to make loopptr's priority lower than ent's?

Alternative: reduce loopptr's live length or refs. E.g., use a different variable for the `ent` computation... no.

Hmm, hold on. Let me reconsider: maybe with the address conflict fixed, the whole allocation changes (fewer insns, different live lengths). Let's just test.

Actually, let me reconsider whether ent is really r80 (3 refs live 12, crosses 1 call). Yes: ent = (s16*)(s2+2), used in func_8012BC60(s3, ent) and func_8012B6D4(s3, ent). 3 refs (1 set + 2 uses), live 12.

Priority ent = floor_log2(3)=1 → 1*3/12*1e4 = 2500. And r80 has size... allocno_size is 1 for pointers. Fine.

loopptr: 9 refs, live 35 → 3*9/35*1e4 = 7714.

To flip: need loopptr pri < 2500 → live > 108 or refs ≤ ... With 6 refs: floor_log2(6)=2, 2*6/35=0.34→3428. With 5 refs: 2*5/35=2857. With 4: 2*4/35=2285 < 2500! So if loopptr had 4 refs and live 35, it'd be below ent.

Hmm, the loop: `s2 = D_801202A0; s5 = s2 + 0x3240; if (s2 != s5) { s3 = a0+4; L: ent = (s16*)(s2+2); if (*s2 == 0xF2) {... unkCC = (s32)s2 ...} s2 += 0x86; if (s2 != s5) goto L; }`.

Refs of s2: init set, use in s5 = s2+0x3240, test s2 != s5, *s2, s2+2, (s32)s2, s2 += 0x86, test s2 != s5 → 8 refs + maybe. It reports 9.

Alternatively, increase ent's priority: ent with more refs. If ent had 4 refs (live 12): floor_log2(4)=2, 2*4/12 = 6667 > loopptr 7714? No, 6667 < 7714. 5 refs live 12: 2*5/12=8333 > 7714. Yes! So giving ent one or two more refs would push it above loopptr.

But adding refs to ent changes the code. Hmm. Alternatively reduce loopptr's live length below 35... increasing priority. No.

Alternatively: make s5 and s2 the same? No.

Hmm, wait. But maybe the whole thing is moot: maybe once the $16 conflict is gone, the *order line* itself changes because the number of allocnos crossing calls changes, and local-alloc gives different regs... Let me just test the dead-reset fix and see the score. Empirical beats theory.

Let me apply: replace the launder-blank + call with the dead-reset pattern.

Current win.c (goto version) around lines 100-116:
```
                void *p;
                ... stores ...
<blank>
                func_8012A828(a0, &D_801C00D0);
                func_8002D4C8(0x531, 0);
                func_8002D4C8(0x526, 0);
                func_800291C8(0xA, 0x3025);
                func_8012A828(a0, &D_801C00D0);
```
New:
```
                void *p;
                ...stores...
                p = &D_801C00D0;
                func_8012A828(a0, p);
                p = 0;
                func_8002D4C8(0x531, 0);
                func_8002D4C8(0x526, 0);
                func_800291C8(0xA, 0x3025);
                func_8012A828(a0, &D_801C00D0);
```
Hmm, but is `p = 0` a "launder"? No — it's a dead reset (C0414), real C, no lever. It's a plain assignment that flow deletes as dead. Good.

Let me apply and score.
