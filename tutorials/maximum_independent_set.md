---
title: Backtracking
subtitle: MIS
author: Miguel Miní
keywords: Markdown, Pandoc, VSCode
bibliography: mybib.bib
csl: https://raw.githubusercontent.com/citation-style-language/styles/master/ieee.csl
fontsize: 11.5pt
mainfont: Arial, Palatino, Georgia, Times
---

# Enfoque Brute Force

- Todos los nodos aislados se toman o desechan si son positivos o no.

- Sea $T(n)$ la complejidad del problema, si se toma un elemento queda el problema $T(n - deg(v) - 1)$. En otro caso $T(n-1)$.

- En el peor caso: $T(n) = T(n-1) + T(n-2) + O(1)$, luego la complejidad queda como $fib(n+1)$

# más DP

- si dividimos el problem en dos $n = n_1 + n_2$. con O(2^{n_2}) de memoria, podemos resolver el problema 
en $O(n_2 2^{n_2} + fib(n_1))$

# heavy pruning

- si todos los nodos tiene grado <= 2, entonces el grafo solo tiene caminos o ciclos, ambos se pueden resolver en $O(n)$.

- en otro caso tenemos $T(n) = T(n-1) + T(n-4)$, así la solución para la ecuacion $x^4 = x^3 + 1$ es la base de la complejidad
exponencial: $1.3803 < e^{1/3}$, luego la complejidad es $O(n e^{n/3})$ 

- agregando dp podemos tener $O(n_2 2^{n_2} + n_1 e^{n_1/3})$




