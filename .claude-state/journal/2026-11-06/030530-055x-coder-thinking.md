---
ts: 2026-11-06T10:05:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VQRsMUWNjWY7qry1yiOi
---
Priority = floor_log2(n_refs)*n_refs*size / (death-birth). Higher priority allocated first.

s1ang (r75): n_refs 2, size 1, live 7 → pri = 1*2*1/7 = 0.2857 → 2857.
d is global.

Other local qtys: r72 (refs 4, live 6) → 1*4/6=0.667 → 6667; r78 (refs 10, live 10) → 3*10/10=3 → 30000; etc. But those don't need callee-saved regs (they don't cross calls), so they get caller-saved regs first.

Wait — does local-alloc give a callee-saved reg to a qty that doesn't cross a call? It would prefer caller-saved (reg_alloc_order starts with caller-saved). So no.

For s1ang, caller-saved regs are excluded because it crosses the call. So it picks the first callee-saved in reg_alloc_order. Let me check MIPS REG_ALLOC_ORDER in the reference: mips.h.

If REG_ALLOC_ORDER for GR_REGS is [2,3,4,5,...16,17,...], then the first callee-saved is 16 (s0).

To make s1ang get 17, we need 16 to be taken. Since s1ang is the only local qty crossing the call, 16 is free.

BUT: what if we make d (the divisor) a *local* qty that also crosses the call and has higher priority? d's def is insn 6 (block 0), uses in blocks 2,4,6,7,9 → global. Can't.

What if we restructure so that d is used ONLY in block 0 and later blocks don't use d? The divisions are in blocks 6,7,9. Hmm.

What if we make s1ang's live range LONGER (death-birth bigger) so its priority drops, but it still gets s0 (only candidate). No.

So, to flip, we need a second local qty crossing the call with higher priority than s1ang (2857). Such a qty would take s0, and s1ang would take s1. What local qty could cross the call and be used after? Any variable defined before the call and used after, but NOT used in other blocks (else global).

For example: `s32 tmp;` defined before the call (e.g., `tmp = something`), used after the call in block 0, and not used elsewhere. It must survive to local-alloc (not be dead). And its use must be in block 0 after the call.

But any extra variable+use adds instructions. Unless it replaces an existing instruction/register. Hmm.

Wait — what about `u5`? It's the ratan2 result. In the target, u5 is in a0/v0. It doesn't need a callee-saved reg because v0 isn't clobbered after the call (no more calls). Actually, local-alloc decides based on "crosses a call": u5 is born AT the call (def = call result), so it doesn't cross the call (it's born after the call's clobber). So it's fine in v0.

What about `q`? later blocks.

Hmm, what about `arg0`? It's used before the call only (the loads). So no.

So there's no second local-crossing-call variable.

Hmm, what if we *add* one via a real C construct that the target also has? The target's asm has only s0 and s1 saved. So no third variable.

Wait, maybe the answer is a *copy preference*. Look at qty_sugg_compare: "First priority goes to quantities that have copy preferences". If s1ang has a copy preference for s1, it would be allocated in a separate pass (the sugg pass) and could get s1 even if s0 is free!

How does a qty get a copy preference? When there's a move between the qty and a hard register, e.g., `s1ang = something` where something is in a hard reg. Or when the qty is tied to a hard reg by regmove/caller-saves.

In the target, is there any copy involving s1ang? The load `lh s1,18(v0)` — no copy pref. Hmm.

Unless... local-alloc's "preferences" come from `reg_preferred_class`? No, that's the class.

Hmm, copy preferences arise from `qty_phys_copy_sugg` set when a move insn connects the qty to a hard reg. E.g., if the source had `s1ang = (s32)something_in_s1`.

Hmm.

Alternatively: `regmove` or `reload`?

Let me reconsider. Maybe the original target's s1ang was allocated in a *different* way: maybe it's the `d` that local-alloc gave s0, and s1ang got s1 via global. But d is global...

Wait, unless in the ORIGINAL, d's uses were all in block 0 too! What if the divisions are NOT in separate blocks? Look at the target: the divisions at 394c and 398c are in the two arms of `if (iVar4 >= 0)`. Those are separate blocks. So d is used in ≥2 blocks → global.

Hmm, but what if the original source computed the division differently, e.g., using a helper? No.

Let me reconsider the whole priority: maybe in the original, s1ang had a LOWER priority than another local-crossing qty, OR s1ang was assigned s1 because s0 was live from the START (e.g., a callee-saved reg holding something from the caller). No.

