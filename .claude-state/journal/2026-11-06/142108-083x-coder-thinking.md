---
ts: 2026-11-06T21:21:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YZQVbn3W8d4l0L7h5Ln9
---
Score 146, mine 215 ins vs target 206. That's 9 extra instructions. The base pin to $18 was doing a lot: it forced `base` into s2 and the whole register layout. Without the pin, the code is very different (9 extra insns). This is a big residual.

The pin `base = $18` (s2). The target uses s1 for `base`? Let me look: target has `move s1,a0` at line 2, so s1=a0 (the arg). And `base`? Target line 50: `addiu a0,sp,16` etc.

Hmm, this is complex. The pin was NEEDED DIFFERS. Removing it changes a lot.

Let me look at the target's structure. Target 206 insns; mine 215. The pin removal loses the "base stays in a callee-saved reg" behavior.

This is likely a WALL (pin under global-alloc). But let me try real-C moves: the pin was $18 (s2). Removing it, the compiler must still assign base to a callee-saved reg because it's live across calls. The difference is which one and the frame/order.

Given the budget (20-30 min per item) and this is complex, let me first see if a simple real-C change can recover. But 9 extra instructions suggests a structural difference (e.g., the base+0x80 and base reassignment).

Wait, mine has 215 vs 206 — 9 extra. Let me look at where the extra come from. The diff shows the epilogue has extra lui/addiu pairs (mine 180-205). Let me look at the full diff more.

Actually, the key: target uses `sh v0,-8(s0)` where s0 = base-ish (tp?), while mine uses `lui a0; lh a0,-8(a0); sh v0,-8(at)` — i.e., mine rematerializes D_801274F0 each time instead of keeping it in a reg. That's the `tp` launder: `tp = (s32)D_801274F0_8017CF48; __asm__("" : "=r"(tp) : "0"(tp));` — the launder forces tp into a register (a 2nd set), preventing rematerialization. Without it, the compiler rematerializes the symbol address for each use → extra lui/addiu.

So the tp launder is load-bearing: it keeps tp (the D_801274F0 pointer) in a register instead of rematerializing. Target keeps it in s0.

To crack: give tp a real 2nd set that prevents rematerialization. Per C0414/moves: the pattern "split pv = pv & mask" or a real 2nd set. But tp is a constant symbol address. Hmm.

Wait, but target has `lh a0,-8(s0)` where s0 = tp. And tp = D_801274F0. So target materializes tp once into s0 and uses it. Mine rematerializes (lui/lh) each time because REG_EQUIV allows it.

The launder `tp = tp` (via asm) makes tp non-equivalent (2nd set) so it must live in a register. Real C equivalent: a real 2nd set of tp that's live. E.g., compute tp from another variable, or reassign it.

Actually, look at the moves: "launder->real 2nd set" e.g. `vol = vol | 0x3000;`. For a symbol address, what real 2nd set? 

Idea: `tp = (s32)D_801274F0_8017CF48;` then later `tp = tp;`? identity, removed.

What about using `tp` in the store then re-reading? No.

Hmm. Alternatively, use a pointer type: `u8 *tp = D_801274F0...`; then tp[0] etc. But the code does `*(Blk8*)tp = *(Blk8*)buf;` then `tp - 8`. If tp is a pointer, the same.

The launder's effect: make tp a real pseudo (not REG_EQUIV). To break REG_EQUIV with real C, make the assignment non-constant: e.g., `tp = (s32)D_801274F0_8017CF48 + 0;` — folded.

What if tp is computed from `buf`? no.

Hmm, this item has both pin and launder, and it's a big residual. It might be a WALL. But let me try a few things.

First, let me try: remove only the pin, keep the launders (partial), to isolate. And remove only the launders, keep pin. This tells me which lever causes what.

Actually the task requires all row kinds gone for MATCH. But isolating helps understand.

Let me score:
- p_only: remove pin, keep launders.
- l_only: remove launders, keep pin.

Let me generate and score.
