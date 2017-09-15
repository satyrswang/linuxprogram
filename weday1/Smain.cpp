#include "classtable.h"
#include <QApplication>
#include<QTextCodec>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Classtable w;
    w.show();

    return a.exec();
}

