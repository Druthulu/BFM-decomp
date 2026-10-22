---
ts: 2026-10-21T23:47:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG06r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_OtDydGheUl0NmXW4r4ch
---
Item 8017EEB0 already has a MATCH (win.c scores 0, no pin)! The previous run got it but didn't write the results row. Let me verify win.c is lever-free: it uses a `w` temp, no register/__asm__.

win.c content:
```c
void func_8017EEB0(void *a0)
{
    s32 v0;
    s32 w;
    s32 s0 = (s32)a0;
    if (func_8012BDBC(s0, 0x300) != 0) {
        w = func_8012BCCC(s0);
        if (w > 0xFFFFF) goto lo;
        v0 = (w < 0x6400);
        if (v0) v0 = 8; else v0 = 4;
        goto store;
    }
    v0 = func_8012BCCC(s0);
    if (v0 < 0x4000) { v0 = 0xF; goto store; }
lo:
    if (func_8012BEE8(s0) == 0) return;
    v0 = 2;
store:
    ((Unkstruct_800B5CB8 *)s0)->unk2 = v0;
}
```
No pin, no launder, no barrier, no keepalive → lever-free, score 0 → MATCH.

But careful: "no signature or decl change outside the body (callers stay as they are)" — the body signature is the same. Good.

So item 8017EEB0 = MATCH, best 0. The move: split the first call's result into a separate variable `w` so the second call's result `v0` keeps $2 (the pin's reg) — i.e. the call result that must be in $2 is the one from the second path.

Wait, which pin? orig pins `register s32 v0 __asm__("$2")`. The unpinned version names the variable v0 (a plain s32) and adds `w`. The mechanism: the first call's result is used twice (compare and compare) → in a separate temp `w` so that the $2 register is free for the second call's result / the value stored.

Let me note the mechanism precisely: the target keeps the *return value of the second* call (the one in the else path) and the stored value in $2; by giving the first call's result its own variable `w` (2 uses), the second call's result pseudo wins $2 (higher priority: shorter live range? or fewer refs) and the stored value keeps $2 as well.

Good. Let me record this as MATCH for 8017EEB0.

Now, item 8017D3A0 is the same shape as 8017E4E0 (the $3 pin) — likely the same wall. Item 8017FB50 — let me look. And 8014CF04.

Let me check the remaining items' orig.c and existing candidates: 8017FB50 and 8014CF04.
