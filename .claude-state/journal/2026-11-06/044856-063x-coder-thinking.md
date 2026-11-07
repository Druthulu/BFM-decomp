---
ts: 2026-11-06T11:48:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1EN0ekfwYOh0ONtb91VW
---
Worse (53, 121 ins). The extra temp costs an insn (or the block changes regalloc).

Hmm. Let me go back to p1 (score 6) and think about the specific fix: target vx=a0, vy=v1; mine vx=split(s1,v1), vy=s2.

What if I write the second group so vx is used at 0x18 BEFORE x is modified? I.e. move the `*(s16*)(p+0x18) = vx;` store before `x += w_`? That changes the store order but maybe the target's store order at 0x18 is after 0x10? Target order: sh 16, sh 18(vy), sh 24(vx). So 0x18 comes after 0x10. But the scheduler could move it.

Alternatively, force vx to be a copy by using vx in a context that conflicts with x: e.g., `p[0x18] = vx` where vx is used after x's modification — already.

The compiler's decision to use x directly for the early store and copy later is copy propagation (flow). It's legal because vx = x.

What if vx is used three times, once before and twice after? Still same.

What if the add is written as `x = x + w_;` and the compiler... same.

Hmm, what about making the copies *not* trivially propagatable: e.g. `vx = (s32)(u16)x;`? That adds a truncation insn? Actually storing s16 later truncates anyway; `(u16)x` would zero-extend... `(s16)x` would sign-extend — an extra insn (sll/sra) unless the store does it.

Target: `move a0,s1` is a plain move.

OK, alternative: maybe the *order* of the two copies matters. Target has vx copy (a0=s1) at 53 and vy copy (v1=s2) at 55, with sh s1,16 at 74... 

Let me try small statement-order permutations on p1:
- swap `*(s16*)(p + 8) = vx;` and `*(s16*)(p + 0xA) = vy;`
- swap vx=x and vy=y (with barrier after both)
- move `vy = y` before `vx = x`
- move the vx/vy stores before the c stores
- move the c stores before vx/vy stores (already)

Each is cheap. Let me generate ~10 variants of p1 and score.

Actually, wait. Let me reconsider the root: in p1 mine, the first `sh s1,8` uses x (s1) directly and `sh s2,10` uses y (s2). The copies v1=s1 for the 0x18 use; and vy's 0x12 use uses s2 directly too (sh s2,18).

So the compiler eliminated BOTH copies and only materialized the one needed after modification (v1 = x copy for 0x18). But for vy: 0x12 use is after y's modification? No: source order is sh 0x12 = vy BEFORE y += h_. So vy's 0x12 use is before the modification → y usable directly. And 0x1A use after y += h_ → needs a copy of y. Wait, target's vy is used at 0xA, 0x12, and 0x1A. Mine uses s2 at 0xA and 0x12, and... mine[73] sh s2,18? Let me re-read the p1 diff:

```
  insert  mine[53:53] target[53:54]
       53  --                                 | move	a0,s1
  replace mine[54:55] target[55:56]
       54  move	v1,s1                         | move	v1,s2
  replace mine[67:69] target[68:70]
       67  sh	s1,8(v0)                        | sh	a0,8(v0)
       68  sh	s2,10(v0)                       | sh	v1,10(v0)
  replace mine[73:75] target[74:76]
       73  sh	s2,18(v0)                       | sh	v1,18(v0)
       74  sh	v1,24(v0)                       | sh	a0,24(v0)
```
So mine: move v1,s1 at 54 (copy of x). sh s1,8; sh s2,10; sh s2,18(0x12); sh v1,24(0x18). And the 0x1A store (y after add) uses s2 (modified y). Right.

Target: move a0,s1 (vx copy), move v1,s2 (vy copy); sh a0,8; sh v1,10; sh v1,18(0x12); sh a0,24(0x18); and 0x1A uses s2 (modified y).

So target makes BOTH copies; mine makes only the x copy (v1). Both are correct.

