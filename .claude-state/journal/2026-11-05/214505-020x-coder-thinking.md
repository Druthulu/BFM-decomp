---
ts: 2026-11-06T04:45:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_59Dtc5WQTOqNm1418Vky
---
Same copy. The do-while causes p to be treated as live across a loop back edge → global alloc → v1 copy. To avoid, use a0 directly (no p). Let's write b7 with `*(u8 *)a0` etc. and do-while around stores.

Actually better: do-while around the store, with direct a0 access. Let's test.

Also try: keep p but declare it inside each do-while? b5 did that and still got copy (23). Hmm b5 had p assigned inside; still copy. Because p is a pointer variable that global-alloc assigns? It could be that the loop makes local-alloc not assign it. Let's try direct a0.

Candidate b7:
```
void func_8017F5A4(void *a0, s32 a1) {
    s32 v0;
    v0 = ((u8*)a0)[0] - a1;
    ...
    do { ((u8*)a0)[0] = v0; } while(0);
```
This may compute the address each time.

Alternatively use `p` but force it into a0 via... no pin allowed.

Hmm. The copy v1,a0 is a global-alloc artifact: p is live across a loop boundary so local-alloc refuses. If instead the do-while contains no loop back edge after flow? do{}while(0) gets converted... C0535 says it splits cse1 EBB. Apparently by the time of local-alloc, the do-while is still a loop (NOTE_INSN_LOOP_BEG?) or at least the pseudo is live at a label.

Let's test b7 with a0 directly.
