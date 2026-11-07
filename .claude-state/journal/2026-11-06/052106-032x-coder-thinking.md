---
ts: 2026-11-06T12:21:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FsnHd6yCI3dlHnAuwRKy
---
Candidate wall tag: `combine-copy-merge` (combine merges a reg copy the target keeps, so the pin stays) or `cse-copy-merge`. Our situation: cse/copy-prop merges the copy. Hmm, `cse-copy-merge`: "cse merges a copy the target keeps in its own reg (G22x)".

But let me try a few more shapes before walling. Time check: started ~05:13, now maybe 05:30.

Let me try the trick of making the copy non-mergeable via a real 2nd set on the LATER value: e.g., the later tests use `a1s` where a1s = arg1 computed as a real operation that gcc can't merge but still emits `move`? Hmm.

Wait, here's a thought: the target's copy `move t3,a1` happens because the asm clobbers a1. What if instead the first test's computation is `arg1 & 1` assigned to a variable that is *stored* or used such that gcc assigns it a1? The andi could be allocated a1 if a1 is free at that point. a1 is free if arg1's value doesn't need to survive... but it does.

What if the later uses re-read arg1 from a global? No.

Alternative: change the C so the later tests use a *different source* that yields the same value: e.g., store arg1 into a global early and read it back later? That changes memory (not allowed semantically).

Hmm.

Actually, let me reconsider the problem: maybe we don't need the copy at all if the LATER tests are rewritten to not need arg1's full value. The later tests are:
```
if (arg1 & 0x8000) { ... }
...
if (arg1 & 1) { ... }
```
Both use only bits 15 and 0. The first test uses bit 0. Could we compute the flags differently? The target code reads t3 (the copy) for these. To match, we need a register holding the value. 

What if we compute a single mask `m = arg1 & 0x8001` once and test `m & 0x8000`, `m & 1`? That changes insns.

Hmm, what if the later uses read `(s16) arg1` computed fresh from a1 each time? Then a1 must stay live → no.

Let me try yet another approach: maybe the whole top can differ if we restructure the FIRST test to use a1v as a real second set computed from a *different variable* that happens to be in a1. What other value is in a1? Nothing at entry.

OK here's another idea: gcc's local-alloc might allocate a1v to a1 if a1v is born early and used immediately, and a1v's input is the param pseudo whose home is a1 — with the param's LATER uses forced to another register by a *hard-register conflict*. What creates a conflict? If a1 is also needed by something else (a call's argument or an asm). No calls.

Hmm, actually — maybe the multiply/divide? No.

Let me try: what if we make the first test's andi result be used much later (e.g., move the `if` after some code)? No, the branch is first.

Let me try a completely different C spelling: use a pointer deref to get the low bit? No.

Alternatively: accept PARTIAL? PARTIAL means win.c scores 0 keeping only some levers (kinds still kept). Our kinds are barrier,keepalive,launder. A PARTIAL would keep one of those. E.g., keep the launder (asm) but remove barrier+keepalive. But the launder IS the crux here; if the launder must stay, the result is PARTIAL:launder. That's allowed by the INTERFACES: "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". So I could produce a win.c that keeps the launder asm (and maybe the pins?) but drops barrier and keepalive, scoring 0. But wait, the pins are of kind "pin"? Item 1 kinds: barrier,keepalive,launder (no pin). The pins in the body are `register s32 pos __asm__("$12")` and `register s32 a1v __asm__("$5")` — those ARE pins by kind, but the item's kinds list says barrier,keepalive,launder. Hmm, the kinds file says "barrier,keepalive,launder". The pins are not listed! Maybe because the pins are considered... hmm, "levers of other kinds the def already had (pins under other causes) may stay, never added". So pins may stay (not a row kind for this item).

Oh! That changes things. The pins may stay! Only barrier, keepalive, launder must go. So I can keep `register s32 pos __asm__("$12")` and `register s32 a1v __asm__("$5")` pins, and only remove the launder asm, the two barriers, and the keepalive asm.

But the launder is what makes a1v take arg1's value. Without it, a1v = arg1 (plain assignment) with the pin $5: `a1v = arg1;` where a1v is pinned to $5. That emits `move a1,a1`? Since arg1 is in a1 too, gcc may optimize it away or emit a self-move. Then arg1's later uses... 

Let me try: keep pins, replace launder with `a1v = arg1;`, drop barriers and keepalive. Score it. Since a1v is pinned to $5, gcc must put a1v in a1; arg1 is also a1 (incoming). The assignment a1v = arg1 with both in a1 → no move; then a1v's uses read a1. But arg1's later uses also read a1 → conflict? a1v and arg1 both in a1 is fine (same value, gcc may not know). Hmm, but if a1v is a distinct pseudo pinned to a1 and arg1 is also in a1, gcc would emit `move a1,a1` (or nothing) — but then when a1v is used, a1 still holds the value. Then arg1's later uses also in a1. No copy to t3 needed. That differs from target (which needs move t3,a1).

Hmm, but wait: with the launder removed but pins kept, the pin on a1v ($5) still forces a1v into a1. gcc's local-alloc: a1v pinned → $5. arg1 is a param, its home could be a1. Then `a1v = arg1` → move $5,$5 eliminated? gcc's RTL has a1v as a separate pseudo in $5; a move from $5 to $5 is a no-op copy; gcc might keep it as `move a1,a1` (which the assembler keeps as addu a1,a1,zero). Actually gcc usually removes self-moves.

But then arg1's later uses read a1 (its home). So the code would have a1v and arg1 both in a1 — gcc doesn't know they're the same value but it's fine. No t3 copy → mismatch.

So we'd need arg1's home to be t3, i.e., arg1's pseudo must be moved out. With the pin on a1v ($5), arg1's pseudo might conflict: a1v is live from the assignment to the first test, arg1 live throughout. Since a1v occupies $5 during that range and arg1 also wants $5... a1v is hard-pinned; arg1 is a param with home $5. Conflict! gcc must move arg1 elsewhere: `move t3,a1` at entry! Then a1v = arg1 reads t3 and writes $5 → `move a1,t3`. But target has `move t3,a1` and `andi a1,a1,1`, not `move a1,t3`.

Hmm, target's andi reads a1 (the incoming). If arg1's home is t3, the andi's input would be t3.

So the launder's "0" constraint made the asm read the incoming a1 directly. Without asm, we can't read the incoming a1 if arg1's home is t3.

OK so what if arg1's home IS a1 and a1v's pin forces a1v into a1, and gcc handles the overlap by copying arg1 out before a1v is born, then reading a1 for a1v's input? The input of `a1v = arg1` is arg1 (home a1) → reading a1 is natural; the copy of arg1 to t3 must happen before a1v's birth because a1v's use would... no, a1v = arg1 doesn't clobber a1 (same value). The copy is only needed if a1v's value differs. gcc would just do nothing (or move a1,a1).

So without the asm's opacity, we can't force the copy.

Therefore: keep the launder? But launder is a row kind that must go for MATCH. A PARTIAL keeping the launder is acceptable!

PARTIAL: result = PARTIAL:launder if win.c scores 0 while keeping only the launder (dropping barrier, keepalive, and the pins? pins may stay). Let me try: take orig.c, remove the two barrier asm lines and the keepalive line, keep the launder and the pins. Does it score 0?

Actually the barriers are needed for scheduling (the if-arm store ordering) and keepalive for pos's liveness. Let me test: orig minus barriers minus keepalive, keeping pins+launder.

Let me construct b1.c = orig with the three asm lines removed (barriers x2, keepalive x1). Score.
