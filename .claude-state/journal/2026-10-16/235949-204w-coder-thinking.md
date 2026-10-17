---
ts: 2026-10-17T05:59:49.635Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
I need to be careful here—shared function names at the same address across overlays may actually refer to different functions in different overlays, so I can't just group callers by name. I should restrict matches to binaries whose definition actually comes from the shared header, rather than overlay-local duplicates with the same symbol name.

My SET-based heuristic is also crude since it flags any write before the jal, including unrelated branches, so those cases need manual review. Given the scale, I'm triaging into batches—starting with Batch 1, covering simple PASS-only cases scoped to a single definition, listing out functions like func_8001C9D0, func_800CE134, and several SC0x overlay functions along with the larger shared ones like func_80169228 and func_80157D20 that have many PASS callers. I'm also noting that "PASS" means the caller forwards its own incoming parameter unchanged, so if the caller doesn't declare that parameter, the issue cascades upward.

To verify this properly I need to check each caller's actual signature, so I'm planning a small script that finds every call site for a given function name, then scans backward from that line to locate the enclosing function's declaration so I can confirm its parameter list.
