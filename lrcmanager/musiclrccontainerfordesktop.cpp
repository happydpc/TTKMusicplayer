#include "musiclrccontainerfordesktop.h"
#include "musiclrcmanagerfordesktop.h"
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QToolButton>
#include <QPushButton>
#include <QSettings>

MusicLrcContainerForDesktop::MusicLrcContainerForDesktop(QWidget *parent)
        : MusicLrcContainer(0), m_parentClass(parent)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint |
                         Qt::WindowStaysOnTopHint );
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    m_containerType = "DESKTOP";
    creatToolBarWidget();
    m_desktopWidget = new QWidget(this);
    m_desktopWidget->setObjectName("desktopWidget");
    m_musicLrcContainer << new MusicLRCManagerForDesktop(m_desktopWidget)
                        << new MusicLRCManagerForDesktop(m_desktopWidget);
    layout->addWidget(m_desktopWidget);
    layout->addWidget(m_toolBarWidget);
    this->setLayout(layout);

    //Move the QWidget in the appropriate location
    QDesktopWidget* desktop = QApplication::desktop();
    QRect deskRect = desktop->availableGeometry();
    move( 200, deskRect.height() - this->height() - 150);

    m_geometry.setX(deskRect.width()-300);
    m_geometry.setY(80);
    m_desktopWidget->setMaximumSize(m_geometry.x(), 2*m_geometry.y());
    m_desktopWidget->setMinimumSize(m_geometry.x(), 2*m_geometry.y());
    setSelfGeometry();

    m_reverse = false;
    m_windowLocked = false;

    m_currentLrcFontSize = static_cast<MusicLRCManagerForDesktop*>(m_musicLrcContainer[0])->getFirstFontSize();
}

MusicLrcContainerForDesktop::~MusicLrcContainerForDesktop()
{
    clearAllMusicLRCManager();
    delete m_showMainWindow;
    delete m_toolPreSongButton;
    delete m_toolNextSongButton;
    delete m_toolPlayButton;
    delete m_toolCloseButton;
    delete m_toolSettingButton;
    delete m_toolWindowLockedButton;
    delete m_toolLrcBigerButton;
    delete m_toolLrcSmallerButton;
    delete m_toolUpdateLrcButton;
    delete m_toolBarWidget;
    delete m_desktopWidget;
}

void MusicLrcContainerForDesktop::creatToolBarWidget()
{
    m_toolBarWidget = new QWidget(this);
    m_toolBarWidget->setStyleSheet("background-color:rgba(0,0,0,155)");
//    m_toolBarWidget->setFixedHeight(30);
    m_toolBarWidget->setFixedWidth(320);
    m_toolBarWidget->setGeometry(0,-10,320,20);

    m_showMainWindow = new QPushButton(m_toolBarWidget);

    m_toolCloseButton = new QToolButton(m_toolBarWidget);
    m_toolCloseButton->setGeometry(290,0,30,30);
    connect(m_toolCloseButton,SIGNAL(clicked()),SLOT(close()));

    m_toolWindowLockedButton = new QToolButton(m_toolBarWidget);
    m_toolWindowLockedButton->setGeometry(260,0,30,30);
    connect(m_toolWindowLockedButton,SIGNAL(clicked()),SLOT(setWindowLockedChanged()));

    m_toolLrcBigerButton = new QToolButton(m_toolBarWidget);
    m_toolLrcBigerButton->setGeometry(200,0,30,30);
    connect(m_toolLrcBigerButton,SIGNAL(clicked()),SLOT(setLrcBigerChanged()));

    m_toolLrcSmallerButton = new QToolButton(m_toolBarWidget);
    m_toolLrcSmallerButton->setGeometry(230,0,30,30);
    connect(m_toolLrcSmallerButton,SIGNAL(clicked()),SLOT(setLrcSmallerChanged()));

    m_toolUpdateLrcButton = new QToolButton(m_toolBarWidget);
    m_toolUpdateLrcButton->setGeometry(170,0,30,30);
    connect(m_toolUpdateLrcButton,SIGNAL(clicked()), SIGNAL(theCurrentLrcUpdated()));

    m_toolSettingButton = new QToolButton(m_toolBarWidget);
    m_toolSettingButton->setGeometry(140,0,30,30);
    connect(m_toolSettingButton,SIGNAL(clicked()),SLOT(currentLrcCustom()));

    m_toolPreSongButton = new QToolButton(m_toolBarWidget);
    m_toolPreSongButton->setGeometry(50,0,30,30);
    m_toolNextSongButton = new QToolButton(m_toolBarWidget);
    m_toolNextSongButton->setGeometry(110,0,30,30);
    m_toolPlayButton = new QToolButton(m_toolBarWidget);
    m_toolPlayButton->setGeometry(80,0,30,30);
    connect(m_toolPreSongButton,SIGNAL(clicked()), m_parentClass, SLOT(musicPlayPrivious()));
    connect(m_toolNextSongButton,SIGNAL(clicked()), m_parentClass, SLOT(musicPlayNext()));
    connect(m_toolPlayButton,SIGNAL(clicked()), m_parentClass, SLOT(musicKey()));
    connect(m_showMainWindow,SIGNAL(clicked()), m_parentClass, SLOT(showNormal()));

    setButtonIcon();
    setButtonCursor();
    setButtonTips();
    m_toolBarWidget->hide();
}

