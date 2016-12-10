OpenAL:: OpenAL(void)
{
    device = alcOpenDevice(NULL);

    if(!device)
    {
        puts("Error: Failed to open Audio device.");
        throw std::exception();
    }

    context = alcCreateContext(device, NULL);

    if(!context)
    {
        puts("Error: Failed to create OpenAL Context.");

        alcCloseDevice(device);
        throw std::exception();
    }

    alcMakeContextCurrent(context);
}

OpenAL::~OpenAL(void)
{
    alcMakeContextCurrent(NULL);
        alcDestroyContext(context);
    
    alcCloseDevice(device);
}

