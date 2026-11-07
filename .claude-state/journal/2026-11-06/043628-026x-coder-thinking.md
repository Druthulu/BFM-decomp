---
ts: 2026-11-06T11:36:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SonFlzQu1cXYOR5MDClj
---
So stop_search_p returns 1 on: JUMP_INSN, BARRIER, CODE_LABEL (when labels_p), or an INSN that is ASM_INPUT / has asm operands / is a SEQUENCE.

fill_slots_from_thread (line 3316) is the forward-scan from a thread; it calls `stop_search_p(trial, !thread_if_true)`. So labels_p = !thread_if_true. For the fall-through thread (thread_if_true = 0?), labels_p = 1, so a CODE_LABEL stops it. For the taken thread, labels_p=0, labels don't stop.

So in the original: the barrier asm is the first insn in the fall-through (if-body). For the fall-through thread scan, it hits the asm → stop. Then it tries the taken thread (the else/after), scanning forward and finding `addiu v0,s1,1`.

Real C: I need an ASM_INPUT or a label at the head of the fall-through. Since no asm allowed, a CODE_LABEL would stop the fall-through scan (labels_p=1 for fall-through). So if I can arrange a label at the start of the if-body... 

A label can be created by a `goto` target. E.g., if there's a label inside the if-body. But labels are placed where control flow merges. 

Idea: use a `do { ... } while(0)` around the if-body. Does gcc emit a label for the do-while(0)? A do-while(0) with no break might be optimized away. But C0535 says do{}while(0) splits cse1's EBB — meaning gcc keeps a note/label? Actually an empty loop body creates a `NOTE_INSN_LOOP_BEG/END`? Hmm.

Alternatively, the label from a `goto` that jumps to the if-body head:
```
do {
    if (D_80115158[i].h == 0) goto skip;
    {
        ot = call(...);
    }
skip:
    i++; w++;
} while (i < cnt);
```
Here the branch is `beqz` to skip. The fall-through is the call setup. The taken thread is `skip:`. For the fall-through thread, the first insn is `move a0,s0`; stop_search_p on an INSN that's not asm returns 0, so it keeps scanning. It might find a safe insn to steal from the call setup. Hmm, but then the target region...

Actually, wait. Let me reconsider which thread is which. The beqz at 83 branches when h==0 to ff8 (skip). So the "taken" thread is the skip (i++). The fall-through is the call. In the original with the barrier, the fall-through scan stops at the barrier. Then it fills from the taken thread (ff8): `move s1,v0`? No, it found `addiu v0,s1,1` (insn 89 at ff4) — wait ff8 is the target. Let me recheck: beqz v0,ff8. Target ff8: `move s1,v0` (insn 90). Hmm, but the delay slot is `addiu v0,s1,1` at fe0. That's insn 89 (ff4) which is BEFORE the target ff8. So reorg did not fill from the taken thread at ff8; it filled from... Actually reorg's fill_slots_from_thread with thread_if_true=1 scans from the branch target (ff8) forward: ff8 move s1,v0, ffc sll, ... It would find something. But the delay slot insn is `addiu v0,s1,1` which is at ff4 (insn 89), which is in the fall-through thread before the branch target? No.

Hold on. Let me re-read the structure. At ff0 `move s0,v0` (after call), ff4 `addiu v0,s1,1`, ff8 `move s1,v0`. So the call returns, s0=ret, then i++ (addiu v0,s1,1; move s1,v0). Then loop check. The beqz at fdc jumps to ff8, skipping the call+move s0 but NOT skipping the i++. So if h==0: jump to ff8 (move s1,v0) — but v0 must already be i+1! That's why the delay slot computes `addiu v0,s1,1` — so that when the branch is taken to ff8, v0 holds i+1 and `move s1,v0` completes the increment. Clever. So the delay slot insn `addiu v0,s1,1` is the computation of i+1, needed on the taken path. On the fall-through path, the call happens, then i+1 is recomputed at ff4 (because the call clobbered v0).

So the delay slot is filled from the taken thread (the branch target ff8) — reorg copies an insn from the target thread that computes v0=i+1. But the target thread at ff8 starts with `move s1,v0`, which uses v0. Where does reorg get `addiu v0,s1,1`? It must be looking backward? Actually reorg's fill_slots_from_thread scans the thread from `thread` forward. Hmm.

Wait, maybe the thread is defined differently. Let me look at fill_simple_delay_slots: it tries `fill_slots_from_thread (insn, condition, insn, next_trial, ...)` for the fall-through and `fill_slots_from_thread (insn, condition, jump_target, ...)`. Actually let me read the code around fill_simple_delay_slots.

Actually, maybe the delay-slot fill here comes from the fall-through after all: reorg's try_fill_simple_delay_slots scans the fall-through for insns safe to execute before the branch. The fall-through is the call setup `move a0,s0` etc. The insn `addiu v0,s1,1` is not in the fall-through (it's after the call). Hmm.

Let me just read fill_simple_delay_slots.
