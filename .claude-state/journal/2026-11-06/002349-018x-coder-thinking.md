---
ts: 2026-11-06T07:23:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_M5kQNPq7x7tJl4VsQsUi
---
Score 14. Register shifts: target uses a1,a2,a3 where mine uses a0,a1,a2. So the target keeps $4 (a0) busy at the point of the struct copies — that's what the pin/keepalive did: keep_a0 = arg0 means $4 holds arg0 through those copies; target uses a1,a2,a3 for the loads/stores. Removing the keepalive frees a0, so local-alloc uses a0..a2.

So the pin `keep_a0 = arg0` alone: is it kept? Without the keepalive use, `keep_a0` is assigned but never used — flow deletes it. But register-asm variables: does flow delete a set to a register variable? Probably yes if dead. Then $4 is free. So we need a real C use of arg0 that keeps it live in $4 across the copies... but a use would require the value. Hmm.

Wait — the keepalive is `__asm__ __volatile__("" :: "r"(keep_a0))`. This is an asm with an input operand: it forces keep_a0 live at that point in a register, but empty asm with "r" doesn't require $4 specifically... Actually keep_a0 is a register-asm variable bound to $4, so its "r" operand must be in $4.

To replace with real C: we need arg0 (or a copy) to be live in $4 at that point. The target uses $4 as an argument register — maybe the target actually calls func_800CAF84 with arg0? No, func_800CAF84 takes void.

Hold on. Target: mine[32] insert `li a0,75` earlier than mine. In target, `li a0,75` occurs at 32 (before the store?), mine at 33. So the target sets up `id = 0x4B` earlier. That's a scheduling/order thing.

But the main issue is the register pairs. The target has a0 occupied, so the loads go to a1,a2,a3. What keeps a0 occupied in target? Probably the parameter arg0 is still live in a0 — because target didn't copy it to s0? No: s0 = arg0, so arg0 copied to $16 (s0). After that a0 is dead unless something uses it. But target's `li a0,75` at insn 32 means a0 is being set there. Between insn 10 and 25, a0 must hold something live. What? Possibly the `id = 0x4B` value? No, li at 32.

Hmm, maybe the target keeps arg0 in a0 because the original source passed arg0 to something? Let's look at the actual target disassembly to understand. Let me find the target object. The score tool says "the function in build/". Let me look at delever_search.py to find how it gets target and whether I can dump it. Let me check `--explain` maybe prints full diff with the residual explanation. Actually the diff above is enough.

Let's think: target register usage a0 at insns 10-25 held something. What could be live across the struct copies? The `keep_a0 = arg0` then keepalive at line after copies. The real C original likely had `arg0` used later in the function, e.g. the `func_80146A6C(id, s1, 0, 0, 0, 0x8000, 0)`? No, uses s1.

Or maybe the original kept arg0 for a later `((Unkstruct...*)arg0)->unk1C` access. But s0 = arg0 already.

Alternatively the original source was:
```
s32 s0 = arg0;
...
```
and the copy to s0 might be scheduled late; in target, arg0 (a0) is live until s0 copy? Let me see the full target disassembly. I can get it via delever_search --explain with a path? Let me read the tool's explain output format. Or simply run dt.sh with orig.c and a nonzero score? orig scores 0 so no diff.

Let's find target asm. Check tools/delever_search.py for obj path and a disassembly helper. Maybe there's `tools/objdump` wrapper. Let me grep for "objdump".
