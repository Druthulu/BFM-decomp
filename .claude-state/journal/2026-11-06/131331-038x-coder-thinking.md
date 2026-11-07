---
ts: 2026-11-06T20:13:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zkenrOWsPdCoeu8TYbNl
---
For the -1024 constant (a `set reg = const`), which branch? Line 895 is in the "consec sets" branch. Line 791 branch is the general one with savings = n_times_used[regno]. The dump said "Insn 96: regno 90 (life 1), move-insn savings 1". So savings=1, lifetime=1.

Condition to hoist: threshold * 1 * 1 >= insn_count(28) → threshold >= 28.

threshold = (loop_has_call ? 1 : 2) * (1 + n_non_fixed_regs).

The loop has a call (func_8012C588), so factor 1. Without pin: n_non_fixed_regs = 27 → threshold 28 → hoist (28>=28). With pin: 26 → 27 → no hoist.

So we need n_non_fixed_regs <= 26, i.e., one more fixed register. Can't do without a pin... 

BUT: maybe we can make `loop_has_call` false? It's true because of the call inside the loop. No.

Or make insn_count > 28: insn_count is the count of insns in the loop. If I can add one real insn that survives to loop.c and gets removed after... Let's find what deletes insns after loop.c. cse2 can delete dead insns? cse2 is `cse_main` — it may delete redundant insns via `delete_insn` for redundant computations. E.g., a redundant set that cse2 finds already in a register: if I add an insn computing something cse2 can prove redundant, cse2 deletes it. 

Idea: inside the loop, add a redundant load that cse2 deletes? cse2 deletes insns whose result is already in a register (`delete_insn` for redundant expression). But cse1 runs before loop and would also delete it. Unless the redundancy only appears after loop.c's hoisting... circular but possible: the hoisted constant itself creates redundancy.

Alternatively, add an insn that cse1 keeps but cse2 deletes because loop.c changed things.

Hmm, tricky.

Different approach: reduce the *final* extra 3 insns a different way — accept the hoist but make the hoisted constant use a register that doesn't cost 2 callee-save insns? The hoisted constant needs a reg live across the loop: s4 (callee-saved) because the loop is inside a switch and the preheader... Actually the constant is only live inside the loop, so it could be an s-reg (s4). The cost: sw s4 in prologue + lw s4 in epilogue + li = 3 insns vs target's li in-loop = 1. Net +2? The diff said mine 200 vs target 197, so +3 (li, sw, lw) and target's in-loop li counts as 1 — mine also has... no, mine's in-loop store is `sh s4,10(v0)` without li, so mine = target - 1 (in-loop li) + 3 = +2. But score says +3. Let me recount: target 197, mine 200.

Hmm, maybe mine also differs in the register (v0 vs v1) causing... The diff showed: delete mine[40] li s4 (-1 for target), replace mine[51:54] with target[49:52]: mine has 3 insns (lw v0; nop; sh s4,10(v0)), target has 3 (lw v1; li v0; sh v0,10(v1)) — same count. Then + sw s4,32(sp) and + lw s4,32(sp) = +2, and li s4 = +1, total +3, but target has li in-loop which mine lacks: -1 → +2. Contradiction. Unless mine's in-loop block has one extra nop: mine 2150 lw v0,0(s1); 2154 nop; 2158 sh s4,10(v0) — the nop is the load delay slot filler (target has li v0 filling the delay slot). So both 3 insns. Then mine's prologue sw s4 and epilogue lw s4 and preheader li s4 = +3, target's in-loop li = mine doesn't have → -1, net +2. But actual +3. Let me recount by looking at the full disassembly diff — maybe there's another difference (e.g., a nop elsewhere).

Whatever. Let's think about other ways to prevent hoisting.

Idea: make the -1024 store's value *shared* with another use so that the pseudo has n_times_used > 1? That would make savings 2 → hoist more.

Idea: make the constant pseudo `global`? m->global is true if the reg is used outside the loop. If global, there are extra conditions in move_movables for global movables (they must be moved with special care but still can be moved).

