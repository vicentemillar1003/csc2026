# CI Exercise: Parallel ROOT Analysis + Merge (GitHub Actions)

## Goal
Run the same analysis over multiple ROOT files in parallel (matrix jobs),
collect outputs (artifacts), merge the ROOT histograms, and commit results into:
`exercises/TT-E2-docs-and-ci/ci-parallel-root/plots/`.

## What you learn
- workflow_dispatch inputs
- matrix strategy (parallel jobs)
- artifacts (upload/download)
- reproducible environments with Docker in Actions
- committing generated results from CI

## How to run
1) Fork the repository
2) Enable Actions in your fork (Actions tab -> enable workflows)
3) Ensure workflow has write permission (Settings -> Actions -> General -> Workflow permissions -> Read and write)
4) Go to Actions -> "CI Exercise - Parallel ROOT Analysis and Merge"
5) Click "Run workflow"
   - data_file:
     - exercises/TT-E2-docs-and-ci/ci-parallel-root/data.csv
     - exercises/TT-E2-docs-and-ci/ci-parallel-root/mc.csv
   - max_events:
     - 0 means "all events"
     - try 20000 for faster runs

## Expected outputs
After the run finishes, pull latest changes and check:
- plots/histogram_*.png
- plots/histogram_*.root
- plots/merged_histograms_<data|mc>.root
- plots/merged_histograms_<data|mc>.png
