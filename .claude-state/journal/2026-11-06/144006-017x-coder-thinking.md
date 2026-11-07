---
ts: 2026-11-06T21:40:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_D3ynmt5CPCbENeNH2SFR
---
So local-alloc qty priority = floor_log2(n_refs)*n_refs*size / (death-birth). Higher priority allocated first (gets the lowest free register in class, likely $3 before $4 since registers allocated in order and $2 is taken? Actually $2 v0, $3 v1, $4 a0...).

find_free_reg tries registers in a specific order; for local-alloc it scans hard regs from `regs` order. In local-alloc.c find_free_reg:

```c
  for (i = 0; i < n; i++)
    {
      ...
      for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)
	if (TEST_HARD_REG_BIT(regs, regno) ...
```
Actually it uses `regs` from `reg_class_contents`. Order is regno ascending, so $2, $3, $4, ... but with `regs` mask restricted to class. Since $2 (v0) is probably already used by something (the packet pointer? pkt in v0?), $3 given to first qty.

Wait: the diff shows target has oidx in $3, tag in $4. Mine has tag in $3, oidx in $4. Higher priority gets $3.

So we need oidx's priority > tag's priority. Currently tag wins. Ways: increase oidx n_refs (refs) or reduce life (death-birth), reduce tag's, or change size (mode).

n_refs is from reg_n_refs computed in flow. The tag value is `*(u16 *)(base + 0xA3D2)` used twice — but flow counts refs weighted by loop depth. oidx also twice. Both HImode? tag is u16 load (HImode), oidx is s32 (SImode). qty_size = size in words: SImode 1? HImode 1? For 32-bit ints, size is 1 (one word) for both SI and HI. qty_size is the number of hard registers? In alloc_qty, size passed = `reg_size[regno]`? Let me check: qty_size[qty] = size where size is from `reg_size` (in words). Both 1.

Priority = floor_log2(n_refs)*n_refs*size/lifetime. floor_log2(2)=1, so pri = 2/life for both. The one with shorter life wins. oidx is computed at 166 and dies at...? tag computed at 162? Hmm.

Actually wait: which insn births first? mine insn 162 lw v1,0(a3) — that's tag load, and 166 lw a0,20(sp) is otz load. So tag is born earlier, dies earlier or later?

Both used in the same two expressions (index for D_800A6614 load at 187/188 and otp store at 193). Actually oidx is used twice (both index computations), tag is used twice too. Their live ranges both from birth to last use ~189/193.

Hmm, but death/birth: oidx born at 166 (lw otz) maybe earlier: oidx = g.otz<<2 is computed at 166-170. tag: addiu a3 (base+0xA3D2) at ~160, lw at 162. So tag born slightly earlier. Lives: tag from 162 to 189 (lw v0,0(a0) uses index), oidx from 166 to 189. So tag's lifetime longer → lower priority → should get $4, and oidx $3. But mine has tag in $3! So maybe n_refs differ.

Wait, the diff shows mine insn 162 lw v1,0(a3) = tag in v1($3) — so tag got $3. So tag's priority > oidx's. Perhaps because oidx is dead after the first use and recomputed? Let's look at the disassembly more carefully. mine 166 lw a0,20(sp); 170 sll a0,a0,2; 172 addu v0,a0,v0. So oidx in a0($4) and used immediately. Then 176-179 uses v1 (tag): and v1,v1,a2; or v1,v1,v0; sw v1,0(a3). Wait that's the first packet store `*(u32*)pkt = (*(u32*)pkt & 0xFF000000) | (D_800A6614[idx] & 0xFFFFFF)`? Hmm.

Let me get the full mine disassembly. I'll use --keep and objdump.

Actually maybe there's a simpler framing: the notes already tried "Widths (oidx s16/u16/u32), an explicit tag temp, oidx inlined / moved / cast, and the tail statement orders all stay at 13-16." So many moves tried. I need something new: change n_refs or live range of one qty.

Ideas:
- Add an extra use of oidx in a way that increases n_refs without changing code: e.g., reuse oidx for a second thing. n_refs counts register references in RTL; using oidx again (as the value stored somewhere) adds refs. But that changes code.
- Reduce the tag's n_refs: compute tag via a different expression so it's used once? But it's needed twice. Could hoist the tag into a temp declared u16 → but then the temp has 2 refs same. Could compute `tag << 14` once into a variable and use that variable twice: then tag has 1 ref, the shifted var 2 refs (but then the shift var maybe gets $3). Hmm.

Wait, note says "an explicit tag temp" tried, stays 13-16.

Let me look at target ordering to understand which register is which. Actually the key: target oidx $3, tag $4. Since both are used in the two index computations, maybe target's oidx is a *different quantity* with more refs: In target, oidx might be computed as `g.otz << 2` once and used 4 times? The source: 
```
oidx = g.otz << 2;
*(u32 *)pkt = (*(u32 *)pkt & 0xFF000000) | (*(u32 *)&D_800A6614[oidx + (*(u16 *)(base + 0xA3D2) << 14)] & 0xFFFFFF);
otp = (u32 *)&D_800A6614[oidx + (*(u16 *)(base + 0xA3D2) << 14)];
*otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
```
The two identical address expressions: cse would common-subexpression-eliminate them into one? In the target, maybe the address is computed twice (lui/addiu pairs at 180-181 and ...). The diff shows mine 180-181 lui v1 / addiu v1 vs target lui a0/addiu a0 — that's the D_800A6614 address in the tag register? Hmm.

Let me just dump both disassemblies. Use --keep.

Actually, the target disassembly can be found via the build artifacts. dt.sh runs delever_search --try; the target is from build/. Let me find the reference .s. Search build dir for ov_SC06_029.

But simpler: use `--keep` on the scoring and objdump the candidate. And for target, maybe `--explain` prints more. Let me try --explain.
