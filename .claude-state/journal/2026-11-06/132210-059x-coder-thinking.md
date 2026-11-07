---
ts: 2026-11-06T20:22:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_saobDr70HdSCgJt2UGnp
---
`stop_search_p` stops at CODE_LABEL (when labels_p=1) and at ASM_INPUT/asm. So the barrier works because asm stops the search; a CODE_LABEL also stops it (with labels_p=1, used in fill_slots_from_thread at line 1804).

So a real-C block boundary that leaves a CODE_LABEL at the join would stop the search. The join point after an if/else always has a label (the end label). But reorg still copied across it... The bnez is inside the then-arm; its "thread" is the else arm; the xori is after the join label.

Hmm, the search at line 1804: `for (trial = thread; !stop_search_p (trial, 1); ...)` — thread = the else arm start (2190). It scans the else arm: lw (INSN), nop, then the join label? If a CODE_LABEL is at the join before the xori, the search stops there and the xori wouldn't be found. But mine DID copy the xori, so either there's no label there or the path is different.

Wait, maybe the search is on the *fall-through* (own thread) rather than the else thread. Let me look at the structure again. The `if (v == 0) { ...; return; }` then `else { v = ...; }`. The then-arm ends with `return` (a jump to the epilogue). The bnez at 217c is `if (v != 0) goto else_arm`. So the bnez's thread (target) is the else arm.

The xori is after the join. The else arm is: 2190 lw, 2194 nop, 2198 xori. The label at 2190 is the else target. Then after the else arm, the join has no label? The join is 2198/219c which is the fall-through of the else arm — no label needed. So the search from the else-arm thread finds the xori without a label. Hence the copy.

To stop it, we'd need a label or an asm between the else arm and the xori. A do{}while(0) around `v ^= 1;` might place a NOTE_INSN_LOOP_BEG (a NOTE, which stop_search_p returns 0 for) and a JUMP_INSN (stop_search_p returns 1 for JUMP_INSN!). A do-while(0) expands to a loop: NOTE_INSN_LOOP_BEG, body, NOTE_INSN_LOOP_END, and a JUMP_INSN back. With the condition constant 0, the jump is `jump Lend` where Lend is right after — jump_optimize may delete it (a jump to the next insn) leaving a CODE_LABEL maybe.

C0535 says do{}while(0) splits cse1 EBB — so it survives cse1 as a block split. Whether it survives to reorg depends on jump2.

Let me just try: wrap `v ^= 1;` in `do { v ^= 1; } while (0);`. But the brief says: "`do{}while(0)` only with `// !FAKE: do-while`". OK, add the comment.

Let me test that for the barrier.

For the launder (the constant rematerialization), let me try variants:
- `r = 0xFFF80000; r += 0;` no.
- Maybe `s32 r = 0xFFF80000;` → `u32 r = 0xFFF80000u;`?
- What about assigning r to a variable then using it: the rematerialization happens because the pseudo has a REG_EQUAL note with the constant and combine propagates it into the call arg. If we make r a `s16`/`u16`? The value 0xFFF80000 needs 32 bits.
- C0414 dead-reset after the call: `r = 0;`? Since r is a pseudo and dead, deleted. But maybe assign it to something live? 
- Real 2nd set like item 2: `r |= 0;` identity.
- What about `r = 0xFFF80000; r = r >> 0;`? folds.

Hmm. The launder here is `asm("" : "=r"(r) : "0"(r))` — it forces r to be a single register, opaque. The real-C analogue: make r a *variable that is also used later*, so it can't be rematerialized at the call? If r is used after the call (e.g., `v = r;`?), that changes code.

Wait, maybe there's a simpler real-C: the constant `0xFFF80000` as the second arg. What if we write the call as `func_8012B178(q, 0xFFF80000);` directly (no temp)? Then combine would materialize it at the call — probably in the delay slot (same as mine). Target has it earlier.

What makes the target materialize it at the source position? The launder forced the constant insn to be emitted at r's definition and prevented combine from propagating the REG_EQUAL note (because the asm clobbered r's value... actually the asm's output r makes the REG_EQUAL note invalid, so combine can't substitute).

Real C to invalidate the REG_EQUAL: make r's value non-constant from the compiler's view but still 0xFFF80000 at runtime. That's an identity launder (banned).

Alternative: get the same *final code* another way: the target's sequence is `lui a1,0xfff8; li v0,7; jal; sh v0,2(s0)`. Mine: `li v0,7; sh v0,2(s0); jal; lui a1,0xfff8`. The difference is the order of the constant load and the store.

What if we move the store AFTER the call in the source? No — the target has the store's sh in the delay slot, so the store is before the call in the instruction stream. Source order: `((Unk*)s0)->unk2 = 7; func_8012B178(q, r);`.

Hmm, if we set r earlier (before the store), does combine still rematerialize? Combine rematerializes constants at the call if the pseudo has REG_EQUAL and dies. It doesn't care about source position. So the launder is really needed to break the REG_EQUAL.

Wait — actually, is it combine or sched2 that does this? The notes say "the zero-byte re-tie on the $a1 pin (ADD-8 -> §245 addendum, 'the re-tie barrier pins call-arg setup to source order') stops the constant from being rematerialised down at the call." So the launder pins call-arg setup to source order.

Hmm, real-C alternative: make the constant non-rematerializable by giving it a REG_EQUAL that combine won't use: e.g., if the constant is loaded from a variable that's not constant-folded. 

What about making r a parameter of an inlined...? no.

What about using a different spelling that produces the same `lui a1,0xfff8` but as a *computed* value: `r = (s32)((u32)0xFFF80000u);` folds.

Hmm. What if we split the store: the target's `li v0,7` and `sh v0,2(s0)`: the store is before the call. Mine has that too. The only issue is the lui position.

Idea: make the lui not rematerializable by making it depend on the *first* arg q (which is s0): `r = (s32)((u32)q & 0) | 0xFFF80000` — identity, banned.

Idea: use a variable that combine can't prove constant because it's assigned in both arms? They're separate locals r and r2.

Hmm, wait. Maybe I'm overcomplicating: what if `r` is declared as `volatile`? `volatile s32 r = 0xFFF80000;` — volatile forces a stack slot, likely changing code.

What about making r an array element? no.

Let me look at the moves.md for launder cracks involving "rematerialis" or "rematerialize".
