//######
//## TreeMainWindow.cpp
//## ==================
//## 07.04.2013: Creation
//## 02.06.2019: Version v2
//## 09.07.2022: Prise en compte QT57
//######

#include  "TreeMainWindow.h"
#include  "TreeWidget.h"

#include  "FileOpen.xpm"
#include  "FileSave.xpm"

//
// <<<< TreeMainWindow::TreeMainWindow
//
TreeMainWindow::TreeMainWindow( QWidget * p_Parent )
  : QMainWindow( p_Parent )
{

  //-- MENU

  _Menu = new QMenu( this );
  _Menu->setTitle( "&Fichier" );

  this->menuBar()->addMenu( _Menu );

  _Menu->addAction( QPixmap( (const char **) FileOpen )
    , "Choisir Dossier racine"
    , this, SLOT ( slot_Choisir_Dossier_Racine() ), Qt::ALT | Qt::Key_S );

  _Menu->addSeparator();

  _Menu->addAction( "Quitter", this , SLOT ( slot_QUIT() ), Qt::ALT | Qt::Key_Q  );

  //-- SPLITTER

  _Splitter = new QSplitter( this );

  this->setCentralWidget( _Splitter );

  //-- TREEWIDGET Source et Destination

  _TW_Dossier = new TreeWidget( _Splitter );
  _TextEdit   = new TextEdit( _Splitter );
  _TextEdit->setReadOnly( true );

#ifdef WIN32
  QByteArray BA_HOME( getenv( "HOMEDRIVE" ) );
  BA_HOME.append( getenv( "HOMEPATH" ) );
#else
  QByteArray BA_HOME( getenv( "HOME" ) );
#endif

  QString DefautDIR( BA_HOME );

  Choisir_Dossier_Racine( DefautDIR );

  //-- SLOTS
  connect( _TW_Dossier, SIGNAL( SIGNAL_Statut_Fichier( QString ) )
         , this,        SLOT  ( slot_Statut_Fichier  ( QString ) ) );

  connect( _TW_Dossier, SIGNAL( SIGNAL_RightClicked           ( QTreeWidgetItem *, int ) )
         , this,        SLOT  ( slot_PopupContextMenu_TreeView( QTreeWidgetItem *, int ) ) );
}
// >>>> TreeMainWindow::TreeMainWindow


//
// <<<< TreeMainWindow::Choisir_Dossier_Racine
//
void TreeMainWindow::Choisir_Dossier_Racine( QString p_Dossier )
{
   QFileInfo FI_Racine( p_Dossier );

   if ( FI_Racine.isSymLink() ) {
    _Path_Dossier_Racine = FI_Racine.symLinkTarget();
   } else {
    _Path_Dossier_Racine = p_Dossier;
   }

  _TW_Dossier->Add_FirstChild( _Path_Dossier_Racine );

  // Affiche le statut du dossier racine au lancement
  Statut_Fichier(_Path_Dossier_Racine);
}
// >>>> TreeMainWindow::Choisir_Dossier_Racine


//
// <<<< TreeMainWindow::Statut_Fichier
//
void TreeMainWindow::Statut_Fichier( QString p_Path )
{
  QFileInfo qFI( p_Path );

  if ( !qFI.exists() )
    return;

  QDate mDate = qFI.lastModified().date();
  QTime mTime = qFI.lastModified().time();

  QString qDate = mDate.toString( "dd.MM.yyyy" );
  QString qTime = mTime.toString( "hh:mm:ss" );

  QString message;

  if (qFI.isDir()) {
    message = QString("📁 Dossier : %1  -  Modifié le %2 à %3").arg(p_Path).arg(qDate).arg(qTime);
  }
  else if (qFI.isFile()) {
    message = QString("📄 Fichier : %1  -  Modifié le %2 à %3").arg(p_Path).arg(qDate).arg(qTime);
  }

  this->statusBar()->showMessage(message);
}

// >>>> TreeMainWindow::Statut_Fichier