Hold on — maybe I should check: is `d` really global in the target? The target's `move s0,a1` is in the prologue. If d were local, local-alloc would place the copy in the block... but the copy is in the prologue which is block 0. And d is used in blocks 6,7,9 → global. So yes global.

OK, at this point, maybe item 2 is also a WALL (lreg-qty-order or global-pri-bank-order). But let me try some C variations empirically first — maybe a simple restructure flips it. The catalog: decl order/scope, statement order, init at decl, pointer reuse, widths.

Idea: What if `s1ang` is declared as `s16`? Then the load is `lh` (same) but the value's mode is HImode. The `& 0xFFF` would promote to s32 with a sign-extension. Hmm, that changes instructions.

Idea: What if we compute `u6` differently: `u6 = s1ang; u6 &= 0xFFF;`? Same RTL.

Idea: What if we merge `u6 = s1ang & 0xFFF` into the `if`: `if ((s1ang & 0xFFF) == u5) return 0; iVar4 = u5 - (s1ang & 0xFFF); ...`? Then s1ang is used multiple times → higher refs → higher priority (still s0). And the andi might be duplicated.

Idea: make s1ang used in a later block → global. E.g., use s1ang in the division blocks. Hmm, but that changes code.

Wait, actually — here's a thought. What if we make s1ang GLOBAL by using it in a *different block* while keeping the same instructions? The target has `andi s1,s1,0xfff` in block 0 (before the first bne). But what if the source computes u6 in block 0 and ALSO uses s1ang in a later block in a way that's folded? Hmm.

Alternatively, make `s1ang`'s *definition* happen in a different block from its use. The def is `lh s1,18(v0)` before the call, the use `andi` after. Both block 0.

Hmm, unless we introduce a block boundary between them: the call doesn't create one (no nonlocal labels). But a *branch* would. If we put a branch between the load and the use... the target has none.

Hmm OK. Let me look at the keepalive's role again. The keepalive is on `u5`, not s1ang. Let me test: pin removed but keepalive kept. What's the residual? If the keepalive alone fixes everything except the pin... no, the pin is what forces d=s0.

Let me test a variant: pin removed, keepalive kept. And also test: what if I remove the pin but keep `register s32 d;` (no asm)? Probably no effect.

Actually, WAIT. Let me reconsider the possibility that the *original* function is the one in `func_8012B8E4.h` — the SAME body but with globals D_80126CB8/D_80126CB4 instead of D_80126B5E/D_80126B66 and a different signature (s32 arg0, s32 arg1). Hmm, both have pins.

Let me look for a version of this body in a NON-header TU (hand-written) that might reveal the lever-free source. Search for `u6 = s1ang & 0xFFF` — only headers. So no.

Let me try the empirical variations now. Time budget: 20-30 min per item. Let me move fast.

Let me create variants and score them. I'll use sc.sh which is fast (one line each).

Variants for item 2 (all lever-free):
v1 = nopin.c (baseline).
v2: s1ang load AFTER the u5 computation.
v3: `s16 d` instead of `s32 d`.
v4: use `arg1` directly in divisions (no d variable): `q = iVar4 / (s16)arg1;`
v5: d assigned at decl: `s32 d = arg1;`
v6: s1ang declared before d.

Let me write these. Actually, the scoring is against includer 0. Let me use sc.sh with multiple files.

Let me write them quickly. I'll write a small script? No, use Write for each file. That's several Write calls. Alternatively, use a single bash heredoc to create files — but the instructions say use the Write tool for scratch files. Hmm, "Write scratch scripts and notes under .run/ with the Write tool". Creating candidate .c files via bash heredoc might be OK but let me follow the guidance and use Write. To save calls, I'll write a few files in one Bash call using python? That's a shell write. The rule says scripts, not inline python -c. Hmm.

I'll use the Write tool for each candidate. Let me be efficient: write v2..v6.

Actually, let me reconsider the most promising: to flip local-alloc, make s1ang's qty have a *copy preference* for s1. How? If the source loads s1ang through a copy from a hard reg... 

Alternatively, make s1ang's live range LONGER so its priority drops below... no, it's alone.

OK here's a cleaner idea: make `d` local by moving the divisions into the same block? No.

Another idea: make s1ang's use happen in a block OTHER than block 0, e.g., compute u6 in the `if` condition but after a branch. Hmm.

