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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets>
#include <QtCore>

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <iostream>
#include <algorithm>
#include "diagramitem.h"
#include "diagramtextitem.h"


class DiagramScene;

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
QT_END_NAMESPACE

//! [0]
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   MainWindow();


private slots:
    void backgroundButtonGroupClicked(QAbstractButton *button);
    void buttonGroupClicked(int id);
    void deleteItem();
    void pointerGroupClicked(int id);
    void bringToFront();
    void sendToBack();
    void itemInserted(DiagramItem *item);
    void textInserted(QGraphicsTextItem *item);
    void currentFontChanged(const QFont &font);
    void fontSizeChanged(const QString &size);
    void sceneScaleChanged(const QString &scale);
    void textColorChanged();
    void itemColorChanged();
    void lineColorChanged();
    void textButtonTriggered();
    void fillButtonTriggered();
    void lineButtonTriggered();
    void handleFontChange();
    void itemSelected(QGraphicsItem *item);
    void about();
////////////////////////////ADD CODE///////////////////////////////////////////////
    void openFile();
//    void load(QString fileName);
    void save();
    void saveas();
    void newA();
    void copy();
    void paste();
    void cut();
    void undoFile();
    void openUndoFile();
    void undo();
    void redoFile();
    void openRedoFile();
    void redo();
    void group();
    void ungroup();
    friend QDataStream & operator << (QDataStream & out, DiagramItem *& item);
    friend QDataStream & operator >> (QDataStream & in, DiagramItem *& item);
    //QUndoStack *undoStack;
    //QUndoView * undoView;
///////////////////////////////////////////////////////////////////////////////////

private:
    void createToolBox();
    void createActions();
    void createMenus();
    void createToolbars();
    QString m_currentFile;

    QWidget *createBackgroundCellWidget(const QString &text,
                                        const QString &image);
    QWidget *createCellWidget(const QString &text,
                              DiagramItem::DiagramType type);
    QMenu *createColorMenu(const char *slot, QColor defaultColor);
    QIcon createColorToolButtonIcon(const QString &image, QColor color);
    QIcon createColorIcon(QColor color);

    DiagramScene *scene;
    QGraphicsView *view;

    QAction *exitAction;
//////////////////////////ADD CODE/////////////////////////////////
    QAction *openAction;
    QAction *saveAction;
    QAction *saveasAction;
    QAction *newAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *cutAction;
    QAction *undoAction;
    QAction *redoAction;
    QAction *groupAction;
    QAction *ungroupAction;
///////////////////////////////////////////////////////////////////
    QAction *addAction;
    QAction *deleteAction;

    QAction *toFrontAction;
    QAction *sendBackAction;
    QAction *aboutAction;

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *aboutMenu;

//////////////////////////////////////////////////ADD CODE////////////////////////////////////////////////////
    QMenu *editMenu;
    QMenu *toolMenu;

    QString fileName;
    QString loadFile;
    QString filename;

    QGraphicsItemGroup * groups;
//QList<QGraphicsItemGroup> groupL;
    QUndoStack * m_UndoStack;
//QList<QGraphicsItem*> itemCopy
    QList <QGraphicsItem*> storeList;

    DiagramItem * storeShape;
    DiagramTextItem * storeText;
    DiagramItem * pasteShape;
    DiagramTextItem * pasteText;
    QGraphicsLineItem * pasteLine;
    qreal xShape;
    qreal yShape;
    qreal xText;
    qreal yText;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


    QToolBar *textToolBar;
    QToolBar *editToolBar;
    QToolBar *colorToolBar;
    QToolBar *pointerToolbar;

    QComboBox *sceneScaleCombo;
    QComboBox *itemColorCombo;
    QComboBox *textColorCombo;
    QComboBox *fontSizeCombo;
    QFontComboBox *fontCombo;

    QToolBox *toolBox;
    QButtonGroup *buttonGroup;
    QButtonGroup *pointerTypeGroup;
    QButtonGroup *backgroundButtonGroup;
    QToolButton *fontColorToolButton;
    QToolButton *fillColorToolButton;
    QToolButton *lineColorToolButton;
    QAction *boldAction;
    QAction *underlineAction;
    QAction *italicAction;
    QAction *textAction;
    QAction *fillAction;
    QAction *lineAction;

};
//! [0]

#endif // MAINWINDOW_H
