# Landau–Twin Prime Computational Verification

This repository contains the C++ source code, results, and checkpoint data from a two-month continuous computation verifying the **Landau conjecture** in the domain of **twin primes** up to  
n ≈ **2.4478 × 10¹⁰**.

All output ranges confirmed the conjecture as **TRUE**, with no counterexamples (`FALSE`) found throughout the analytic bound required by equation (6),  
n ≥ 2.4366420220 × 10¹⁰.

---

## 📘 Overview

The project implements a **resumable, checkpointed C++ computation** of the Landau conjecture as applied to twin primes.  
It was executed on a **Dell Precision T5500 (Xeon)** workstation running Ubuntu Linux, continuously for approximately two months.

The code supports:
- Safe interruption and resume via checkpoint (`checkpoint.txt`)
- Automatic CSV export by range (`twin_table_range_*.csv`)
- Graceful handling of signals (`SIGINT`) for mid-run save
- Verification logging (`TRUE` / `FALSE`) per analytic test

---

## ⚙️ Usage

### Compile
```bash
g++ -O3 -std=c++17 Landau_twin_prime_v5.cpp -o Landau_twin_prime_v5
Run
./Landau_twin_prime_v5.cpp

The program automatically resumes from the latest checkpoint if present:
last_n: 24478788778
last_twin1: 24478786331
last_twin2: 24478786333

| File                     | Description                                                         |
| ------------------------ | ------------------------------------------------------------------- |
| `landau_twinprime.cpp`   | Core C++ source code implementing the Landau–twin-prime computation |
| `checkpoint.txt`         | Last processed index and twin pair (auto-resumed on next run)       |
| `twin_table_range_*.csv` | Output data files for each processed range (10.5281/zenodo.17273964)|
| `false_check.log`        | Optional verification log (empty if all TRUE)                       |
Sample output of twin_table_range_*.csv:
27412668,9999996119,9999996121,9999997168,54825338,27415148,True
27412669,9999996497,9999996499,9999997306,54825340,27415148,True
27412670,9999997169,9999997171,9999997408,54825342,27415148,True
27412671,9999997307,9999997309,9999997918,54825344,27415148,True
27412672,9999997409,9999997411,9999998146,54825346,27415148,True
27412673,9999997919,9999997921,9999998230,54825348,27415148,True
27412674,9999998147,9999998149,9999998596,54825350,27415148,True
27412675,9999998231,9999998233,9999998608,54825352,27415148,True
27412676,9999998597,9999998599,9999999016,54825354,27415148,True
27412677,9999998609,9999998611,9999999700,54825356,27415148,True


Mathematical Context

The Landau conjecture posits the infinitude of twin primes.
In this experiment, we verify numerically that within the range
n ≤ 2.4478 × 10¹⁰, the associated analytic condition (equation 6 in the reference notes) holds true without exception.

Citation

If you use these results or data in academic work, please cite as:

"A short note about Landau's inequality for prime pairs"

    September 2025

    DOI: 10.13140/RG.2.2.27245.86246

    Marco Bortolamasi, Arturo Ortiz Tapia

Authors
Marco Bortolamasi
National Order of engineers, Italy.
https://www.researchgate.net/profile/Marco-Bortolamasi

Arturo Ortiz-Tapia
Chartered Mathematician, Institute of Mathematics and its Applications (IMA, UK)
https://www.researchgate.net/profile/Arturo-Ortiz-Tapia

License

This repository is released under the MIT License.
You are free to use, modify, and distribute it, provided attribution is given.

“Every computation that upholds a conjecture is a bridge between numerical persistence and mathematical truth.”
— A. Ortiz-Tapia & GPT-5 (2025),



