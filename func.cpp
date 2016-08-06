void contentDifference(QDir &sDir, QDir &dDir, QFileInfoList &diffList, int dirNum);							finished
void on_syncBtn_clicked();																						
void recursiveContentList(QDir &dir, QFileInfoList &contentList, int dirNum);									finished
bool extToCopy(QFileInfo info, QStringList arr);																finished
void setExtArray(QLineEdit *inputline, QStringList *arr);														finished
bool check(QFileInfo info, int folder);																			finished
int countSize(QLineEdit* inputLine, QButtonGroup* buttons);														finished
void another