Idea: make the store use a *different mode* so the constant insn is not a simple movable: e.g., `*(s16*)... = -0x400;` is movhi_internal2 with const -1024. What if we write `*(u16*)... = 0xFC00;`? Still a movhi with a constant; the RTL would be (const_int 64512) — hoist decision identical (savings 1, lifetime 1) but the value differs → the final `li` would be `li v0,0xfc00` which doesn't match target's `li v0,-1024`. Unless the score normalizes... no, the diff compares text.

Idea: prevent hoisting by making the loop's insn_count larger through *real* code that the target also has but placed differently? The target loop has exactly 28 insns? Wait — target's loop is 197 insns total for the function; the loop body in target has the same instructions as vA except the li. So target's loop at loop.c time might have had 28 insns too, and its threshold was 27 (pin). So the target's source was compiled WITH the pin. Our job is to find lever-free C that produces the same code. The lever's effect is compiler-global (n_non_fixed_regs), so this is likely a genuine WALL: `loop-threshold-fixedreg` — the pin's fix_register lowers n_non_fixed_regs by 1, dropping loop.c's hoist threshold below insn_count so -1024 stays in the loop.

But hold on — maybe there's another real-C way to make the loop.c hoist not desirable: the condition uses `m->lifetime` = uid_luid[last]-uid_luid[first]. If the constant pseudo's first use were earlier (before the loop), lifetime would be larger → MORE hoist. If lifetime were 0? Can't.

What about making the constant's *use* happen twice so savings=2? more hoist.

What about making the constant insn a *conditional* one (m->cond)? Then the condition includes `1 == invariant_p(src)` — still true for a const. Hmm, but then also `m->dependencies == 0 || invariant` and `m->consec == 0 || consec_sets_invariant`. For a simple const set, cond would be... m->cond is set when tem|tem1|tem2 > 1, i.e., conditionally invariant. A constant set inside an if is conditionally invariant → m->cond=1, but the extra checks pass. So still moved.

Hmm what if the store is inside a loop whose preheader can't hold it... no.

What about splitting the loop into two loops via do-while? No.

OK here's another thought: make insn_count bigger by making the loop *contain* more insns at loop.c time that are later combined/deleted by *combine* (which runs after loop). Combine merges insns: e.g., `x = a + 1; y = x + 1;` → combine merges. If I write the loop body with an extra temp chain that combine folds away, the final code is the same but loop.c sees more insns. But careful: the extra insns must not change sched1 or regalloc. Combine runs before sched1, so if combine removes them, sched1 sees the same RTL.

But would cse1 delete them first? If they're real computations used by the store, cse1 keeps them.

Concretely: the store value -0x400. Write `s32 v = -0x400; ... *(s16*)... = v;` — one insn, same as before. To add an insn that combine removes: e.g., `s32 v = 0 - 0x400;` → combine folds to -0x400 in the same insn (no extra insn).

What about a chain: `s32 v = 0x400; ... = -v;` — `li v,0x400` then `neg`? combine folds `neg(0x400)` into -1024? Possibly. That's 2 insns at loop.c time, 1 after combine. But `0x400` constant itself would be hoisted instead (savings 1, lifetime 1) — hoisting the 0x400 and keeping neg in-loop gives `li s4,0x400; neg v0,s4` = 2 insns, worse, and the hoist would happen.

Hmm.

What about making the store value a *computation on a loop-invariant global* that cse2/combine folds? E.g., `s32 v = D_801AECEC;` no.

Let's step back and consider: maybe a completely different C spelling makes the -1024 store not a movable at all. What if the store is written as part of a larger expression where the constant is an operand of an add with a register? E.g., `*(s16*)((u8*)(*p) + 0xA) = -0x400;` — the address computation uses the constant 0xA offset (part of the mem operand) and the value -1024.

What if we express the value as `(s16)(0x400 * -1)`? Constant folding at the tree level → -1024.

