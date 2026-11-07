---
ts: 2026-11-06T12:54:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CU9UdYKfOvgv7JFTRBKu
---
p3 = 2, same. p1 = 15 (extra insn).

Hmm, so reordering the source doesn't help: the scheduler still hoists the C64 pair above the sh.

New thought: what if the sh is hoisted by the *branch* into the join? No.

Let me reconsider: maybe the real difference is in the *arm* blocks. In target, arm0's last insns: lhu v0; j 62c; addiu v0,v0,-2 (delay slot). So y = D_801C11BA - 2 is computed in the delay slot of the jump. In mine, is it the same? The diff showed only one region differing, so yes, everything else matches.

So the only difference is the join block's first two/three insns.

What if the y store were the *first* statement in the join block and something else follows that forces the lui/ori down... 

IDEA: What if the C64 store's address expression used the `y` variable? No.

IDEA: Make the C64 store's *value* not a constant but something cse can't build early: e.g., `(mhi | 0x64808080)`? mhi = 0xFF000000; 0xFF000000 | 0x64808080 = 0xFF000000 (no). Hmm.

IDEA: `(0x64808080 & m24)` where m24 = 0xFFFFFF → 0x808080. No.

IDEA: store `(u32)(0x64808080)` via a variable `mhi`-like: e.g. declare `u32 m64; m64 = 0x64808080;` in the decls, then use m64 in the store. Assignment placed where? If placed before the y store, the build is before; if after, sched may still hoist. But a variable assignment creates a pseudo with a live range; local-alloc might assign it a register and the build would be an insn that sets a register. Its priority could be higher (reg-killing) → hoisted even more. Let me try anyway: declare `u32 m64;` and `m64 = 0x64808080;` right before the y store (so the source order matches target: build, then store). Hmm, target has the build AFTER the sh. Let me place the assignment AFTER the sh: `m64 = 0x64808080;` then `*(u32*)((u8*)out+0x4) = m64;`.

Hmm, but then the constant build is a separate insn `li m64` and the store uses the register — same code shape (lui/ori into v1, sw). If local-alloc gives m64 v1... maybe.

Also the register pressure: v1 is used later at 166 `lw v1,0(s0)`. Fine.

Let me try:
- q1: `u32 m64;` decl, `m64 = 0x64808080;` immediately after the y store, store uses m64.
- q2: same but assignment before the y store.

Another idea: make the C64 store the *only* one whose constant needs 2 insns; what if I split it as `*(u16*)(out+4) = 0x8080; *(u16*)(out+6) = 0x6480;` → two sh stores, different instructions. No.

Another idea: maybe the residual is really about the *sh's* placement, and a different y type could matter: y as `u16` → `lhu v0; addiu; sh`. Same.

What about the possibility that the target's sh is a `sh` from a *different* source form: e.g. `*(s16*)((u8*)out+0xA) = y;` where y is s16. Already.

Hmm, let me look at this from the angle of: what would make the lui/ori NOT reg-killing? If the constant build were `addiu`-only... no.

Let me look at LAUNCH_PRIORITY and schedule_insn to understand which insns launch early. Actually, let me check `adjust_priority` (line 2503) — that's the interesting one for "birth boost".
