---
ts: 2026-11-06T04:10:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Dl1rseAvRYlirQuuLOlb
---
Pass order: jump_optimize → cse1 → delete_dead_from_cse → jump_optimize → loop_optimize → cse2 → ... → combine → sched1 → ...

Dead code elimination (flow_analysis) runs BEFORE combine (line 2983) — and `delete_dead_from_cse` runs right after cse1. So a dead assignment x = t would be deleted by delete_dead_from_cse AFTER cse1 — too late? No: cse1 already ran and did the invalidation; delete_dead_from_cse removes insns whose results are unused, but the invalidation effect on cse1 is already baked in (cse1 made its decisions during the pass). So a DEAD reassignment could work: cse1 sees the dead `x = t` insn (it exists during cse1), invalidates x's entry, and then the second load isn't forwarded. After cse1, delete_dead_from_cse removes the dead insn. 

So: add a dead reassignment of the same C variable between the two loads! But will the front-end/expand keep it? At -O0 no, but with optimization, the C front-end (c-expand) may not delete it; GCC 2.7.2 has no early DCE except `-fdelete-null-pointer-checks`? The front-end emits all assignments; dead ones survive to cse1. `delete_dead_from_cse` removes them.

But what dead assignment to write in C? `x = 0;` where x is not used after. In c4, x WAS used (second load assigned to x). Let me instead:
```
s32 x = *(s16*)((s32)s0 + 0x2E);
s32 diff = 8 - x;
t = diff << 9;
x = 0;                          // dead, but cse1 sees it -> invalidates the MEM->x entry
{
    s32 x2 = *(s16*)((s32)s0 + 0x2E);
    ...
}
```
But will the front-end warn/remove `x = 0`? No. Expand emits `(set (reg x) 0)`. cse1 processes it, invalidates x's value, so the MEM entry (whose value is x) is invalidated? Wait: the MEM entry is a table element for the expression `(mem ...)`, and its equivalence class contains x (the register that holds the loaded value). When x is set to 0, cse calls `invalidate(x)` which removes x from the table; does it remove the MEM entry? The MEM entry's value register is x; if x is no longer valid, the entry can't be used for forwarding because validation checks the value register. `lookup` returns the MEM element, then the code searches `first_same_value` for a REG that is valid (`reg_in_table == reg_tick`). If x is invalid, no REG found → no forwarding. 

So a dead `x = 0;` should work, and then delete_dead_from_cse removes the dead set. But careful: `delete_dead_from_cse` might also remove the FIRST load if x is dead? x is used by `diff -= x`, so the first load is live.

Wait, but will combine/sched later reintroduce? The second load stays.

Also, the dead `x = 0` might be removed by jump_optimize BEFORE cse1? jump_optimize doesn't do DCE of register assignments (it does jump-related). The flow_analysis that does DCE runs after combine, so the dead set survives cse1. Good.

But there's a subtlety: `x = 0` might be a `const` that cse records; it sets x to 0 (invalidating x's loaded value). 

Let me test this! c8:
```
    {
        s32 x;
        s32 diff = 8;
        x = *(s16 *)((s32)s0 + 0x2E);
        diff -= x;
        t = diff << 9;
        x = 0;
    }
    {
        s32 x2 = *(s16 *)((s32)s0 + 0x2E);
        *(u16 *)((s32)s0 + 0xE) += (x2 << 6);
    }
```
This is a "dead-reset cse-breaker" (C0414 style!) — the moves.md/C0414 mentions "dead-reset cse-breaker". C0414: "dead-reset cse-breaker; cracked 3 launders in G16x". So this is exactly the documented technique. 

Let me create and score.