Actually! Here's a thought: what if we compute `u6` *inside* the first `if`? Like:
```
iVar4 = u5 - (s1ang & 0xFFF);   // block 0? 
```
No.

Let me think about the target's `if (u6 == u5) return 0;` — the branch is in block 0. The andi is before it.

What if we restructure as:
```
if (u5 == (s1ang & 0xFFF)) return 0;
```
Same.

Hmm.

Let me look at the actual instruction sequence of the target and see if maybe there's a *different* interpretation: maybe `lh s1,18(v0)` loads into s1, and `andi s1,s1,0xfff` — what if the source variable is not s1ang but the result of a *function call* stored? No.

Let me now consider the "copy preference" route more concretely. In local-alloc, copy preferences come from `reg_preference_for`? Let me look at where qty_phys_copy_sugg is set: in `block_alloc`, when scanning insns, for a `(set (reg) (reg))` or `(set (reg) (hard reg))`. Let me grep.

Actually, a simpler and well-known trick: assigning a value from a function *parameter* creates a copy from a hard reg (a0/a1). If s1ang were initialized from arg1 (a hard reg), it might prefer that hard reg. But s1ang is loaded from memory.

What if we write `s1ang = arg0->unk20->unk12`? same.

Hmm, what if we make s1ang come from a copy of a *hard register* that is s1? There's no s1 value.

OK, let me step back and consider that item 2 might be a WALL (lreg-qty-order). But before that, let me test whether the keepalive removal alone (with pin) changes anything, and the pin removal alone (with keepalive). This tells me if the keepalive is still needed for scheduling.

Let me just do the empirical tests. Write v2, v3, v4 and score.

Actually, let me reconsider something important: the `--explain` residual after removing BOTH levers had score 21, and the diff includes the prologue order AND the register swap. But maybe the keepalive's removal causes the scheduling diff (u5 before sll) and the pin's removal causes the register swap. If I remove only the pin (keep the keepalive), the score might be small (just the register swap). And the register swap might be fixable by C without the keepalive mattering.

Let me test:
- p1: pin removed, keepalive kept → residual?
- p2: pin kept, keepalive removed → residual?

Let me write these two files.

Actually, the ultimate goal is both removed. But knowing the residuals helps.

Let me write p1 and p2 and v2..v5 in one go using the Write tool multiple times. That's 5 calls. Fine.

Hmm, actually let me be smarter. The `--explain --path` option: "--explain: moves to apply first, `|`-separated, named as the trace names them". That's for applying generator moves. Not helpful.

Let me just write files.

Actually, I realize I should reconsider the whole approach: maybe there's a much simpler C change that makes local-alloc choose s1 for s1ang: declare `s1ang` as `u32` or `s16`. Width changes affect size and priority! If s1ang is `s16`, qty_size is still 1 (HImode is 1 reg). Hmm.

What if s1ang's live range is longer because of the declaration position? Live range is computed from actual uses, not decls.

What if we use `s1ang` in the division computation too? That would extend its live range across the blocks → GLOBAL. And then global-alloc would order d (pri 5185) before s1ang (pri lower) → d=s0, s1ang=s1! But using s1ang in the divisions would add instructions (unless it replaces u6, which it does: the divisions use iVar4 = u5 - u6, and u6 is used in the 0x800 adjustments too).

Hmm wait: s1ang is used only via u6. If instead of a u6 variable we used `(s1ang & 0xFFF)` everywhere, s1ang would be used in blocks 2,4,6,7,9 → global. But then the andi would be recomputed at each use → extra instructions. Unless cse hoists it. CSE might keep the andi in block 0 and use the result... Actually cse would create a register for the common subexpression and use it, but that register would be the same as u6 (live across blocks) → global. Then the target's `andi s1,s1,0xfff` in block 0 with the result used across blocks → the result register would be global. But the target uses s1 for the andi result and s1 is callee-saved.

Hmm! That's interesting: if u6 (= s1ang & 0xFFF) is used in multiple blocks, it becomes global. And s1ang itself (used only in the andi) could be local. But the target has s1 holding the ANDI RESULT (andi s1,s1,0xfff — in-place, s1 is both source and dest). So s1ang and u6 share s1 (the andi is in-place because s1ang dies there).

Hmm, if u6 were global and s1ang local, they'd get different regs. Not matching.

