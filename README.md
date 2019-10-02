# programming_experiment
### C_Test 使用数组
### Hash_search hash array 查找
### BF_search Bloom Filter原理
实验最终实现了三个版本的在给定的海量个数的字符串中查找特定的字符串方法。
版本一：数组实现的array_search方法，查询结构内存分配564250KB，字符比较次数178643767632次，命中个数516819个字符串；
版本二：哈希表实现hashtable_search, 查询结构内存分配760420KB，字符比较次数21375006次，命中个数516819个字符串；
版本三：Bloom Filter实现, 查询结构内存分配8192KB，字符比较次数134720658次，命中个数516819。

