/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
//
//  AFTER TEST
//


#include "arrow.h"
#include "diagramitem.h"
#include "diagramscene.h"
#include "diagramtextitem.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QtWidgets>
//#include "commands.h"

const int InsertTextButton = 10;


struct save_arrow{
    quint16 source;
    quint16 target;
};

QDataStream & operator << (QDataStream & out,const save_arrow & arrow){
    return out << arrow.source << arrow.target;

}
//! [0]
MainWindow::MainWindow()
{
    createActions();
    createToolBox();
    createMenus();

    scene = new DiagramScene(itemMenu, this);
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));
    connect(scene, SIGNAL(itemInserted(DiagramItem*)),
            this, SLOT(itemInserted(DiagramItem*)));
    connect(scene, SIGNAL(textInserted(QGraphicsTextItem*)),
            this, SLOT(textInserted(QGraphicsTextItem*)));
    connect(scene, SIGNAL(itemSelected(QGraphicsItem*)),
            this, SLOT(itemSelected(QGraphicsItem*)));
    createToolbars();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(toolBox);
    view = new QGraphicsView(scene);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("Diagramscene"));
    setUnifiedTitleAndToolBarOnMac(true);
}
//! [0]

//! [1]
void MainWindow::backgroundButtonGroupClicked(QAbstractButton *button)
{
    undoFile();
    QList<QAbstractButton *> buttons = backgroundButtonGroup->buttons();
    foreach (QAbstractButton *myButton, buttons) {
        if (myButton != button)
            button->setChecked(false);
    }
    QString text = button->text();
    if (text == tr("Blue Grid"))
        scene->setBackgroundBrush(QPixmap(":/images/background1.png"));
    else if (text == tr("White Grid"))
        scene->setBackgroundBrush(QPixmap(":/images/background2.png"));
    else if (text == tr("Gray Grid"))
        scene->setBackgroundBrush(QPixmap(":/images/background3.png"));
    else
        scene->setBackgroundBrush(QPixmap(":/images/background4.png"));

    scene->update();
    view->update();
}
//! [1]

//! [2]
void MainWindow::buttonGroupClicked(int id)
{
    undoFile();
    QList<QAbstractButton *> buttons = buttonGroup->buttons();
    foreach (QAbstractButton *button, buttons) {
        if (buttonGroup->button(id) != button)
            button->setChecked(false);
    }
    if (id == InsertTextButton) {
        scene->setMode(DiagramScene::InsertText);
    } else {
        scene->setItemType(DiagramItem::DiagramType(id));
        scene->setMode(DiagramScene::InsertItem);
    }
}
//! [2]

//! [3]
void MainWindow::deleteItem()
{
    undoFile();
    foreach (QGraphicsItem *item, scene->selectedItems()) {
        if (item->type() == Arrow::Type) {
            scene->removeItem(item);
            Arrow *arrow = qgraphicsitem_cast<Arrow *>(item);
            arrow->startItem()->removeArrow(arrow);
            arrow->endItem()->removeArrow(arrow);
            delete item;
        }
    }

    foreach (QGraphicsItem *item, scene->selectedItems()) {
         if (item->type() == DiagramItem::Type)
             qgraphicsitem_cast<DiagramItem *>(item)->removeArrows();
         scene->removeItem(item);
         delete item;
     }
}
//! [3]

///////////////////////////////////////ADD CODE////////////////////////////////////////////////
void MainWindow::newA()
{
	MainWindow *newWin = new MainWindow;
	newWin->show();
}

inline QDataStream & operator <<(QDataStream & out, Arrow * &items){
    Arrow * itemArrow= qgraphicsitem_cast<Arrow*>(items);
    out<<itemArrow->pos();
    out<<itemArrow->zValue();
    //out<<itemArrow->myColor();
    out<<itemArrow->pen();
    out<<itemArrow->line();
    out<<itemArrow->scale();
    //out<<itemArrow->myColor;
    return out;
}
inline QDataStream & operator <<(QDataStream & out, DiagramTextItem * &items)
{
    DiagramTextItem * itemText = qgraphicsitem_cast<DiagramTextItem*>(items);
    out<<itemText->font();
    out<<itemText->zValue();
    out<<itemText->pos();
    out<<itemText->toPlainText();
    out<<itemText->defaultTextColor();

    return out;
}

