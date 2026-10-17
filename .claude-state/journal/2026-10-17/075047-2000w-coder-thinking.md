---
ts: 2026-10-17T13:50:47.928Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
The clock seems trustworthy enough, so I've got roughly 34 minutes left for pin4. I'm going to dig into how gcc's CSE handles symbol_ref in calls, checking whether the address declared elsewhere in the translation unit plays a role.

Looking at the register allocation details for r177 — it crosses a call, lands in s0, has 3 refs and high priority — I'm wondering whether s0 being free matters here since my target also has s0 free. The real question is whether CSE replaced a set of r178 to the symbol with a set to r177, then combined that copy — in the target, r4 (hard reg a0) gets clobbered by the first call, so the second assignment to r4 must create a fresh pseudo since CSE can't find the symbol in a live register. So to replicate this, the first value needs to either be in a hard register or have its pseudo invalidated, meaning it must be set again — even if that reassignment is dead code, CSE would still process it as invalidating the old value.

But that dead store would normally get deleted by flow's dead code elimination at -O2, which feels too close to an artificial steer I'd already rejected. I want a more natural variant: a register like r4 being reused as a genuine variable for some later purpose, like a pointer to stack data passed to a later call, rather than a throwaway dead assignment — something like a pointer variable set to the symbol, used in one call, then reassigned to point at actual stack data used by subsequent calls like RotTransPers.

Returning a value through a function call doesn't help either since it'd just become a move instruction. I'm starting to doubt natural C can separate these calls unless there's a label trick, so I should check the other TU example to see if its target function has duplicated lui instructions — that would mean cse doesn't merge there, and I need to find that function's name to disassemble it directly.
