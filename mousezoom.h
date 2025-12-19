#ifndef MOUSEZOOM_H
#define MOUSEZOOM_H

#include "qcustomplot.h"
#include <QTableWidget>

/**
 * @brief 增强型绘图控件 (MouseZoom)
 * 继承自 QCustomPlot，提供针对试井分析优化的交互体验。
 * 1. 滚轮缩放：默认全向，按住左键纵向缩放，按住右键横向缩放。
 * 2. 提供通用辅助功能（如表格右键菜单）。
 */
class MouseZoom : public QCustomPlot
{
    Q_OBJECT
public:
    explicit MouseZoom(QWidget *parent = nullptr);

    // [新增] 静态辅助函数：为表格添加通用右键菜单（复制等）
    static void addTableContextMenu(QTableWidget* table);

protected:
    void wheelEvent(QWheelEvent *event) override;
};

#endif // MOUSEZOOM_H