inline QDataStream & operator <<(QDataStream & out, DiagramItem * &items)
{

    DiagramItem * itemShape = qgraphicsitem_cast<DiagramItem*>(items);
    out<<static_cast<int>(itemShape->diagramType());
    out<<itemShape->pos();
    out<<itemShape->zValue();
    out<<itemShape->brush();
    return out;

}

inline QDataStream & operator >>(QDataStream & in, Arrow * &items){
    QPointF arrowPos;
    qreal arrowZVal;
   // QColor arrowColor;
    QPen arrowPen;
    QLineF arrowLine;
    qreal arrowScale;
    DiagramItem * arrowStart;
    DiagramItem * arrowEnd;

    in >> arrowPos >> arrowZVal >> arrowPen >> arrowLine >> arrowScale;
    items = new Arrow(arrowStart,arrowEnd);
    items->setPos(arrowPos);
    items->setZValue(arrowZVal);
    //items->setColor(arrowColor);
    items->setPen(arrowPen);
    items->setLine(arrowLine);
    items->setScale(arrowScale);
    return in;
}

inline QDataStream & operator >>(QDataStream &in, DiagramTextItem * &items)
{
    QFont textFont;
    qreal textZVal;
    QPointF textPos;
    QString textToPlainText;
    QColor textDefaultTextColor;
    in >> textFont >> textZVal >> textPos >> textToPlainText >> textDefaultTextColor;
    items = new DiagramTextItem(NULL);
    items->setFont(textFont);
    items->setZValue(textZVal);
    items->setPos(textPos);
    items->setPlainText(textToPlainText);
    items->setDefaultTextColor(textDefaultTextColor);
    return in;
}
inline QDataStream & operator >>(QDataStream &in, DiagramItem * &items)
{
        int x;
        DiagramItem::DiagramType type;
        qreal zVal;
        QPointF pos;
        QBrush brush;
        in >> x;
        type = static_cast<DiagramItem::DiagramType>(x);
        in >> pos >> zVal >> brush;
        items = new DiagramItem(type,NULL);
        items->setPos(pos);
        items->setZValue(zVal);
        items->setBrush(brush);
        return in;
}


void MainWindow::openFile()
{

    loadFile = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Flowchart Diagram(*.fd);;Any files(*.*)"));
    QFile file(loadFile);
    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(this,tr("Save File Failed"),
                              tr("Error: No Authority!"),QMessageBox::Retry);
        return;
    }
    scene->clear();
    QDataStream stream (&file);

    for(;!stream.atEnd();){
        int type;
        stream >> type;
        if(type == 1){
            DiagramItem * itemShape;
            stream >> itemShape;
            itemShape->setContextMenu(itemMenu);
            scene->addItem(itemShape);
         }else if(type == 2){
            DiagramTextItem * itemText;
            stream >> itemText;
            scene->addItem(itemText);
        }else if(type == 3){
            Arrow * itemArrow;
            stream >> itemArrow;
            scene->addItem(itemArrow);
        }
    }


}

void MainWindow::save()
{
    if(loadFile == NULL || loadFile == ""){
        saveas();
        return;
    }
    QFile file(loadFile);
    if(!file.open(QIODevice::WriteOnly)){
        //error message
        QMessageBox::warning(this,
                             tr("File error"),
                             tr("Failed to open\n%1").arg(loadFile));
        return;
    }
    QDataStream stream(&file);
    foreach (QGraphicsItem * item, scene->items()) {
        DiagramItem * itemShape = qgraphicsitem_cast<DiagramItem *>(item);
        DiagramTextItem * itemText = qgraphicsitem_cast<DiagramTextItem*>(item);
        Arrow * itemArrow = qgraphicsitem_cast<Arrow*>(item);
        if(itemShape){
            stream << int(1);
            stream << itemShape;

        }else if(itemText){
            stream << int(2);
            stream << itemText;

        }else if(itemArrow){
            stream << int(3);
            stream << itemArrow;

        }
    }
    file.close();
}

