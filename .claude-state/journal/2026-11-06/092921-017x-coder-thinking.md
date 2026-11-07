---
ts: 2026-11-06T16:29:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SVBgIpPOSWNsWFzG8TQF
---
So cross-jump matches backward. With minimum 2. In mine, both arms end in `beqz v0,L; nop` and before that slti... The delay slot nop is an insn. Actually the branch insn's delay slot is separate. So matching backward: [nop] vs [nop], [beqz v0,Lskip] vs [beqz v0,Lskip] → match (rtx_renumbered_equal_p compares branch target? For JUMP_INSN pattern, the label... In MIPS, branch is a JUMP_INSN with label, pattern is set pc... Actually rtx_renumbered_equal_p on the pattern with label operand; labels differ but renumbered_equal may treat them... hmm). Minimum 2: after matching nop and beqz (minimum goes 2→1→0), it merges those two insns into a shared block: shared `beqz v0, skip; nop` then both fall into call? Actually merging last2 insns... That's what happened: mine got both arms branch to shared beqz.

In target, the then arm's end is `j 2bb8; nop` (jump insn) and else arm ends `beqz v0,2bc8; nop`. Backward: nop vs nop match (min 2→1); j vs beqz: GET_CODE differ (JUMP_INSN vs JUMP_INSN? both are JUMP_INSN on MIPS — branch and jump are both JUMP_INSN). Patterns differ → break, minimum=1 >0 → no merge. Good.

So target requires the then-arm's final insn be an unconditional jump to the call block, and else-arm's final be a conditional branch. Which natural C gives that? If the source is:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    goto docall;       /* explicit goto — but that's an identity-ish statement? It's a real control-flow move, not a launder */
} else {
    if (d >= 0x201) goto skip;
}
docall:
    call; return;
```
Hmm, `goto docall;` where docall is right after the else — that's a plain forward goto, real C control flow, not an identity launder (identity launders are value operations like `w = (w>>16<<16)|x`). But is an explicit goto "a real C move"? C0505 catalog mentions loop shape, statement order etc. A goto is allowed (other matches use goto loops). But would this goto survive and produce j 2bb8? Yes, an unconditional jump to the block after else-arm. Actually with `goto docall` where docall follows the else arm, the then arm ends with unconditional jump; else falls through. That exactly matches target!

But wait, does it? The then arm: `if (d >= 0x51) goto skip; goto docall;` — GCC might simplify: skip and docall both reachable. Then arm's tail: beqz skip; j docall. Target: `2ba0 beqz v0,2bc8` then `2ba8 j 2bb8`. Yes exactly.

However — would the `goto docall` be considered "identity statement" launder? No; it changes control flow structure, and the target's instruction layout literally requires the then arm to jump. Actually, hmm, an unconditional `goto` to the next block is a no-op control-flow-wise; GCC's CFG might see the block falls through and turn the jump into fallthrough anyway. But the block order: then-arm, else-arm, docall. Then-arm can't fall through to docall (else-arm is in between), so the jump is needed. Fine.

Alternatively write it as:
```
if (unk70 == 0) {
    if (d < 0x51) goto docall;
} else {
    if (d >= 0x201) goto skip;
}
goto skip;      /* ??? */
```
No.

Let me just try the goto version. But careful: `if (d >= 0x51) goto skip;` then `goto docall;` where docall placed after the else. But then the `if/else` structure: else arm ends, falls to docall label. So:

```
    if (d <= 0) { ... }
    else if ((...) & 1) == 0) {
        if (unk70 == 0) {
            if (d >= 0x51) goto skip;
            goto docall;
        } else {
            if (d >= 0x201) goto skip;
        }
docall:
        func_801822A4(param_1);
        return;
    }

skip:
    ...
```
Wait the `return` in docall: target has `jal; move a0,s3; j epilogue; nop` — so call then return → j to epilogue. Fine.

Hmm but the structure `else if (...) { ... }` — the call inside that else-if block after a label. A label inside a block is fine.

Actually simpler: keep call where it is, and add `goto docall` in then arm with label before the call:
```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    goto docall;
} else {
    if (d >= 0x201) goto skip;
}
docall:
    func_801822A4((void *)param_1);
    return;
```
Yes, call remains at same place; label before it. Let's try.

Wait: careful, `goto docall` jumping to label immediately after the if-else... The then-arm block would end with an unconditional jump over the else arm to docall. Target expects that. Let's test.

Actually hold on: does the then arm have the compare `d >= 0x51` → `slti v0,v1,81; beqz v0, skip` (branch if d>=81). Target's then arm: `2b9c slti v0,v1,81; 2ba0 beqz v0,2bc8` yes. Good.

Let's try variants.
