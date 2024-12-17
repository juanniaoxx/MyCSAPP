[TOC]

## The Memory Hierarchy(分层)

内存系统最重要的特点就是**利用局部性(locality)**

> [!Important]
>
> 将会学到
>
> - DRAM\SRAM\Disk\SSD
> - Locality

### Storage Technologies

> [!Note]
>
> ![SRAM原理图](assets/SRAM_1.png)                 
>
> |                      | DRAM       | SRAM       |
> | -------------------- | ---------- | ---------- |
> | 构成                 | 电容       | 六个晶体管 |
> | 速度                 | 较慢       | 较快       |
> | 价格                 | 较便宜     | 较贵       |
> | 集成度               | 较高       | 较低       |
> | 功耗                 | 低         | 高         |
> | 主要用途             | 主存、显存 | Cache      |
> | 是否采用**定时刷新** | 是         | 否         |
> | 是否地址线服用       | 是         | 否         |
>
> > [!TIp]
> >
> > 1. DRAM和SRAM都是易失性，掉电都会导致存储信息丢失。
> > 2. DRAM为啥要刷新而SRAM为啥不要刷新？
> >    - DRAM使用电容存储，而SRAM用晶体关。电容天然存在**漏电问题**。
> >    - 刷新(refresh):reading it out and the rewriting it.[读出重写]
>
> **DRAM chip**
>
> ![image-20241213215752077](assets/DRAM_chip.png)
>
> ![image-20241213220212632](assets/RAS&CAS.png)
>
> RAS request: row access strobe reques 行访问选通请求
>
> CAS request: column access strobe request 列访问选通请求
>
> 对于范围$(i,j)$块，先选择第$i$行，再从第$i$行中选择第$j$个 
>
> DRAM会首先进行RAS，即行选通，然后把这一行写入row buffer(行缓冲区)再进行列访问。
>
> > [!caution]
> >
> > **通过这种方式可以使地址引脚(pins)减半！**
>
> **典型字拓展（并联）**  8M * 8 ----> 8M * 64
>
> ![image-20241213221109680](assets/多块DRAM组合.png)

**Accessing Main Memory**

![image-20241216145251595](assets/bus.png)

Example: load

```assembly
movq A, %rax
```

![image-20241216145359054](assets/load.png)

Example :Store

```assembly
movq %rax, A
```

![image-20241216145628643](assets/Store.png)

### Disk

#### Disk Geometry

![image-20241216151443633](assets/Disk_Geomety.png)



> [!note]
>
> **Surface**磁面，一般来说一个磁盘有一个（两个）磁面，具体看磁盘使得构造。
>
> **Tracks**磁道
>
> **Sectors**扇区，磁盘的读写单位。一般是固定大小常见温彻斯特盘是（512B）
>
> **Gaps**间隔,用以分割一个个扇区，保存有磁盘格式化的形象。
>
> **Cylinder**柱面，同一位置的磁道构成的空间结构
>
> 一般描述磁盘容量用[盘面数/磁道(柱面)数/扇面数]乘在一起在乘以扇面的容量就可以。



一个笔试题：如果每个磁道所含的扇面数相同，则越靠近内部的磁道记录密度越大。

#### Disk 传输时间的计算

![image-20241216165649240](assets/Disk寻址.png)

- seek time (寻道时间):寻找对应的磁道 由于磁头每次开始移动的位置并不唯一，所以计算seek的时候一般采用平均时间
  - $T_{avgseek}=\frac{T_{maxseek}}{2}$,单位一般是ms

- Rotational Latency(旋转延迟):寻找对应磁道的对应扇区, 由于每次需要旋转的距离是不能确定的，所以一般也采用平均时间(旋转半圈)
  - 一般会告诉磁盘转速，单位rpm(每分钟转多少次)
  - $T_{avgrot}=\frac{60}{n(rmp)}\times\frac{1}{2}\times1000 (ms)$ 单位化成ms