void MusicLrcContainerForDesktop::setButtonIcon()
{
    m_toolCloseButton->setIcon(QIcon(QPixmap(":/image/close").scaled(30,30)));
    m_toolWindowLockedButton->setIcon(QIcon(QPixmap(":/desktopTool/lockWindow").scaled(30,30)));
    m_toolLrcBigerButton->setIcon(QIcon(QPixmap(":/desktopTool/lrcsizeUp").scaled(30,30)));
    m_toolLrcSmallerButton->setIcon(QIcon(QPixmap(":/desktopTool/lrcsizeDown").scaled(30,30)));
    m_toolUpdateLrcButton->setIcon(QIcon(QPixmap(":/desktopTool/updateLrc").scaled(30,30)));
    m_toolPreSongButton->setIcon(QIcon(QPixmap(":/desktopTool/previous")));
    m_toolNextSongButton->setIcon(QIcon(QPixmap(":/desktopTool/next")));
    m_toolPlayButton->setIcon(QIcon(QPixmap(":/desktopTool/play")));
    m_toolSettingButton->setIcon(QIcon(QPixmap(":/desktopTool/setting")));
    m_showMainWindow->setIcon(QIcon(QPixmap(":/image/windowicon")));
}

void MusicLrcContainerForDesktop::setButtonCursor()
{
    m_toolCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_toolWindowLockedButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_toolLrcBigerButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_toolLrcSmallerButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_toolUpdateLrcButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_toolPreSongButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_toolNextSongButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_toolPlayButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_toolSettingButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_showMainWindow->setCursor(QCursor(Qt::PointingHandCursor));

    m_showMainWindow->setStyleSheet("QPushButton{background:transparent;border-none;}\
                                     QPushButton::hover{image:url(:/image/shadow);}");
    m_toolCloseButton->setStyleSheet(MusicObject::QToolButtonStyleDesktopTool);
    m_toolWindowLockedButton->setStyleSheet(MusicObject::QToolButtonStyleDesktopTool);
    m_toolLrcSmallerButton->setStyleSheet(MusicObject::QToolButtonStyleDesktopTool);
    m_toolUpdateLrcButton->setStyleSheet(MusicObject::QToolButtonStyleDesktopTool);
    m_toolLrcBigerButton->setStyleSheet(MusicObject::QToolButtonStyleDesktopTool);
    m_toolPreSongButton->setStyleSheet(MusicObject::QToolButtonStyleDesktopTool);
    m_toolNextSongButton->setStyleSheet(MusicObject::QToolButtonStyleDesktopTool);
    m_toolPlayButton->setStyleSheet(MusicObject::QToolButtonStyleDesktopTool);
    m_toolSettingButton->setStyleSheet(MusicObject::QToolButtonStyleDesktopTool);
}