void MainWindow::saveas()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), tr("Flowchart Diagram"), tr("*.fd"));
    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly)){
        //error message
        QMessageBox::warning(this,tr("Save Failed"),tr("Error"),QMessageBox::Retry);
        return;
    }
    QDataStream stream(&file);
    foreach (QGraphicsItem * item, scene->items()) {
        DiagramItem * itemShape = qgraphicsitem_cast<DiagramItem *>(item);
        DiagramTextItem * itemText = qgraphicsitem_cast<DiagramTextItem*>(item);
        Arrow * itemArrow = qgraphicsitem_cast<Arrow*>(item);
        if(itemShape){
            stream << int(1);
            stream << itemShape;

        }else if(itemText){
            stream << int(2);
            stream << itemText;

        }else if(itemArrow){
            stream << int(3);
            stream << itemArrow;

        }
    }
    file.close();
    loadFile = filename;
}

void MainWindow::copy()
{
    undoFile();
    if(scene->selectedItems().isEmpty()){
        return;
    }
    if(!storeList.isEmpty()){
        storeList.clear();
    }
    foreach (QGraphicsItem * items, scene->selectedItems()) {
        if(items->type() == DiagramItem::Type){
            DiagramItem * copyShape = qgraphicsitem_cast<DiagramItem*>(items);
            storeShape = new DiagramItem(copyShape->myDiagramType,NULL);
            storeShape->setBrush(copyShape->brush());
            storeShape->setPos(copyShape->pos() - QPointF(15,15));
            storeShape->setZValue(copyShape->zValue());
            xShape = 15;
            yShape = 15;
            storeList.append(storeShape);
        }else if(items->type() == DiagramTextItem::Type){
            DiagramTextItem * copyText = qgraphicsitem_cast<DiagramTextItem*>(items);
            storeText = new DiagramTextItem();
            storeText->setPlainText(copyText->toPlainText());
            storeText->setPos(copyText->pos());
            storeText->setFont(copyText->font());
            xText = 15;
            yText = 15;
            storeList.append(storeText);
        }
    }
}

void MainWindow::paste()
{
    undoFile();
    foreach (QGraphicsItem * items, storeList) {
        if(items->type() == DiagramItem::Type){
            DiagramItem * pShape = qgraphicsitem_cast<DiagramItem*>(items);
            pasteShape = new DiagramItem(pShape->myDiagramType,NULL);
            pasteShape->setPos(pShape->pos() + QPointF(xShape,yShape));
            pasteShape->setBrush(pShape->brush());
            pasteShape->setZValue(pShape->zValue());
            xShape = xShape + 15;
            yShape = yShape + 15;
            scene->addItem(pasteShape);
        }else if(items->type() == DiagramTextItem::Type){
            DiagramTextItem * pText = qgraphicsitem_cast<DiagramTextItem*>(items);
            pasteText = new DiagramTextItem();
            pasteText->setPlainText(pText->toPlainText());
            pasteText->setPos(pText->pos() + QPointF(xText,yText));
            pasteText->setFont(pText->font());          
            xText = xText + 15;
            yText = yText + 15;
            scene->addItem(pasteText);
        }

    }

}

void MainWindow::cut()
{
    undoFile();
    copy();
    foreach(QGraphicsItem * items, scene->selectedItems()){
        if(items->type() == DiagramItem::Type){
            DiagramItem * cutItem = qgraphicsitem_cast<DiagramItem*>(items);
            cutItem->removeArrows();
        }
        scene->removeItem(items);
        delete(items);
    }
}

