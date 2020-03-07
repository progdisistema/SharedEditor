#include "remotecursor.h"
#include <QTextDocument>
#include <QDebug>
#include <QTextBlock>

RemoteCursor::RemoteCursor(QTextCursor cursor, QTextBlock initial_block, int initial_index, const QString& color)
{
    this->cursorHtml = "<span style='background-color:" + color + ";display:block'>&nbsp;</span>";

    this->remoteCursor = cursor;
    this->remoteCursor.setPosition(initial_block.position() + initial_index);
    this->remoteCursor.insertHtml(cursorHtml);
}

RemoteCursor::RemoteCursor() {} // necessary to use QMap

RemoteCursor::~RemoteCursor() {
}

void RemoteCursor::moveTo(QTextBlock block, int index) {
    qDebug() << "remote cursor" << index;
    int oldPosition = remoteCursor.position();
    // set position before remote cursor and delete it
    qDebug() << "deleting at" << oldPosition - 1;
    this->remoteCursor.setPosition(oldPosition - 1);
    this->remoteCursor.deleteChar();

    // put in new position
    this->remoteCursor.setPosition(block.position() + index);
    this->remoteCursor.insertHtml(cursorHtml);
    qDebug() << "new position" << this->remoteCursor.position();
}

int RemoteCursor::getPosition()
{
    return remoteCursor.position();
}
