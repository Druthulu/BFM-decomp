---
ts: 2026-11-06T17:32:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gDS5okjixaClbNrks1H4
---
In the pinned build, pseudo 75 is NOT in the global list (9 regs, no 75) because it's pinned to $2 (fixed). So the pinned build's sh16 is the fixed reg.

In nopin, 75 is global with "preferences: 3" (v1). The preference comes from local-alloc's combine_regs: 75 tied to a hard reg v1? Or a copy preference.

Where would v1 come from? Look at the nopin final asm: `sll $3,$4,16` — dest v1. The suggestion for v1 might come from... the store `sh v1,242(s0)`? no.

Hmm, wait: in the *flow* dump for nopin, the shift insns' pattern is ashlsi3. For MIPS, ashlsi3 is a 3-operand pattern but gcc's local-alloc may treat it as a 2-address-ish tie: the output must not conflict with the input? The combine_regs call for shift insns uses "may_save_copy=0" and ties the dying input to the output qty. So 75 is tied to 77's qty (if 77 dies at 396). Then 75 and 77 share a qty → same register! In the asm, the first sll is `sll v1,a0,16` — if 75 and 77 shared a register, it'd be `sll v1,v1,16` (source = dest). It's not. So they didn't tie.

The second shift: 147 dies at 419; if tied, `sll v1,v1,16`; the asm shows `sll $3,$2,16` (v1,v0) — not tied either.

So where does preference 3 come from? Maybe from a *different* insn in 75's qty. Local-alloc's qty for 75 might include other pseudos (e.g., a pseudo copied from v1).

I'm burning time (8 min). Let me try a completely different C shape: maybe use a *conditional* to compute sh16 without the two assignments:
```
if (r[0x49] == 5) {
    angle = angle << 16;
}
...
```
no.

Alternative: assign `sh16` a value at declaration (`s32 sh16 = 0;`) then overwrite — adds a def (a `li`?) that may be deleted if dead. If the initial 0 is a def at the top, the pseudo becomes global across more blocks... Try it.

Also try: `sh16 = 0;` right before the if (an extra dead store, deleted by flow but may affect the qty).

Let me try a batch:
a1: `s32 sh16 = 0;` at declaration.
a2: `sh16 = 0;` before the if.
a3: `sh16 = angle << 16;` and in the else `sh16 = p[0x79] << 16;` — current.
a4: use `p[0x79]` for the then arm's source too but with a cast.

Let me run a1, a2.
