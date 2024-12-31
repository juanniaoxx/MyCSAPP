[TOC]

## Lab

> ### Lab是CSAPP的精华
>
> 要尽量自己独立的完成，可以借助网络资源来完善和提醒，切忌不能看别人的实现然后简单的copy一份！

### Data Lab

![image-20241221221513536](assets/Datalab.png)

#### **bitxor**

题目分析，仅用`~(按位取反)` and `&(按位与)`，本质上一道逻辑运算的习题。

$A\oplus B=?$

1. 显而易见的一种

$A \oplus B = \sim (A \& B) \& (\sim A \& \sim B)$

#### tmin 

返回二进制最小的值(0x80000000) = $-2^{31}$ 

最直接的想法就是用1然后左移动31位

允许使用的整数为(0x0 ~0xff(255)),咋直接定义一个最大整数是不合理的。

#### isTmax ?

二进制最大的数为(0x7ffffff) = $2^{31} - 1$ 

#### alloddbits

判断某个数的二进制表示的奇数位是否全为`1`

> Input: 0xFFFFFFFD
>
> Output: 0
>
> Expian:
>
> D = 1101
>
> ​       |-----> 位置1(奇数)对于的二进制数为`0`而非`1`
>
> Input: 0xAAAAAAAA
>
> Output: 1
>
> Expian:
>
> 1010 1010 .... 1010
>
>  |  |  |  |         |  | ----> 所有奇数位都为`1`  



### Bomb Lab

### Attack Lab

### Arch Lab

### Cache Lab

### Tsh Lab

#### Malloc Lab

#### Proxy Lab

