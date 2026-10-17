---
ts: 2026-10-17T14:09:46.683Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
Three minutes in now. Checking v0: with p initialized before the guard and bumped by two sets, the pointer ends up stored relative to p, consistent with the sw instruction storing at offset 16 from s2. That confirms two sets plus a distant set produce p-relative stores, leaving register allocation to verify—whether p maps to s2 or s0, idx to s0 or s1, and tbl to s1 or s2.

I'm tracing where p's address gets set relative to the guard and the lh loads—if p is set early, it'd conflict with the shared parameter register, so the target likely sets p late, after the lh scheduling. That means cse shouldn't treat p's constant offset as known unless there's an intervening label or branch between p's assignment and the stores, so I'm trying to figure out what control flow could separate them.

I'm considering whether this is a three-iteration loop rather than something unrolled, and whether the scheduler moves the address-load instruction late within the block rather than across blocks. I'm also wondering if cse's knowledge of p's constant value gets invalidated specifically around the call, or whether p's type/struct layout somehow prevents the offset folding that's visible in some stores but not others.

I'm now reconsidering whether cse simply refuses to fold the symbolic address because the cost model on MIPS with -G0 favors a register-plus-offset addressing mode over constructing a lui+symbol address, making the register form cheaper and therefore preferred even when the constant is known.

Actually, I realize the fold isn't blocked by cse's cost logic at all -- it's update_equiv_regs during local-alloc that performs the REG_EQUIV substitution. When there's only one set to p, REG_EQUIV lets later offsets fold into absolute lui/sw forms, but when p is reassigned (initial set plus a bump), REG_EQUIV isn't established, so the accesses stay register-relative. I need to check whether v1, which also has two sets to p, actually folded or stayed relative, since that would confirm or break this theory.
