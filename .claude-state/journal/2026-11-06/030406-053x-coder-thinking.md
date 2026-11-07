---
ts: 2026-11-06T10:04:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VkWKYZDDJKQc50YbMlMh
---
`prev_code == CALL_INSN && nonlocal_label_list != 0` — a block starts after a call ONLY if there are nonlocal labels (setjmp). Otherwise, a call does NOT end a block. So block 0 spans the call. Good.

So s1ang (r75) is local, born and dies in block 0, crosses the call → local-alloc gives it s0.

Now, to make s1ang global, its use must be in a different block. The only blocks are created by labels/jumps. The first branch after the call is `if (u6 == u5) return 0;`. If u6's use were after that branch... but the target has the andi before the bne.

Hmm, so s1ang is local in the original too. Then how did the original get s1ang in s1?

Because local-alloc assigns regs in an order; if some OTHER local pseudo crossing the call took s0 first, s1ang would get s1. In the nopin body, r75 is the only local pseudo crossing a call. But in the ORIGINAL, maybe there was another one — e.g., the original had a different variable live across the call that took s0.

Wait, but the target uses only s0 and s1. d is global (r74) and s1ang is local (r75). Target: d=s0, s1ang=s1. For local-alloc to give s1ang s1, s0 must be unavailable during s1ang's live range. s0 is unavailable if some hard reg 16 is occupied... 

Hmm! What if in the original, d was ALSO local-alloc'd to s0? If d were local, local-alloc would assign d and s1ang in some order. But d spans blocks → global.

Unless... hmm, what if in the original, the divisor copy `move s0,a1` was NOT for a variable `d` but for `arg1` itself, and the divisions use arg1 directly. Wait: if we write the divisions as `iVar4 / (s16)arg1`, then arg1 is used after the call — but arg1 (hard reg a1) is clobbered by the call. The compiler would need to copy it. But the compiler might copy it into a callee-saved reg via a *different mechanism*: the pseudo for `arg1` is `reg/v:SI 5 a1`? No, arg1 arrives in a1 and the compiler creates a pseudo for it. If arg1 is used after the call, the pseudo is live across the call → global. Its def is at the function entry (insn 0?), so it's live from the start. Hmm, that's what d is.

Wait, in the nopin body, insn 6 is `(set (reg/v:SI 74) (reg:SI 5 a1))` — the `d = arg1` copy. r74 is d.

Hmm, what if we DON'T create a separate d, and instead use `arg1` directly in the divisions? Then the pseudo for arg1 would be the one live across the call. The sign extension `(s16)arg1` at the div. Let me think: `q = iVar4 / (s16)arg1;`. The compiler would sign-extend arg1 (sll/sra) at the prologue or at each use? Since (s16)arg1 is a 16-bit value, gcc would emit `sll t,a1,16; sra t,t,16` — but if the sign-extension is at each use, two extra insns.

Actually the target does exactly ONE sll+sra (at 3904/3910) right after the call, before the branches, so the sign extension is hoisted (cse) into one place. So writing `(s16)arg1` at each division would still produce one sign extension (cse merges them). Hmm, maybe.

But the register: if the pseudo is `arg1` (not a copy), its def is the incoming arg (a1) and it's live across the call → global (live across blocks). Its priority: refs? Used in 2 divisions → n_refs ~ 2-3, live length from entry to the divs ~ 40. pri = floor_log2(2)*2/40 = 0.05. s1ang local pri 2857. Global-alloc happens AFTER local-alloc; s1ang already took s0. So d would get s1. Same problem.

Hmm. The problem: s1ang always gets s0 via local-alloc because it's the only local callee-saved-needing pseudo.

Unless the original's s1ang was NOT local. What if in the original, s1ang's use was in a different block? 

Wait — let me reconsider the target asm: the `andi s1,s1,0xfff` at 3908 is right after `sll s0,s0,0x10` at 3904. What if the andi is actually the *last insn of block 0* and the bne starts block 1? Yes. And the load is in block 0. So same block.

Hmm, hold on. Let me reconsider whether local-alloc assigns s0 to the *first* eligible qty or the highest-priority qty. In local-alloc.c, `local_alloc` iterates over qtys in order of `qty_n_refs`? Let me read.

Actually, maybe the order is by `qty_phys_reg` preference or by the order qtys were created. If s1ang is the only one, it gets s0 regardless.

So the original must have had another pseudo crossing the call that took s0. What could that be? Maybe the original code had the `d` variable live-across but ALSO local? No.

Wait — maybe the original used a different source shape where TWO variables are live across the call and local: e.g., `u5` (the ratan2 result) is used after the call (it's in a0/v0). u5 is defined by the call (v0) and used in the block → local, but v0 is caller-saved and the value is used right after the call (no other call between) so it stays in v0/a0. Fine.

Hmm, what about `s1ang`? If the original had `s1ang` AND another local variable live across the call, local-alloc would assign the higher-priority one s0 and the other s1. The target shows only s1ang in s1 and d in s0. If the "other" is d... but d is global.

Hmm, wait! Unless d is NOT global in the original. Let me reconsider: if `d = arg1` is assigned in the prologue and used in the divisions in later blocks → live across blocks → global. Unless the divisions are in the SAME block as the prologue. They're not (branches).

OK, radically different idea: what if the original's divisor variable was declared with `register` (K&R style) — no effect.

What if the original used `s16 d` and the sign extension is at the divs... no.

Let me look at the sibling `func_8012B8E4.h` — it's the same body with the pin. Both needed the pin. So the project hasn't cracked it.

Hmm, let me look at whether OTHER shards cracked a `pin $16` on a divisor live across a jal. moves.md line 19: "keepalive,pin | func_800D2A24 | WALL expand-void-return". Line 40: "keepalive,pin | func_80184FB0 | PARTIAL:keepalive,pin expand-void-return". Line 58: "keepalive,pin | func_80140958 | PARTIAL:pin loop-const-hoist".

Let me grep moves.md for "$16" or "s0" pins with MATCH. Also grep for "headers1".

Let me search moves.md for "s0" and "$16".
