---
ts: 2026-11-07T00:08:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_poPb29PEGtS7d6u8o4oT
---
The cse dump doesn't show equivalences. Let me check the .rtl dump instead — it shows the RTL after cse1? The .rtl dump is the final RTL. Hmm.

Actually, a better approach: let me look at the .lreg (after local-alloc) or the .greg for the pinned body to see if t is a hard reg and iVar5 separate.

Actually, the key question: is the copy `iVar5 = t` in the RTL? Let me look at the .sched or .lreg dump for the pinned body. Let me grep for "move" around the loads.

Hmm, let me look at the .rtl dump for func_8012DBD0 in the pinned body and find the relevant insns.

Actually, this is a rabbit hole. Let me take a step back and consider the time budget. Item 2 started 17:01; it's now ~17:20 (19 min). I have ~10 min left on this item.

Given the complexity (params permutation + t + launder + all 141 includers to verify), this is likely a WALL. But let me do a focused set of tries:
1. Try the t as separate per-block temps.
2. Try the param permutations combined with different t spellings.

Actually, wait. Let me reconsider the t issue once more. What if the trick is the *declaration* of t as a variable assigned 5 times — cse sees t as multi-set and treats `iVar5 = t` as a copy it can't equate because... hmm.

Let me just check: in my lever-free body, is the copy present in the RTL? Let me look at the .lreg dump for the lever-free body (w0) and see if there's a copy. Actually, mine's assembly shows `lh s1,4(a0)` — no copy. So cse merged.

Hmm, in the pinned body, the copy exists.

The difference is the hard reg. So cse's make_regs_eqv with a hard reg source must behave differently.

Let me look at cse_insn's handling. Actually, let me look at the code path: in cse_insn, for a `set` of a REG from a REG:
```
if (GET_CODE (src) == REG)
  {
    ...
    if (REGNO_QTY_VALID_P (REGNO (src)))
      ...
      make_regs_eqv (dest, src)
  }
```
Hmm, and there's a check for hard regs: cse doesn't equate a pseudo to a hard reg if the hard reg is "fixed"? Let me grep cse.c for make_regs_eqv call sites.
