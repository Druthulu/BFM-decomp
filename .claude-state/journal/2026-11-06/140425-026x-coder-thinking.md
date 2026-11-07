---
ts: 2026-11-06T21:04:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yxKLHCmwakN9gsC03fgs
---
So at this stage (early rtl, maybe before combine), `a` is (reg/v:SI 4 a0) — a "virtual" register with hard reg 4? Interesting: `reg/v:SI 4` means a virtual register that's been assigned hard reg 4? Actually reg/v is a "user variable" (register variable). GCC represents `register asm` variables as `reg/v:SI 4` — a virtual register that's tied to hard reg 4? Hmm. It's a pseudo with the "user variable" flag and the hard reg 4 as its "alternate".

insn 35: (set (reg/v:SI 4 a0) (reg:SI 85)) — the andi result (pseudo 85) copied into a.
insn 42: (set (reg/v:SI 72) (reg/v:SI 4 a0)) — ang = a.

Then later passes. Let me find where it becomes andi $16. Look at the .lreg dump or .greg. Let me grep the lreg dump for "reg/v:SI 4" and see the allocation.

Actually, the key: `reg/v:SI 4` is a virtual register numbered 4 with the "user variable" attribute and preferred hard reg 4? In GCC 2.7.2, a `register asm` variable's DECL_RTL is `(reg:SI 4)` — a hard register, but the "v" flag might denote "user variable". Hmm, but insn 35 sets it from pseudo 85, and insn 42 copies to pseudo 72. Later local-alloc decides.

Let me look at .lreg (local-alloc) and .greg (global-alloc) dumps for the allocation of these.
