---
ts: 2026-11-06T04:09:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BoA1SJbQJg7I0hA8AOZu
---
No twin. Let me look at the pass order and the "cse" behavior at loop boundaries: maybe the do-while trick works only if placed differently. In C0535: "do{}while(0) splits cse1 EBB; cracked a sched1-birth-order item". So the EBB split affects sched1, not cse necessarily.

Actually, hold on. Let me reconsider: maybe cse DOES forward but the forwarding creates a **copy** `x2 = x1` which is then deleted, and the target's double load comes from the ORIGINAL having the first value NOT in a register anymore because the first block's result `t` forced a register conflict. No, no spills.

Let me look at the target's instruction count and the register allocation: target uses v0 for both loads and v1 for the 0xE load. Mine uses v1 for the 0x2E load and v0 for 0xE. So target re-loads into v0 (same reg). If cse forwarded, one load into v1 and reuse.

Could the second load be a **reload of a spilled value**? The function has no stack slots besides saved regs. No.

OK let me try to find the original source through the ROM's build: maybe the `build/asm` has the original splat assembly with comments? No.

Let me try more variants in a batch, including:
- a1: pointer reuse (s16 *q) for both.
- a2: first via u16 then cast? (would change to lhu)
- a3: `s16` temp variable for x2 declared at top (decl order).
- a4: separate scopes vs same.
- a5: `s32 x2; x2 = *(s16*)...;` (init at decl vs assign).
- a6: `diff = 8 - *(s16*)...;` (no compound assignment).
- a7: `t = (8 - *(s16*)...) << 9;` one expression.
- a8: reorder the two blocks (x2 block before diff block).
- a9: store the diff expression using the same variable as x2.
- a10: `s16 x2 = *(s16*)...;` (s16 instead of s32).

Some of these might change the load into lhu.

Let me create a batch quickly using a gen script. I'll write a small bash script under the item dir that emits variants. But writing many files manually is tedious; let me use a python script under .run (allowed; scripts, not inline). Actually a bash script with sed is fine.

Let me write gen.sh that produces variants from nopin.c by line edits. But the body lines 31-39. Let me just write variants as full files with a heredoc? That's a lot.

Alternative: use python script .run/P40/T11/G20/gen2.py to generate variants programmatically from a template. Let me do that — it's allowed (scripts under shard).

Template body with placeholders. I'll write gen2.py that reads nopin.c and applies replacements.

Actually, let me first try a few high-value ones manually:

a1: pointer reuse:
```
    {
        s16 *q = (s16 *)((s32)s0 + 0x2E);
        s32 diff = 8;
        diff -= *q;
        t = diff << 9;
        *(u16 *)((s32)s0 + 0xE) += (*q << 6);
    }
```
a2: swap block order:
```
    {
        s32 x2 = *(s16 *)((s32)s0 + 0x2E);
        *(u16 *)((s32)s0 + 0xE) += (x2 << 6);
    }
    {
        s32 diff = 8;
        diff -= *(s16 *)((s32)s0 + 0x2E);
        t = diff << 9;
    }
```
a3: diff one-expression, x2 s16:
```
    t = (8 - *(s16 *)((s32)s0 + 0x2E)) << 9;
    {
        s16 x2 = *(s16 *)((s32)s0 + 0x2E);
        *(u16 *)((s32)s0 + 0xE) += (x2 << 6);
    }
```
a4: x2 as u16? no.

a5: `s32 x2; x2 = *(s16*)...` (separate decl).

a6: reuse the same variable `diff`? no.

Let me write a gen script. I'll write .run/P40/T11/G20/func_.../gen.py.

Hmm, wait. Time check: started item 2 at ~20:52. Now maybe ~21:05. Let me check date. I'll batch.

Actually, let me reconsider the fundamental question by reading cse_insn's load handling to see exactly when forwarding is blocked. Let me find the code that records a MEM load and the validation. Search for "in_memory" and the lookup of src.
