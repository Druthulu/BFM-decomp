# The firewall fixture — the audit's negative control

`blob.bin` is sixteen synthetic bytes (`printf 'DECOMP-FIXTURE!!'`), derived from no game; `blob.sha1` is its SHA1 in
`sha1sum` format. The kit's installer (Step 3) copies **only the `.sha1` file** into the new repository as
`config/firewall-fixture.sha1` and lists it in `config/firewall.txt` as a `fixture:` hash source, so the audit has at least
one resolvable source before the extraction manifest exists. The control then **plants** a copy of the blob under scratch
(`.run/firewall-control/planted.bin`), runs the audit on that path alone, asserts it FAILS naming the planted file, removes
the copy, and asserts the tree PASSES. An audit that has not failed on the fixture is not trusted to pass (the source
project's negative-control rule). The blob itself is never tracked in the new repository — the kit's package folder is
gitignored after install.