Let me look at the target again: `lh s1,18(v0)` then `andi s1,s1,0xfff` then `bne s1,a0`. So s1 = u6 = s1ang & 0xFFF. s1ang dies at the andi. So s1ang is local (short live), u6 is used at the bne (block 0) and in the branches? Let me see: after the bne, `subu v1,a0,s1` at 391c — u6 used in block 1/2. Then `addiu v0,s1,4096` at 392c, `addiu v0,s1,-4096` at 393c. So u6 is used across multiple blocks! So u6 is GLOBAL, in s1.

And s1ang is local, in s1 too (in-place andi). Interesting: local-alloc gave s1ang s0? But the target has the andi in s1... 

Wait, if s1ang were in s0 and u6 in s1, the andi would be `andi s1,s0,0xfff`. The target has `andi s1,s1,0xfff` (in-place), meaning s1ang and u6 share the same register s1. That's possible if local-alloc ties them (copy preference) — the andi's source and dest can be the same register, and local-alloc prefers to coalesce.

Hmm, so in the target: s1ang (local) and u6 (global) both in s1. local-alloc ties the qty of s1ang and u6? They're connected by the andi (a copy-like op where src can be dest). Local-alloc's "copy preference" might tie them.

In the nopin body: r75 = s1ang (local, s0), and u6 is... let me find. In the alloc table, which is u6? Probably r76 or r77 (global). The target's `andi s1,s1` in-place means u6's qty is tied to s1ang's qty.

Hmm, in the nopin body, the residual shows `andi s0,s0,0xfff` (mine) vs `andi s1,s1,0xfff` (target). So mine also has the andi in-place (s0). So s1ang and u6 are tied in mine too (both s0). And u6 global? If u6 is global and s1ang local, and they're tied, then the tie means u6 gets s0 too (the local's reg). So s1ang got s0, and u6 followed.

So the question is exactly: local-alloc gave s1ang s0. If it gave s1, everything follows.

Now, the tie: s1ang (local) is tied to u6 (global) because the andi can write in place. When a local qty is tied to a global qty, the local qty's allocation determines the global's.

So to get s1: local-alloc must give s1ang s1.

Local-alloc priority of s1ang: refs 2, live 7 → 2857. Is there another local qty crossing the call? No. So s0.

Hmm, unless we make s1ang's qty include u6 (the tie) — the tie means the qty has more refs/live length? The qty for a tie group is the union. If s1ang is tied to u6 (global), they might be in different passes.

Hmm, this is deep. Let me just try: what if we make u6's live range or s1ang's refs different.

Let me look at the local-alloc's tie behavior: when a local qty is tied to a global, `qty_phys_copy_sugg` might give it a preference. 

I think the most efficient path now is empirical: try a bunch of C variants and look at the score. Let me write ~6 variants and run sc.sh.

Variants:
1. v2: move s1ang assignment after u5 (load after call).
2. v3: `s16 d;` 
3. v4: no d; use (s16)arg1 in divs.
4. v5: `s32 d = arg1;` at decl (init at decl).
5. v6: s1ang declared `s16`.
6. v7: u6 = s1ang; u6 &= 0xFFF; (split)

Let me write them.

Actually, let me think about which is most likely: The target's local-alloc gave s1ang s1. The ONLY way is s0 unavailable. Since s1ang is the only local-crossing-call qty, s0 must be unavailable because... the qty is tied to a global that has s0? No, global runs after.

OR: `qty_phys_copy_sugg` makes local-alloc allocate s1ang in the "suggested" pass, where it could get a specific reg. If s1ang has a copy preference for s1, it'd get s1.

Where would a copy preference for s1 come from? If u6 (global) is already... no, global runs after.

Hmm, what if the *first* pass (qty_sugg_compare) handles qtys with preferences. s1ang's source is memory, dest is the andi — the andi creates a preference between s1ang and u6's qty. Both are the same qty? If the andi is a 3-operand op (andi rt,rs,imm), gcc's movsi/andsi pattern might allow the output to be the same as input, creating a tie. If s1ang and u6 are tied into one qty, then that qty is global (u6 used in multiple blocks) and local-alloc wouldn't handle it. Hmm, but the dump shows s1ang as a local qty (r75) separate from u6.

OK I'll stop theorizing and go empirical. Let me write the variants.

Given time constraints (20-30 min/item, 4 items), and item 1 is a WALL, let me allocate ~25 min to item 2. Let me write variants.