void MusicLrcContainerForDesktop::setButtonTips()
{
    m_toolCloseButton->setToolTip(tr("hide"));
    m_toolWindowLockedButton->setToolTip(tr("lockLrc"));
    m_toolLrcBigerButton->setToolTip(tr("lrcBiger"));
    m_toolLrcSmallerButton->setToolTip(tr("lrcSmaller"));
    m_toolUpdateLrcButton->setToolTip(tr("updateLrc"));
    m_toolPreSongButton->setToolTip(tr("Privious"));
    m_toolNextSongButton->setToolTip(tr("Next"));
    m_toolPlayButton->setToolTip(tr("Play"));
    m_toolSettingButton->setToolTip(tr("Setting"));
    m_showMainWindow->setToolTip(tr("showMainWindow"));
}

void MusicLrcContainerForDesktop::startTimerClock()
{
    m_musicLrcContainer[!m_reverse]->startTimerClock();
}

void MusicLrcContainerForDesktop::initCurrentLrc()
{
    m_musicLrcContainer[0]->setText(tr("unFoundLrc"));
    m_musicLrcContainer[0]->setGeometry(0, 20,
                                        static_cast<MusicLRCManagerForDesktop*>(m_musicLrcContainer[0])->getGeometryX(),
                                        m_geometry.y());
    m_musicLrcContainer[1]->setGeometry(0, m_geometry.y() + 20,0,0);
}

void MusicLrcContainerForDesktop::updateCurrentLrc(const QString& first,
                                                   const QString& second, qint64 time)
{
    m_reverse = !m_reverse;
    static_cast<MusicLRCManagerForDesktop*>(m_musicLrcContainer[ m_reverse])->resetOrigin();
    m_musicLrcContainer[ m_reverse]->stopLrcMask();
    m_musicLrcContainer[ m_reverse]->setText(second);
    m_musicLrcContainer[!m_reverse]->setText(first);
    m_musicLrcContainer[!m_reverse]->startLrcMask(time);
    m_musicLrcContainer[0]->setGeometry(0, 20,
                                        static_cast<MusicLRCManagerForDesktop*>(m_musicLrcContainer[0])->getGeometryX(),
                                        m_geometry.y());
    int pos = m_geometry.x() - static_cast<MusicLRCManagerForDesktop*>(m_musicLrcContainer[1])->getGeometryX();
    if(pos < 0 ) pos = 0;
    m_musicLrcContainer[1]->setGeometry(pos, m_geometry.y() + 20,
                                        static_cast<MusicLRCManagerForDesktop*>(m_musicLrcContainer[1])->getGeometryX(),
                                        m_geometry.y());
}

void MusicLrcContainerForDesktop::stopLrcMask()
{
    for(int i=0; i<m_musicLrcContainer.count(); ++i)
        m_musicLrcContainer[i]->stopLrcMask();
}

void MusicLrcContainerForDesktop::setMaskLinearGradientColor(QColor color)
{
    for(int i=0; i<m_musicLrcContainer.count(); ++i)
        m_musicLrcContainer[i]->setMaskLinearGradientColor(color);
}

void MusicLrcContainerForDesktop::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    if(!m_windowLocked && event->button() == Qt::LeftButton )
        m_offset = event->globalPos() - frameGeometry().topLeft();
}

void MusicLrcContainerForDesktop::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    if(!m_windowLocked && (event->buttons() & Qt::LeftButton) )
    {
       setCursor(Qt::CrossCursor);
       move(event->globalPos() - m_offset);
       QSettings().setValue("DLRCGEOMETRYCHOICED",QWidget::geometry());
    }
}

void MusicLrcContainerForDesktop::enterEvent(QEvent *event)
{
    if(m_windowLocked) return;
    QWidget::enterEvent(event);
    m_toolBarWidget->show();
    setStyleSheet("#desktopWidget{border: 1px solid #555555;background-color:rgba(0,0,0,40)}");
}

void MusicLrcContainerForDesktop::leaveEvent(QEvent *event)
{
    if(m_windowLocked) return;
    QWidget::leaveEvent(event);
    m_toolBarWidget->hide();
    setStyleSheet("background-color:transparent");
}

