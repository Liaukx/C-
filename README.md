# C-
大一下课程设计，无GUI，基于文件

* 设计一个管理系统
-	系统功能结构
* 给系统管理者和使用者提供不同的功能。
* 管理者：增加新书，删除已有图书，浏览全部
* 使用者：借阅图书，归还图书，浏览全部 
-	类设计
* account类——记录使用者账户
账户id
recordMap记录该账户借还记录
* Date类——记录借还书的时间
年 月 日
* Book类——书籍信息
图书名 作者 ISBN 价格  数目
* schedule类 ——修改库存书籍数目
增加或减少Book对象的数目
-	UML图
  
![image](https://github.com/Liaukx/C-/blob/main/image/%E5%9B%BE%E4%B9%A6%E7%AE%A1%E7%90%86%E7%B3%BB%E7%BB%9F%E7%B1%BB%E8%AE%BE%E8%AE%A1.jpg)
 
具体实现见代码

 
反思

通过设计管理系统，体会到这些思想在实际问题中的重要意义。
本来，借鉴课本的银行账目管理系统，想尽可能把这学期学到的重点都用到自己的课程设计里，可是在设计的时候情况百出，一个是理不清各个类之间的关系，另一个是被继承束缚着。但其实达到一个共能可以用的方法有很多。在以后的工程实践中应该选择更适合的方法。
遗憾的是，我的课程设计里没有继承和虚函数。本来设计类的时候想要把管理人员和普通用户设计成两个用户类，account是抽象类。但是感觉这增加了本系统的复杂度，特别是在账目登录，信息加载与查询问题里就会变得特别麻烦（因为只使用文件读写，不用数据库），相应的，如果把文件信息放到数据库里，很多功能都会变得容易起来，而且查询效率也会显著提升。只是时间关系，放弃了对数据库的学习。
再者就是对异常的处理，没有使用系统函数来throw异常，而是自己编写了简单的异常处理，深表遗憾。

