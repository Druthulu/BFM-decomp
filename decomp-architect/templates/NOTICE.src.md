# NOTICE — the sources under `src/`

The C files under `src/` are a **reimplementation of the executable code of *{{GAME_TITLE}}*** ({{PLATFORM}},
{{GAME_SERIAL}}), written so that the game's own compiler turns them back into the original machine code byte for byte.
They exist for **study, interoperability and preservation**: to document how the game works, to make its code readable,
and to keep it buildable after the original tools and media are gone.

*{{GAME_TITLE}}* and its code are **© TODO(publisher, year)**. The original work is theirs. This project is not
affiliated with, sponsored by or endorsed by the rights holder.

**No license is asserted over the contents of `src/`.** They are derived from the copyrighted program and are published
as a reimplementation for the purposes above, in the manner of other matching decompilations of commercial games. Nothing
here grants anyone more rights in the original work than they already have, and nothing here should be read as a license
to distribute the game or its compiled code. The compiled output of these sources is, by design, identical to the
original binaries — distributing that output is distributing the game's code; don't.

What this repository does **not** contain: the game's executable, its disc or cartridge data, any disassembly listing,
any memory image, or the vendor's SDK. Building requires your own copy of the game (see the top-level `README.md`).

The rest of the repository — the tooling under `tools/`, the build system and the documentation under `docs/` — is the
project's own work and is licensed under {{LICENSE_CHOICE}} (`LICENSE`). Third-party components are listed with their
licenses in `THIRD_PARTY.md`.