void MusicLrcContainerForDesktop::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
    emit desktopLrcClosed();
}

void MusicLrcContainerForDesktop::setWindowLockedChanged()
{
    m_windowLocked = !m_windowLocked;
    if(m_windowLocked)
    {
       m_toolBarWidget->hide();
       setStyleSheet("background-color:transparent");
    }
    emit setWindowLockedChanged(m_windowLocked);
    QSettings().setValue("DLRCLOCKEDCHOICED",m_windowLocked ? 1 : 0);
}

void MusicLrcContainerForDesktop::setSelfGeometry()
{
    for(int i=0; i<m_musicLrcContainer.count(); ++i)
        static_cast<MusicLRCManagerForDesktop*>(m_musicLrcContainer[i])->setSelfGeometry(m_geometry.x(), m_geometry.y());
}

void MusicLrcContainerForDesktop::setLrcBigerChanged()
{
    if(m_currentLrcFontSize > 35) return;
    int y = m_geometry.y();
    m_geometry.setY(++y);
    setSelfGeometry();
    for(int i=0; i<m_musicLrcContainer.count(); ++i)
        static_cast<MusicLRCManagerForDesktop*>(m_musicLrcContainer[i])->setLrcFontSize(++m_currentLrcFontSize);
    QSettings().setValue("DLRCSIZECHOICED",m_currentLrcFontSize);
}

void MusicLrcContainerForDesktop::setLrcSmallerChanged()
{
    if(m_currentLrcFontSize < 25) return;
    int y = m_geometry.y();
    m_geometry.setY(--y);
    setSelfGeometry();
    for(int i=0; i<m_musicLrcContainer.count(); ++i)
        static_cast<MusicLRCManagerForDesktop*>(m_musicLrcContainer[i])->setLrcFontSize(--m_currentLrcFontSize);
    QSettings().setValue("DLRCSIZECHOICED",m_currentLrcFontSize);
}

void MusicLrcContainerForDesktop::contextMenuEvent(QContextMenuEvent *event)
{
    QWidget::contextMenuEvent(event);
    QMenu menu(this);
    QMenu changColorMenu(tr("changColorMenu"),this);
    changColorMenu.setStyleSheet(MusicObject::MusicSystemTrayMenu);
    menu.setStyleSheet(MusicObject::MusicSystemTrayMenu);
    menu.addAction(tr("searchLrcs"), this, SLOT(searchMusicLrcs()));
    menu.addAction(tr("hide"), this, SLOT(close()));
    menu.addAction(QIcon(QPixmap(":/contextMenu/lock")),tr("lockLrc"),this,SLOT(setWindowLockedChanged()));
    menu.addAction(tr("updateLrc"), this, SIGNAL(theCurrentLrcUpdated()));
    menu.addMenu(&changColorMenu);

    createColorMenu(changColorMenu);
    menu.addAction(tr("customSetting"),this,SLOT(currentLrcCustom()));

    menu.exec(QCursor::pos());
}

void MusicLrcContainerForDesktop::setSettingParameter()
{
    MusicLrcContainer::setSettingParameter();
    QSettings para;
    for(int i=0; i<m_musicLrcContainer.count(); ++i)
    {
        m_musicLrcContainer[i]->setLrcFontSize((LrcSizeTable)(
                                                m_currentLrcFontSize = para.value("DLRCSIZECHOICED").toInt()));
    }
    para.value("DLRCLOCKEDCHOICED").toInt() == 1 ? m_windowLocked = true : m_windowLocked = false;
    QRect rect = para.value("DLRCGEOMETRYCHOICED").toRect();
    if(!rect.isEmpty())
        setGeometry(rect);
}

void MusicLrcContainerForDesktop::showPlayStatus(bool status)
{
    m_toolPlayButton->setIcon(!status ? QIcon(QPixmap(QString::fromUtf8(":/desktopTool/stop")))
                                      : QIcon(QPixmap(QString::fromUtf8(":/desktopTool/play"))) );
}