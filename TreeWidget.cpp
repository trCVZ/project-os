//######
//## TreeWidget.cpp
//## ==============
//## 07.04.2013: Creation
//## 02.06.2019: Version v2
//## 09.07.2022: Prise en compte QT57
//######

#include  "TreeWidget.h"

#include "I_ClosedFolder_16.xpm"
#include "I_NormalFile_16.xpm"

#define K_FN  0
#define K_CK  1
#define K_SZ  2
#define K_PN  3
#define K_DT  4
#define K_ZZ  5 

//
// <<<< TreeWidget::TreeWidget
//
TreeWidget::TreeWidget( QWidget * p_Parent ): QTreeWidget( p_Parent )
{
  //-- Add Subdirectories as children  when user clicks on a file item,
  //-- otherwise adding all children recursively may consume HUGE amount of memory

  QTreeWidgetItem * HeaderItem = new QTreeWidgetItem();

  HeaderItem->setText( K_CK, QString( " "  ) );
  HeaderItem->setText( K_FN, QString( "File Name"   ) );
  HeaderItem->setText( K_SZ, QString( "Size (Bytes)") );
  HeaderItem->setText( K_PN, QString( "Path"        ) );
  HeaderItem->setText( K_DT, QString( "Date modif." ) );
  HeaderItem->setText( K_ZZ, QString( " "  ) );

  this->setHeaderItem( HeaderItem );

  this->setSortingEnabled( true );
  this->sortItems( 0, Qt::AscendingOrder );

  this->Adjust_ColumnSize();

  connect( this , SIGNAL( itemClicked     ( QTreeWidgetItem *, int ) )
         , this , SLOT  ( slot_itemClicked( QTreeWidgetItem *, int ) ) );

  connect( this , SIGNAL( currentItemChanged     ( QTreeWidgetItem *, QTreeWidgetItem * ) )
         , this , SLOT  ( slot_currentItemChanged( QTreeWidgetItem *, QTreeWidgetItem * ) ) );

  connect(this, &QTreeWidget::itemChanged, this, &TreeWidget::onItemChanged);
}
// >>>> TreeWidget::TreeWidget


//
// <<<< TreeWidget::~TreeWidget
//
TreeWidget::~TreeWidget()
{
}
// >>>> TreeWidget::~TreeWidget


//
// <<<< TreeWidget::Add_FirstChild
//
void TreeWidget::Add_FirstChild( QString p_FilePath )
{
  QFileInfo fileInfo( p_FilePath );

  if ( fileInfo.isSymLink() ) {
    return;
  }

  QString FileName = fileInfo.fileName();

  QTreeWidgetItem * child = new QTreeWidgetItem();

  child->setCheckState( K_CK, Qt::Checked );
  child->setTextAlignment( K_CK, Qt::AlignCenter );

  child->setText( K_FN, fileInfo.fileName() );

  child->setIcon( K_FN, *( new QIcon( QPixmap( (const char **) I_ClosedFolder_16 ) ) ) );
  child->setText( K_PN, fileInfo.absoluteFilePath() );
  child->setText( K_DT, fileInfo.lastModified().toString("dd.MM.yyyy hh:mm:ss") );

  this->clear();
  this->addTopLevelItem( child );

  this->Add_Children( p_FilePath, child );

  child->setExpanded( true );

  this->Adjust_ColumnSize();
}
// >>>> TreeWidget::Add_FirstChild


//
// <<<< TreeWidget::Add_Children
//
void TreeWidget::Add_Children( QString p_FilePath, QTreeWidgetItem * p_Item )
{
  if ( p_Item && p_Item->childCount() != 0 ) return;

  QDir * DIR = new QDir( p_FilePath );
  QFileInfoList filesList = DIR->entryInfoList();

  foreach ( QFileInfo fileInfo, filesList ) {

    if ( fileInfo.isSymLink() ) continue;

    QString FileName = fileInfo.fileName();

    if ( FileName == "."  ) continue;
    if ( FileName == ".." ) continue;

    QTreeWidgetItem * child = new QTreeWidgetItem();

    child->setCheckState( K_CK, Qt::Checked );
    child->setTextAlignment( K_CK, Qt::AlignCenter );

    child->setText( K_FN, fileInfo.fileName() );

    if ( fileInfo.isFile() ) {
      child->setIcon( K_FN, *(new QIcon( QPixmap( (const char **) I_NormalFile_16 ) ) ) );
      child->setText( K_SZ, QString::number( fileInfo.size() ) );
      child->setTextAlignment( K_SZ, Qt::AlignRight );
    }

    if ( fileInfo.isDir() ) {
      child->setIcon( K_FN, *( new QIcon( QPixmap( (const char **) I_ClosedFolder_16 ) ) ) );
      child->setText( K_PN, fileInfo.absoluteFilePath() );
    }

    child->setText( K_DT, fileInfo.lastModified().toString("dd.MM.yyyy hh:mm:ss") );

    if ( p_Item == 0 ) {
      this->addTopLevelItem( child );
    } else {
      p_Item->addChild( child );
    }
  }
}
// >>>> TreeWidget::Add_Children