- Data transfer(传输时间)
  - $T_{transfer}=\frac{1}{rpm}\times\frac{1}{average \#sectors/track}\times\frac{60}{1min}$

一般时间只和`seek`与`rotational`有关，`data transfer`一般低于前二者的量级

#### connecting I/O Devices

![image-20241216170606010](assets/I_O bus.png)

> [!Important]
>
> **Reading a disk sector**
>
> ![image-20241216170746673](assets/Reading_disk.png)

```mermaid
graph TD
A[Cpu 告诉磁盘控制器读磁盘指令]-->|包含逻辑磁盘地址，目标内存地址|B[磁盘控制器转换成对应的物理地址]
B-->|DMA|C[CPU执行其他指令，磁盘采用DMA传送数据给MM]
C-->|中断CPU|D[CPU获取传输完成信息]
D-->E[CPU重新调度]
```

#### SSD (Soild State Disks)

![image-20241216182652821](assets/SSD.png)

> [!Caution]
>
> Reading from SSDs is **faster** than writing.[读比写快]
>
> 随机读/写比顺序读写慢
>
> ![image-20241216183234746](assets/SSD_1.png)

**Page(页)是读写单位，Block（块）是擦除单位。**

> [!Note]
>
> ​	A page can be written only after the entire block to which it belongs has been erased (已擦除)(typically, this means that all bits in the block are set to 1). However, once a block is erased, each page in the block can be written once with no further erasing.

> [!important]
>
> | **特性**       | **SSD（固态硬盘）**                                       | **HDD（机械硬盘）**                       |
> | -------------- | --------------------------------------------------------- | ----------------------------------------- |
> | **存储介质**   | 闪存芯片（NAND Flash）                                    | 磁性盘片（Spinning Platter）              |
> | **速度**       | **快**：读写速度通常为 500 MB/s ~ 7,000 MB/s（NVMe 更快） | **慢**：读写速度通常为 50 MB/s ~ 150 MB/s |
> | **耐用性**     | **好**：无机械部件，抗震性能强，不易损坏                  | **较差**：机械部件易受震动影响，容易磨损  |
> | **噪音**       | **静音**：无机械运动，无噪音                              | **有噪音**：磁盘旋转与磁头运动会产生声音  |
> | **功耗**       | **低**：更节能，适合便携设备                              | **高**：需要驱动电机，耗电较大            |
> | **容量**       | 容量较小，主流为 256 GB ~ 4 TB                            | 容量大，主流为 1 TB ~ 20 TB               |
> | **价格**       | **贵**：每 GB 成本较高                                    | **便宜**：每 GB 成本较低                  |
> | **寿命**       | **有限写入寿命**：有写入次数限制，但现代 SSD 已大幅改善   | **长寿命**：如果维护得当，可长时间使用    |
> | **体积与重量** | **小巧轻便**：适合轻薄设备                                | **笨重**：体积较大，重量较重              |
> | **碎片影响**   | **无影响**：数据分布不影响速度                            | **明显**：碎片化严重时，性能下降          |
> | **启动时间**   | **快**：几乎瞬间响应                                      | **慢**：需要等待磁盘旋转达到工作状态      |

### Locality (局部性)

**temporal locality and spatial locality**时间局部性与空间局部性

![image-20241216204634481](assets/Locality.png)

> 时间局部性：在一段时间内，程序倾向于访问同一数据
>
> 空间局部线：在一段时间内，程序倾向于访问与最近访问的数据地址相邻的数据

**Memory Hierarchy(存储层次)**

![image-20241216204943801](assets/Hierarchy.png)

> [!Important]
>
> **the core of hierarchy**: `cache`
>
> the faster and smaller storage device at level k serves as a cahce for the large and slower storage device at level k + 1
>
> cache都本质是下层都副本(copies)
>
> ![image-20241216205219551](assets/copy.png)



各种各样都Cache

![image-20241216205251429](assets/各种各样都Cache.png)

### 重点章节：Cache Memories

#### Cache匹配

图示：二路组相联

![image-20241217092223518](assets/Cache一图流.png)

> [!Important]
>
> Cache参数列表
>
> ![image-20241217092313591](assets/Cache_paramenters.png)

关键三步走：组选择(set selection)、行匹配(line matching)、字抽取(word extraction)

> 是通过主存地址匹(mm address)配对应的Cache
>
> 组选择：根据Set index选择对应的组
>
> 行匹配：通过在对应都set内比较Tag标签和vaild位是否有效判断Cache是否命中
>
> 若命中则进入字抽取阶段
>
> 根据offest位判断抽取Cache行对应都第几块内容

Chatgpt写的[Cache模拟器](./Cache.html)

**直接映射(direct-mapped)**

![image-20241217100044958](assets/Direct_Map.png)

> [!Note]
>
> **thrashing(抖动)** 直接映射有个很严重都问题(组相联也有但要好一点)，不同都地址会被映射到同一个Cache行上，可能导致Cache行不停都换入换出。
>
> 例子：
>
> ```c
> float dotprod(float x[8], float y[8]) {
>     float sum = 0. 0;
>     int i = 0;
>     
>     for (i = 0; i < 8; i++)
>         	sum += x[i] * y[i];
>     return sum;
> }
> ```
>
> ![image-20241217101331502](assets/thrashing.png)
>
> 容易发现每次访问x[i]时会把x对应都block写入cache，但y[i]与x[i]对应都cache行号一致导致每次访问y[i]都会导致x[i]被重写，导致频繁都换入换出。
>
> 解决办法:
>
> 1. 让y[i]与x[i]分别存放在不同都cache行中 (用空间换)
>
> ![image-20241217101724256](assets/Sol1.png)
>
> 2. 采用全相联(用钱换)

> [!Caution]
>
> 为啥用把set index放在中间，而不是高位呢？
>
> **均匀分布内存地址**，避免局部性导致组冲突。
>
> **利用空间局部性**，提升缓存性能。
>
> **简化硬件实现**，减少复杂性。
>
> **优化标记长度**，节省存储和比较开销。
>
> **保留高位的层次信息**，为地址管理和内存优化提供更好的支持

