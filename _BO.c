_BO:: _BO(void)
{
    glGenBuffers(1, &bufferObject);
}

_BO::~_BO(void)
{
    glDeleteBuffers(1, &bufferObject);
}

//...
