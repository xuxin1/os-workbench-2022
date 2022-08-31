# 实验 M1 🧪

* 实验地址(https://jyywiki.cn/OS/2022/labs/M1)

## 实验资料 📚
* linux /proc 文件详解 (https://jyywiki.cn/OS/2022/labs/M1)
* c 语言 file 操作 (https://blog.csdn.net/zhanghaiyang9999/article/details/107032563)
* c 语言 file dir 操作 (https://blog.csdn.net/dream_allday/article/details/75243818)
  

 ## 实验目的 🎯
 
 * 实现pstree 命令
 * Linux 系统中可以同时运行多个程序。运行的程序称为进程。除了所有进程的根之外，每个进程都有它唯一的父进程，你的任务就是把这棵树在命令行中输出。你可以自由选择展示树的方式 (例如使用缩进表示父子关系，这是最容易的)。
## 预期结果
* `pstree [OPTION]…`
  * `-p, --show-pids: 打印每个进程的进程号。`
  * `-n --numeric-sort: 按照pid的数值从小到大顺序输出一个进程的直接孩子。`
  * `-V --version: 打印版本信息。`
## 实验步骤

- 获取进程号
  - 读取 /proc 目录下的 数字编号文件夹名称（数字为进程的PID）
  - 读取 /proc/number/status 文件中的信息 （获取PID 和 PPID）
- 通过 PID 和 PPID 建立进程间的相关联系
- 构建进程树 (按照pid)
- 实现 CLI 参数解析

## 实验问题 🤔

* [ ] 你的程序遵守 POSIX 的返回值规定吗？如果你的 main 函数返回了非 0 的数值，我们将认为程序报告了错误——在非法的输入上返回 0，以及在合法的输入上返回非 0 都将导致 Wrong Answer。
* [ ] 程序够 roubust 吗？它会不会在一些非法的输入上 crash？如果系统里的进程很多呢？如果内存不够了呢？如果 open 或者 malloc 失败了呢？要知道，crash 一般是因为 undefined behavior (UB) 导致的——UB 没把所有的文件都删掉真是谢天谢地了。
* [ ] 万一我得到进程号以后，进去发现文件没了 (进程终止了)，怎么办？会不会有这种情况？万一有我的程序会不会 crash……？
* [ ] 进程的信息一直在变，文件的内容也一直在变 (两次 cat 的结果不同)。那我会不会读到不一致的信息(前一半是旧信息、新一半是新信息)？这两个问题都是 race condition 导致的；我们将会在并发部分回到这个话题。