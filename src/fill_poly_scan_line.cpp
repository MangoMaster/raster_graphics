// encoding: utf-8
#include <opencv2/opencv.hpp>
#include <forward_list>
#include "main.h"

// 按照插入排序的方法，将节点插入有序链表，使之按x递增排列
void insertSorted(std::forward_list<EdgeTableNode> &sorted_list, const EdgeTableNode &node)
{
    auto iter_prev = sorted_list.before_begin();
    auto iter = sorted_list.begin();
    while (iter != sorted_list.end() && iter->x < node.x)
    {
        iter_prev = iter;
        ++iter;
    }
    sorted_list.insert_after(iter_prev, node);
}

// 冒泡排序，按x递增排列
void bubbleSort(std::forward_list<EdgeTableNode> &list)
{
    auto sort_tail = list.end();
    // 无节点时，已经有序
    bool sorted = (list.begin() == list.end());
    // 已经有序时终止
    while (!sorted)
    {
        sorted = true;
        // 从头开始排序，sort_tail及之后的节点已经就位
        auto iter = list.begin();
        auto iter_next = ++list.begin();
        while (iter_next != sort_tail)
        {
            if (iter->x > iter_next->x)
            {
                sorted = false;
                // 交换iter和iter_next的内容
                std::iter_swap(iter, iter_next);
            }
            iter = iter_next;
            ++iter_next;
        }
        sort_tail = iter; // sort_tail前移一位
    }
}

// 更新结点的x，移除y_max的结点，再次排序
void update(std::forward_list<EdgeTableNode> &active_edge_table, int y_max)
{
    for (auto iter_prev = active_edge_table.before_begin(), iter = active_edge_table.begin();
         iter != active_edge_table.end();)
    {
        if (iter->y_max == y_max)
            // 移除y_max的结点
            iter = active_edge_table.erase_after(iter_prev);
        else
        {
            // 更新x
            iter->x += iter->delta_x;
            // 更新iter
            iter_prev = iter;
            ++iter;
        }
    }
    // 最后重新排序
    bubbleSort(active_edge_table);
}

void fill(std::forward_list<EdgeTableNode> &active_edge_table, cv::Mat &image, int y, const cv::Scalar &color)
{
    // 空AET特殊处理
    if (active_edge_table.begin() == active_edge_table.end())
        return;

    for (auto iter_prev = active_edge_table.before_begin(), iter = active_edge_table.begin(), iter_next = ++active_edge_table.begin();
         iter_next != active_edge_table.end();)
    {
        // 扫描线与多边形顶点相交
        if (round(iter->x) == round(iter_next->x))
            // 扫描线与多边形边重合已在NET中处理
            if (iter->y_max == y)
            {
                if (iter_next->y_max == y)
                {
                    // 两边位于扫描线下侧，计0个交点
                    // 移除iter和iter_next
                    iter_next = active_edge_table.erase_after(iter);
                    ++iter_next;
                    iter = active_edge_table.erase_after(iter_prev);
                }
                else
                {
                    // 两边位于扫描线两侧，计1个交点
                    // 移除iter
                    iter = active_edge_table.erase_after(iter_prev);
                    ++iter_next;
                }
            }
            else if (iter_next->y_max == y)
            {
                // 两边位于扫描线两侧，计1个交点
                // 移除iter_next
                iter_next = active_edge_table.erase_after(iter);
            }
            else // 两边位于扫描线上侧，计2个交点，不处理
            {
                iter_prev = iter;
                iter = iter_next;
                ++iter_next;
            }
        else
        {
            iter_prev = iter;
            iter = iter_next;
            ++iter_next;
        }
    }

    // 空AET特殊处理
    if (active_edge_table.begin() == active_edge_table.end())
        return;

    for (auto iter = active_edge_table.begin(); iter != active_edge_table.end(); ++iter, ++iter)
    {
        auto iter_next = std::next(iter);
        for (int x = iter->x; x <= iter_next->x; ++x)
            drawPixel(image, x, y, color);
    }
}

