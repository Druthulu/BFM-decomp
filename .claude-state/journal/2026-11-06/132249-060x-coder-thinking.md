---
ts: 2026-11-06T20:22:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_C2d7QQJJcUTYG5izAfoR
---
Interesting: line 191 gives a MATCH pattern: "the 12 launders on v -> six `v = (s16)v;` real 2nd sets (v is a sign-extended s16, so the cast is a no-op)". Here r is a s32 constant 0xFFF80000. A cast `r = (s16)r;` would change the value. But maybe a cast to a type that doesn't change the value: `r = (s32)r;` — identity (banned as an identity launder? It's a cast, no value change; but the G14 case used `(s16)v` where v is an s16 so it's value-preserving, and they call it a "real 2nd set"). Hmm, `v = (s16)v;` is effectively identity for an s16 variable. They accepted it as a crack (MATCH). So a value-preserving cast that materializes a real 2nd set could count. But the brief says "identity-statement launders (w = (w>>16<<16)|x, identity address spellings) do NOT count as a crack". A cast to the same type might be viewed as an identity launder by the expert.

Hmm. Risky. Better find a genuine one.

Line 212: "the re-tie gives vol a 2nd SET ... plain C: `vol = vol | 0x3000;` right before the call — value preserved because the arg ORs 0x3000 and masks 0xFFFF". That's value-preserving via the surrounding computation. Here, r = 0xFFF80000 is passed directly to func_8012B178. Is there a value-preserving transformation? The callee might mask it, but we don't know. `r = 0xFFF80000; ... call(q, r)` — any change to r changes the argument.

What if we write the constant in a way that produces a 2-set but same value: e.g., `r = 0xFFF80000; r = r;` (self-set, deleted).

Hmm, what about the fact that 0xFFF80000 = -0x80000. `r = -0x80000;` same.

What if r is declared `s32 r = 0xFFF80000;` and then `r = (s32)(u32)r;` — identity cast.

