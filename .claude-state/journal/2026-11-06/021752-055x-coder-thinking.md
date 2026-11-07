---
ts: 2026-11-06T09:17:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3Jzd3Dpmluyxq4yKYdGQ
---
Item 4: the loop with goto. The value v0 = base or 0. If we keep the keepalive but drop the pin, v0 is a plain local. Its sets: v0=(u32*)base in loop, v0=0 after loop. Used by asm at epilogue. Local-alloc: v0's life spans the loop? Its birth is in the loop body, death at epilogue — crosses a block. That's a global pseudo (not block-local) → global-alloc gives it a callee-saved reg, not v0. Hmm, target has it in v0.

Let me just test keepalive-only.

Also the important note: "expand_value_return stmt.c:2505; the TU's extern is void". Hmm, this suggests that if the function had a `return v0;` (value return) in a *void* function, expand_value_return is NOT called (we saw). So the comment may be wrong or refers to something else. Whatever.

Let me test item 4 with pin removed.