// 多边形的扫描转换-扫描线算法
// 输入vertices为每个多边形轮廓的顶点序列，n_vertices为每个多边形轮廓的顶点数，n_contours为多边形轮廓数
void fillPolyScanLine(cv::Mat &image, const cv::Point **vertices, const int *n_vertices, int n_contours, const cv::Scalar &color)
{
    // 初始化NET
    std::forward_list<EdgeTableNode> new_edge_table[image.rows];
    int y_min = image.rows;
    int y_max = 0;
    for (int i = 0; i < n_contours; ++i)
    {
        // 将首尾结点连边放入NET
        if (vertices[i][0].y < vertices[i][n_vertices[i] - 1].y)
        {
            new_edge_table[vertices[i][0].y].emplace_front(vertices[i][0].x, vertices[i][n_vertices[i] - 1].y,
                                                           double(vertices[i][n_vertices[i] - 1].x - vertices[i][0].x) / (vertices[i][n_vertices[i] - 1].y - vertices[i][0].y));
            // 更新y_min
            if (vertices[i][0].y < y_min)
                y_min = vertices[i][0].y;
        }
        else if (vertices[i][0].y > vertices[i][n_vertices[i] - 1].y)
        {
            new_edge_table[vertices[i][n_vertices[i] - 1].y].emplace_front(vertices[i][n_vertices[i] - 1].x, vertices[i][0].y,
                                                                           double(vertices[i][0].x - vertices[i][n_vertices[i] - 1].x) / (vertices[i][0].y - vertices[i][n_vertices[i] - 1].y));
            // 更新y_max
            if (vertices[i][0].y > y_max)
                y_max = vertices[i][0].y;
        }
        else // vertices[i][0].y == vertices[i][n_vertices[i] - 1].y
        {
            // 两边位于扫描线两侧时，需要结点
            if ((vertices[i][n_vertices[i] - 2].y < vertices[i][0].y && vertices[i][1].y > vertices[i][0].y) ||
                (vertices[i][n_vertices[i] - 2].y > vertices[i][0].y && vertices[i][1].y < vertices[i][0].y))
            {
                new_edge_table[vertices[i][0].y].emplace_front(vertices[i][0].x, vertices[i][0].y, INFINITY);
            }
            // 更新y_min和y_max
            if (vertices[i][0].y < y_min)
                y_min = vertices[i][0].y;
            else if (vertices[i][0].y > y_max)
                y_max = vertices[i][0].y;
        }
        // 将其他边放入NET
        for (int j = 1; j < n_vertices[i]; ++j)
        {
            if (vertices[i][j - 1].y < vertices[i][j].y)
            {
                new_edge_table[vertices[i][j - 1].y].emplace_front(vertices[i][j - 1].x, vertices[i][j].y,
                                                                   double(vertices[i][j].x - vertices[i][j - 1].x) / (vertices[i][j].y - vertices[i][j - 1].y));
                // 更新y_max
                if (vertices[i][j].y > y_max)
                    y_max = vertices[i][j].y;
            }
            else if (vertices[i][j - 1].y > vertices[i][j].y)
            {
                new_edge_table[vertices[i][j].y].emplace_front(vertices[i][j].x, vertices[i][j - 1].y,
                                                               double(vertices[i][j - 1].x - vertices[i][j].x) / (vertices[i][j - 1].y - vertices[i][j].y));
                // 更新y_min
                if (vertices[i][j].y < y_min)
                    y_min = vertices[i][j].y;
            }
            else // vertices[i][j - 1].y == vertices[i][j].y
            {
                // 两边位于扫描线两侧时，需要结点
                if (j == 1)
                {
                    if ((vertices[i][n_vertices[i] - 1].y < vertices[i][j].y && vertices[i][j + 1].y > vertices[i][j].y) ||
                        (vertices[i][n_vertices[i] - 1].y > vertices[i][j].y && vertices[i][j + 1].y < vertices[i][j].y))
                    {
                        new_edge_table[vertices[i][j].y].emplace_front(vertices[i][j].x, vertices[i][j].y, INFINITY);
                    }
                }
                else if (j == n_vertices[i] - 1)
                {
                    if ((vertices[i][j - 2].y < vertices[i][j].y && vertices[i][0].y > vertices[i][j].y) ||
                        (vertices[i][j - 2].y > vertices[i][j].y && vertices[i][0].y < vertices[i][j].y))
                    {
                        new_edge_table[vertices[i][j].y].emplace_front(vertices[i][j].x, vertices[i][j].y, INFINITY);
                    }
                }
                else
                {
                    if ((vertices[i][j - 2].y < vertices[i][j].y && vertices[i][j + 1].y > vertices[i][j].y) ||
                        (vertices[i][j - 2].y > vertices[i][j].y && vertices[i][j + 1].y < vertices[i][j].y))
                    {
                        new_edge_table[vertices[i][j].y].emplace_front(vertices[i][j].x, vertices[i][j].y, INFINITY);
                    }
                }
                // 更新y_min和y_max
                if (vertices[i][j].y < y_min)
                    y_min = vertices[i][j].y;
                else if (vertices[i][j].y > y_max)
                    y_max = vertices[i][j].y;
            }
        }
    }

    std::forward_list<EdgeTableNode> active_edge_table;
    for (int y = y_min; y <= y_max; ++y)
    {
        for (auto iter = new_edge_table[y].begin(); iter != new_edge_table[y].end(); ++iter)
            insertSorted(active_edge_table, *iter);
        fill(active_edge_table, image, y, color);
        update(active_edge_table, y);
    }
}