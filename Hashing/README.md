### First hash function
<img src="https://render.githubusercontent.com/render/math?math=h_1(x) = [\sum_{i=1}^{m} f(x_i)]\ mod\ \ell"  width="500" height="100">

### Second hash function
<img src="https://render.githubusercontent.com/render/math?math=h_2(x) = [\sum_{i=1}^{m} a_i \cdot f(x_i)]\ mod\ \ell \\"  width="500" height="100">

ℓ is the # of buckets in the hash table

## Ai Values:
```
 [5233, 8129, 9927, 6160, 2003, 8521, 8877, 3752, 8587, 9240, 6972, 6139, 7897]
```

## ℓ = 5851

### Distribution of hash locations (Histogram)
![](./Graphs/h1_plot.png)
![](./Graphs/h2_plot.png)

### Length of the longest chain
![](./Graphs/longest_chain_plot_h1.png)
![](./Graphs/longest_chain_plot_h2.png)

### Number of collisions as function of ℓ
![](./Graphs/collisions_vs_l_h1.png)
![](./Graphs/collisions_vs_l_h2.png)
