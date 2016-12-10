#ifndef VAO_H
#	 define VAO_H

#    define BUFFER_OFFSET(I) ((char *) NULL + (I)) 

class VAO
{
    GLuint vertexArrayObject;

    public:
        VAO(void);
       ~VAO(void);

        void bind(void)
        {
            glBindVertexArray(vertexArrayObject);
        }

        void attributePointer(GLint attributeLocation, GLint size);
        void attributePointer(GLint attributeLocation, GLint size, const GLvoid *pointer);
        void attributePointer(GLint attributeLocation, GLint size, GLsizei stride, const GLvoid *pointer);
};

#    include "VAO.c"
#endif
