> SCU 数据结构课设

# 目录

[TOC]

# 数据结构与算法分析课程设计实验报告

> 基于哈夫曼编码的压缩与解压缩软件

## 一、问题描述

用哈夫曼编码设计一个压缩软件

## 二、基本要求

要求此软件能对输入的任何类型文件进行哈夫曼**编码**，产生编码后的压缩文件，也能对输入的压缩文件进行**译码**， 生成原文件。

## 三、工具/准备工作

首先在进行此次设计前，我先对于课上所讲授的哈夫曼编码的有关知识进行了系统的复习。实现本次课程设计所采用的C++集成开发环境软件为**[CLion](https://www.jetbrains.com/clion/)**，同时，为了实现最后的GUI功能，由于使用的软件为Clion并非Visual Studio，无法使用MFC库。因此为了实现软件最后的GUI功能，还安装了[**Qt5.14.2**](http://iso.mirrors.ustc.edu.cn/qtproject/archive/qt/5.14/5.14.2/qt-opensource-windows-x86-5.14.2.exe)用于实现最终的GUI功能。到此，所有前期准备工作全部完成。

## 四、分析与实现

### 1.哈夫曼树结构

为了实现哈夫曼编码首先应该实现哈夫曼树。由于C++中char型变量位数为8，因此哈夫曼树的叶子节点最多为256个，因此此处给出哈夫曼树的节点类的实现，tree数组为最终构成的哈夫曼树。

```c++
// 节点类
class Node {
private:
    char val;
    int w;
    int index, l = 0, r = 0, p = 0, code_len = 0;
public:
    char code[255];
};
// 哈夫曼树数组
Node *tree = new Node[256 * 2];
```

下表为相关变量解释：

| 变量        | 解释           |
| ----------- | -------------- |
| `val`       | 节点所代表的值 |
| `w`         | 权重           |
| `index`     | 节点下标       |
| `l`         | 节点左儿子下标 |
| `r`         | 节点右儿子下标 |
| `p`         | 节点父节点下标 |
| `code_len`  | 编码长度       |
| `code[255]` | 对应的编码     |

### 2.文件读取

   为了方便每一次对于的文件的读写，本次设计中专门基于C++ fstream封装了一个用于文件读写的`FileOperation`类。该类可以完成对于文件的二进制读写，方便了后续代码的编写。

   ```C++
   class FileOperation {
   private:
       char *Buffer;
       fstream f;
       int length;
       string path;
   public:
       ~FileOperation();
       void setPath(string Path);
       void BinaryRead();
       void BinaryWrite();
       char *getBuffer();
       void setBuffer(char Buffer[], int length);
       int Length() const;
   };
   ```

   下表为相关变量以及成员函数解释

   | 名称                                         | 解释                 |
   | -------------------------------------------- | -------------------- |
   | `Buffer`                                     | 用于储存读取到的数据 |
   | `f`                                          | 文件流               |
   | `length`                                     | Buffer数组的长度     |
   | `path`                                       | 文件路径             |
   | `~FileOperation()`                           | 析构函数             |
   | `void setPath(string Path)`                  | 设置读取文件的路径   |
   | `void BinaryRead();`                         | 文件读               |
   | `void BinaryWrite();`                        | 文件写               |
   | `har *getBuffer();`                          | 获取`Buffer`         |
   | `void setBuffer(char Buffer[], int length);` | 设置`Buffer`         |
   | `int Length() const;`                        | 获取`length`         |

### 3.建立哈夫曼树

建立哈夫曼树的大致思路如下：

- 首先先对文件进行二进制读取，储存在Buffer数组中，读取操作如下：

  ```c++
  FileOperation fileOp;
  fileOp.setPath(Path);
  fileOp.BinaryRead();
  ```
  
- 使用`CountData`函数统计不同char值出现的频率，并储存在`map`中，并且为了使后续建立哈夫曼树更加方便，此处使用C++ STL中的优先队列`priority_queue`根据不同节点的频率排序储存，并且返回最终的优先队列，其中`CountData`函数实现如下：

  ```c++
  priority_queue<Node> static CountData(char Buffer[], int size) {
      map<int, int> counters;
      priority_queue<Node> q;
      for (int i = 0, tmp; i < size; i++) {
          tmp = (int) Buffer[i];
          if (!counters.count(tmp)) {
              counters.insert({tmp, 1});
          } else {
              counters[tmp]++;
          }
      }
      auto it = counters.begin();
      while (it != counters.end()) {
          q.push(*(new Node(it->first, it->second)));
          it++;
      }
      return q;
  }
  ```

- 最后使用`CountData`中获取的优先队列进行哈夫曼树的建立，原理为每次从优先队列中获取头两个结点加入到树中，并且新生成一个权重为刚刚那两个节点权重之和的节点加入到队列中，循环此过程，直至队列为空，具体实现如下：

  ```c++
  pair<Node *, int> static CreateHuffmanTree(priority_queue<Node> q) {
      Node *result = new Node[2 * q.size() + 1];
      Node VOID;
      result[0] = VOID;
      int idx = 0;
      while (true) {
          auto FirstNode = q.top();
          q.pop();
          auto SecondNode = q.top();
          q.pop();
          FirstNode.setIndex(++idx);
          result[idx] = FirstNode;
          SecondNode.setIndex(++idx);
          result[idx] = SecondNode;
          if (FirstNode.getL() != 0 && FirstNode.getR() != 0) {
              result[FirstNode.getL()].setP(FirstNode.getIndex());
              result[FirstNode.getR()].setP(FirstNode.getIndex());
          }
          if (SecondNode.getL() != 0 && SecondNode.getR() != 0) {
              result[SecondNode.getL()].setP(SecondNode.getIndex());
              result[SecondNode.getR()].setP(SecondNode.getIndex());
          }
          Node newNode(0, FirstNode.getW() + SecondNode.getW(), FirstNode.getIndex(), SecondNode.getIndex());
          q.push(newNode);
          if (q.size() == 1) {
              result[++idx] = q.top();
              result[idx].setIndex(idx);
              result[result[idx].getL()].setP(result[idx].getIndex());
              result[result[idx].getR()].setP(result[idx].getIndex());
              return {result, idx};
          }
      }
  }
  ```

  到此哈夫曼树建立完成

### 4.构造哈夫曼编码

利用上一步以及创建好的哈夫曼树构造哈夫曼编码，从根节点开始，节点左边赋0，节点右边赋1，以此方式遍历整棵哈夫曼树最后得到对应的哈夫曼编码，最后返回一个`key`为`char`值，`value`为对应编码以及长度的`map`，具体实现如下：

```c++
map<char, pair<char *, int>> static HuffmanCode(pair<Node *, int> args) {
    map<char, pair<char *, int>> MII;
    Node *tree = args.first;
    int size = args.second;
    tree[size].code[0] = '\0';
    for (int i = size - 1; i > 0; i--) {
        strcpy(tree[i].code, tree[tree[i].getP()].code);
        if (tree[tree[i].getP()].getL() == i) {
            strcat(tree[i].code, "0");
        } else {
            strcat(tree[i].code, "1");
        }
        tree[i].setCode_len(strlen(tree[i].code));
        if (tree[i].getL() == 0 && tree[i].getR() == 0) {
            MII.insert({tree[i].getVal(), {tree[i].code, tree[i].getCode_len()}});
        }
    }
    return MII;
}
```

### 5.生成压缩文件

这一步十分简单，只需要将文件读写类中的Buffer中的所有char都对应替换为对应的哈夫曼编码，最后文件长度不是8的倍数的话则补齐，防止文件读写过程中出错，最终返回编码结果以及编码长度，具体实现如下：

```c++
pair<char *, int> static Encode(char Buffer[], int length, map<char, pair<char *, int>> MCC) {
    string res;
    for (int i = 0; i < length; i++) {
        res += MCC[Buffer[i]].first;
    }
    int remainder = res.length() % 8;
    int cnt = (res.length() + ((remainder == 0) ? 0 : (8 - remainder))) / 8;
    char *result = new char[cnt];
    for (int i = 1; i <= 8 - remainder; i++)
        res += "0";
    for (int i = 0; i < cnt; i++) {
        result[i] = stoi(res.substr(i * 8, 8), 0, 2);
    }
    return {result, cnt};
}
```

### 6.生成解压文件

1. 首先先实现一个`change`函数，其功能为将一段8位二进制`char`转换为`int`，具体实现如下：

   ```c++
   inline string change(char c) {
       string data;
       for (int i = 0; i < 8; i++)
           if ((c >> (i - 1)) & 0x01 == 1)
               data += "1";
           else 
               data += "0";
       for (int a = 1; a < 5; a++) {
           char x = data[a];
           data[a] = data[8 - a];
           data[8 - a] = x;
       }
       return data;
   }
   ```

2. 其次实现一个`CodeTurnover`函数，将生成的哈夫曼编码转置，以达到解码的效果，具体实现如下：

   ```c++
   map<string, char> static CodeTurnover(map<char, pair<char *, int>> MCC) {
       map<string, char> mcc;
       auto it = MCC.begin();
       while (it != MCC.end()) {
           mcc.insert({it->second.first, it->first});
           it++;
       }
       return mcc;
   }
   ```

3. 最后利用`1. 2.`中实现的函数对已压缩的文件进行解压，具体过程为将读取到的`Buffer`每隔8位进行一次解码，最后得到原文件，具体实现如下：

   ```c++
   string static Decode(char *Buffer, int length, map<string, char> MCC) {
       string data;
       for (int i = 0; i < length; i++) {
           data += change(Buffer[i]);
       }
       string tmp, DataOrigin;
       for (int i = 0; i < data.length(); i++) {
           tmp += data[i];
           if (MCC.count(tmp)) {
               DataOrigin += MCC[tmp];
               tmp = "";
           }
       }
       return DataOrigin;
   }
   ```

### 7.储存哈夫曼树等信息

为了使压缩和解压具有可逆性，即在不同时间也可对文件进行解压，需要对于源文件的部分信息进行保存，具体体现为保存哈夫曼树以及源文件的后缀，具体实现为下：

1. 保存源文件相关信息

   ```c++
   void static storeTree(map<char, pair<char *, int>> result, string path) {
       fstream fout(path, ios::binary | ios::out);
       fout.seekg(0, ios::beg);
       auto it = result.begin();
       while (it != result.end()) {
           fout.write((char *) &it->first, sizeof(char));
           fout.write((char *) &it->second.second, sizeof(int));
           for (int i = 0; i < it->second.second; i++)
               fout.write((char *) &it->second.first[i], sizeof(char));
           it++;
       }
       fout.close();
   }
   ```

2. 读取源文件相关信息

   ```c++
   map<char, pair<char *, int>> static attainTree(string path) {
       map<char, pair<char *, int>> tmp;  char a;  int c;
       fstream fin(path, ios::binary | ios::in);
       fin.seekg(0, ios::beg);
       while (!fin.eof()) {
           fin.read((char *) &a, sizeof(char));
           fin.read((char *) &c, sizeof(int));
           char *b = new char[c];
           for (int i = 0; i < c; i++) {
               fin.read((char *) &b[i], sizeof(char));
           }
           tmp.insert({a, {b, c}});
       }
       fin.close();
       map<char, pair<char *, int>> result;
       auto it = tmp.begin();
       while (it != tmp.end()) {
           int a = it->second.second;
           char *temp = new char[a + 1];
           temp[a] = '\0';
           for (int i = 0; i < a; i++) {
               temp[i] = it->second.first[i];
           }
           result.insert({it->first, {temp, it->second.second}});
           it++;
       }
       return result;
   }
   ```

   

### 8.GUI功能实现

使用Qt库简单实现了该软件的GUI界面，GUI界面主要包含压缩以及解压两个按钮，功能简单，此处不过多赘述，界面类如下：

```c++
class GUI : public QDialog {
Q_OBJECT
public:
    GUI(QWidget *parent = 0);

private slots:
    void Compress();
    void Decompress();

private:
    QPushButton *compress;
    QPushButton *decompress;
    QLabel *Image;
};
```

具体实现代码过于冗长且意义不大，详情可见源码，此处展示核心事件代码

1. 压缩事件

   ```c++
   FileOperation fileOp;
   fileOp.setPath(Path);
   fileOp.BinaryRead();
   auto q = CountData(fileOp.getBuffer(), fileOp.Length());
   pair<Node *, int> res = CreateHuffmanTree(q);
   map<char, pair<char *, int>> result = HuffmanCode(res);
   try {
       system("md d:\\Huffman_Compressor");
   } catch (exception e) {
       cout << e.what();
   }
   storeTree(result, "D:/Huffman_Compressor/" + name + "." + weightName);
   pair<char *, int> finalResult = Encode(fileOp.getBuffer(), fileOp.Length(), result);
   fileOp.setPath(resultPath);
   fileOp.setBuffer(finalResult.first, finalResult.second);
   fileOp.BinaryWrite();
   ```

2. 解压事件

   ```c++
   FileOperation fileOp;
   fileOp.setPath(Path);
   fileOp.BinaryRead();
   map<char, pair<char *, int>> weight = attainTree("D:/Huffman_Compressor/" + name + "." + w);
   string OriginData = Decode(fileOp.getBuffer(), fileOp.Length(), CodeTurnover(weight));
   fileOp.setPath(resultPath);
   fileOp.setBuffer(const_cast<char *>(OriginData.c_str()), OriginData.length());
   fileOp.BinaryWrite();
   ```

## 五、测试与结论

### 1.GUI界面展示

![image-20221205201421731](C:\Users\TBK\AppData\Roaming\Typora\typora-user-images\image-20221205201421731.png)

<table rules="none" align="center">
	<tr>
		<td>
			<center>
				<img src="C:\Users\TBK\AppData\Roaming\Typora\typora-user-images\image-20221205201741485.png" width="60%" />
				<br/>
				<font color="AAAAAA">解压</font>
			</center>
		</td>
		<td>
			<center>
				<img src="C:\Users\TBK\AppData\Roaming\Typora\typora-user-images\image-20221205201517652.png" width="60%" />
				<br/>
				<font color="AAAAAA">压缩<font>
			</center>
		</td>
	</tr>
</table>

### 2.功能测试

此处测试文本文件（txt）以及图片文件（jpg）。

1. 文本文件 

   ![](C:\Users\TBK\AppData\Roaming\Typora\typora-user-images\image-20221205202558509.png)
   
   如图所示，压缩率大致为50%，现在对其解压。
   
   ![image-20221205202944520](C:\Users\TBK\AppData\Roaming\Typora\typora-user-images\image-20221205202944520.png)

​		如图所示，解压成功

2. 图片文件

   ![image-20221205203328542](C:\Users\TBK\AppData\Roaming\Typora\typora-user-images\image-20221205203328542.png)

​		如图所示，压缩成功，但是压缩率一般，下面进行解压![image-20221205203556536](C:\Users\TBK\AppData\Roaming\Typora\typora-user-images\image-20221205203556536.png)

​		如图所示，解压成功。

### 3.结论

本课程设计程序满足课程设计题目的要求。

## 六、课程设计总结

1. 此次课程设计利用哈夫曼编码算法并使用Qt库，完成了一个压缩与解压缩软件的实现。在设计过程中多处使用了C++ STL中内置的数据结构，如在构造哈夫曼树的过程中使用优先队列`priority_queue`以及在不同函数中传值时使用`map`,`pair`等数据结构，使得开发过程变得更加快捷、方便；
2. 经过多次测试之后，发现txt等文本文件压缩效率可达40%~60%，压缩效率相当可观。可是对于jpg、png等图像文件，压缩效率普遍较低，大约10%~20%，压缩效率较低。在经过大量资料查阅后得知由于图像文件的哈夫曼树节点较多，导致哈夫曼编码的平均长度大约为7.5（未压缩长度为8），哈夫曼编码的平均长度并不低，导致压缩率变低。并且目前市场上常用的压缩软件所采用的方法并不只是单纯的哈夫曼编码压缩，因此此软件对于图像文件的压缩率低的问题是图像文件储存格式以及哈夫曼编码自身问题导致。