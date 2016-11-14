#ifndef OpenAL_H
#	define OpenAL_H

class OpenAL
{
	ALCdevice *device; ALCcontext *context;

	public:
		OpenAL(void);
	   ~OpenAL(void);

		//...
};

//...

#	include "OpenAL.c"
#endif