void MainWindow::undoFile()
{
    QFile file("undoFile.fd");
    if(!file.open(QIODevice::WriteOnly)){
        //error message
        QMessageBox::warning(this,
                             tr("File error"),
                             tr("Failed for undo\n%1"));
        return;
    }
    QDataStream stream(&file);
    foreach (QGraphicsItem * item, scene->items()) {
        DiagramItem * itemShape = qgraphicsitem_cast<DiagramItem *>(item);
        DiagramTextItem * itemText = qgraphicsitem_cast<DiagramTextItem*>(item);
        Arrow * itemArrow = qgraphicsitem_cast<Arrow*>(item);
        if(itemShape){
            stream << int(1);
            stream << itemShape;

        }else if(itemText){
            stream << int(2);
            stream << itemText;

        }else if(itemArrow){
            stream << int(3);
            stream << itemArrow;

        }
    }
    file.close();

}

void MainWindow::openUndoFile()
{
    QFile file("undoFile.fd");
    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(this,tr("Save File Failed"),
                              tr("Error: No Authority!"),QMessageBox::Retry);
        return;
    }
    scene->clear();
    QDataStream stream (&file);

    for(;!stream.atEnd();){
        int type;
        stream >> type;
        if(type == 1){
            DiagramItem * itemShape;
            stream >> itemShape;
            itemShape->setContextMenu(itemMenu);
            scene->addItem(itemShape);
         }else if(type == 2){
            DiagramTextItem * itemText;
            stream >> itemText;
            scene->addItem(itemText);
        }else if(type == 3){
            Arrow * itemArrow;
            stream >> itemArrow;
            scene->addItem(itemArrow);
        }
    }



}

void MainWindow::redoFile()
{
    QFile file("redoFile.fd");
    if(!file.open(QIODevice::WriteOnly)){
        //error message
        QMessageBox::warning(this,
                             tr("File error"),
                             tr("Failed in redo\n%1"));
        return;
    }
    QDataStream stream(&file);
    foreach (QGraphicsItem * item, scene->items()) {
        DiagramItem * itemShape = qgraphicsitem_cast<DiagramItem *>(item);
        DiagramTextItem * itemText = qgraphicsitem_cast<DiagramTextItem*>(item);
        Arrow * itemArrow = qgraphicsitem_cast<Arrow*>(item);
        if(itemShape){
            stream << int(1);
            stream << itemShape;

        }else if(itemText){
            stream << int(2);
            stream << itemText;

        }else if(itemArrow){
            stream << int(3);
            stream << itemArrow;

        }
    }
    file.close();

}

void MainWindow::openRedoFile()
{
    QFile file("redoFile.fd");
    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(this,tr("Save File Failed"),
                              tr("Error: No Authority!"),QMessageBox::Retry);
        return;
    }
    scene->clear();
    QDataStream stream (&file);

    for(;!stream.atEnd();){
        int type;
        stream >> type;
        if(type == 1){
            DiagramItem * itemShape;
            stream >> itemShape;
            itemShape->setContextMenu(itemMenu);
            undoFile();
            scene->addItem(itemShape);
         }else if(type == 2){
            DiagramTextItem * itemText;
            stream >> itemText;
            undoFile();
            scene->addItem(itemText);
        }else if(type == 3){
            Arrow * itemArrow;
            stream >> itemArrow;
            undoFile();
            scene->addItem(itemArrow);
        }
    }


}

void MainWindow::undo()
{
    redoFile();
    openUndoFile();
}

void MainWindow::redo()
{
    undoFile();
    openRedoFile();
}

void MainWindow::group()
{
    undoFile();
    groups = scene->createItemGroup(scene->selectedItems());
    groups->setFlag(QGraphicsItem::ItemIsSelectable,true);
    groups->setFlag(QGraphicsItem::ItemIsMovable,true);

}

void MainWindow::ungroup()
{
    undoFile();
    scene->destroyItemGroup(groups);
}


//////////////////////////////////////////////////////////////////////////////////////////////




//! [4]
void MainWindow::pointerGroupClicked(int)
{
    undoFile();
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}
//! [4]

//! [5]
void MainWindow::bringToFront()
{
    undoFile();
    if (scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() >= zValue && item->type() == DiagramItem::Type)
            zValue = item->zValue() + 0.1;
    }
    selectedItem->setZValue(zValue);
}
//! [5]

