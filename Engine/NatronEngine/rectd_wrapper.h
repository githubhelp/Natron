#ifndef SBK_RECTDWRAPPER_H
#define SBK_RECTDWRAPPER_H

#include <shiboken.h>

#include <RectD.h>

class RectDWrapper : public RectD
{
public:
    RectDWrapper();
    RectDWrapper(const RectD& self) : RectD(self)
    {
    }

    RectDWrapper(double l, double b, double r, double t);
    virtual ~RectDWrapper();
    static void pysideInitQtMetaTypes();
};

#endif // SBK_RECTDWRAPPER_H

