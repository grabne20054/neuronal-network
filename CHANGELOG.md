## 2026-09-20
- 708297e — grabne20054
  chore: changed argument call



## 2026-09-17
- 166440b — grabne20054
  fix: update prediction sample handling and improve argument validation in predict.c



## 2026-09-17
- 0358d90 — grabne20054
  Merge branch 'dev/normalize' into dev/split-purposes



## 2026-09-17
- 14d1446 — grabne20054
  Add normalization parameters and functions for network predictions

- Updated network_t structure to include normalization parameters: medians and iqrs.
- Added normalize_prediction_sample function to preprocess prediction samples using the normalization parameters.
- Modified the normalize function to store medians and IQRs in the network structure.
- Updated save_network and load_network functions to handle the new normalization parameters.
- Adjusted main function to use a new dataset for predictions and print normalized prediction results.
- Introduced test datasets (dataset0.h and dataset1.h) for training and prediction testing.


## 2026-09-17
- d413335 — Grabner Mathias
  feat: restructure build process and add training/prediction functionality



## 2026-09-16
- 425b404 — Grabner Mathias
  fix: correct header level for version 1.0.2 in changelog



## 2026-09-16
- b9019eb — Grabner Mathias
  chore: add initial changelog file



## 2026-09-16
- ed11b0e — Grabner Mathias
  chore: remove outdated README content and TODOs



## 2026-09-16
- 7832248 — Grabner Mathias
  feat: add preprocessing functionality for data normalization



## 2026-09-14
- e484516 — grabne20054
  feat: implement save and load functionality for layers and neurons, update network management



## 2026-09-12
- 0938b9e — grabne20054
  refactor: rename start_network to train_network for clarity



## 2026-09-12
- 400c981 — grabne20054
  refactor: comment out debug print statement in perform function



## 2026-09-10
- da16274 — Mathias
  feat: add command-line argument parsing and network memory management



## 2026-09-10
- 450b9ca — Mathias
  feat: v1.0



## 2026-09-10
- 6630849 — Grabner Mathias
  refactor: remove debug print statements and streamline backpropagation logic



## 2026-09-10
- 6c10c99 — Grabner Mathias
  feat: basic workin example train



## 2026-09-10
- 00a6691 — Mathias
  chore: sync



## 2026-09-03
- 84d4244 — Grabner Mathias
  chore: sync



## 2026-09-01
- 5f3b3c8 — grabne20054
  fix: correct neuron count in network initialization and update epoch print format



## 2026-08-28
- 13b6f78 — Grabner Mathias
  basic working example sigmoid 0-1



## 2026-08-27
- 1625480 — Grabner Mathias
  chore: sync



## 2026-08-26
- 38a2456 — grabne20054
  chore: sync



## 2026-08-25
- 0b48f7c — Grabner Mathias
  feat: update network functions to include weight and bias adjustments



## 2026-08-25
- ba512fc — Grabner Mathias
  feat: minimal working example



## 2026-08-25
- 6dd1b99 — Grabner Mathias
  chore: sync



## 2026-08-25
- deae852 — grabne20054
  chore: sync



## 2026-08-24
- a211f3b — Mathias Grabner
  Initial commit


