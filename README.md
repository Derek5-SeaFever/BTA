# BTA

可批量、快速将BiliBili视频 BV号转换成 AV 号

## 参数列表

1. BTA -d/D dirPath
  + dirPath 为批量从文件读取 BV 号的文件路径
2. BVxxxxxxxxxx/bvxxxxxxxxxx/xxxxxxxxxx
  + xxxxxxxxxx 表示 BV 号(不带 BV 头)
  + 可同时传递多个 BV 号做参数
  + 但是必须声明在 -d/D 参数前，否则无效
3. - v/V/H/h
  + 查看相关信息

## 错误列表

ERROR1 - 无法读取 BV 号文件

**解决：**请确保文件真实存在，并检查文件路径是否正确！

ERROR2 - 无法创建 AV 号文件

**解决：**确保本程序拥有在当前目录下创建TXT文件的权利，可以使用管理员身份调用本程序

ERROR3 - BV 号转化错误

**解决：**这往往是由于 BV 号位数不正确造成的！

1. 检查 BV/bv 是否写成了 Bv/bV ,默认只以全大写或全小写的 BV 作为 BV 头；
2. 一般 BV 号是 10 位，检查是否超出。

ERROR4 - AV 号不存在

**解决：**这是因为转换后的 AV 号小与 0 或大于 100000000 (即不合法 AV 号格式)造成的，请确保 BV 号是正确的格式

ERROR5 - 无效参数

**解决：**默认只支持 -d/D 或 -v/V/H/h 或 BV 号三种参数形式。

ERROR6 - 检测到非法字符 X

**解决：**这是由于传入的 BV 号包含非法字符(非字母)造成的，而且常出现在从文件读取 BV 号时。

ERROR7 - 检测到非法字符 X

**解决：**这是由于传入的  BV 号不合法造成的。非法字目有：_数字_**0**、_大写字母_**I**、_大写字幕_**O** 和 _小写字母_**l**。

## 常见问题

如果发现 AVList.txt 中输出 av0 ，请小心检查！这往往时 ERROR6 和 ERROR7 造成的；

[博客链接](https://www.cnblogs.com/seafever/BTA.html)
