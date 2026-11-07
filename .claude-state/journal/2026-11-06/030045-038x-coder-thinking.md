---
ts: 2026-11-06T10:00:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DTbkJs84LaqSpbZjjgmm
---
Priority = floor_log2(n_refs) * n_refs / live_length * 10000 * size. Higher priority = allocated first (gets s0).

For d: n_refs and live_length. For s1ang: n_refs and live_length.

d: defined early (move s0,a1 at prologue), used at two divisions late. Live length is large. n_refs maybe 3 (def + 2 uses) or 4 (the (s16)d copy adds).
s1ang: loaded at 38f0, used at 3908 (andi) — live length small (~few insns). n_refs 2.

So s1ang has smaller live_length → higher priority → gets s0. That explains mine (s1ang→s0).

To make d get s0, we need d's priority > s1ang's. Options:
1. Increase d's n_refs.
2. Decrease s1ang's priority (increase its live length, or reduce refs to 1).
3. Increase s1ang's live_length.

Since s1ang's live length is short (it's loaded right before the call? no — it's loaded at 38f0 before the jal, used at 3908 after). Its live range spans the call, so it must be callee-saved.

Idea: make s1ang live longer (e.g., define it earlier / use it later) to reduce its priority. Or use it more times to... no, more refs increases priority.

Alternatively: reduce d's live length? d is defined at the start (move s0,a1) and used at the divs. If we move `d = arg1;` later (after the jal), d's live length shrinks → higher priority. But the target has `move s0,a1` in the prologue (before the jal). Hmm, so d must be assigned early. But we could have a *different* variable carry arg1 early and assign d late? That would add instructions.

Hmm wait, actually in the target, `move s0,a1` is in the prologue because d is a global-alloc'd variable (live across call) and the assignment `d = arg1` is at the top of the source. If we moved the assignment later, the move would be later — but target has it at the top. So d must be assigned early.

Hmm, so how did the original source get d into s0 with s1ang in s1? Let's compute:

d: def at insn 3 (move s0,a1) [in source order: d = arg1 at top], used at divs (~insn 50, 60). live_length ~ 50.
s1ang: def at insn ~14 (lh s1,18), used at ~21. live_length ~ 7.

pri(d) = floor_log2(3)*3/50 = 1*3/50 = 0.06
pri(s1ang) = floor_log2(2)*2/7 = 1*2/7 = 0.285

So s1ang wins. Yet target has d in s0. So the original source must have made s1ang's priority lower or d's higher.

Wait — unless in the target, `d` is NOT a global-alloc variable. Hmm, d is live across the jal, so it must be callee-saved. Unless... the original used a `register` variable or the compiler put it in a callee-saved reg via local-alloc? No, live across call → global.

Hmm, wait: maybe in the original, `d` had more refs. Look at the target: `sll s0,s0,0x10` at 3904, `sra s0,s0,0x10` at 3910. So d = (s16)d is a separate copy. And d is used in 2 divs. So n_refs(d) = 1 (move s0,a1) + 1 (sll) + 1 (sra, the def of the narrowed d?) ... 

Actually the `d = (s16)d` creates: sll s0,s0,16 (uses d, defs d) then sra s0,s0,16 (uses d, defs d). Hmm, that's 2 instructions for the sign-extension (sll+sra) because it's a 16-bit sign extension of a 32-bit value.

Refs: d = arg1 (def); sll uses d (ref); sra defs d (ref); div uses d (ref) ×2. So n_refs ~ 5. live_length from insn 3 to insn 60 ~ 57.

pri(d) = floor_log2(5)*5/57 = 2*5/57 = 0.175.
s1ang: n_refs 2, live 7 → 0.285. s1ang still wins.

Hmm. So how did the original get d in s0? Maybe s1ang had a longer live range in the original source. E.g., if s1ang was defined before the jal and used after more code. In the target, `lh s1,18(v0)` at 38f0 is right before the jal; used at 3908. That's the live range. 7 instructions.

Unless the original source's s1ang variable had a longer live range but the register was reused... no, live range is computed from the RTL, which matches the asm.

Hmm, so maybe my priority calc is off, or the allocno_size differs, or the allocno ordering includes other pseudos.

Wait — maybe `d` and `s1ang` are not in the same allocno... they are separate.

Alternatively, maybe the difference is `local-alloc` not global: `d` might be allocated by local-alloc if it's not live across the call? No, it is.

Hmm, but actually: in global-alloc, the pseudos live across calls are the ones in the global set. s1ang IS live across the jal (loaded before, used after). d is live across. Both global.

Let me reconsider: maybe the priority formula uses `reg_n_refs` counted differently (each insn occurrence, including defs). Let me instead empirically try C variations.

The most promising C-level lever: make s1ang's live range longer, or reduce its refs. E.g., avoid the separate `s1ang` variable by folding `s1ang & 0xFFF` — but the load must still happen before the call and the mask after. If we inline the load into u6's computation after the call, the load would be after the call → different code. No.

Alternative: change the order: compute u6 before u5? The target order: u5 = ratan2(...); d=(s16)d; u6 = s1ang & 0xFFF. In the target, `lh s1,18` is before the jal, and `andi s1,s1,0xfff` after. So s1ang is loaded early (hoisted before the call by sched1? or source order?).

Wait: in the source, `s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);` comes BEFORE the u5 = ratan2 line. So the load is before the call in source order. Yes.

Hmm OK. Let me look at what makes the priority different. Maybe `allocno_size`: for DImode etc. Both SImode (size 1).

Let me try an empirical approach: test variants and see which gives s0 for d.

Variants to try:
A. Declare d as `s16`? No — d is used as a divisor; the target sign-extends it with sll/sra, suggesting it's s32 holding a s16 cast. If d were s16, the sign extension would be implicit at use sites (maybe the same sll/sra). Let me consider: `s16 d = arg1;` then `q = iVar4 / d;` → division promotes d to s32 with sign extension at each use → two sign extensions (2 extra instructions) unless cse. Hmm.

B. Reorder: move `s1ang = ...` after the u5 computation? But then the load might be after the jal (bad).

C. Add a use of d before the call to increase refs: e.g., `d = arg1; if (d == 0) ...`? adds code.

D. Make s1ang live longer by using it after the branches? no.

E. Change `s1ang` to be computed from a different expression that has more refs but same code... 

Hmm, what about the `register` keyword? The pin uses `register ... __asm__("$16")`. Without asm, plain `register s32 d;` doesn't pin. But maybe `register` changes allocation priority? In gcc, `register` variables get REG_LIVE_LENGTH... no, but they're preferred? Actually local-alloc/global-alloc treat register decls the same; only `-ffixed` or explicit reg names matter.

F. Declare d at the top but assign `d = (s16)arg1;` at the top (instead of `d = arg1` then `d = (s16)d` later). Then the sign extension happens at the prologue: `move s0,a1; sll s0,s0,16; sra s0,s0,16`. But the target has `sll s0,s0,0x10` at 3904 (after the jal), not in the prologue. So no.

G. What if we assign d in two places to raise refs? e.g. `d = arg1; ... d = (s16)d;` is what we have.

Hmm, let me reconsider the priority numbers. Maybe I should just read the actual RTL/dumps to see n_refs and live_length. There's tools/cc1_dumps_tu.sh and hdump.sh (header pass dumps). The brief says use hdump.sh for header pass dumps. Let me use hdump.sh to see the greg dump with allocno priorities.

Let me check hdump.sh usage.
