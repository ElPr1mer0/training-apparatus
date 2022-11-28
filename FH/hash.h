#ifndef HASH_H
#define HASH_H

#include <QString>

class HASH{
public:
    QString GetHash(QString);

private:
    int ReceivingExistCodes(int);
    int GetControlSum(QString);
    const int hashSize = 100;
};

#endif // HASH_H