//! [6]
void MainWindow::sendToBack()
{
    undoFile();
    if (scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() <= zValue && item->type() == DiagramItem::Type)
            zValue = item->zValue() - 0.1;
    }
    selectedItem->setZValue(zValue);
}
//! [6]

//! [7]
void MainWindow::itemInserted(DiagramItem *item)
{

    pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
    buttonGroup->button(int(item->diagramType()))->setChecked(false);
}
//! [7]

//! [8]
void MainWindow::textInserted(QGraphicsTextItem *)
{
    undoFile();
    buttonGroup->button(InsertTextButton)->setChecked(false);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}
//! [8]

//! [9]
void MainWindow::currentFontChanged(const QFont &)
{
    undoFile();
    handleFontChange();
}
//! [9]

//! [10]
void MainWindow::fontSizeChanged(const QString &)
{
    undoFile();
    handleFontChange();
}
//! [10]

//! [11]
void MainWindow::sceneScaleChanged(const QString &scale)
{
    undoFile();
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}
//! [11]

//! [12]
void MainWindow::textColorChanged()
{
    undoFile();
    textAction = qobject_cast<QAction *>(sender());
    fontColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/textpointer.png",
                                     qvariant_cast<QColor>(textAction->data())));
    textButtonTriggered();
}
//! [12]

//! [13]
void MainWindow::itemColorChanged()
{
    undoFile();
    fillAction = qobject_cast<QAction *>(sender());
    fillColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/floodfill.png",
                                     qvariant_cast<QColor>(fillAction->data())));
    fillButtonTriggered();
}
//! [13]

//! [14]
void MainWindow::lineColorChanged()
{
    undoFile();
    lineAction = qobject_cast<QAction *>(sender());
    lineColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/linecolor.png",
                                     qvariant_cast<QColor>(lineAction->data())));
    lineButtonTriggered();
}
//! [14]

//! [15]
void MainWindow::textButtonTriggered()
{
    undoFile();
    scene->setTextColor(qvariant_cast<QColor>(textAction->data()));
}
//! [15]

//! [16]
void MainWindow::fillButtonTriggered()
{
    undoFile();
    scene->setItemColor(qvariant_cast<QColor>(fillAction->data()));
}
//! [16]

//! [17]
void MainWindow::lineButtonTriggered()
{
    undoFile();
    scene->setLineColor(qvariant_cast<QColor>(lineAction->data()));
}
//! [17]

//! [18]
void MainWindow::handleFontChange()
{
    undoFile();
    QFont font = fontCombo->currentFont();
    font.setPointSize(fontSizeCombo->currentText().toInt());
    font.setWeight(boldAction->isChecked() ? QFont::Bold : QFont::Normal);
    font.setItalic(italicAction->isChecked());
    font.setUnderline(underlineAction->isChecked());

    scene->setFont(font);
}
//! [18]

//! [19]
void MainWindow::itemSelected(QGraphicsItem *item)
{
    DiagramTextItem *textItem =
    qgraphicsitem_cast<DiagramTextItem *>(item);

    QFont font = textItem->font();
    fontCombo->setCurrentFont(font);
    fontSizeCombo->setEditText(QString().setNum(font.pointSize()));
    boldAction->setChecked(font.weight() == QFont::Bold);
    italicAction->setChecked(font.italic());
    underlineAction->setChecked(font.underline());
}
//! [19]

//! [20]
void MainWindow::about()
{
    QMessageBox::about(this, tr("About Diagram Scene"),
                       tr("The <b>Diagram Scene</b> example shows "
		       "use of the graphics framework. "
		       "Here is the website: "
		       "http://doc.qt.io/qt-5/qtwidgets-graphicsview-diagramscene-example.html"));
}
//! [20]

//! [21]
void MainWindow::createToolBox()
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(buttonGroupClicked(int)));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createCellWidget(tr("Conditional"), DiagramItem::Conditional), 0, 0);
    layout->addWidget(createCellWidget(tr("Process"), DiagramItem::Step),0, 1);
    layout->addWidget(createCellWidget(tr("Input/Output"), DiagramItem::Io), 1, 0);
