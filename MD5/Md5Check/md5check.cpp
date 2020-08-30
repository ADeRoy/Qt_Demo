#include "md5check.h"



Md5Check::Md5Check(QObject *parent) : QObject(parent)
{

}

void Md5Check::getMd5CheckSumSlot(const QString &filePath)
{
    QFile file(filePath);
    QByteArray md5Result;
    QFileInfo md5FileInfo;
    md5FileInfo = QFileInfo(filePath);  /*获取文件信息，考虑到文件过大*/

    int totalSize = md5FileInfo.size()/(1024*1024); /*   把Byte字节转换成M兆    */
    if(md5FileInfo.size()%(1024*1024)>0)
        totalSize+=1;                               /*   多余补一    */
    int currentSize = 0;                /*当前进度，读取的M兆数*/

    if(file.open(QIODevice::ReadOnly))
    {
        QCryptographicHash hash(QCryptographicHash::Md5);
        while (!file.atEnd()) {         //读取文件直到读物完整
            QByteArray content = file.read(1024*1024);  /*每次读取一兆M*/
            hash.addData(content);      /*分段进程MD5累加*/
            currentSize++;              /*当前进度，进度加一*/
            emit sendProgressBarSignal(totalSize,currentSize);  /*传送百分比信号*/
        }
        md5Result = hash.result().toHex();      /*MD5值为32位的十六进制数*/
        emit sendMd5CheckSumSignal(md5Result);  /*发送MD5结果*/
        file.close();
    }
}
