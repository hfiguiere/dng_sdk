# libjxl Integration Runbook

This document captures the integration workflow used for the recent libjxl
refresh in this repository. The goal is repeatability: import upstream subset,
fix integration breakages quickly, and prune safely.

## Scope and intent

- We do **not** use libjxl as a git submodule.
- We vendor a curated subset of upstream sources under:
  - `camera_raw/libjxl/libjxl`
- We maintain our own build wiring in:
  - mac project/configs
  - Windows project/filter files
- We intentionally remove upstream files not needed for our integration build
  (tests, docs, CI, packaging/tooling, etc.).

## High-level strategy

1. Import the new upstream release subset.
2. Build early to surface real compile/link blockers.
3. Fix integration breakages in dependency order.
4. Mirror source-list/project-file updates across mac and Windows.
5. Run an explicit prune pass with a reviewed manifest.
6. Stage only the intended add/delete set.

## Preflight

- Assume a noisy working tree after copy-in; do not reset/revert blindly.
- Keep changes scoped to `camera_raw/libjxl` unless build errors prove broader
  fixes are required.
- Prefer read-only git inspection during analysis (`git status`, `git diff`).

## Build-first debugging loop

Use one authoritative build target first (mac `cr_validate`) to drive fixes.

Example command:

```bash
xcodebuild \
  -project /Users/erichan/Projects/git/acr_integration/camera_raw/cr_sdk/projects/mac/cr_validate.xcodeproj \
  -scheme "cr_validate release 64" \
  -configuration Release \
  -derivedDataPath /Users/erichan/Projects/git/acr_integration/.deriveddata \
  build
```

Repeat: build -> fix top blocker -> rebuild.

## Breakage patterns to check first

### 1) SIMD/backend target issues (Highway)

Symptoms:
- backend/compiler failures in SIMD-specific paths.

Action:
- Apply local target-disable knobs in project config when needed.

Example used in this integration:
- File: `camera_raw/libjxl/client_projects/mac/Configs/jxl.xcconfig`
- Added: `HWY_DISABLED_TARGETS=25952256`
- Purpose: disable problematic SVE targets in this environment.

### 2) Toolchain/header compatibility

Symptoms:
- libc++/C-header include-order conflicts.

Action:
- Use minimal local include portability fix.

Example used in this integration:
- File: `camera_raw/libjxl/libjxl/lib/jxl/enc_chroma_from_luma.cc`
- Change: `<cfloat>` -> `<float.h>`

### 3) Link-time missing symbols from upstream source splits

Symptoms:
- undefined symbol in third_party component after upstream update.

Action:
- identify newly split translation unit in upstream.
- add that source file to all client project files.

Example used in this integration:
- Missing symbol source: skcms baseline transform split.
- Required source added:
  - `camera_raw/libjxl/libjxl/third_party/skcms/src/skcms_TransformBaseline.cc`

### 4) Preserve local CMake guard customizations (Android/build-minimal)

Context:
- We carry local guard customizations from commit
  `838d3bac23cb264e57ba5160d9630024c01a3673`
  ("jxl upgrade android changes").
- Large upstream file refreshes can overwrite these blocks.

After every libjxl import, explicitly verify these guards still exist:

- `camera_raw/libjxl/libjxl/CMakeLists.txt`
  - `if(BUILD_TESTING)` around `include(third_party/testing.cmake)`
  - `if(JPEGXL_ENABLE_TOOLS)` around `add_subdirectory(tools)`
- `camera_raw/libjxl/libjxl/third_party/brotli/CMakeLists.txt`
  - `if(BROTLI_CLI)` around brotli CLI target/install block
- `camera_raw/libjxl/libjxl/third_party/highway/CMakeLists.txt`
  - `if(HWY_BUILD_TESTS)` around `hwy_test`
  - `if(HWY_BUILD_LIST_TARGETS)` around `hwy_list_targets`

If any of the above are missing after import, restore them before final
build/validation.

### 5) Preserve Android JXL encoder source-list override (`gain_map.cc`)

