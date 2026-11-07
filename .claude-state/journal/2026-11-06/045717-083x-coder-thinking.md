---
ts: 2026-11-06T11:57:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_H2QnrqAiXswvkkjI3d4g
---
My line-based removal broke the code because the barriers/launders are inline in statements like:
```
{ void *q = &blk; RotMatrixZ(ang, q); __asm__ __volatile__("" : "=r"(q)); }  // !FAKE: launder out-only
{ void *q; __asm__ __volatile__("" : : : "memory"); q = &blk;  // !FAKE: barrier memory
  RotMatrixZ(ang2, q); __asm__ __volatile__("" : "=r"(q)); }
```
Removing whole lines destroys braces. v0 worked (89) because... hmm v0 removed both barrier and launder lines; the line 21/23 barriers are standalone lines, 43/45 standalone, 55 standalone. The launders at 25,33,37,48,56 — some are inline in `{ ... }` lines (33, 37, 48?) and removing them removes the statement line. For v0, removing both sets happened to balance? It compiled (89). p1 (launder only) broke; p2 (barrier only) broke.

I need to do this properly: replace the asm snippets with real C rather than deleting lines.

Let me look at the exact body again (lines 304-364 shown earlier). Body lines (relative to 304 = 1):

1: void func_800CB56C(s32 arg0) {
2:
3:
4:     extern Blk20 D_800AE620;
5:     extern void RotMatrixZ(s32 a0, void *a1);
6:     extern void ApplyMatrixSV();
7:     extern void MulMatrix0(s32 a0, void *a1, s32 a2);
8:     extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
9:     extern s32 func_80128ED8(s32 param_1, s32 *param_2);
10:    extern void func_80146C3C();
11:
12:    u16   vec[8];
13:    Blk20 blk;
14:
15:    s32 ent;
16:    s32 obj;
17:    s32 ang;
18:    register s32 ang2 __asm__("$4");  // pin $4
19:
20:    obj = ((Unkstruct_800CB56C *)arg0)->unk20;
21:    __asm__ __volatile__("" : : : "memory");  // barrier
22:    ent = ((Unkstruct_800CB56C *)arg0)->unk34;
23:    __asm__ __volatile__("" : : : "memory");  // barrier
24:    { register Blk20 *s __asm__("$5") = &D_800AE620; s32 t0, t1, t2;  // pin $5
25:      __asm__ __volatile__("" : "=r"(s) : "0"(s));  // launder
26:      t0 = s->w[0]; ...
...
33:    { void *q = &blk; RotMatrixZ(ang, q); __asm__ __volatile__("" : "=r"(q)); }  // launder out-only
34:    vec[0] = ...
...
37:    { void *q = &blk; ApplyMatrixSV(q, vec, vec); __asm__ __volatile__("" : "=r"(q)); }  // launder
...
43:    __asm__ __volatile__("" : : : "memory");  // barrier
...
45:    __asm__ __volatile__("" : : : "memory");  // barrier
...
46:    { register Blk20 *s __asm__("$7") = &D_800AE620;  // pin $7
47:      s32 t0, t1; register s32 t2 __asm__("$6");  // pin $6
48:      __asm__ __volatile__("" : "=r"(s) : "0"(s));  // launder
...
55:    __asm__ __volatile__("" : : : "memory");  // barrier
56:    { void *q; __asm__ __volatile__("" : : : "memory"); q = &blk;  // barrier memory
57:      RotMatrixZ(ang2, q); __asm__ __volatile__("" : "=r"(q)); }  // launder

So the line-based removal removed lines 33, 37, 48, 56 (which contain the whole statement) and line 25 (just the launder). Line 56's barrier is part of a multi-line block — removing it leaves `{ void *q; q = &blk; ...` which is valid actually... but it removed the `{` too → broken.

For v0 I removed both 55 and 56 — line 55 is the standalone barrier and 56 the `{ void *q; __asm__...` line. Removing both left `RotMatrixZ(ang2, q); ...` without the opening brace → should break. But v0 compiled at 89. Hmm, maybe my line indices are off; let me look at the actual v0.

Let me just rewrite v0 properly by hand from the source, removing barriers/launders semantically:

```
void func_800CB56C(s32 arg0) {
    extern Blk20 D_800AE620;
    ...
    u16 vec[8];
    Blk20 blk;
    s32 ent, obj, ang;
    register s32 ang2 __asm__("$4");  // pin $4

    obj = ((Unkstruct_800CB56C *)arg0)->unk20;
    ent = ((Unkstruct_800CB56C *)arg0)->unk34;
    { register Blk20 *s __asm__("$5") = &D_800AE620; s32 t0, t1, t2;  // pin $5
      t0 = s->w[0]; ... }
    ang = ((Unkstruct_800CB56C *)arg0)->unk10;
    RotMatrixZ(ang, &blk);
    vec[0] = ((Unkstruct_800CB56C *)arg0)->unk30 << 2;
    vec[1] = 0;
    vec[2] = 0x30;
    ApplyMatrixSV(&blk, vec, vec);
    ent += 0x38;
    func_8012F14C(ent, (s32)vec, (s32)vec);
    ...
    ang2 = ang + 0x200;
    ((Unkstruct_800CB56C *)arg0)->unkE = vec[2];
    { register Blk20 *s __asm__("$7") = &D_800AE620;  // pin $7
      s32 t0, t1; register s32 t2 __asm__("$6");  // pin $6
      ... }
    RotMatrixZ(ang2, &blk);
    MulMatrix0(ent, &blk, arg0 + 0x38);
    ...
}
```

Let me look at the exact source lines 315-364 again (I have them above). The body:
```
    u16   vec[8];
    Blk20 blk;

    s32 ent;
    s32 obj;
    s32 ang;
    register s32 ang2 __asm__("$4");  // !FAKE: pin $4 ...

    obj = ((Unkstruct_800CB56C *)arg0)->unk20;
    BARRIER
    ent = ((Unkstruct_800CB56C *)arg0)->unk34;
    BARRIER
    { register Blk20 *s __asm__("$5") = &D_800AE620; s32 t0, t1, t2;  // pin $5
      LAUNDER(s)
      t0 = s->w[0]; t1 = s->w[1]; t2 = s->w[2];
      blk.w[0] = t0; blk.w[1] = t1; blk.w[2] = t2;
      t0 = s->w[3]; t1 = s->w[4]; t2 = s->w[5];
      blk.w[3] = t0; blk.w[4] = t1; blk.w[5] = t2;
      t0 = s->w[6]; t1 = s->w[7];
      blk.w[6] = t0; blk.w[7] = t1; }
    ang = ((Unkstruct_800CB56C *)arg0)->unk10;
    { void *q = &blk; RotMatrixZ(ang, q); LAUNDER(q); }
    vec[0] = ((Unkstruct_800CB56C *)arg0)->unk30 << 2;
    vec[1] = 0;
    vec[2] = 0x30;
    { void *q = &blk; ApplyMatrixSV(q, vec, vec); LAUNDER(q); }
    ent += 0x38;
    func_8012F14C(ent, (s32)vec, (s32)vec);
    ((Unkstruct_800CB56C *)arg0)->unk6   = vec[0];
    ((Unkstruct_800CB56C *)arg0)->unkA = vec[1];
    ang2 = ang + 0x200;
    BARRIER
    ((Unkstruct_800CB56C *)arg0)->unkE = vec[2];
    BARRIER
    { register Blk20 *s __asm__("$7") = &D_800AE620;  // pin $7
      s32 t0, t1; register s32 t2 __asm__("$6");  // pin $6
      LAUNDER(s)
      ... copies ... }
    { void *q; BARRIER; q = &blk;
      RotMatrixZ(ang2, q); LAUNDER(q); }
    MulMatrix0(ent, &blk, arg0 + 0x38);
    if (func_80128ED8(obj, (s32 *)(arg0 + 0x24)) != 0) {
        ((void (*)(s32))func_80146C3C)(arg0);
    }
}
```

Wait, there are 5 barriers per the grep: lines 21, 23, 43, 45, 55, plus one inline at 56. That's 6 barrier occurrences but grep showed 5 with "// !FAKE: barrier" (21,23,43,45,55) and 56 is "// !FAKE: barrier memory" — hmm, grep matched "// !FAKE: barrier" which includes "barrier memory". Let me recheck: bar list was [21, 23, 43, 45, 55] — 5 items. But line 56 also has a barrier (`__asm__ __volatile__("" : : : "memory")` with comment "// !FAKE: barrier memory"). Maybe my grep pattern was "// !FAKE: barrier" and it should match. Whatever — I'll work from the source text.

Let me construct v0 properly with a Python script doing semantic replacements on the exact source text, then verify it compiles and scores.

Replacements:
1. Remove standalone barrier lines: `    __asm__ __volatile__("" : : : "memory");  // !FAKE: barrier memory — ...` (full lines).
2. `{ register Blk20 *s __asm__("$5") = &D_800AE620; s32 t0, t1, t2;  // ...\n      __asm__ __volatile__("" : "=r"(s) : "0"(s));  // ...\n` → keep the block line without the launder.
3. `{ void *q = &blk; RotMatrixZ(ang, q); __asm__ __volatile__("" : "=r"(q)); }` → `RotMatrixZ(ang, &blk);`
4. Similarly for ApplyMatrixSV.
5. The last block: `{ void *q; __asm__ __volatile__("" : : : "memory"); q = &blk;\n      RotMatrixZ(ang2, q); __asm__ __volatile__("" : "=r"(q)); }` → `RotMatrixZ(ang2, &blk);`
6. The second Blk20 copy block: remove the launder line.

Let me write v0 by hand with Write (cleanest), based on the source. I'll keep the pins ($4 ang2, $5 s, $7 s, $6 t2).

Actually careful: pins are levers of other kinds; they may stay. Keep them.

Let me write v0.c.
