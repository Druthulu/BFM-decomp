# Outreach: the tools announcement (post-flip)

> **Where:** the decomp community Discord's tools channel, and/or a row on the Decompedia (decomp.wiki) tools page.
> **When:** after the flip, once `github.com/Druthulu/xsig` has its topics and the README's "Tools from this project" section is
> live. **Who:** Drew, in his own voice; edit freely. Written the way a developer posts, no code spans, no AI acknowledgement
> (rule candidate (j), S89).

**Discord post:**

```
Made a small tool while doing the Brave Fencer Musashi decomp that might be useful to other PS1 projects: xsig
(https://github.com/Druthulu/xsig). It hashes functions with the relocated fields masked out, so the same function at
two different link addresses gets the same signature. We used it to find shared code across overlays (2,220 groups in
BFM) and to check other games: against Xenogears, Vagrant Story and Tomba it found 103 shared functions, all PsyQ
library code, so mostly it's good for spotting library functions and shared overlay code. Stdlib only, MIT, has tests.
The full decomp is at https://github.com/Druthulu/BFM-decomp if anyone's curious, everything's matched.
```

**Decompedia tools-page row (if the page takes rows):** name xsig, language Python (stdlib), license MIT, platform MIPS /
PlayStation-era, one line: "relocation-masked function signatures for finding shared code across overlays and across games",
link to the repo.

**Facts the post rests on:** `tools/xsig/README.md` (the worked example: 103 hits across three games, all library; 126 against
Tomba with one 19-instruction non-library HIGH), `config/dedup.us.yaml` (2,220 groups), the E4 log entry (8/8 tests).
