---
ts: 2026-11-06T21:21:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OhE3A6BqgHroZEnOv7Cd
---
Only that: mine's move is at 25, target at 24. So mine has one extra instruction before the move (or the move is one slot later). Both are 35 insns.

Let me get mine's full instruction list. I can use delever_search --explain? Or --try --keep and objdump. Simpler: dump the includer TU with the body spliced. But the header include mechanism... tryinc uses a shadow include dir.

Alternative: run the same command with --keep? tryinc doesn't pass --keep. Let me write a small variant: I can run delever_search directly with --try on the includer TU and --body, plus --keep, then objdump the candidate object. But the header is included, so the body must replace the header's function. tryinc handles the rotation.

Hmm, simpler: the diff tells me enough. Mine at 24 is something else, and the move is at 25. Let me guess from the code: after `beqz`, mine probably has `nop` or the `li v0,3072` before the move.

Target:
24: move a0,s0
25: li v0,3072
26: sh v0,16(v1)
27: li v0,1
28: jal
29: sh v0,184(a0)

Mine likely:
24: li v0,3072
25: move a0,s0
26: sh v0,16(v1)
...

So in mine the move is scheduled after the li. Both are in the branch-delay region? The beqz delay slot: target fills it with the move; mine fills it with the li? Then the move comes next.

So the ordering difference: which insn goes into the delay slot. That's reorg's decision (delay slot filling) or sched1/sched2.

The keepalive asm was preventing the move from sinking past the li? Actually the asm made `a` live at that point, forcing the move early.

Lever-free options: change the C so the move is born earlier. E.g., move the assignment `a = arg0;` to the top of the inner if, or before the `if (*(s16*)...< 0xc00)` test. Hmm, the target has the move at 68c0, which is in the beqz delay slot of the *outer* if (after `beqz v0,68d8` at 68bc). Wait: 68bc beqz v0,68d8 — that's the branch of the *inner* if (`if (*(s16*)(q+0x10) < 0xc00)`), since 68b8 is `slti v0,v0,3072` and 68bc `beqz v0,68d8`. Yes: the inner if's branch, delay slot = `move a0,s0`.

So the move is in the inner-if branch delay slot, before the then-block (`li v0,3072; sh; li v0,1; jal; sh`).

In mine, the delay slot is filled with `li v0,3072` and the move comes after. Both are valid reorg choices; the difference likely comes from sched1 ordering (which insn is first after the branch).

Idea: make `a = arg0` happen *before* the branch (hoist it), so it's available for the delay slot. E.g., place `a = arg0;` before the `if (*(s16 *)((u8 *)q + 0x10) < 0xc00)` test. Then the move is born before the branch, and reorg could put it in the delay slot. But would that change the code? The move would be at a different position (before the lh/slti). Hmm, target has the move in the delay slot, which is after the slti. If the move is born before the slti, sched1 might move it around.

Actually, what does the target's source look like? The keepalive asm forces `a` to be live at the asm point (right after `a = arg0`), which is before the store `*(u16*)(q+0x10) = 0xc00` and before `*(u16*)(a+0xb8)=1`. Hmm, the asm is a scheduling barrier in sched1? A volatile asm is a barrier for scheduling.

Without the asm, sched1 is free to move the `a = arg0` copy later (it's only needed at the store and the call). So the move sinks after the li.

To prevent sinking without asm: make `a` needed earlier by a real use. Hmm, but any real use adds an instruction.

Alternative: change the expression structure so the copy is naturally born early. E.g., use `a` (instead of q/arg0) for the store: `*(u16 *)((u8 *)q + 0x10) = 0xc00;` — that's q. The target uses q for the store and a for the other store.

Hmm, what if we compute `a = arg0` at the top of the function (before the outer if)? Then `a` would be live across the whole body. The move would be at the start (after the prologue), not matching.

What if `a = arg0` is placed right after the inner `if` condition is computed? Same as now.

Let me think about the actual scheduling. Mine: `li v0,3072` in the delay slot, `move a0,s0` after. Target: `move a0,s0` in the delay slot, `li v0,3072` after.

Reorg fills the delay slot with the first eligible insn after the branch (with `-O2` and `-mips1`? Actually the target's code uses `.set noreorder` for the branch+delay). The choice depends on sched1/sched2 order: which insn comes first in the stream after the branch.

In mine, sched1 ordered `li v0,3072` before `move a0,s0`; in target, the reverse. sched1 orders by dependencies and priorities. The move `a0=s0` has no dependencies; `li v0,3072` none either.

Hmm, how to make sched1 emit the move first? The keepalive asm was the barrier. Without it, maybe change the order of the C statements: put `a = arg0;` before... it's already before the store. Hmm, but the store `*(u16*)((u8 *)q + 0x10) = 0xc00` doesn't use `a`. The move is only needed for the later store and the call.

What if the store `*(u16 *)((u8 *)a + 0xb8) = 1;` were moved before `*(u16 *)((u8 *)q + 0x10) = 0xc00;`? Then the move would be needed earlier (for the first store) → it'd be scheduled before the li? Let's see the target order: li v0,3072; sh v0,16(v1); li v0,1; jal; sh v0,184(a0). The `sh v0,184(a0)` is in the jal delay slot. So the store to a+0xb8 is after the call setup.

Hmm, if we reorder the C stores, the target order would change (mismatch). But maybe the scheduler reorders them back? Worth a try.

Another idea: make `a` a different variable that's naturally live: e.g., use `arg0` directly instead of `a` for the two uses:
```
*(u16 *)((u8 *)arg0 + 0xb8) = 1;
func_80146CA0(arg0);
```
Then there's no `a` variable at all — and no move! The target has `move a0,s0` because a0 is the call's arg register; the call needs arg0 in a0, so a `move a0,s0` is needed anyway! Wait — the target's `move a0,s0` is exactly the call argument setup (arg0 is in s0; the call needs it in a0). So even without the `a` variable, the call `func_80146CA0(arg0)` requires a move from s0 to a0. And the store `*(u16*)((u8*)arg0+0xb8) = 1` in the delay slot uses a0 (the target shows `sh v0,184(a0)`).

So a lever-free body using arg0 directly might produce exactly the target:
```
if (*(s16 *)((u8 *)q + 0x10) < 0xc00) {
    *(u16 *)((u8 *)q + 0x10) = 0xc00;
    *(u16 *)((u8 *)arg0 + 0xb8) = 1;
    func_80146CA0(arg0);
}
```
But then the pin `$4` for `a` is gone (a doesn't exist). The kinds = keepalive; the pin is a different kind that "may stay, never added". If we remove it (by removing the variable), that's fine — fewer levers.

But will the scheduler order the `move a0,s0` into the delay slot? The move is needed for the store and the call, both after. sched1 might still sink it. Let's test.

Also, maybe we can drop the pin entirely: `register void *a __asm__("$4")` is a pin (kind pin, not in kinds). The instruction says levers of other kinds "may stay, never added" — but removing them is also fine (MATCH = kinds gone; keeping others is allowed). Let me test the no-variable version first.

Let me also consider: maybe with `a` gone, the move appears exactly as target. Test.