//! [21]
    ///////////////////ADD CODE///////////////////////////////
    layout->addWidget(createCellWidget(tr("Terminal"),DiagramItem::Oval),2,0);
    layout->addWidget(createCellWidget(tr("Preparation"),DiagramItem::Hexagon),2,1);
    layout->addWidget(createCellWidget(tr("Off-Page Connector"),DiagramItem::Pentagon),3,0);

    ///////////////////////////////////////////////
    QToolButton *textButton = new QToolButton;
    textButton->setCheckable(true);
    buttonGroup->addButton(textButton, InsertTextButton);
    textButton->setIcon(QIcon(QPixmap(":/images/textpointer.png")));
    textButton->setIconSize(QSize(50, 50));
    QGridLayout *textLayout = new QGridLayout;
    textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
    textLayout->addWidget(new QLabel(tr("Text")), 1, 0, Qt::AlignCenter);
    QWidget *textWidget = new QWidget;
    textWidget->setLayout(textLayout);
    layout->addWidget(textWidget, 1, 1);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);

    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    backgroundButtonGroup = new QButtonGroup(this);
    connect(backgroundButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(backgroundButtonGroupClicked(QAbstractButton*)));

    QGridLayout *backgroundLayout = new QGridLayout;
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Blue Grid"),
                                                           ":/images/background1.png"), 0, 0);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("White Grid"),
                                                           ":/images/background2.png"), 0, 1);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Gray Grid"),
                                                           ":/images/background3.png"), 1, 0);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("No Grid"),
                                                           ":/images/background4.png"), 1, 1);

    backgroundLayout->setRowStretch(2, 10);
    backgroundLayout->setColumnStretch(2, 10);

    QWidget *backgroundWidget = new QWidget;
    backgroundWidget->setLayout(backgroundLayout);


//! [22]
    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    toolBox->addItem(itemWidget, tr("Basic Flowchart Shapes"));
    toolBox->addItem(backgroundWidget, tr("Backgrounds"));
}
//! [22]

