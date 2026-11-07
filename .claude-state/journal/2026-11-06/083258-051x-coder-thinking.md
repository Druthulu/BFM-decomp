---
ts: 2026-11-06T15:32:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Wq6mr5Sl3xbFdFu6beu0
---
So --try does NOT strip. It splices the body as-is. But the spliced TU (orig_tu.c) at line 3187 shows `flags = raw;` with no asm after it... 

OH WAIT. The orig_tu.c I copied might be from the a7 --keep run! I ran `--try orig.c --keep` then `cp .../p3/ov_SC03_113_jr_8017C294.c $D/orig_tu.c`. But the scratch dir is per-PID, and the file name is the same. Since the previous command also used p3 (same pid? different invocations have different pids). Hmm, `p{os.getpid()}` — each python process has a different pid. The path printed was p3 both times? The first --keep printed `.../p3/cand.o`; the second also `.../p3/`? That would mean same pid, unlikely... unless the RUN dir path is fixed at p3? Hmm, earlier output showed `p3` for both a1 and a7. So os.getpid() gave 3? No... Actually maybe the RUN path uses a fixed "p3" from an env var. Let me check: `RUN / "score" / ... / f"p{os.getpid()}"` → pid. Both printed p3? The first --keep printed p3, the second printed p3. Different processes can't have pid 3. Unless the printed path is from a cached... Hmm, actually the message I saw for a1 and a7 both said p3. Suspicious. Maybe I misread; the a1 output said `p3` and a7 said `p3`. Let me check the actual dirs.

Anyway, the issue: the TU I copied for the orig dump may be the a7 TU (stale). That explains no asm. Let me redo carefully: run --try orig.c --keep, take the printed path, dump that.

Also note the copy in the TU at line 3187 lacks the asm — consistent with it being the a7 splice (a7 has ret=0 and no asm). Let me check whether a7_tu.c has `ret = 0;`.
