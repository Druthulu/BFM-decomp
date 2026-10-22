---
ts: 2026-10-22T00:30:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_vTJtesa9yxCTb57CvRV4
---
Now I see the target's shape. Key: 
- 1430: `lui s1,0x0` / 1434: `addiu s1,s1,0` → s1 = &D_80126B5E (the address in a callee-saved reg).
- 145c: `lh v0,0(s1)` (cam->x)
- 1478: `lh v1,4(s1)` (cam->y)
- 14e4: `lhu v0,0(s1)` (x again)
- 14e8: `lhu v1,4(s1)` (y again)

So all four loads use s1. Without the lever, cse would rematerialize the address for the later loads (a second `lui/addiu` into a caller-saved reg).

Now, plain C: how to keep the address in one register across the call?

The lever: `cam = (Cam183098 *)&D_80126B5E; __asm__("" : "=r"(cam) : "0"(cam));` — the asm makes the value of cam *opaque* (the compiler doesn't know it equals the constant) so find_best_addr can't rematerialize %hi/%lo.

Plain C options to make the address opaque:
(a) Load the pointer from memory: is there a global that holds this address? Let me check the TU for something like `D_80126B5E` usage. Hmm.

(b) Use a *static* local pointer variable in the function:
```
static Cam183098 *camBase = (Cam183098 *)&D_80126B5E;
Cam183098 *cam = camBase;
```
This adds a static variable to the object (.data/.bss) — the object changes, but the function's instructions would be: lw camBase → a load instead of lui/addiu. The target has lui/addiu → mismatch. No.

(c) Make the address computation involve something non-constant but zero-cost at runtime: e.g.
```
Cam183098 *cam = (Cam183098 *)&D_80126B5E;
```
→ constant.

Hmm what if the pointer is derived from another *global pointer* in the TU? E.g. some global that holds a related address... unlikely.

(d) What if the address is computed as `(Cam183098 *)((u8 *)&D_80126B5E + 0)`? Folded.

(e) What if we use a *pointer arithmetic* form: `&D_80126B5E` cast to a char pointer and then to the struct pointer — folded.

(f) KEY IDEA: what if the pointer is *reused* from an existing register: e.g. the target loads the address into s1 and uses it. If the C used a pointer variable that is *also* used for something else...

(g) What if the *loads* are done through a pointer that is a *function parameter*? No.

(h) What if the address is expressed as a *cast of an integer constant* through a `s32` variable:
```
s32 addr = (s32)&D_80126B5E;      /* constant */
Cam183098 *cam = (Cam183098 *)addr;  /* cast of a constant → folded */
```
Folded.

(i) What if we use a *union* or a *struct member* to hide the address?

(j) What if the address is taken from a *static const array* in the TU? Same constant.

Hmm. So the fundamental issue: cse knows the address is a constant and rematerializes.

Wait — maybe the rematerialization happens because of *how* the address is used. Let me actually TEST the lever-free version and see what the compiler produces. Maybe the difference is smaller than I think, and a small change (e.g. using the pointer in the else branch differently) fixes it.

Let me write the orig (with the lever) and a lever-free candidate and compare.

Candidate c1: remove the asm line only:
```
cam = (Cam183098 *)&D_80126B5E;
```
and see the score and the asm.

Let me write orig.c and c1.c. The body is lines 3304-3372.

Note: the body includes a comment block above (3300-3302) — not part of the body.

Let me write orig.c (with the asm) and c1.c (without).

For the scoring, note the target is 60+ instructions. Let me write both files now.

Also, I need to think about the "keepalive"/other levers in this function — the kinds file says only "launder".

Let me write the two files.
