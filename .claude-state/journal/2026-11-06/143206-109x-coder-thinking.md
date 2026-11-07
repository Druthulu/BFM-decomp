---
ts: 2026-11-06T21:32:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6SXubZSKEXk5d5W9cleh
---
None better than 12. b=42, c=10 (119), e=18 (119), d=12.

The pin is load-bearing. This looks like a WALL. But I need ≥20 min and ≥30 tries. Started ~15:15, now ~15:25 (10 min), ~6 tries. Need more.

Let me think harder about the coalescing. Target: n and m in s0. Mine: n in v1, result v0, m in s0.

The reason target coalesces: the pin. Without it, local/global alloc gives n v1.

Is there a real-C way? Let me look at the moves log for "$16" pin cracks. grep moves for "pin $16" or "pin" MATCHes.

Line 280: "launder,pin | func_8019059C | PARTIAL:pin ... $16 src pin redundant". Line 274: "$16 park". Let me grep for "$16" in moves.

Actually, let me reconsider: maybe the crack is to use `unsigned` arithmetic so the modulo is done differently. The target's sequence is the signed modulo (bgez correction). If n is unsigned, `q % 4` would be `andi` (no sign correction) — different.

Hmm.

Let me look at what determines n's register. n is a global allocno (crosses the `if (q<0)` branch). Its priority = refs/live_length. In mine it gets v1 (caller-saved). Global-alloc assigns caller-saved regs first if available (cheaper, no save/restore). To force callee-saved, the allocno must cross a call OR all caller-saved be taken.

So: make n cross a call. The only way without changing the algorithm is to have n live across the `rand()` for the sign. In target, is n live across that rand? Target: subu s0 (n=q%4) at 830, rand at 834, sll s0 at 838, negu at 848. So n (s0) is live across the rand at 834! Because n=q%4 is used in the sll at 838 (after the rand). So YES, n crosses the rand in the target.

In MINE: n in v1, subu v0,v0,v1 at 72, then sll s0,v0 at 74. Wait, mine's sll is at 74 which is BEFORE the rand? Let me check the asm order. The diff showed lines 68-74 and 82-89. Let me see mine's full asm around there. If mine computes sll before the rand, then n is dead before the rand.

So the difference might be: target schedules the sll AFTER the rand (so n crosses), mine schedules it BEFORE (n dead). That's a sched1 ordering difference. If n crosses the rand, it must be callee-saved → s0.

How to make the sll happen after the rand? The source `m = (q - n) << 16; if ((rand() & 1) == 0) m = -m;` — the compiler can compute m<<16 before or after the rand. sched1 decides. If I write `m = q - n;` then `if ((rand()&1)==0) m = -m;` then `m = m << 16;` — then the <<16 is after the negu, and n (q-n) crosses the rand (n = q-n is used after). But target has sll BEFORE negu. Hmm.

Let me look at the actual mine asm to confirm the sll position. Let me get the full asm. I'll use --keep and objdump, or just read the diff which shows line numbers. The diff is instruction-index based (mine[68:73] target[68:73]). Line 74 mine `sll s0,v0,0x10`. What's the rand call position? Let me capture the whole diff and look at the context lines around 74.

Actually, dt.sh shows only replaced lines. Let me get mine's full asm via --keep + objdump. Or use the .s from the dump.

Let me just run delever_search --keep and objdump the object. That's a few steps. Alternatively, I can reason: in mine, line 72 subu v0,v0,v1, line 74 sll s0,v0. If the rand call is at line 73 (between), then n is dead at 72 (before rand) and m<<16 after. Target: subu s0 at 72, rand, sll s0 at 74. So both have rand between subu and sll! Then n crosses in target but not mine (because mine's n is v1, dead at subu; the crossing value is v0 which is caller-saved!).

Wait, mine's subu result is v0 (caller-saved), which crosses the rand. But v0 crosses a call — that's wrong (v0 is clobbered by calls). Unless mine's rand call is BEFORE the subu. Let me check the actual order.

I need the asm. Let me get it.
