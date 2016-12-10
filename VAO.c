VAO:: VAO(void)
{
    glGenVertexArrays(1, &vertexArrayObject);
}

VAO::~VAO(void)
{
    glDeleteVertexArrays(1, &vertexArrayObject);
}

void VAO::attributePointer(GLint attributeLocation, GLint size)
{
    glEnableVertexAttribArray(attributeLocation); glVertexAttribPointer(attributeLocation, size, GL_FLOAT, GL_FALSE, 0, NULL);
}

void VAO::attributePointer(GLint attributeLocation, GLint size, const GLvoid *pointer)
{
    glEnableVertexAttribArray(attributeLocation); glVertexAttribPointer(attributeLocation, size, GL_FLOAT, GL_FALSE, 0, pointer);
}

void VAO::attributePointer(GLint attributeLocation, GLint size, GLsizei stride, const GLvoid *pointer)
{
    glEnableVertexAttribArray(attributeLocation); glVertexAttribPointer(attributeLocation, size, GL_FLOAT, GL_FALSE, stride, pointer);
}