What if we use an enum or a static const? Same constant.

What if the value comes from a global variable that is initialized to -1024? Then it's a load from memory, not a constant → not hoistable (unless cse knows the value). E.g., use `D_8019B928`-like table? Semantics: the value must be -1024. A global read would emit `lw` and change code. No.

So: a genuine WALL candidate. But before giving up (need ≥30 tries and ≥20 min), let me consider other real-C routes to the same final code that avoid the -1024 constant being hoisted:

Route: make the -1024 insn appear *after* the loop's last use of... no.

Route: make loop.c's insn_count larger by an insn that survives loop.c but is deleted by *flow/reorg/reload* later. Which passes delete insns? 
- `combine` deletes insns it merges.
- `reorg` deletes nops.
- `flow_analysis` doesn't delete.
- `global_alloc`? no.
- `reload` may.
- `jump_optimize` (jump2, after reload) deletes unreachable code.

So combine is the main one. Can I add an insn that combine merges into an existing insn *without changing the result*? For example, the address computations: `off` is used as `(s32)&D_8019B928 + off`. If I write it as two steps: `s32 a = (s32)&D_8019B928 + off; t = *(u16*)a;` — that's the same RTL (one add). Combine wouldn't change it.

What about making a redundant copy: `s32 t2 = t; ... store t2` — cse1 would propagate the copy (copy propagation) and delete it before loop. Hmm.

What if the extra insn is a `move` that combine turns into a no-op (deleted)? `s32 u = t; use t2 = u` — copy prop in cse1 deletes.

What about an insn that's dead only after loop.c's transformation? E.g., the loop counter `i` — loop.c may convert. Hmm.

Another route: make the hoist *not desirable* by increasing `insn_count` legitimately: the target loop has 28 real insns; if my loop had 29, the hoist wouldn't happen — but then my final code has one more insn... unless that insn is merged by combine. 

Alternatively, reduce `m->lifetime`: lifetime = uid_luid[last_uid] - uid_luid[first_uid] where first/last are the insn UIDs where the register is first defined and last used. For the constant pseudo, first=96 (the li), last=the store (right after) → 1. Can't be less than 1.

Reduce `savings`: savings = n_times_used = 1 minimum.

So the only lever is threshold (compiler-global) or insn_count.

Hmm, wait: what about making `loop_has_call` true→false? threshold doubles if no call in the loop (2*27=54 ≥ 28 → hoist). Worse.

What if the loop contains a call to a function that GCC doesn't know is a call? no.

What about making the constant insn part of a *libcall*? no.

OK, another idea: make the constant not a `CONST_INT` but a `CONST_DOUBLE`/symbol? no.

Alternative: since the -1024 store's base is `*p` (reloaded), what if we write the store to a *different base expression* such that cse keeps the address and combine folds the constant into... no.

Let me look at whether the target's `li v0,-1024` could arise from a *different* C construct: e.g., `CAST_NONSTRUCT(s16, *p, 0xA) = -0x400;` → sh with const. What if the source wrote it as `*(s16 *)((u8 *)*p + 0xA) = -0x400;`? Same.

I think this is a WALL. But the brief wants ≥30 scored tries and ≥20 min for a WALL. I have ~10 tries so far (orig, nopin, vA, vC, vD, vE, vF + a few). Let me spend a bit more on plausible real-C moves before walling:

1. Move the `-0x400` store earlier/later in the loop (statement order) — the target has it between the two table groups; maybe a different order changes insn_count? No, but sched could... no, hoisting is loop.c.

2. Make the -1024 store use a temp that's also used for something else in the loop, making the constant pseudo shared: e.g., reuse the same variable for both -0x400 and -0x92 (the other constant): `s32 c = -0x400; ... = c; ... c = -0x92; ... = c;` Then c has 2 sets in the loop → n_times_set=2 → the movable logic treats consecutive sets (m->consec). For a register set twice with different constants, each is a movable with consec... This could make the hoist less attractive? m->lifetime would span both uses, savings=1. Hmm: with 2 sets of the same pseudo in the loop, `n_times_set[regno]=2`, and in scan_loop, a set with n_times_set>1 goes to `consec_sets_invariant_p` path (line ~870, the else branch), where m->lifetime spans first to last and savings=1. lifetime would be large (both uses) → hoist MORE likely (threshold*lifetime >= insn_count).

