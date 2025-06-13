# Principal Component Analysis (PCA)

This project provides a from-scratch implementation of **Principal Component Analysis (PCA)**, a widely used method for **dimensionality reduction** in high-dimensional data analysis. The implementation relies solely on fundamental linear algebra operations and basic statistical tools.

---

## Overview

PCA projects high-dimensional data onto a lower-dimensional linear subspace by identifying the directions of **maximum variance**. These directions correspond to the **eigenvectors** of the data's **covariance matrix** associated with the largest eigenvalues.

Given a data matrix $X \in \mathbb{R}^{n \times d}$, where each row is a $d$-dimensional observation:

1. Center the data by subtracting the empirical column-wise mean:

   $X_c = X - \mu$

2. Compute the empirical covariance matrix:

   $C = \frac{1}{n - 1} X_c^\top X_c$

3. Extract the top $k$ eigenvectors $V_k \in \mathbb{R}^{d \times k}$ of $C$.

4. Project the centered data onto the subspace spanned by the principal components:

   $Y = X_c V_k \in \mathbb{R}^{n \times k}$

5. Optionally, restore the column means to the reduced data for interpretation.

By performing these steps, the resulting low-dimensional representation $Y$ captures the majority of the variance in the original data.

---

## Mathematical Components

* **Covariance Matrix Computation**

  $C = \frac{1}{n - 1} X^\top X$

* **Power Iteration Algorithm**

  An iterative method for approximating the dominant eigenvectors of $C$ via orthogonal deflation.

* **Low-Rank Approximation**

  Constructed via:

  $A \approx Y V_k^\top + \mu$

* **Frobenius Norm**

  Used to measure approximation error:

```math
\|A - \tilde{A}\|_F = \left( \sum_{i,j} (A_{ij} - \tilde{A}_{ij})^2 \right)^{\frac{1}{2}}
```

---

## Future Extensions

* Generalized SVD-based PCA
  
---
