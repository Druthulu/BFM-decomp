---
ts: 2026-11-07T00:54:29.389Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: af5fe0128a7f156b5
model: claude-opus-5-5
effort: medium
turnId: 02b7900c-695e-429d-929f-6afcc168ca86
---
I'm drafting the c112 brief while P1x runs, covering bank B12 and a TSV pass. The TSV pass needs a script for rows bank_rows won't touch, and W48x's three held WALL rows can be handled by including W48x in the shard list so bank_rows rewrites them. I also need to cover the family rows: four functions times two kinds, eight rows in total.

I'm settling how the parked instruction rows get re-judged: their pass moves to parked (instruction) and the instrument notes there was no lever-free attempt, with the cause tied to the missing C spelling. For the non-instruction kinds in those functions, I'm treating the whole function as walled by its instruction lever, which I'll state in the brief. I'm also dropping the [3.40-agent] suffixes, and for 8015444C I'll have the coder try deleting the dead declaration and gate it, walling the rows with decl-asm-label-order evidence if that doesn't match.

I'm noting that a few singleton rows may still be uncovered after the bank pass, though the held W48x rows, family functions, P1/P1x, G23x, the instruction functions and 8015444C all appear accounted for. I'll leave the non-singleton head-class rows out of scope, since the done-when condition only asks about singletons. I'm also planning to have the coder write a Python script for the TSV pass, and I'll put that in the brief as instructions.
