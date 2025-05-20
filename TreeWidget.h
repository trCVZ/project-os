//######
//## TreeWidget.h
//## ============
//## 07.04.2013: CrÃ©ation
//## 02.06.2019: Version v2
//## 09.07.2022: Prise en compote QT57
//######

#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QtCore>
#include <QtWidgets>

class TreeWidget:public QTreeWidget
{
  Q_OBJECT

public:
  TreeWidget( QWidget* p_Parent );
  ~TreeWidget();

  void Add_FirstChild( QString p_FilePath );
  void Add_Children  ( QString p_FilePath, QTreeWidgetItem * p_Item );

  void Adjust_ColumnSize();

  QString Get_PathName( QTreeWidgetItem * p_Item );

  void keyPressEvent  ( QKeyEvent   * p_Event );
  void mousePressEvent( QMouseEvent * p_Event );

signals:
  void SIGNAL_RightClicked  ( QTreeWidgetItem *, int );
  void SIGNAL_Statut_Fichier( QString );

public slots:
  void slot_currentItemChanged( QTreeWidgetItem * p_Current, QTreeWidgetItem * /* p_Previous  */ );
  void slot_itemClicked       ( QTreeWidgetItem * p_Item, int /*p_Column*/ );
  void onItemChanged(QTreeWidgetItem *item, int column);

};
#endif

