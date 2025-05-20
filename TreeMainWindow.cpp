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

#define K_FN  0
#define K_CK  1
#define K_SZ  2
#define K_PN  3
#define K_DT  4
#define K_ZZ  5

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

  QAction* aideAction = _Menu->addAction("Aide", this, SLOT(slot_Aide()));
  aideAction->setShortcut(Qt::Key_F1);

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
void TreeMainWindow::slot_PopupContextMenu_TreeView(QTreeWidgetItem *p_Item, int)
{
  QMenu PopupM("PopupMenu TreeView");

  if (!p_Item) {
    return;
  }

  QString PathName = _TW_Dossier->Get_PathName(p_Item);
  QFileInfo FI_Path(PathName);
  FI_Path.setCaching(false);

  while (FI_Path.isSymLink()) {
    PathName = FI_Path.symLinkTarget();
    FI_Path.setFile(PathName);
  }

  if (PathName.isEmpty()) return;

  QAction *actionCopyPath = PopupM.addAction("Copier le chemin");

  QAction *actionRename = nullptr;
  QAction *actionDelete = nullptr;

  if (FI_Path.isFile()) {
    actionRename = PopupM.addAction("Renommer");
    actionDelete = PopupM.addAction("Supprimer");
  }

  QPoint PM_Point = QCursor::pos() + QPoint(12, 8);
  QAction *ACT_x = PopupM.exec(PM_Point);

  if (ACT_x == nullptr) {
    return;
  }

  if (ACT_x == actionCopyPath) {
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(PathName);
  }

  if (ACT_x == actionRename) {
    bool ok;
    QString newName = QInputDialog::getText(this, "Renommer", "Nouveau nom :", QLineEdit::Normal, FI_Path.fileName(), &ok);
    if (ok && !newName.isEmpty() && newName != FI_Path.fileName()) {
      QString newPath = FI_Path.dir().absoluteFilePath(newName);
      if (QFile::rename(PathName, newPath)) {
        p_Item->setText(K_FN, newName);
        p_Item->setText(K_PN, newPath);
      } else {
        QMessageBox::warning(this, "Erreur", "Impossible de renommer le fichier.");
      }
    }
  }

  if (ACT_x == actionDelete) {
    if (QMessageBox::question(this, "Supprimer", "Voulez-vous vraiment supprimer ce fichier ?") == QMessageBox::Yes) {
      if (QFile::remove(PathName)) {
        delete p_Item;
      } else {
        QMessageBox::warning(this, "Erreur", "Suppression impossible.");
      }
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


//
// <<<< TreeMainWindow::slot_Aide
//
void TreeMainWindow::slot_Aide()
{
  QMessageBox::information(this, "Aide", 
    "Bienvenue dans l'application !\n\n"
    "• F1 ou menu Fichier > Aide : afficher cette aide\n"
    "• ALT+S : choisir le dossier racine\n"
    "• ALT+Q : quitter\n"
    "• Cliquez sur un fichier ou dossier pour voir ses informations\n"
    "• La colonne 'Date modif.' affiche la date de dernière modification\n"
  );
}
// >>>> TreeMainWindow::slot_Aide

