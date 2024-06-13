# Welcome to OptiPharm's documentation

OptiPharm is a global evolutionary optimizer. It can be considered a general-purpose algorithm because it can be used to solve any optimization problem that involves the computation of the similarity of two compounds given as input parameters. In other words, it is independent of the objective function used to measure the similarity between two given molecules. 

OptiPharm is a global optimization method in the sense that it makes an effort to analyze the whole search space looking for promising areas where the local and global optima can be. In other words, instead of focusing on a set of pre-specified starting points, it applies procedures to find promising subareas of the search space, which will be deeper analyzed during the optimization procedure. OptiPharm applies procedures based on species evolution to gradually adjust one of the molecules (the query) to the other (the target), which remain fixed during the optimization procedure.

