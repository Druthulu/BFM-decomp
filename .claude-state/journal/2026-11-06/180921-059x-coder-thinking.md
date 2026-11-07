---
ts: 2026-11-07T01:09:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_aQiOTk2EnA5xHUzVy09H
---
Score 1: exactly one instruction differs: `sw v0,516(a0)` (mine) vs `sw v0,516(s0)` (target). Same ins count (16).

So the target keeps s0 as the base for the second store (offset 0x204), while lever-free the compiler uses a0.

The source:
```
  s0 = a0;
  ((void (*)(void *))func_8017EE68)(a0);
  new_var = (char *) s0;
  v0 = 0x8;
  *((s32 *) (((char *) s0) + 0x200)) = v0;
  v0 = 0x100000;
  *((s32 *) (new_var + 0x204)) = v0;
  func_80171990((u8 *) s0);
```
Target: both stores use s0; the call func_80171990 gets s0. And after the first call, a0 is free.

The prior note: "sched1 hoists the arg copy `a0 = P(param)` above both stores (pseudo copy; the pinned body's copy reads hard $16 set after call 1), then reload_cse rewrites the 0x204 store base s0 -> a0."

Hmm: in the lever-free body, `s0 = a0` (a pseudo copy) gets hoisted by sched1 above the first call? Wait, the param a0 is copied to s0 before the call. Then reload_cse substitutes a0 for s0 where possible (since a0 and s0 hold the same value and a0 is not clobbered... but the call to func_8017EE68 clobbers a0!). Hmm, after the call, a0 is dead/undefined; the compiler may reload... 

Actually the diff: mine uses a0 as the base for the 0x204 store, meaning the pseudo s0 got allocated to a0 (same reg) for that use? No — register pairs say a0->s0 x1, i.e., mine has a0 where target has s0. So the value is in a0 in mine for that one instruction.

Wait, the second store's base `new_var + 0x204` where new_var = (char*)s0. In mine, that became a0+0x204, so the compiler used a0 (the param reg) — meaning the pseudo holding the pointer was allocated a0 for that use, i.e., the pointer copy `s0 = a0` was coalesced/propagated and the value lives in a0 after the call? But the call clobbers a0...

Unless: the call `func_8017EE68(a0)` is to a function whose declaration doesn't clobber a0? It's called through a cast `((void (*)(void *))func_8017EE68)(a0)`. The call clobbers caller-saved regs including a0.

Hmm, but the compiler could re-materialize: `s0` (pseudo) is allocated to... let me think. The pseudo s0 (the copy of the param) is live across call 1 → it must be in a callee-saved reg ($s0 in the target). In mine, the register pair says the base of the second store is a0 — so the compiler decided the value is in a0 at that point? That can't be right across a call.

Wait — maybe the copy `s0 = a0` was moved AFTER the call by sched1 (the note says "sched1 hoists the arg copy a0 = P(param) above both stores" — confusing). Let me look at the actual instructions. Let me dump the target and my candidate.

Let me get the full disassembly of both. Use the target dump from the build object. I can use dt.sh --keep? Or tools/delever_search.py --explain which prints the full mnemonic diff. The diff showed only one instruction differing, so let me just look at the target listing.

Where to get the target insns? `delever_search.py --explain <tu> <fn>` prints all differing blocks but only the diffs. Since only one differs, I need the full listing.

Option: use `--keep` with --try to get cand.o and objdump it; and the target object is in build/. Let me find the baseline object path: oracle.baseline_path(rec["obj"]). Hmm.

Simpler: the score output says mine[10] = sw v0,516(a0), target[10] = sw v0,516(s0). Let me get the whole 16 instructions via a dump tool: `.run/P40/T10/hdump.sh` (header pass dumps)? The brief mentions `.run/P40/T10/hdump.sh` for header pass dumps. Let me look at it.

Or use tools/cc1_dumps_tu.sh on a scratch TU with the body, then read the .s. That gives the compiler's own output for my body (not the target).

For the target, I can objdump the baseline object. Let me find the build object: build/... Let me ask the tool: `delever_search.py --explain` with an empty path prints the diff blocks only.

Alternative: `masked_diff` etc. Let me just use --keep to get cand.o and objdump both. Actually the target is the function in build/'s object. The T10 dir might already have a target dump. Let me check .run/P40/T10/func_8017E98C/ — no tgt file.

Hmm, .run/P40/T10/ has tgt_*.txt for func_80177940 only.

Let me look at hdump.sh.
