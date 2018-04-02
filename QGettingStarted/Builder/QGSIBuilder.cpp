#include "QGSIBuilder.h"
#include "../Util/QGSExceptionInvalidValue.h"
#include "../Util/QGSExceptionIO.h"

static const int DEFAULT_MAX_CONNECTION_COUNT = 8;

QGSIBuilder::QGSIBuilder(QObject * parent)
	:QGSTask(parent)
{

}

QGSIBuilder::~QGSIBuilder()
{

}
