---
ts: 2026-11-06T21:22:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cWQFCqpDvYrzepwbiEmT
---
Key insight: without the ap launder, mine uses `move a0,s0` where s0=buf address (materialized once into s0), while target uses `addiu a0,sp,16` (recomputes buf address inline each call). So the launder forces ap into a register (s0) and then moves it, while target recomputes sp+16 inline.

Wait, target uses `addiu a0,sp,16` for the buf argument. Mine uses `move a0,s0` where s0 = addiu sp,16. So the launder's removal makes the compiler materialize buf into s0 and reuse (more moves), whereas target recomputes inline.

Hmm, so actually the launder FORCES ap to be in a register (a pseudo), which then gets coalesced... Confusing. The target (with launder) uses inline addiu sp,16 — so the launder does NOT force a register for the buf uses; it forces ap into a pseudo that the compiler then... 

Wait, target line 50: `addiu a0,sp,16` — this is the ap argument for the FIRST call `func_8017D418((s16*)ap, ...)`. So ap = buf = sp+16, materialized directly as the arg. In mine (no launder), `addiu s0,sp,16` then `move a0,s0`. So the difference: with launder, ap is used directly (inline addiu); without, ap is hoisted into s0 and reused for all calls.

Hmm, that's the opposite of what I'd expect. The launder `ap = buf; asm(ap)` creates a 2nd set that... makes ap *not* CSE-able? Actually the launder forces ap to have a specific value that can't be rematerialized as sp+16? No, target DOES use sp+16 inline.

Wait, target uses `addiu a0,sp,16` for the calls, so ap = sp+16 inline. And later `ap = buf` again before the base+0x80 check. So the launder's effect: it makes `ap` a variable whose value is `buf` (sp+16), but the compiler chooses to recompute inline for each call rather than keep it in a reg. Hmm.

Actually, maybe the launder forces the buf address to be a real pseudo (not directly sp+16), so global-alloc assigns it a reg, but the reg is... no.

This is getting complicated. Let me focus on the counts: l_only has 215 vs 206. The extra 9 come from materializing s0=buf and s4=base and using moves instead of inline addius, plus rematerializing D_801274F0.

Wait, actually the register pairs: s4->s3 x20, s3->s0 x8. So mine uses s4 where target uses s3, and s3 where target uses s0. It's mostly a register shift: mine uses one MORE callee-saved register (s4), pushing the frame from 40 to 44. That's the 1 extra word. And the extra instructions are moves (move a0,s0) vs inline addiu.

Hmm. The p_only (pin removed, launders kept) = 206 ins, score 23 REG-callee. So with launders kept, the count matches. The pin removal causes a callee-saved reg difference.

And l_only (pin kept, launders removed) = 215. So the launders are needed for count.

So both are load-bearing. This is a 2-lever wall likely.

Let me reconsider: maybe there's a real-C restructure that produces target exactly. But with 20-30 min budget, and this being complex, I should decide. I've spent ~8 min on item 3. Let me try a few real-C moves:

For the ap launders: the target wants ap used inline (addiu sp,16) for calls but... Actually wait, let me re-read. Target's FIRST call is `func_8017D418((s16*)ap, (s16*)base)`. Target asm line 50: `addiu a0,sp,16`. So a0 = ap = sp+16. The launder `ap = buf; asm(ap)` — the asm makes ap a "real" variable; the compiler still passes sp+16. 

Then the SECOND call `func_8017D418(buf, (s16*)(base+0x10))` uses `buf` directly → also sp+16. So target passes sp+16 inline both times. Mine (no launder) hoists sp+16 into s0 and moves. So the launder PREVENTS the hoisting. Interesting — the launder (asm) acts as a barrier that prevents the compiler from CSE-ing the sp+16 into a register across calls.

So the real-C equivalent of the ap launder: prevent hoisting the buf address. Hmm, but the asm is what does it. Without asm, the compiler hoists.

Actually, maybe I have it backwards: with the launder, ap is a separate pseudo (2nd set), so `(s16*)ap` uses that pseudo. The compiler assigns it... to a0 inline? The asm output is tied to input, so ap's value is in some reg. But target shows `addiu a0,sp,16` directly for the arg — that could be the asm's output being coalesced into a0 and reload rematerializing sp+16 into a0. 

Without the launder, `ap = buf` and `(s16*)ap` — the compiler CSEs the address and keeps it in s0 across all calls.

So the launder's effect: makes ap a *different pseudo* than buf, so the address isn't shared between ap uses and buf uses. With the launder, ap is one pseudo and buf another. Without, they're the same → hoisted.