//
// <<<< TreeWidget::Adjust_ColumnSize
//
void TreeWidget::Adjust_ColumnSize()
{
  this->resizeColumnToContents( K_FN );
  this->resizeColumnToContents( K_CK );
  this->resizeColumnToContents( K_SZ );
  this->resizeColumnToContents( K_PN );
  this->resizeColumnToContents( K_DT );
  this->resizeColumnToContents( K_ZZ );

  this->update();

  int Size_PN = this->columnWidth( K_PN );
  int Size_ZZ = this->columnWidth( K_ZZ );

  int MaxSize = 1;

  if ( Size_ZZ > MaxSize ) {
    Size_PN = Size_PN + Size_ZZ  - MaxSize;
    Size_ZZ = MaxSize;
  }

  this->setColumnWidth( K_PN, Size_PN );
  this->setColumnWidth( K_ZZ, Size_ZZ );
}
// >>>> TreeWidget::Adjust_ColumnSize


//
// <<<< TreeWidget::Get_PathName
//
QString TreeWidget::Get_PathName( QTreeWidgetItem* p_Item )
{
  if ( ! p_Item ) {
    return "";
  }

  QString FileName = p_Item->text( K_FN );
  QString PathName = p_Item->text( K_PN );

  if ( FileName.isEmpty() ) {
    return "";
  }

  if ( PathName.isEmpty() ) {
    QTreeWidgetItem * p_Parent = p_Item->parent();

    PathName = p_Parent->text( K_PN ) + QString( "/" ) + FileName;
  }

  return PathName;
}
// >>>> TreeWidget::Get_PathName


//
// <<<< TreeWidget::keyPressEvent
//
void TreeWidget::keyPressEvent( QKeyEvent * p_Event )
{
  bool b_IGNORE = false;

  QTreeWidgetItem * qItem = this->currentItem();

  switch ( p_Event->key() ) {
  case Qt::Key_Space:

    if ( qItem ) {
      bool b_WasChecked = ( qItem->checkState( K_CK ) == Qt::Checked );

      if ( b_WasChecked ) {
        qItem->setCheckState( K_CK, Qt::Unchecked );
      } else {
        qItem->setCheckState( K_CK, Qt::Checked );
      }
    }

    b_IGNORE = true;

    break;

  case Qt::Key_F5:
    this->Adjust_ColumnSize();
    break;

  default:
    break;
  }

  if ( b_IGNORE ) {
    p_Event->ignore();
  } else {
    QTreeView::keyPressEvent( p_Event );
  }
}
// >>>> TreeWidget::keyPressEvent


//
// <<<< TreeWidget::mousePressEvent
//
void TreeWidget::mousePressEvent( QMouseEvent* p_Event )
{
  QPoint            qPoint;
  QTreeWidgetItem * qItem;

  if ( p_Event->button() == Qt::LeftButton ) {

#ifdef QT57
    qPoint = QPoint( p_Event->x(), p_Event->y() );
#else
    qPoint = p_Event->pos();
#endif

    qItem  = (QTreeWidgetItem * ) this->itemAt( qPoint );

    int k_Column;

    if ( qItem ) {
      k_Column = this->columnAt( qPoint.x() );

      if ( k_Column > 0 ) {
        p_Event->accept();
      }
    }
  }

  if ( p_Event->button() == Qt::RightButton ) {

#ifdef QT57
    qPoint = QPoint( p_Event->x(), p_Event->y() );
#else
    qPoint = p_Event->pos();
#endif

    QTreeWidgetItem * qItem = this->itemAt( qPoint );

    int k_Column;

    k_Column = this->columnAt( qPoint.x() );  // Coordonnees relatives

    emit SIGNAL_RightClicked( qItem, k_Column ); // qItem peut etre NULL

    p_Event->accept();
  }

  QTreeWidget::mousePressEvent( p_Event );
}
// >>>> TreeWidget::mousePressEvent


//
// <<<< TreeWidget::slot_itemClicked
//
void TreeWidget::slot_itemClicked( QTreeWidgetItem* p_Item, int /*p_Column*/ )
{
  QString FilePath = p_Item->text( K_PN );

  if ( FilePath.isEmpty() ) return;

  QFileInfo FI_Path( FilePath );

  if ( FI_Path.isSymLink() ) return;
  if ( FI_Path.isFile()    ) return;

  this->Add_Children( FilePath, p_Item );

  this->Adjust_ColumnSize();
}
// >>>> TreeWidget::slot_itemClicked


//
// <<<< TreeWidget::slot_currentItemChanged
//
void TreeWidget::slot_currentItemChanged( QTreeWidgetItem * p_Current
                                        , QTreeWidgetItem * /* p_Previous  */ )
{
  QString PathName = this->Get_PathName( p_Current );

  if ( ! PathName.isEmpty() ) {
    emit SIGNAL_Statut_Fichier( PathName );
  }
}
// >>>> TreeWidget::slot_currentItemChanged


//
// <<<< TreeWidget::onItemChanged
//
void TreeWidget::onItemChanged(QTreeWidgetItem *item, int column)
{
        Qt::CheckState state = item->checkState(K_CK);

        // Applique l'état à tous les enfants
        for (int i = 0; i < item->childCount(); ++i) {
            QTreeWidgetItem *child = item->child(i);
            child->setCheckState(K_CK, state);
        }
}
// >>>> TreeWidget::onItemChanged