Alternatively, maybe there's another way to get the target order: the launder is about *combine* not substituting. Combine substitutes a constant into a call arg if the pseudo dies there. If r is used a second time (after the call), combine won't substitute (the pseudo doesn't die). We need a 2nd use that emits no extra code... 

What about using r in the *other* arm? Different scope.

What if we make r live by using it in a comparison that flow eliminates? no.

OK here's another thought: what if we assign `r` to a *global* or use it in a store that's already there? E.g., `((Unk*)s0)->unk1C = v;` uses v, not r.

Hmm.

Let me reconsider the first cluster (the barrier) — maybe both clusters can be fixed by one structural change.

Actually, let me look at whether a do-while(0) helps the barrier, and separately try the launder alternatives. Let me test a batch:

vD: barrier → `do { v ^= 1; } while (0);` (with the !FAKE comment), launder still removed. Score?
vE: launder → replace `r = 0xFFF80000;` with `r = 0xFFF80000; r = (s32)(u32)r;`? Identity cast — hold off.
vF: launder → `s32 r = 0xFFF80000; ... call(q, r); ... r = 0;`? 

Hmm wait. Let me reconsider the launder's exact semantics: `__asm__ __volatile__("" : "=r"(r) : "0"(r));` — output r tied to input r. In RTL: `(set (reg r_new) (asm_operands ... (reg r)))` with the constraint that they're the same reg. So r gets a new pseudo, same register.

What if we replace it with a real C 2nd set that's *dead but survives* because it's used by... hmm.

Actually — what about the `q` pin? `register s32 q __asm__("$4") = s0;` — q is pinned to $4. The launder on r prevents rematerialization. What if we pin r to a register? The brief says: "no new lever of any kind" — adding a pin is banned.

What if we make the constant *not* a constant by computing it from `q`? e.g., `r = (s32)((u32)q & 0xFFF80000);` — that's not identity but changes the value if q's low bits... q=s0 (a pointer). 0xFFF80000 & s0 ≠ 0xFFF80000 generally. Not equivalent.

What about `r = 0xFFF80000 | (s32)((u32)q & 0);` — identity.

Hmm, what about making the value come from a union/bitfield? no.

Let me think about the target's actual codegen. Target: `lui a1,0xfff8` at the source position, then `li v0,7`, then `sh v0,2(s0)`, then `jal` with `sh` in the delay slot. Wait no, target:
```
21b8 move a0,s0
21bc lui a1,0xfff8
21c0 li v0,7
21c4 jal
21c8 sh v0,2(s0)
```
Mine:
```
21b8 move a0,s0
21bc li v0,7
21c0 sh v0,2(s0)
21c4 jal
21c8 lui a1,0xfff8
```
So in mine, the constant insn was rematerialized INTO the jal's delay slot, and the store moved up. In target, the constant stays at its source position, and reorg filled the delay slot with the store.

If we prevent combine's substitution (r not dying at the call), the constant stays at its definition, and then sched2/reorg places the sh in the delay slot.

What if `r` is used *after* the call in a way that is already in the code? In the then-arm, after `func_8012B178(q, r); v = 0x20;` — v is set. If we wrote `v = r, v = 0x20;` no.

Hmm, what about making r's second set *inside the same arm after the call*: `func_8012B178(q, r); r = 0;` — dead, deleted.

What if r is a `s32` but we store it to a stack variable that's already there? e.g., `v = 0x20;` and then `r = v;`? That's a real set but adds `move`.

OK, let me look at the problem from the "what does the target source look like" angle. The target was compiled from this source WITH the launder. Our job: find a lever-free body scoring 0. Maybe there's a completely different formulation of this arm that produces the target code without the launder.

E.g., reorder the source statements: `((Unk*)s0)->unk2 = 7;` before `r = 0xFFF80000;`? Then the constant's definition is after the store. Combine still substitutes into the call.

What if we pass the constant expression directly: `func_8012B178(q, 0xFFF80000);`? Then combine materializes at the call → same as mine.

What if the constant is assigned to `v` temporarily? no.

Hmm, what about the `li v0,7` / store order: in target, lui comes first (source position of r), then li v0,7, then jal with sh. In mine, li v0,7, sh, jal, lui.

Wait, actually, is it combine that rematerializes, or sched2 moving the lui down? Let me check the dumps: if the .combine dump shows `lui a1` before the call and .sched2 moves it into the delay slot, then a scheduling fix might work.

Let me dump the pinned orig and the nolau versions and compare .combine/.sched/.sched2.

Actually, quicker: the notes say "the zero-byte re-tie ... stops the constant from being rematerialised down at the call". Rematerialization is combine's `subst` / `try_combine`? In gcc 2.7.2, combine's `subst` replaces a register with its known constant in a later insn if it dies (`reg_dead`). Actually, that's "combine" via `try_combine`? No — the REG_EQUAL propagation into a call arg is done by... hmm, `combine` handles one insn's REG_EQUAL with a following insn. For a call arg, the constant would be loaded into a register; combine could merge `lui a1,K` + `jal` into the jal's delay slot? That's scheduling (sched2/reorg), not combine.

Hmm: `lui a1,0xfff8` then `jal` — reorg puts the lui in the jal's delay slot (it's the last insn before the call and can be moved). In target, the lui is NOT in the delay slot because the `sh` is there instead. So maybe it's reorg: it fills the jal's delay slot with the best candidate; with the launder, the sh is chosen; without, the lui is chosen.

Wait, but in mine the sh is BEFORE the jal (at 21c0) and the lui after (delay slot). In target the lui is before and sh in the delay slot. So both have one insn in the delay slot; the difference is which.

This is reorg's fill: the insn right before the jal is moved into the delay slot. In target, the source order at RTL: r's lui, then li v0,7, then sh, then jal. Reorg moves the *sh* (the insn immediately before the jal) into the delay slot? Actually reorg doesn't move an insn into the delay slot of a following jump unless... The jal's delay slot is filled by reorg's `fill_slots_from_thread`/`dbr_schedule`. The insn before the jal at 21c0 in mine is the sh; reorg moved the sh UP (before the jal) and the lui down? No...

Let me compare RTL. Let me dump .sched2 (post-reload, dbr is after sched2). Actually the .dbr dump shows reorg decisions.

Let me dump the nolau and orig and compare the .dbr/.sched2 dumps for this function. That will show where the order is decided.

Let me do that. Disk: the TU is small? src/ov_SC02_011 file size? Let me check quickly. Dumps ~ a few MB, fine.