Real-C: if ap and buf are distinct variables but the compiler unifies them... To prevent unification, make ap = a *different* expression that equals buf but isn't syntactically buf. E.g., `ap = &buf[0];`? That's still buf. `ap = (void*)((u8*)buf + 0);` folded. `ap = (void*)buf;` same.

Hmm. But maybe we can use a separate copy: `void *ap = buf;` — still unified by cse.

What if `ap` is assigned from `buf` but buf is modified in between? No.

Alternatively: make the calls use `buf` directly for the first (target does) and ap only... no.

This is genuinely hard. Let me check the budget and decide: item 3 started ~14:42. It's a complex 2-lever item. I'll give it until ~15:05 (23 min), trying variants, then WALL.

Let me try a batch of real-C moves:
1. tp as pointer + a genuine 2nd set (2 live sets) to stop rematerialization.
2. ap = &buf[0] instead of buf.
3. Replace ap with a separate stack array? no.

Actually, let me reconsider the tp launder separately. In p_only (launders kept, pin removed) = 206 ins score 23. So the launders are FINE; only the pin is the issue there. Let me look at p_only's diff to understand the pin. Maybe I can fix the pin with real C more easily, and then the launders... but I still must remove the launders.

Given both are needed, and the launders are hard, let me focus on whether the launders can be replaced. The tp launder: target keeps tp in s0. Without it, rematerializes. 

Real 2nd set for tp: `tp = (s32)D_801274F0_8017CF48;` then `*(Blk8*)tp = *(Blk8*)buf;`. What if we compute tp as `tp = (s32)D_801274F0_8017CF48;` and then use `tp` in a way that requires its value in a reg: it already does (the store base and tp-8). The compiler chooses to rematerialize because REG_EQUIV.

To break REG_EQUIV: assign tp from a non-constant. What about `tp = (s32)D_801274F0_8017CF48; tp = tp + 0;`? Folded. `tp = (s32)((u8*)D_801274F0_8017CF48 + 0);` folded.

What about: `tp = (s32)D_801274F0_8017CF48; ... tp = (s32)D_801274F0_8017CF48;` with the first used before the second. Both same constant; cse merges. But maybe if a call intervenes, cse still knows it's constant.

Hmm, what if we make tp depend on `flag` in a way that's value-preserving but opaque: `tp = (s32)D_801274F0_8017CF48 + (flag - flag);` — flag-flag = 0, combine folds.

What if tp = base-related? base = &D_80185FF0 + ... no.

OK, I think this item is a WALL. But let me try one thing: the launders might be replaceable by using a **volatile** read of the address? That adds a load (extra insn).

Alternatively — maybe the intended crack is different: use `buf` directly and avoid ap entirely for the first call, and for tp use a pointer variable with real arithmetic.

Let me look at the whole function's structure and think about what real C would produce the target. Actually, the target was produced by the orig C (with levers). We need equivalent. The levers are doing codegen steering that real C might replicate via different structure.

Given the difficulty and time, let me try 4 quick variants and then WALL.

Variants:
- t1: replace tp launder with a duplicate assignment after the first func_80012F74 call.
- t2: replace ap launders by `ap = &buf[0];` (should be same).
- t3: for tp, declare `u8 *tp` and use `tp[0]`/`tp[-8]` style? 
- t4: remove ap variable entirely, use buf in the first call: `func_8017D418((s16*)buf, ...)` and drop `ap=buf`.

Let me test t1, t2, t4 (each removes levers? no, these are partial). Actually for the final MATCH I need all levers gone. Let me construct full candidates:
- F1: pin removed + launders replaced by t1/t4 style.

Let me build F1: 
- base plain decl
- first call uses buf directly (drop ap for first), and the second `ap = buf` block: drop ap, use buf.
- tp: duplicate assignment.

Actually if I drop ap entirely, the code becomes `func_8017D418(buf, ...)` for the first and `func_8017D418(buf, (s16*)(base+0x80))` for the second. That's t4. Let me test that (with pin removed and tp launder kept? no, must remove tp too). 

Let me be systematic. Build F1:
```
void func_8017CF48(s32 a0) {
    s32 tp;
    s32 base;
    s16 buf[4];
    ...
    L00C:
    base = (s32)&D_80185FF0;
    if (func_8017D418(buf, (s16*)base)) goto L164;
    ... (buf uses)
    base = base + 0x80;
    if (func_8017D418(buf, (s16*)base)) goto L164;
    ...
    LEND:
    tp = (s32)D_801274F0_8017CF48;
    *(Blk8*)tp = *(Blk8*)buf;
    t0 = func(...*(s16*)(tp-8)...);
    ...
}
```
This drops ap entirely and tp launder. Let me test. If the count is 206 and score small, good.

Let me build it.