The difference is a pure register-allocation/copy-propagation choice. To force the vy copy: make vy's live range conflict with y. vy is used at 0xA (before y+=h_) and 0x12 (before) and 0x1A (after). The 0x1A use after the modification requires the value, but the compiler could... wait, in mine, 0x1A uses s2 which is y AFTER y += h_? No! 0x1A should store vy (the OLD y), but mine stores s2 after the add? Let me check the order in mine: sh s2,18 (0x12) at 73, then addu s2,s2,t1 at 76, then sh s2,26 (0x1A) at 79. Hmm, 0x1A = old vy = old y, but s2 was modified! Unless the 0x1A store is `*(s16*)(p+0x1A) = y;` — wait the source says `*(s16 *)(p + 0x1A) = y;`! Let me re-read:

```
    y += h_;
    *(s16 *)(p + 0x1A) = y;
    *(s16 *)(p + 0x20) = x;
    *(s16 *)(p + 0x22) = y;
```
Yes! The 0x1A store is y (new y), not vy. I misread. So vy is used only at 0xA and 0x12, both before y += h_. So the compiler can use y directly for both — no copy needed. Target still copies vy into v1 and uses v1 at 0xA and 0x12.

So target's vy copy is gratuitous (the launder forced it). Mine is optimal. To match, I need to force the copy.

How to force: make vy's use conflict with y. If y += h_ were scheduled/textually before the 0x12 store, then vy's value would be needed after y changes → copy required. In the target's schedule: sh v1,18 (0x12) at 38a4 comes AFTER lw t1(h_) at 3894 but before addu s2 at 38b4. Hmm, so no conflict.

What if I move the `y += h_;` statement before the 0x12 store? Source:
```
x += w_;
sh 0x10 = x;
sh 0x12 = vy;
sh 0x18 = vx;
y += h_;
```
If I reorder to:
```
x += w_;
sh 0x10 = x;
y += h_;
sh 0x12 = vy;
sh 0x18 = vx;
sh 0x1A = y;
```
Hmm, that changes the store order relative to target: target has 0x12 at 38a4 before the y add. So no.

Alternatively make vy used after y's modification: it isn't.

Hmm. So target's vy copy is a launder artifact. To reproduce it lever-free... we need a real C reason for vy to be a distinct pseudo. 

What if we use vy for something else too? E.g. store vy at 0x12 and... it's only 2 uses.

What if the declaration is `u16 vy`? Then vy = y truncates (extra insn) and the stores are s16 (no extra). Hmm, `u16 vy; vy = y;` → truncation to u16 happens implicitly; stored as s16 later → the compiler may keep the full value and store half. Actually assigning to a u16 variable forces a truncation? In C, `vy = y` where vy is u16: the value is converted to u16 (zero-extend) — gcc may or may not emit the truncation if all uses are halfword stores. Typically gcc keeps the value in a register and the s16 store truncates. So no extra insn, but vy becomes a different mode (HImode) pseudo → can't coalesce with s32 y! That would force the copy `move v1,s2`... or a subreg.

That's a real C move ("s16/u8 widths" in the catalog!). Let me try `u16 vx, vy;` or `s16 vx, vy;` with p1 (barriers kept).

Careful: `vx = x` with vx u16 truncates x to 16 bits; then stored as s16 → same bytes as target's sh. The target does `move a0,s1` then `sh a0,8(v0)` — truncation at store. With u16 vx, gcc might emit `sll/srl` or just use the low half. Since MIPS stores only need the low 16 bits, gcc usually doesn't emit truncation for a store of a u16 variable... but the variable's value is truncated at assignment; gcc's RTL would be (subreg:HI (reg:SI)) and the store matches. Likely no extra insn.

Let me test:
p5: p1 + `s16 vx, vy;`
p6: p1 + `u16 vx, vy;`
p7: p1 + `u16 vx; s32 vy;` etc.

Also, note that the item kinds are barrier,launder. Keeping all 4 barriers → if 0, result PARTIAL:barrier.

Let me create these by editing p1 (copy + decl change).