//
// <<<< TreeMainWindow::slot_Choisir_Dossier_Racine
//
void TreeMainWindow::slot_Choisir_Dossier_Racine()
{
  QFileDialog F_Dialog( this );

#ifdef QT57
  F_Dialog.setFileMode( QFileDialog::DirectoryOnly );
#else
  F_Dialog.setFileMode( QFileDialog::Directory );
  F_Dialog.setOptions( QFileDialog::ShowDirsOnly );
#endif

  F_Dialog.setAcceptMode( QFileDialog::AcceptOpen );
  F_Dialog.setSizeGripEnabled( true );

#ifdef WIN32
  QByteArray BA_HOME( getenv( "HOMEDRIVE" ) );
  BA_HOME.append( getenv( "HOMEPATH" ) );
#else
  QByteArray BA_HOME( getenv( "HOME" ) );
#endif

  QString DefautDIR( BA_HOME );

  F_Dialog.setDirectory( DefautDIR );

  QString qDIR = F_Dialog.getExistingDirectory( this, "SÃ©lection Dossier Source" );

  if ( ! qDIR.isEmpty() ) {
    Choisir_Dossier_Racine( qDIR );
  }
}
// >>>> TreeMainWindow::slot_Choisir_Dossier_Racine


//
// <<<< TreeMainWindow::slot_Statut_Fichier
//
void TreeMainWindow::slot_Statut_Fichier( QString p_Path )
{
  this->Statut_Fichier( p_Path );
}
// >>>> TreeMainWindow::slot_Statut_Fichier


//
// <<<< TreeMainWindow::slot_PopupContextMenu_TreeView
//
void TreeMainWindow::slot_PopupContextMenu_TreeView( QTreeWidgetItem * p_Item, int )
{
  QMenu PopupM( "PopupMenu TreeView" );

  if ( ! p_Item ) {
    return;
  }

  QString PathName = _TW_Dossier->Get_PathName( p_Item );

  QFileInfo FI_Path( PathName );

  FI_Path.setCaching( false );

  while ( FI_Path.isSymLink() ) {
    PathName =  FI_Path.symLinkTarget();
    FI_Path.setFile( PathName );
  }

  if ( PathName.isEmpty() ) return;

  QAction * X_Action_DIR = NULL;
  QAction * X_Action_TXT = NULL;

  if ( FI_Path.isDir() ) {

    X_Action_DIR = PopupM.addAction( QString( "Ouvrir ce dossier" ) );

  } else if ( FI_Path.isFile() ) {

    QString SFX = QString( ".%1;" ).arg( FI_Path.suffix() );

    if ( QString( ".cpp;.h;.xpm;.pro;" ).contains( SFX.toLower() ) ) {
      X_Action_TXT = PopupM.addAction( QString( "Afficher le fichier" ) );
    }
  } else {
    return;
  }

  QPoint PM_Point = QCursor::pos() + QPoint( 12, 8 );

  QAction * ACT_x = PopupM.exec( PM_Point );

  if ( ACT_x == NULL ) {
    return;
  }

  if ( ACT_x == X_Action_DIR ) {
    this->Choisir_Dossier_Racine( PathName );
  }

  if ( ACT_x == X_Action_TXT ) {
    QFile Fd_R( PathName );

    if ( Fd_R.open( QIODevice::ReadOnly ) ) {
      QTextStream TS_R( &Fd_R );
      // TS_R.setCodec( QTextCodec::codecForName( "UTF-8" );
      QString S_TEXT = TS_R.readAll();
      Fd_R.close();

      _TextEdit->setReadOnly( false );
      _TextEdit->setText( S_TEXT );
      _TextEdit->setReadOnly( true );
    }
  }
}
// >>>> TreeMainWindow::slot_PopupContextMenu_TreeView


//
// <<<< TreeMainWindow::slot_QUIT
//
void TreeMainWindow::slot_QUIT()
{
  //--  ? Enregistrer_Arborescence( QString p_PathFichier )

  qApp->quit();
}
// >>>> TreeMainWindow::slot_QUIT