Context:
- Merge commit `d1221645e1e727f9d19a650571d220443b098d2a` (PR #1062) pulled in
  `fb9d426982844d273d156fc16046821857af7e5f`
  ("Fix: JXL cmake update for android build").
- That change intentionally adds `extras/gain_map.cc` to
  `JPEGXL_INTERNAL_ENC_SOURCES` in:
  - `camera_raw/libjxl/libjxl/lib/jxl_lists.cmake`
- Upstream refreshes of `jxl_lists.cmake` can silently drop this local line.

After every libjxl import, explicitly verify:
- `extras/gain_map.cc` is still listed in `JPEGXL_INTERNAL_ENC_SOURCES` in
  `camera_raw/libjxl/libjxl/lib/jxl_lists.cmake`.

If it is missing, restore it before final build/validation to preserve Android
build behavior.

## Project-file reconciliation (must do on all platforms)

When adding/removing libjxl sources, mirror changes across:

- mac:
  - `camera_raw/libjxl/client_projects/mac/jxl.xcodeproj/project.pbxproj`
- Windows:
  - `camera_raw/libjxl/client_projects/win/jxl.vcxproj`
  - `camera_raw/libjxl/client_projects/win/jxl.vcxproj.filters`

For this integration, Windows required:
- Add `..\..\libjxl\third_party\skcms\src\skcms_TransformBaseline.cc`
  to `jxl.vcxproj` compile item group.
- Add matching entry under `skcms` filter in `jxl.vcxproj.filters`.

## API-surface expectation (`cr_sdk` / `dng_sdk`)

- Do not assume `cr_sdk`/`dng_sdk` callsite changes are required.
- Only update those layers if build/runtime errors prove API breakage.
- In this integration pass, no `cr_sdk`/`dng_sdk` API-callsite changes were
  needed.

## Prune workflow (recommended)

Use a file-backed manifest so decisions are reviewable and editable.

### 1) Generate status manifest

- Dump scoped status to:
  - `camera_raw/libjxl/prune.txt`

### 2) Annotate each file line

- For each listed file entry, append one of:
  - `-- add`
  - `-- prune`
- Optionally append reason text after the marker.

### 3) Re-read before acting

- Always re-read `prune.txt` after manual edits.

### 4) Apply actions exactly as marked

- First section (`modified:` / `deleted:` tracked entries):
  - stage `-- add` entries.
- Untracked section:
  - stage `-- add` entries.
  - delete `-- prune` entries.
- Keep `prune.txt` untouched unless explicitly asked otherwise.

## What was explicitly required in this integration

Keep/stage these notable skcms changes:

- Added:
  - `camera_raw/libjxl/libjxl/third_party/skcms/src/skcms_public.h`
  - `camera_raw/libjxl/libjxl/third_party/skcms/src/skcms_TransformBaseline.cc`
- Keep deletion:
  - `camera_raw/libjxl/libjxl/third_party/skcms/skcms_internal.h`

## What was pruned in this integration style

Generally prune when not needed by our build/integration:

- upstream docs/examples/CI/tooling/packaging metadata
- tests/benchmarks/fuzz corpora and test-only utilities
- unneeded third_party trees not used in our curated build path

Note: if a file looks "non-runtime" but is referenced by tracked runtime code,
it must be kept. Validate with grep/build errors, not assumptions.

## Verification checklist before final review

- `git status --short camera_raw/libjxl` is understandable and intentional.
- New required files are staged (especially untracked files marked `-- add`).
- Pruned files are actually removed.
- mac and Windows project file lists are consistent for required sources.
- mac `cr_validate` build succeeds after integration fixes.
- No unrelated directory/file churn outside intended scope.

## Common failure modes

- New upstream headers/sources required by old tracked files remain untracked.
- File-list update done only on one platform project file.
- Linker errors from upstream TU splits (third_party components).
- SIMD target regressions after highway update on specific toolchains.

## Suggested future usage

For each libjxl bump, follow this runbook in order and keep a short
release-specific appendix in commit notes or PR description with:

- upstream version/tag imported
- local compatibility deltas applied
- any intentionally deferred upstream pieces
