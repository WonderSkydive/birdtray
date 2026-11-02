// Modified in the community Resolute/X11 edition (2026); see CHANGELOG.md.
#ifndef UNREAD_MONITOR_H
#define UNREAD_MONITOR_H

#include <QThread>
#include <QString>
#include <QColor>
#include <QMap>
#include <QTimer>
#include <QStringList>
#include <QFileSystemWatcher>

class TrayIcon;
class Settings;

class UnreadMonitor : public QThread
{
    Q_OBJECT

    public:
        UnreadMonitor( TrayIcon * parent, Settings * settings = nullptr );

        // Thread run function
        virtual void run() override;
    
        /**
         * Get the current warnings for the watched paths.
         * The null-string key can contain a warning for all paths.
         *
         * @return A path to warnings mapping.
         */
        const QMap<QString, QString> &getWarnings() const;

    signals:
        // Unread counter changed
        void    unreadUpdated( unsigned int total, QColor color );

        /**
         * A warning was added or removed for the given watched path.
         *
         * @param path The watched path or null-string for a global warning.
         */
        void warningChanged(const QString &path);

    public slots:
        void    slotSettingsChanged();
        void    watchedFileChanges( const QString& filechanged );
        void    updateUnread();

        // This one forces rereading Mork files
        void    forceUpdateUnread();

    private:
        void    getUnreadCount_Mork( int & count, QColor& color );
        int     getMorkUnreadCount( const QString& path );
    
        /**
         * Set a warning for a given path or for all paths, if no path is given.
         * Overwrites any previous warning.
         *
         * @param message The warning message.
         * @param path The watched path.
         */
        void setWarning(const QString &message, const QString &path = QString());
        
        /**
         * Reset the warning if there was one for the given watched path.
         * Or reset the global warning for all paths, if no path is given.
         *
         * @param path The path to the watched mork file.
         */
        void clearWarning(const QString &path = QString());

    private:
        Settings *mSettings;

        // Maps the Mork files to unread counts
        QMap< QString, quint32 >  mMorkUnreadCounts;

        // Watches the files for changes
        QFileSystemWatcher  mDBWatcher;

        // Thunderbird tends to do lots of modifications to the MSF file
        // each time a new email arrives. Batch those changes into a bounded
        // interval without restarting the timer on every notification.
        QTimer              mChangedMSFtimer;

        // List of changed files (for MSF monitoring)
        QList<QString>      mChangedMSFfiles;

        // Periodic recovery scan; user interval or a 30-second fallback.
        QTimer              mForceUpdateTimer;

        // Last reported unread
        int    mLastReportedUnread;
        QColor mLastColor;
    
        /**
         * This contains mappings from watched paths to warning messages for that path.
         * If there is a warning in the null-string key, it applies to all paths.
         */
        QMap<QString, QString> warnings;
};

#endif /* UNREAD_MONITOR_H */
