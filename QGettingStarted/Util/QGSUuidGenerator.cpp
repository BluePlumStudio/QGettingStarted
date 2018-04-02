#include "QGSUuidGenerator.h"

QGSUuidGenerator::QGSUuidGenerator(QObject * parent) :QObject(parent)
{
}

QGSUuidGenerator::~QGSUuidGenerator()
{
}

QGSUuidGenerator & QGSUuidGenerator::getInstance()
{
	static QGSUuidGenerator instance;
	return instance;
}

QString QGSUuidGenerator::generateUuid(const QString & seed)
{
	QString UUID;
    char code[] = "x@&asd%j2813";
	char UUIDChars[] = "bad260ecde3bfe752a";
	int i = 0;

	if (seed.isEmpty())
	{
		return UUID;
	}

	while (UUID.length() < 32)
	{
		char c1 = 0;
		char c2 = 0;
		char c = 0;

		srand(seed[(i + code[i % strlen(code)]) % seed.length()].toLatin1() + i);
		c1 = 'a' + rand() % 6;
		c2 = '0' + rand() % 10;
		c = rand() % 32;
		if (c>16)
		{
			if (rand() % 2)
			{
				UUID.push_back(c1);
			}
			else
			{
				UUID.push_back(c2);
			}
		}
		else
		{
			UUID.push_back(UUIDChars[c]);
		}


		i = (i + 1) % 65536;
	}

	return UUID;
}

QString QGSUuidGenerator::generateUuid()
{
	return QUuid::createUuid().toString();
}

