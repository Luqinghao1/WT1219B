#include "mousezoom.h"
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QClipboard>

MouseZoom::MouseZoom(QWidget *parent) : QCustomPlot(parent)
{
    setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectLegend);
    setBackground(Qt::white);
    axisRect()->setBackground(Qt::white);
}

void MouseZoom::wheelEvent(QWheelEvent *event)
{
    Qt::MouseButtons buttons = QApplication::mouseButtons();
    axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
    if (buttons & Qt::LeftButton)
        axisRect()->setRangeZoom(Qt::Vertical);
    else if (buttons & Qt::RightButton)
        axisRect()->setRangeZoom(Qt::Horizontal);
    QCustomPlot::wheelEvent(event);
    axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
}

// [新增] 实现通用表格右键菜单
void MouseZoom::addTableContextMenu(QTableWidget* table) {
    if (!table) return;
    table->setContextMenuPolicy(Qt::CustomContextMenu);

    // 使用 lambda 表达式连接信号，避免需要额外的槽函数
    connect(table, &QTableWidget::customContextMenuRequested, table, [table](const QPoint& pos) {
        QMenu menu;
        QAction* actCopy = menu.addAction("复制内容");

        // 简单的复制逻辑：复制当前选中的单元格文本或控件内的文本
        QObject::connect(actCopy, &QAction::triggered, [table]() {
            QString text = "";
            QList<QTableWidgetItem*> items = table->selectedItems();
            if (!items.isEmpty()) {
                text = items.first()->text();
            } else {
                // 如果是 Widget（如 LineEdit），尝试获取焦点控件的文本
                QWidget* w = table->focusWidget();
                if (QLineEdit* le = qobject_cast<QLineEdit*>(w)) {
                    text = le->text();
                }
            }
            if(!text.isEmpty()) QApplication::clipboard()->setText(text);
        });

        menu.exec(table->mapToGlobal(pos));
    });
}