3. Make the two constants the same variable but ensure the second set kills the first... no.

4. Use `-1024` as an `unsigned` constant? `0xFFFFFC00` as u32 → li v0,-1024? If the store is `*(s16*)... = 0xFC00;` the RTL const is 64512, final `li v0,0xfc00` (ori) ≠ target addiu -1024. Score compares instruction text — `li` is a macro; the diff might compare the raw word? The score is a COUNT diff over disassembly text. `li v0,-1024` vs `li v0,64512` differ → no match.

5. Make the store value a *variable initialized outside the loop*: `s32 m = -0x400;` declared before the loop (in case 2), then in the loop `= m;`. Then the insn `m = -1024` is OUTSIDE the loop (in the preheader) — the final code: `li s4,-1024` in the preheader and `sh s4,10(...)`. Same as mine (hoisted). Score 16.

6. What if we initialize it inside the loop conditionally? no.

7. Make the loop's insn_count > 28 by making the *loop bound* different? no.

8. Maybe use a `u16`/`s16` store to a different address expression that needs an extra insn at loop.c time that combine folds. E.g., `*(s16 *)((u8 *)(*p) + 0xA) = -0x400;` The address `(*p) + 0xA` is a single mem operand (offset folded). Same.

9. `*(s16 *)(*p + 0xA) = -0x400;` where *p is s32*: offset 10 bytes → 0xA not divisible by 4, so gcc must compute a byte address: `addiu v0, v1, 10`? Actually MIPS allows unaligned sh with offset 10 in the mem operand (offset is in bytes) — the RTL is (mem:HI (plus:SI (reg) (const 10))). Fine, same.

10. Make the constant -0x400 be stored via a wider mode: `*(s32*)... = -0x400`? Target sh (16-bit). No.

Hmm.

Wait wait. Let me reconsider the score. Maybe I can match the target with the hoist if the *register* is one that's already saved. The extra cost is: li s4 (hoisted, 1 insn), sw s4 in prologue (1), lw s4 in epilogue (1), minus the in-loop li (1) = +2. But score says +3 and the diff shows also a register pair diff. The count is COUNT = number of differing instruction positions? "score 16 (COUNT; mine 200 ins, target 197)". The score counts mismatched insns maybe weighted. To reach 0 we need identical text.

So we need the li inside the loop.

Hmm, is there any way to make loop.c see insn_count > 28? What is insn_count exactly: "Loop from 60 to 149: 28 real insns" — that's `insn_count`? Let me check: `insn_count` is counted in `loop_optimize` as the number of insns from loop_start to end (`p != end` count). The dump says 28 real insns. And the hoist condition uses insn_count.

If the loop had 29 real insns at loop.c time, no hoist (threshold 28 < 29). So I need one extra real insn inside the loop at loop.c time that disappears later.

Candidates deleted after loop.c:
- cse2 can delete insns (`cse_main` calls `delete_insn` for redundant sets) — yes! cse2 is a full cse pass; it deletes insns whose values are already available. If I add an insn that becomes redundant *after loop.c hoists something*... 

Actually simpler: an insn that cse1 did NOT delete but cse2 will, because loop.c changed the code. Hmm.

- jump_optimize(2) after cse2 deletes unreachable insns; adding unreachable code inside the loop won't count (loop.c counts real insns between loop_start and end, including unreachable? it counts insns in the range).

Hmm! Interesting: loop.c counts insns between loop_start and end, but it only considers the loop's actual insns. `insn_count` in loop_optimize: let me check how it's computed.

Let me look at loop_optimize.
