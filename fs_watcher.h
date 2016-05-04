#ifndef FS_WATCHER_H
#define FS_WATCHER_H



class fsWatcher: public QObject {
private:
    QFileSystemWatcher *watcher;
public:
    fsWatcher(QWidget *parent = 0);
    ~fsWatcher();
};

#endif // FS_WATCHER_H