//! [23]
void MainWindow::createActions()
{
    toFrontAction = new QAction(QIcon(":/images/bringtofront.png"),
                                tr("Bring to &Front"), this);
    toFrontAction->setShortcut(tr("Ctrl+F"));
    toFrontAction->setStatusTip(tr("Bring item to front"));
    connect(toFrontAction, SIGNAL(triggered()), this, SLOT(bringToFront()));
//! [23]

    sendBackAction = new QAction(QIcon(":/images/sendtoback.png"), tr("Send to &Back"), this);
    sendBackAction->setShortcut(tr("Ctrl+B"));
    sendBackAction->setStatusTip(tr("Send item to back"));
    connect(sendBackAction, SIGNAL(triggered()), this, SLOT(sendToBack()));

    deleteAction = new QAction(QIcon(":/images/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit Scenediagram example"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
///////////////////////////////ADD CODE ////////////////////////////////////////////////////////
    newAction = new QAction(tr("N&ew"),this);
    newAction->setShortcut(tr("Ctrl+N"));
    newAction->setStatusTip(tr("New File"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newA()));


    openAction = new QAction(QIcon(":/images/open.png"), tr("O&pen"),this);
    openAction->setShortcut(tr("Ctrl+O"));
    openAction->setStatusTip(tr("Open item"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));

    saveAction = new QAction(QIcon(":/images/save.png"), tr("S&ave"),this);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setStatusTip(tr("Save item"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveasAction = new QAction(tr("S&ave As"),this);
    saveasAction->setShortcut(tr("Ctrl+D"));
    saveasAction->setStatusTip(tr("Save item to..."));
    connect(saveasAction, SIGNAL(triggered()), this, SLOT(saveas()));


    copyAction = new QAction(tr("C&opy"),this);
    copyAction->setShortcut(tr("Ctrl+C"));
    copyAction->setStatusTip(tr("Copy item"));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAction = new QAction(tr("P&aste"),this);
    pasteAction->setShortcut(tr("Ctrl+V"));
    pasteAction->setStatusTip(tr("Paste item"));
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));

    cutAction = new QAction(tr("C&ut"),this);
    cutAction->setShortcut(tr("Ctrl+X"));
    cutAction->setStatusTip(tr("Cut item"));
    connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));

    undoAction = new QAction(tr("&Undo"),this);
    //undoAction = m_UndoStack->createUndoAction(this);
    undoAction->setShortcuts(QKeySequence::Undo);
    undoAction->setStatusTip(tr("Undo Action"));
    connect(undoAction, SIGNAL(triggered()), this, SLOT(undo()));

    redoAction = new QAction(tr("&Redo"),this);
    //redoAction = m_UndoStack->createRedoAction(this);
    redoAction->setShortcuts(QKeySequence::Redo);
    redoAction->setStatusTip(tr("Redo Action"));
    connect(redoAction, SIGNAL(triggered()), this, SLOT(redo()));

    groupAction = new QAction(tr("G&roup"),this);
    groupAction->setShortcut(tr("Ctrl+G"));
    groupAction->setStatusTip(tr("Group item"));
    connect(groupAction, SIGNAL(triggered()), this, SLOT(group()));

    ungroupAction = new QAction(tr("U&ngroup"),this);
    ungroupAction->setShortcut(tr("Ctrl+U"));
    ungroupAction->setStatusTip(tr("Ungroup item"));
    connect(ungroupAction, SIGNAL(triggered()), this, SLOT(ungroup()));



////////////////////////////////////////////////////////////////////////////////////////////////
    boldAction = new QAction(tr("Bold"), this);
    boldAction->setCheckable(true);
    QPixmap pixmap(":/images/bold.png");
    boldAction->setIcon(QIcon(pixmap));
    boldAction->setShortcut(tr("Ctrl+B"));
    connect(boldAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    italicAction = new QAction(QIcon(":/images/italic.png"), tr("Italic"), this);
    italicAction->setCheckable(true);
    italicAction->setShortcut(tr("Ctrl+I"));
    connect(italicAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    underlineAction = new QAction(QIcon(":/images/underline.png"), tr("Underline"), this);
    underlineAction->setCheckable(true);
    underlineAction->setShortcut(tr("Ctrl+U"));
    connect(underlineAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

//! [24]
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
//////////////////////ADD CODE///////////////////////////////////////////////////////////////
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveasAction);

//////////////////////////////////////////////////////////////////////////////////////////////
    fileMenu->addAction(exitAction);


    itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();
    itemMenu->addAction(toFrontAction);
    itemMenu->addAction(sendBackAction);

//////////////////////////////alog/
    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(cutAction); 

    toolMenu = menuBar()->addMenu(tr("&Tool"));
    toolMenu->addAction(groupAction);
    toolMenu->addAction(ungroupAction);


//////////////////////////////////////////////////////////////////////////////////////////////////


    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}
//! [24]

//! [25]
void MainWindow::createToolbars()
{
//! [25]
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);
    editToolBar->addAction(toFrontAction);
    editToolBar->addAction(sendBackAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addAction(cutAction);
    editToolBar->addAction(undoAction);
    editToolBar->addAction(redoAction);

    fontCombo = new QFontComboBox();
    connect(fontCombo, SIGNAL(currentFontChanged(QFont)),
            this, SLOT(currentFontChanged(QFont)));

    fontSizeCombo = new QComboBox;
    fontSizeCombo->setEditable(true);
    for (int i = 8; i < 30; i = i + 2)
        fontSizeCombo->addItem(QString().setNum(i));
    QIntValidator *validator = new QIntValidator(2, 64, this);
    fontSizeCombo->setValidator(validator);
    connect(fontSizeCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(fontSizeChanged(QString)));

    fontColorToolButton = new QToolButton;
    fontColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fontColorToolButton->setMenu(createColorMenu(SLOT(textColorChanged()), Qt::black));
    textAction = fontColorToolButton->menu()->defaultAction();
    fontColorToolButton->setIcon(createColorToolButtonIcon(":/images/textpointer.png", Qt::black));
    fontColorToolButton->setAutoFillBackground(true);
    connect(fontColorToolButton, SIGNAL(clicked()),
            this, SLOT(textButtonTriggered()));

//! [26]
    fillColorToolButton = new QToolButton;
    fillColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fillColorToolButton->setMenu(createColorMenu(SLOT(itemColorChanged()), Qt::white));
    fillAction = fillColorToolButton->menu()->defaultAction();
    fillColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/floodfill.png", Qt::white));
    connect(fillColorToolButton, SIGNAL(clicked()),
            this, SLOT(fillButtonTriggered()));
//! [26]

    lineColorToolButton = new QToolButton;
    lineColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    lineColorToolButton->setMenu(createColorMenu(SLOT(lineColorChanged()), Qt::black));
    lineAction = lineColorToolButton->menu()->defaultAction();
    lineColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/linecolor.png", Qt::black));
    connect(lineColorToolButton, SIGNAL(clicked()),
            this, SLOT(lineButtonTriggered()));

    textToolBar = addToolBar(tr("Font"));
    textToolBar->addWidget(fontCombo);
    textToolBar->addWidget(fontSizeCombo);
    textToolBar->addAction(boldAction);
    textToolBar->addAction(italicAction);
    textToolBar->addAction(underlineAction);

    colorToolBar = addToolBar(tr("Color"));
    colorToolBar->addWidget(fontColorToolButton);
    colorToolBar->addWidget(fillColorToolButton);
    colorToolBar->addWidget(lineColorToolButton);

    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/images/pointer.png"));
    QToolButton *linePointerButton = new QToolButton;
    linePointerButton->setCheckable(true);
    linePointerButton->setIcon(QIcon(":/images/linepointer.png"));

    pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, int(DiagramScene::MoveItem));
    pointerTypeGroup->addButton(linePointerButton, int(DiagramScene::InsertLine));
    connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(pointerGroupClicked(int)));

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(sceneScaleChanged(QString)));

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(pointerButton);
    pointerToolbar->addWidget(linePointerButton);
    pointerToolbar->addWidget(sceneScaleCombo);
