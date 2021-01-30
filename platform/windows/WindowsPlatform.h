#ifndef WindowsPlatform_h
#define WindowsPlatform_h

#include "main/core/Platform.h"

namespace Papaya
{

    class WindowsPlatform : public Platform
    {
    public:
        WindowsPlatform();
        virtual ~WindowsPlatform();

        void Init();
        void Update();
        void Terminate();
    };

} // namespace Papaya


#endif /* end of include guard: WindowsPlatform_h */