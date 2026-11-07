---
ts: 2026-11-06T11:58:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8sNlUZ0jPqZIegGvh6hz
---
The alloc table shows the .greg order is 72 (arg0 pointer, pri 27826) and 75. The temps r73 (temp_a0? pri 1875, v1), r74 (temp_v0? pri 4285, v0), r90 (reload?, pri 3333, v0, blk1).

Hmm, the temps got: r73=v1 (temp_a0), r74=v0 (temp_v0), r90=v0 (reload). And temp_v1? Let me map: r72 = arg0 (16 refs), r73 = 3 refs (temp_a0: lbu, subu, addiu = 3 refs) → v1. r74 = 3 refs (temp_v0: subu, andi, sb? = 3 refs) → v0. r75 = 8 refs (temp_v1: andi?, negu, 2 sh... = 8?) → no hard reg assigned (dies in 2 places). Hmm.

Wait, the .alloc table might be the pre-sched output. This is confusing.

Actually, the final asm shows temp_a0=v1, temp_v0=a0, temp_v1=v0. The alloc table shows r73=v1, r74=v0, r90=v0. Doesn't match directly.

I'm going too deep. Let me try a different approach: instead of moving a store between, use a construct that invalidates cse memory but produces NO extra instruction and doesn't perturb allocation. 

What about a **call**? No, changes code.

What about making the store's address expression involve a pseudo that cse treats as varying and can't prove equal to the load's address? E.g., store via a pointer variable that is computed before but cse can't equate.

Hmm, we tried q.

What if the load's address uses a **different pseudo for arg0** — e.g., the load is through a parameter copy `u8 *p = (u8*)arg0;` where p is a separate pseudo, while the store uses `arg0`. cse might substitute p=arg0 and equate. But what if p is set from arg0 via a memory round-trip? no.

Hmm.

Actually, maybe I should reconsider: the target's regalloc might be achievable by tweaking the source after adding the intervening store. Since the order is right, I need to fix the regalloc. The alloc table suggests temp_v0 and the reload share v0, and temp_a0=v1. Target: temp_a0=a0, temp_v0=v0, temp_v1=v1.

In y07: temp_a0=v1, temp_v0=a0, temp_v1=v0.

What if I swap the declaration order or change temp types to shift priorities? E.g., make temp_a0 `s32` (x05 gave score 2 with a different shape).

Hmm, let me try: with the intervening store, vary the declaration order of temp_a0/temp_v0/temp_v1, and the types. Let me generate ~10 variants of y07 with different declarations and see if any gives score 0.

Variants:
- decl order permutations (6)
- temp_a0 as s32/u8
- temp_v1 as s32/s16
- temp_v0 as s32/u32
- reload into a separate var

Let me generate permutations of declaration order for y07.

Actually, global-alloc allocno numbers depend on the order pseudos are CREATED, which is by first appearance in the source (declarations and uses). The declaration order matters for the allocno numbers, which matter for ties.

Let me try all 6 declaration orders of temp_a0, temp_v1, temp_v0.

Let me write a generator.