//! [27]
}
//! [27]

//! [28]
QWidget *MainWindow::createBackgroundCellWidget(const QString &text, const QString &image)
{
    QToolButton *button = new QToolButton;
    button->setText(text);
    button->setIcon(QIcon(image));
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    backgroundButtonGroup->addButton(button);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}
//! [28]

//! [29]
QWidget *MainWindow::createCellWidget(const QString &text, DiagramItem::DiagramType type)
{

    DiagramItem item(type, itemMenu);
    QIcon icon(item.image());

    QToolButton *button = new QToolButton;
    button->setIcon(icon);
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    buttonGroup->addButton(button, int(type));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}
//! [29]

//! [30]
QMenu *MainWindow::createColorMenu(const char *slot, QColor defaultColor)
{
    QList<QColor> colors;
    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow;
    QStringList names;
    names << tr("black") << tr("white") << tr("red") << tr("blue")
          << tr("yellow");

    QMenu *colorMenu = new QMenu(this);
    for (int i = 0; i < colors.count(); ++i) {
        QAction *action = new QAction(names.at(i), this);
        action->setData(colors.at(i));
        action->setIcon(createColorIcon(colors.at(i)));
        connect(action, SIGNAL(triggered()), this, slot);
        colorMenu->addAction(action);
        if (colors.at(i) == defaultColor)
            colorMenu->setDefaultAction(action);
    }
    return colorMenu;
}
//! [30]

//! [31]
QIcon MainWindow::createColorToolButtonIcon(const QString &imageFile, QColor color)
{
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(imageFile);
    // Draw icon centred horizontally on button.
    QRect target(4, 0, 42, 43);
    QRect source(0, 0, 42, 43);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
}
//! [31]

//! [32]
QIcon MainWindow::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}
//! [3alog2
