---
ts: 2026-10-17T18:46:10.157Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac81395c556dc97c0
model: claude-opus-5-5[1m]
effort: medium
turnId: 2749fb46-32ea-40ac-942d-d9e5fb5596d6
---
I'm tracking the register allocation assignments for block 4's quantities, comparing my version numbers against the target to spot where they diverge, and starting to work through the priority ordering used in local allocation's quantity sort.

I notice K(91) and tmp(90) are tied together through combine_regs at insn 77, and they also connect to 95 via a shared sra operation in both versions. The combined qty {91,90,95} gets v0 in mine but v1 in the target, while M(93) and 94 flip the opposite way — suggesting M has higher priority than the combined quantity in the target's ordering, possibly due to the pin forcing tmp into a hard register.

Working through the local-alloc priority formula, the combined qty's refs sum (7) over its life span gives it a dominant priority ratio compared to M's smaller ref count and shorter life, so M would need significantly more refs or a shorter lifespan to win — something that doesn't seem achievable through direct source changes.

I'm trying to break the tie between K and tmp by reworking the constant subtraction, but since 0xC8000 doesn't fit in an immediate, folding it into the existing dist adjustment doesn't help, and the comparison constant 0xC7FFF is loaded into a different register so it can't be reused via CSE either.

What might actually work is making tmp a global pseudo by having it set and used across both branch arms, since a pseudo referenced in more than one basic block gets allocated with a wider, cross-block liveness class rather than as a short-lived local.
