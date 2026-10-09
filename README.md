# Any Base Converter / 任意进制互转

> 支持 2~36 进制互转，整数与小数，提供 Web、Python、C++ 三种实现。  
> Convert numbers between any bases (2-36), with integer and fraction support.

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Bases](https://img.shields.io/badge/bases-2%20~%2036-brightgreen.svg)
![Languages](https://img.shields.io/badge/languages-Web%20%7C%20Python%20%7C%20C%2B%2B-orange.svg)

---

## ✨ 特性

- ✅ 支持 **2 ~ 36** 任意进制互转
- ✅ 支持 **整数、小数、正负数**
- ✅ 自动去除小数末尾多余的 0
- ✅ 无限循环小数按指定精度截断（默认 30 位）
- ✅ 三种实现：**Web (HTML/JS)**、**Python**、**C++**
- ✅ **不依赖大数库**，基于数字数组的长除法 / 长乘法，可处理超长数字
- ✅ 输入字符不区分大小写，支持 `0-9`、`A-Z`

---

## 📁 目录结构
```

any-base-converter/
├── web/
│ └── index.html # 网页版，浏览器直接打开
├── python/
│ └── base_converter.py # Python 命令行版
├── cpp/
│ └── base_converter.cpp # C++ 命令行版
├── LICENSE
└── README.md

按提示依次输入源进制、目标进制和数值。
```
