---
ts: 2026-11-06T08:32:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eEJi0FtSha6hPPTttkkU
---
Score 9, same insn count. The differences: a2/a3 swapped register assignment (a0 is arg, so a0=a0, a1=a1; a2 and a3 swap), and v0/v1 for t3? Actually off dies: the target uses a2 for a1*20? Let me think.

The signature is void func_8017F6B0(void *a0, s32 a1). a0=arg0, a1=arg1. Target: move a2,a0? Wait target line 1 is "move a2,a0" and mine "move a3,a0". So a0 (the pointer param) is copied to $a2 in target, $a3 in mine. So in target, the a0 param copy goes to $a2; in mine $a3. The difference is due to register allocation ordering: the keepalive on `t3` (and `off`) affected pseudo priorities, so the params got a2/a3 swapped.

Target's `lw v1,0(at)` vs mine `lw v0`: t3 kept alive to load into $v1 in target (v1 used for later?), mine v0.

Key: remove keepalives but make off and t3 live via real C so register allocation matches. What real use? Let's look at the target asm and the current dumps. Let me see the target disassembly and mine for this function. Where's the target asm? delever_search probably compares against build objects. Let me check if there's an existing worked example dir .run/P40/T10/func_80181F4C to see tools. Also maybe tools/cc1_dumps_tu.sh.

First, understand what the keepalives do. `off` is used in all five loads; after the last load it dies. With keepalive, off is live past all five loads. `t3` is loaded at line for t3 and stored to sp10[3] then dies; keepalive keeps it live past that.

In target:
- register pairs: a3->a2 x5, a2->a3 x2, v0->v1 x2.

So mine: a3 holds what target holds in a2 five times (probably the a0 copy and the lhu loads through a0's copy). And mine a2 where target a3 twice (the 4th load/store: lw a3,0(at)/sw a3,28(sp) at insn 17-21 — that's t3), and v0/v1 twice (5th load/store t4).

Hmm interesting. Let's get the full listings. I need target asm. Let me find how dt/delever_search obtains target. Look at .run/P40/T11/bin/held_add.py or delever_search. Maybe simplest: run delever_search --explain for residual? Actually --explain reads one body's residual. It may print both listings.

Alternatively use tools/cc1_dumps_tu.sh + the build object's disassembly. Is there a tool to disassemble target? There is probably `tools/asm_diff.py` or match tools. Let me ask the retriever? The instructions say use pa_ext.py ask for code lookups. But here I can grep tools listing. Let me look at .run/P40/T10/func_80181F4C/ notes for workflow.
