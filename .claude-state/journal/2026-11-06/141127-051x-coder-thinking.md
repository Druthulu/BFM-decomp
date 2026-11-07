---
ts: 2026-11-06T21:11:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sRkNlY6Xd8WOhG3hpDmF
---
So without the barrier, the `lui a0; addiu a0` (e's materialization) moves earlier (to line 31) vs target (line 36), because sched1 reordered it. The barrier prevented that hoisting. So the barrier is a scheduling barrier that keeps e's materialization after the lim load.

This is a sched1-order issue: sched1 hoists the lui/addiu (e) above the lim load. Target keeps it after. The barrier `__asm__ __volatile__("")` is a memory barrier that stops the load from moving across it.

Real-C way to stop sched1 from hoisting e's lui/addiu above the lim load: create a dependency. If e's computation depended on `lim` (the loaded value), sched1 couldn't hoist it. But e = symbol (independent). Hmm.

What if we compute e from `t` or `lim` in a value-preserving way? E.g., e = (s16*)D_801E8F78 (independent). To create a false dependency: e = (s16*)((u32)D_801E8F78 + (lim & 0))? That's an identity launder — prohibited and folded.

What if the barrier's effect is really about the ORDER of `lui a0; addiu a0` relative to the load, and we can get the same by making e's definition depend on `idx` or `lim`? 

Wait — actually the barrier was between `lim = ...` and `e = ...`. It prevented sched1 from moving the e materialization before the lim load. Alternatively, place the e assignment AFTER the slt `t < lim`? No, target has e before slt.

Hmm. Target order:
- sll a1 (off)
- lui at; addu at,at,a1; lh v1 (lim)
- lui a0; addiu a0 (e)
- slt v0,v0,v1
So e's materialization is after the lim load and before the slt.

Without barrier: e's materialization moved to line 31 (before sll a1? line 31-32 in mine). Let me see the full mine/target around 28-40. mine line 31 lui a0, 32 addiu a0, then presumably sll a1 at 33... and target has nop at 31, sll at 32. So without barrier, e is materialized before off's sll.

sched1 hoisted e's lui/addiu to the top of the block. Why? sched1 schedules by priority; the lui/addiu has no dependencies so it can go early. The barrier (asm volatile, a "memory" clobber? empty asm volatile with no clobber) — actually `__asm__ __volatile__("")` with no outputs/inputs/clobbers is a scheduling barrier for sched1? It's a volatile asm; sched.c treats ASM as a barrier maybe.

Real-C way: introduce a dependency so e can't be hoisted above lim. If e's value depended on lim... but it doesn't.

Alternatively, make the lim load and e's materialization ordered by a data dependency in the other direction: make `lim` depend on e! e.g., `lim = ((s16(*)[2])e)[idx][0]` — then e must be computed before lim. But that changes the instruction count/address (we saw 146).

What if e depends on idx (a value loaded before)? e = (s16*)((u32)D_801E8F78 + (idx - idx))? identity, folded.

Hmm.

Alternatively: prevent sched1 hoisting by giving the block a different structure (do-while split). The do-while around e's assignment might create a scheduling barrier / EBB split. We tried d.c (do-while around e) with the barrier-less win.c (which had the a0/a1 swap too). Let me test do-while with l_only (launder kept) — that isolates the ORDER fix. But ultimately I need both fixed in one body.

Let me reconsider: maybe a single real-C move fixes both. For instance, if e's refs are raised AND the scheduling order changes.

Let me first find real-C that fixes the ORDER (replacing the barrier), using l_only as the base (launder kept). Then find real-C that fixes REG (replacing launder), using b_only as base. Then combine.

Actually, maybe the combined fix is: use a do-while block that both splits the EBB and changes priority. Let me test do-while on the barrier-less win.c (already d.c, score 4 REG). Let me get d.c's diff — is it REG only or ORDER too?

Let me check d.c diff.
