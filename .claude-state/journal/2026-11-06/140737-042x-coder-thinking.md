---
ts: 2026-11-06T21:07:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_e23YgLYMXLNF6Ycxp8B8
---
"Note that the statement below does not affect the priority in local-alloc!" — reg_live_length is used for the priority? Wait the priority formula uses qty_death - qty_birth, not reg_live_length. So reg_live_length*2 doesn't affect priority. So my qty_birth/death calc stands: off birth=2*54-1=107, death=2*81=162? death is 2*insn_number+output_p; for REG_DEAD at insn 81, death=2*81=162. So length = 55. e birth=2*73-1=145, death=2*81=162, length=17. Priority off = 1*3*4/55=0.218; e=1*2*4/17=0.47. e > off.

So e should sort first. Yet off got a0. Unless the qsort ordering is opposite: qty_compare returns pri2 - pri1, so qsort puts... For qsort, comparator(a,b) < 0 means a before b. qty_compare(q1,q2) = pri2 - pri1. If pri1 > pri2, returns negative → q1 before q2. So higher priority first. Good, e first.

Hmm, but for next_qty <= 3, the switch is used. How many qtys in this block? The block (case 5 then-arm) has many pseudos: t (v0? no t is in v0 hard), idx (s0), off, lim, e, and the load results, and p, etc. Probably > 3.

Wait — is the whole function ONE basic block? No, there are branches. local-alloc processes per basic block. The block containing insns 48-104 (the then-arm) has: reg 76 (idx, HI), 88, 95(off), 81(lim), 79(e), 105,108,116, and more. Many.

So e should be first. But it's not. Something else: maybe e's qty got merged with the symbol_ref pseudo used at insn 70's address? No.

Hold on. Let me reconsider: maybe the allocation of off to a0 happened in *global-alloc*, not local-alloc. If off or e is live across a call or has multiple blocks, it's global. But both are local to this block. However, local-alloc only handles "pseudos that die but once". off dies once (at 81), e dies once (at 81). So both local.

Hmm, unless e's REG_EQUIV causes it to be *removed* and rematerialized by reload, and the a1 we see is actually reload's choice. But the .greg dump (after global-alloc) already shows a0/a1 — so allocation done before reload.

Wait, the .greg dump shows hard regs already at insn 54 (a0) and 73 (a1). So global-alloc/local-alloc assigned them.

Let me look at whether e (reg 79) is in a different basic block. Let me check the .flow or .lreg dump for basic block boundaries. In .lreg, basic block boundaries are marked with "(note ... NOTE_INSN_BASIC_BLOCK ...)" or ";; Basic block". Let me grep.

Actually — a simpler hypothesis: reg 79 (e) has REG_EQUIV. In global-alloc, qty for e might be considered replaceable and given no hard reg, then reload rematerializes into a1. But the greg dump shows a1 already... unless greg dump is after global-alloc which assigned a1.

Let me just check the lreg dump: does it show hard regs or pseudo? Earlier lreg showed reg:SI 95, reg/v:SI 79 (pseudo numbers). So lreg dump is BEFORE renumbering applied? GCC -dl dumps RTL where pseudos still numbered. The greg dump shows hard regs. So the assignment happened in local-alloc (reg_renumber set) and greg shows it.

So local-alloc assigned off=a0. Given priority, e should win. Unless qty_birth/death differ. Let me look at the actual qty computation — maybe e's qty birth is much earlier because the REG_EQUIV symbol is also referenced... no.

I'm spending a lot of time. Let me take the empirical route: try variants and measure. I have ~20 more minutes budget for this item (started 13:58). Let me try a batch of variants.

Actually, one strong idea: the target might be produced when `off` is NOT a separate variable but the shift is folded into the address, and the condition uses `off` from the lim address... no, target clearly has sll a1 reused.

Let me reconsider: maybe if `e` is used BEFORE `off` is defined in RTL, e gets born earlier and... no, earlier birth → longer range → lower priority.

To raise e's priority: shorten its live range (define it later, right before use) and/or increase refs. Define e as late as possible: currently e is defined at insn 73, used at 81. That's already just before. But `lim` load (insn 70) sits between. If we move e's definition to AFTER lim (it is) — could move it even later, e.g. define e right at the condition. But the source order: lim then e then if. That's the latest.

Hmm, what if we move e's definition into the if body, right before the condition? Then e born later (shorter range). But it's used in the condition. Let me try:
```
lim = D_801E8F78[idx][0];
if (t < lim) {
    e = (s16 *)D_801E8F78;
    if (...)
}
```
Then e is defined inside the if, born at the start of the then-block → shorter range. But the target's e (lui a0) is placed BEFORE the slt (at 90, before slt at 98). If e is defined inside the if, it would be after the branch, i.e., after beqz, not matching target. So no.

OK here's another thought: what if the two "a0/a1" are actually off and *the loaded value* rather than e? No, the lui a1 is clearly e.

Let me try the straightforward: add a genuine 2nd set of e that survives because e is used in BOTH branches. E.g.:

```
e = (s16 *)D_801E8F78;
...
if (t < lim) {
    if (*(s16*)((u8*)e+off+2) == 0 || ...) idx = -1;
}
if (idx >= 0) {
    ...
} else {
    ...
}
```
e not used after.

What if we change `lim` computation to use e in a way that cse still yields the same asm? `lim = ((s16 (*)[2])e)[idx][0];` — this uses e (a0) + off to address lim. Target uses at (lui sym) + off, not e+off. But maybe cse recognizes e's REG_EQUIV and uses the symbol directly, producing `lui at; addu at,at,a1` — exactly target! Because e is REG_EQUIV = symbol, so the address e+off can be rewritten as sym+off. And using e here gives e an extra ref (insn 70), raising n_refs to 3 and extending... hmm extending birth earlier? e defined at 73 but used at 70 would be a use before def — impossible. So e must be defined before lim. Then e born before lim, used in lim and condition → n_refs 3, range longer.

Hmm, if e is defined before the lim load: 
```
e = (s16 *)D_801E8F78;
lim = ((s16 (*)[2])e)[idx][0];
off = idx*4; ...
```
Then e: def, use in lim address, use in condition = 3 refs; born early, range long. off: 2 uses. Priority e = 1*3*4/long vs off = 1*3*4/short. off shorter → off still wins? Hmm.

This is getting complicated. Let me just test a batch empirically. Variants:
- vA: lim via e cast, e defined before off.
- vB: lim via e cast, e defined before lim but after off.
- vC: use a temp for the loaded value and e.
- vD: swap off/e declaration order (decl only).
- vE: `off` as s16 (halfword index): `s16 off; off = idx*2;` and condition uses `e[off+1]`, lim uses `D_801E8F78[idx][0]`.

Let me write these.

Actually wait. I realize there might be a much simpler lever: the `pad[2]` variable. It's declared but unused (`s32 pad[2];`). In the orig it's there presumably to affect stack/frame? Unused local arrays can affect the frame. But the target has frame? Let me check: the function's prologue. It might not matter.

Let me focus. Let me test the cast variants.
