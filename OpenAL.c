OpenAL:: OpenAL(void)
{
  	device = alcOpenDevice(NULL);

	if(!device)
	{
		printf("Error: Failed to open Audio device \n");
		throw std::exception();
	}

	context = alcCreateContext(device, NULL);

	if(!context)
	{
		printf("Error: Failed to create OpenAL Context \n");

		alcCloseDevice(device);
		throw std::exception();
	}

	alcMakeContextCurrent(context);
}

OpenAL::~OpenAL(void)
{
	alcMakeContextCurrent(NULL); alcDestroyContext(context);
	alcCloseDevice(device);
}

//...
