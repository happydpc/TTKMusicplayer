#ifndef MUSICDOWNLOADWIDGET_H
#define MUSICDOWNLOADWIDGET_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (C) 2015 - 2017 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ================================================= */

#include "musicabstractmovewidget.h"
#include "musicabstracttablewidget.h"
#include "musicdownloadquerythreadabstract.h"

#define ROW_HEIGHT  25

namespace Ui {
class MusicDownloadWidget;
}
class QLabel;

/*! @brief The class of the download table item.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_WIDGET_EXPORT MusicDownloadTableItem : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit MusicDownloadTableItem(QWidget *parent = 0);

    ~MusicDownloadTableItem();

    /*!
     * Get class object name.
     */
    static QString getClassName();
    /*!
     * Set current item icon.
     */
    void setIcon(const QString &name);
    /*!
     * Set current item other infomation(size\type\time).
     */
    void setInformation(const QString &info);
    /*!
     * Set current item text name.
     */
    void setText(const QString &text);

protected:
    QLabel *m_text, *m_information, *m_icon;

};

#define BITRATE_ROLE Qt::UserRole + 1

/*! @brief The class of the download table widget.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_WIDGET_EXPORT MusicDownloadTableWidget : public MusicAbstractTableWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit MusicDownloadTableWidget(QWidget *parent = 0);

    virtual ~MusicDownloadTableWidget();

    /*!
     * Get class object name.
     */
    static QString getClassName();
    /*!
     * Clear All Items.
     */
    void clearAllItems();
    /*!
     * Create current itrm by given bitrate\type\icon\otherinfo.
     */
    void createItem(int bitrate, const QString &type, const QString &info,
                    const QString &icon);
    /*!
     * Get current bitrate from item.
     */
    int getCurrentBitrate();

public Q_SLOTS:
    /*!
     * Table widget list cell click.
     */
    virtual void listCellClicked(int row, int column) override;

protected:
    QList<QObject*> m_items;

};

/*! @brief The class of the download widget.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_WIDGET_EXPORT MusicDownloadWidget : public MusicAbstractMoveWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit MusicDownloadWidget(QWidget *parent = 0);

    virtual ~MusicDownloadWidget();

    /*!
     * Get class object name.
     */
    static QString getClassName();
    /*!
     * Set current name to search and download musics.
     */
    void setSongName(const QString &name, MusicDownLoadQueryThreadAbstract::QueryType type);
    /*!
     * Set current name to search and download musics.
     */
    void setSongName(const MusicObject::MusicSongInformation &info,
                     MusicDownLoadQueryThreadAbstract::QueryType type);

Q_SIGNALS:
    /*!
     * Data download changed.
     */
    void dataDownloadChanged();

public Q_SLOTS:
    /*!
     * Override show function.
     */
    void show();
    /*!
     * Query all quality musics is finished.
     */
    void queryAllFinished();
    /*!
     * Change data download save path.
     */
    void downloadDirSelected();
    /*!
     * Start to download music data.
     */
    void startToDownload();
    /*!
     * Data download is finished.
     */
    void dataDownloadFinished();

protected:
    /*!
     * Create all widget in layout.
     */
    void initWidget();
    /*!
     * Enable or disable control state.
     */
    void controlEnable(bool enable);
    /*!
     * Automatically adjust the height according to searched items.
     */
    void resizeWindow();
    /*!
     * Set widget fixed height.
     */
    void setFixedHeightWidget(QWidget *w, int height);
    /*!
     * Set widget moved into given pos.
     */
    void setMoveWidget(QWidget *w, int pos);

    /*!
     * Get match music song infomation.
     */
    MusicObject::MusicSongInformation getMatchMusicSongInformation();
    /*!
     * Query all quality that musics is finished.
     */
    void queryAllFinishedMusic();
    /*!
     * Query all quality that musics is finished.
     */
    void queryAllFinishedMusic(const MusicObject::MusicSongAttributes &attrs);
    /*!
     * Query all quality that movies is finished.
     */
    void queryAllFinishedMovie();
    /*!
     * Query all quality that movies is finished.
     */
    void queryAllFinishedMovie(const MusicObject::MusicSongAttributes &attrs);
    /*!
     * Strat to download music.
     */
    void startToDownloadMusic();
    /*!
     * Strat to download music.
     */
    void startToDownloadMusic(const MusicObject::MusicSongInformation &musicSongInfo);
    /*!
     * Strat to download movie.
     */
    void startToDownloadMovie();
    /*!
     * Strat to download movie.
     */
    void startToDownloadMovie(const MusicObject::MusicSongInformation &musicSongInfo);

    Ui::MusicDownloadWidget *m_ui;
    bool m_querySingleInfo;
    MusicDownLoadQueryThreadAbstract *m_downloadThread;
    MusicDownLoadQueryThreadAbstract::QueryType m_queryType;
    MusicObject::MusicSongInformation m_singleSongInfo;

};

#endif // MUSICDOWNLOADWIDGET_H
