<!-- encoding: utf-8 -->
# 光栅图形学

计算机图形学小作业

## 作者

魏家栋，计72，学号2017011445

## 项目结构

- [报告](./doc/report.md)见doc文件夹
- 源代码见src文件夹
- 测试代码见test文件夹

## 编译与运行

运行源程序：
```sh
cd ./src
make
./main
```

运行测试程序：其中TEST为进行的测试名，可选项有 line_bresenham, circle_midpoint, polylines_bresenham, flood_fill_scan_line, flood_fill_scan_line_bresenham 。
```sh
cd ./test
make TEST
./main
```