[TOC]

## The Memory Hierarchy(分层)

内存系统最重要的特点就是**利用局部性(locality)**

### Storage Technologies

> # Topic
>
> - Random Accesss Memory(RAM)
>   - static RAM
>   - dynamic RAM

> ## SRAM VS DRAM
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
> >  ### **通过这种方式可以使地址引脚(pins)减半！**
>
> **典型字拓展（并联）**  8M * 8 ----> 8M * 64
>
> ![image-20241213221109680](assets/多块DRAM组合.png)



